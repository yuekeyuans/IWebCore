#include "INodyParser.h"
#include <limits>
#include <functional>
#include <mutex>
#include <QDebug>
#include <QFile>

namespace IWebCore{

QMap<QString, INodyParser::Fun> INodyParser::s_map;
QStringList INodyParser::s_keys;
INodyParser::INodyParser()
{
    static std::once_flag flag;
    std::call_once(flag, [&](){
        s_map = {
            {"$if ", &INodyParser::parseIf},
            {"$for ", &INodyParser::parseFor},
            {"${{", &INodyParser::parseVar},
            {"#{{", &INodyParser::parseComment},
            {"$block ", &INodyParser::parseBlock},
            {"$include", &INodyParser::parseInclude},
            {"$with ", &INodyParser::parseWith}
        };

        s_keys = s_map.keys();
    });
}

INody * INodyParser::parseContent(QString content)
{
    INody* node{};
    try{
        if(content.trimmed().startsWith("$extend")){
            eatVariable(content, "$extend", "$extend has no prefix");
            std::tie(node, content) = parseExtend(content);
        }else{
            std::tie(node, content) = parseMixed(content);
        }
    }catch(INodyException e){
        qDebug().noquote() << e.getTraces();
        qFatal(e.getTraces().toUtf8());
    }

    if(!content.isEmpty()){
        qFatal("parse incomplete");
    }

    return node;
}

INody *INodyParser::parseFile(QString path)
{
    QFile file(path);
    if(!file.exists()){
        return nullptr;
    }
    file.open(QFile::ReadOnly | QFile::Text);
    auto content = file.readAll();
    file.close();

    return parseContent(content);
}

std::pair<INody*, QString> INodyParser::parseMixed(QString content)
{
    QList<INody*> nodes;
    INody* node{};

    while(!content.isEmpty() && !content.startsWith("}}")){
        content = content.trimmed();
        for(const QString& key : s_keys){
            if(content.startsWith(key)){
                try{
                    content = content.mid(key.length()).trimmed();
                    std::tie(node, content) = std::mem_fn(s_map[key])(this, content);
                    if(node){
                        nodes.append(node);
                    }
                    break;
                }catch(INodyException e){
                    e.addTrace("parse " + key + " error.", content);
                    throw e;
                }
            }
        }

        std::tie(node, content) = parseHtml(content);
        if(node){
            nodes.append(node);
        }
    }

    if(nodes.isEmpty()){
        return {nullptr, content};
    }
    if(nodes.length() == 1){
        return {nodes.first(), content};
    }

    auto unionNode = new IUnionNody;
    unionNode->m_children = nodes;
    return {unionNode, content};
}

std::pair<INody *, QString> INodyParser::parseHtml(QString content)
{
    QStringList tags = s_keys;
    tags.append("}}");

    int index = std::numeric_limits<int>::max();
    for(auto tag : tags){
        auto pos = content.indexOf(tag);
        if(pos != -1){
            index = index < pos ? index : pos;
        }
    }

    auto node = new IHtmlNody;
    node->m_html = content.mid(0, index);
    return {node, content.mid(index)};
}

std::pair<INody *, QString> INodyParser::parseIf(QString content)
{
    auto ifNode = new IfNody;
    std::tie(ifNode->m_path, content) = readVariable(content, "$if statement can not read condition");
    eatVariable(content, "{{", "$if has no {{");

    std::tie(ifNode->m_elder, content) = parseMixed(content);
    eatVariable(content, "}}", "$if has no }}");

    if(content.startsWith("$elif ")){
        try{
            content = content.mid(QString("$elif ").length()).trimmed();
            std::tie(ifNode->m_younger, content) = parseElif(content);
        }catch(INodyException e){
            e.addTrace("parse $elif error", content);
            throw e;
        }
    }else if(content.startsWith("$else")){
        try{
            content = content.mid(QString("$else").length()).trimmed();
            std::tie(ifNode->m_younger, content) = parseElse(content);
        }catch(INodyException e){
            e.addTrace("parse else error", content);
        }
    }

    return {ifNode, content};
}

std::pair<INody *, QString> INodyParser::parseElif(QString content)
{
    auto ifNode = new IfNody;
    std::tie(ifNode->m_path, content) = readVariable(content, "$elif statement can not read condition");
    eatVariable(content, "{{", "$elif has no {{");
    std::tie(ifNode->m_elder, content) = parseMixed(content);
    eatVariable(content, "}}", "$elif has no }}");

    if(content.startsWith("$elif ")){
        std::tie(ifNode->m_younger, content) = parseElif(content.mid(QString("$elif ").length()));
    }else if(content.startsWith("$else")){
        std::tie(ifNode->m_younger, content) = parseElse(content.mid(QString("$else").length()));
    }

    return {ifNode, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseElse(QString content)
{
    INody* node{};
    eatVariable(content, "{{", "$else has no {{");
    std::tie(node, content) = parseMixed(content);
    eatVariable(content, "}}", "$else has no }}");
    return {node, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseFor(QString content)
{
    auto forNode = new IForNody();
    std::tie(forNode->m_var, content) = readVariable(content, "$for statement can not read loop iterator");
    eatVariable(content, "in", "$for has no in");

    std::tie(forNode->m_path, content) = readVariable(content, "$for statement can not read loop body");
    eatVariable(content, "{{", "$for has no {{");

    std::tie(forNode->m_child, content) = parseMixed(content);
    eatVariable(content, "}}", "$for has no }}");

    return {forNode, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseVar(QString content)
{
    auto varNode = new IVariableNody();
    std::tie(varNode->m_path, content) = readVariable(content, "${{ statement can not read path");
    eatVariable(content, "}}", "${{ has no }}");
    return {varNode, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseComment(QString content)
{
    INody* node{};
    std::tie(node, content) = parseMixed(content);
    delete node;

    eatVariable(content, "}}", "#{{ has no }}");
    return {nullptr, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseExtend(QString content)
{
    auto extendNode = new IExtendNody;
    eatVariable(content, "{{", "$extend, has no {{");
    std::tie(extendNode->m_path, content) = readFilePath(content, "$extend fail to read path");
    eatVariable(content, "}}", "$extend has no }}");

    while(content.startsWith("$block ")){
        INody* blockNode{};
        std::tie(blockNode, content) = parseBlock(content.mid(QString("$block ").length()));
        extendNode->m_children.append(dynamic_cast<IBlockNody*>(blockNode));
    }
    extendNode->computeNody();

    return {extendNode, content};
}

std::pair<INody *, QString> INodyParser::parseBlock(QString content)
{
    auto node = new IBlockNody;
    std::tie(node->m_name, content) = readVariable(content, "$block statement can not read block name");
    eatVariable(content, "{{", "$block has no {{");
    std::tie(node->m_child, content) = parseMixed(content);
    eatVariable(content, "}}", "$block has no }}");
    return {node, content};
}

std::pair<INody *, QString> INodyParser::parseInclude(QString content)
{
    auto node = new IIncludeNody();
    eatVariable(content, "{{", "$include has no {{");
    std::tie(node->m_path, content) = readVariable(content, "$include error with read variable");
    eatVariable(content, "}}", "$include has no }}");
    node->computeNody();
    return {node, content.trimmed()};
}

std::pair<INody *, QString> INodyParser::parseWith(QString content)
{
    auto node = new IWithNody;
    std::tie(node->m_var, content) = readVariable(content, "$with fail read var");
    eatVariable(content, "as ", "$with has no as");
    std::tie(node->m_path, content) = readVariable(content, "$with fail read path");
    eatVariable(content, "{{", "$with has no {{");
    std::tie(node->m_child, content) = parseMixed(content);
    eatVariable(content, "}}", "$with has no }}");
    return {node, content};
}

std::pair<INody *, QString> INodyParser::parseFunction(QString content)
{
    auto nody = new IFunNody;
    std::tie(nody->m_funName, content) = readVariable(content, "$fun error with function");
    eatVariable(content, "{{", "$fun has no {{");
    std::tie(nody->m_child, content) = parseMixed(content);
    eatVariable(content, "}}", "$fun has no }}");
    return {nody, content.trimmed()};
}

std::pair<QString, QString> INodyParser::readVariable(QString content, const QString& failReason)
{
    content = content.trimmed();
    QRegExp regExp("(^[a-zA-Z_]+(\\.[a-zA-Z]+)*)");
    if(regExp.indexIn(content) != -1){
        auto ret = regExp.cap(1);
        if(!ret.isEmpty()){
            return {ret, content.mid(ret.length()).trimmed()};
        }
    }

    throw INodyException(failReason, content);
    return {};
}

std::pair<QString, QString> INodyParser::readFilePath(QString content, const QString &failReason)
{
    content = content.trimmed();
    QRegExp regExp(R"(^[^\s{}]+)");
    if(regExp.indexIn(content) != -1){
        auto ret = regExp.cap(0);
        if(!ret.isEmpty()){
            return {ret, content.mid(ret.length()).trimmed()};
        }
    }

    throw INodyException(failReason, content);
    return {};
}

void INodyParser::eatVariable(QString &content, const QString &val, const QString &failReason)
{
    content = content.trimmed();
    if(!content.startsWith(val)){
        throw INodyException(failReason + " variable:"+  val, content);
    }
    content = content.mid(val.length()).trimmed();
}

}
