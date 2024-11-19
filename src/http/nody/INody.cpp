#include "INody.h"
#include "INodyManage.h"

namespace IWebCore{

INody *INody::clone()
{
    if(auto ptr = dynamic_cast<INodyWithChild*>(this)){
        ptr->m_child = ptr->m_child->clone();
    }
    if(auto ptr = dynamic_cast<INodyWithChildren*>(this)){
        auto children = ptr->m_children;
        ptr->m_children.clear();
        for(auto child : children){
            ptr->m_children.append(child->clone());
        }
    }
    if(auto ptr = dynamic_cast<INodyWithTwins*>(this)){
        ptr->m_elder = ptr->m_elder->clone();
        ptr->m_younger = ptr->m_younger->clone();
    }
    return this;
}

QJsonValue INody::getValue(const QString &path, const QJsonObject &root, const QMap<QString, QJsonValue> &map)
{
    auto rootVal = getValue(path, root);
    if(rootVal.isNull() || rootVal.isUndefined()){
        return getValue(path, map);
    }
    return rootVal;
}

QJsonValue INody::getValue(const QString & path, const QJsonObject& obj)
{
    if(path.isEmpty()){
        return {};
    }
    QStringList args = path.split(".");
    if(!obj.contains(args.first())){
        return {};
    }
    QJsonValue temp = obj[args.first()];
    args.pop_front();
    for(auto arg : args){
        if(!temp.isObject()){
            return {};
        }
        auto obj = temp.toObject();
        if(!obj.contains(arg)){
            return {};
        }
        temp = obj[arg];
    }
    return temp;
}

QJsonValue INody::getValue(const QString &path, const QMap<QString, QJsonValue>&map)
{
    if(path.isEmpty()){
        return {};
    }
    QStringList args = path.split(".");
    if(!map.contains(args.first())){
        return {};
    }
    const auto& obj = map[args.first()];
    args.pop_front();
    if(args.isEmpty()){
        return obj;
    }
    if(obj.isObject()){
        return getValue(args.join("."), obj.toObject());
    }
    return {};
}


INodyWithChildren::~INodyWithChildren()
{
    for(auto node : m_children){
        delete node;
    }
}

INodyWithChild::~INodyWithChild()
{
    delete m_child;
}

INodyWithTwins::~INodyWithTwins()
{
    delete m_elder;
    delete m_younger;
}

QString IUnionNody::execute(const QJsonObject& root, const QMap<QString, QJsonValue>& context)
{
    QString ret;
    for(auto node : m_children){
        ret.append(node ? node->execute(root, context) : QString{});
    }
    return ret;
}

QString IHtmlNody::execute(const QJsonObject&, const QMap<QString, QJsonValue>&)
{
    return m_html;
}

QString IVariableNody::execute(const QJsonObject& root, const QMap<QString, QJsonValue>& context)
{
    auto value = getValue(m_path, root, context);
    if(value.isBool()){
        return value.toBool() ? "true" : "false";
    }else if(value.isDouble()){
        return QString::number(value.toDouble());
    }else if(value.isString()){
        return value.toString();
    }else if(value.isNull() || value.isUndefined()){
        return "";
    }else if(value.isArray()){
        QJsonDocument doc;
        doc.setArray(value.toArray());
        return doc.toJson(QJsonDocument::Indented);
    }else if(value.isObject()){
        QJsonDocument doc;
        doc.setObject(value.toObject());
        return doc.toJson(QJsonDocument::Indented);
    }
    return {};
}

QString IfNody::execute(const QJsonObject& root, const QMap<QString, QJsonValue>& context)
{
    auto value = getValue(m_path, root, context);
    bool condition{false};
    if(value.isBool()){
        condition = value.toBool();
    }else if(value.isString()){
        condition = value.toString().trimmed().isEmpty();
        //        condition = IConvertUtil::toBool(value, condition);
    }else if(value.isUndefined() || value.isNull()){
        condition = false;
    }else if(value.isDouble()){
        condition = value.toDouble();
    }else if(value.isArray()){
        condition = !value.toArray().isEmpty();
    }else if(value.isObject()){
        condition = !value.toObject().isEmpty();
    }

    if(condition){
        if(m_elder){
            return m_elder->execute(root, context);
        }
    }else{
        if(m_younger){
            return m_younger->execute(root, context);
        }
    }
    return {};
}

QString IForNody::execute(const QJsonObject& root, const QMap<QString, QJsonValue>& context)
{
    QString ret;
    QJsonValue value = getValue(m_path, root, context);
    if(value.isArray()){
        auto forContext = context;
        auto array = value.toArray();
        for(const auto& var : array){
            forContext[m_var] = var;
            ret.append(m_child->execute(root, forContext));
        }
    }
    return ret;
}

QString IWithNody::execute(const QJsonObject &root, const QMap<QString, QJsonValue> &context)
{
    auto value = getValue(m_path, root, context);
    if(value.isNull() || value.isUndefined()){
        return {};
    }
    auto withContext = context;
    withContext[m_var] = value;
    return m_child->execute(root, withContext);
}

QString IIncludeNody::execute(const QJsonObject &root, const QMap<QString, QJsonValue> &context)
{
    return m_child ? m_child->execute(root, context) : QString{};
}

void IIncludeNody::computeNody()
{
    m_child = INodyManage::instance()->parseFile(m_path);
}

QString IBlockNody::execute(const QJsonObject &root, const QMap<QString, QJsonValue> &context)
{
    return m_child ? m_child->execute(root, context) : QString{};
}

QString IExtendNody::execute(const QJsonObject &root, const QMap<QString, QJsonValue> &context)
{
    return m_child ? m_child->execute(root, context) : QString{};
}

void IExtendNody::computeNody()
{
    m_child = INodyManage::instance()->parseFile(m_path);
    QMap<QString, IBlockNody* > map;
    for(auto node : m_children){
        map[dynamic_cast<IBlockNody*>(node)->m_name] = dynamic_cast<IBlockNody*>(node);
    }

    replaceBlock(m_child, map);
}

void IExtendNody::replaceBlock(INody *node, QMap<QString, IBlockNody *> map)
{
    if(auto ptr = dynamic_cast<INodyWithChild*>(node)){
        if(auto child = dynamic_cast<IBlockNody*>(ptr->m_child)){
            if(map.contains(child->m_name)){
                ptr->m_child = map[child->m_name]->clone();
                delete child;
            }
        }else{
            replaceBlock(ptr->m_child, map);
        }
    }

    if(auto ptr = dynamic_cast<INodyWithTwins*>(node)){
        if(auto child = dynamic_cast<IBlockNody*>(ptr->m_elder)){
            if(map.contains(child->m_name)){
                ptr->m_elder = map[child->m_name]->clone();
                delete child;
            }
        }else{
            replaceBlock(ptr->m_elder, map);
        }

        if(auto child = dynamic_cast<IBlockNody*>(ptr->m_younger)){
            if(map.contains(child->m_name)){
                ptr->m_younger = map[child->m_name]->clone();
                delete child;
            }
        }else{
            replaceBlock(ptr->m_younger, map);
        }
    }

    if(auto ptr = dynamic_cast<INodyWithChildren*>(node)){
        int len = ptr->m_children.length();
        for(auto i=0; i<len; i++){
            if(auto child = dynamic_cast<IBlockNody*>(ptr->m_children[i])){
                if(map.contains(child->m_name)){
                    ptr->m_children[i] = map[child->m_name]->clone();
                    delete child;
                }
            }else{
                replaceBlock(ptr->m_children[i], map);
            }
        }
    }
}

QString IFunNody::execute(const QJsonObject &root, const QMap<QString, QJsonValue> &context)
{
    Q_UNUSED(root)
    Q_UNUSED(context)
    return {};
}

INodyException::INodyException(const QString &error, const QString& content)
{
    m_error.append(makeTrace(error, content));
}

const char *INodyException::what() const
{
    return m_error.join("\n").toUtf8();
}

void INodyException::addTrace(const QString &error, const QString& content)
{
    m_error.append(makeTrace(error, content));
}

QString INodyException::getTraces()
{
    return m_error.join(" \n");
}

QString INodyException::makeTrace(const QString &error, const QString &content)
{
    int len = content.length();
    QString brief;
    if(len < 100){
        brief = content.left(100);
    }else {
        brief = content.left(50).append(" ...... ").append(content.right(50));
    }
    QString ret = QString("ERROR: ").append(error).append(" NEAR: ").append(brief);
    return ret;
}

}
