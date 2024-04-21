#pragma once

#include "INody.h"
#include <QMap>

namespace IWebCore {

class INodyParser
{
private:
    using Fun = std::pair<INody*, QString> (INodyParser::*)(QString);

public:
    INodyParser();

public:
    INody* parseContent(QString content);
    INody* parseFile(QString path);

private:
    std::pair<INody*, QString> parseMixed(QString);
    std::pair<INody*, QString> parseHtml(QString);
    std::pair<INody*, QString> parseIf(QString content);
    std::pair<INody*, QString> parseElif(QString content);
    std::pair<INody*, QString> parseElse(QString content);
    std::pair<INody*, QString> parseFor(QString content);
    std::pair<INody*, QString> parseVar(QString content);
    std::pair<INody*, QString> parseComment(QString content);
    std::pair<INody*, QString> parseExtend(QString content);
    std::pair<INody*, QString> parseBlock(QString content);
    std::pair<INody*, QString> parseInclude(QString content);
    std::pair<INody*, QString> parseWith(QString content);
    std::pair<INody*, QString> parseFunction(QString content);    // $fun name {{}}

private:
    std::pair<QString, QString> readVariable(QString content, const QString& failReason);
    std::pair<QString, QString> readFilePath(QString content, const QString& failReason);
    void eatVariable(QString& content, const QString& val, const QString& failReason);

private:
    QString m_content;
    static QMap<QString,  Fun> s_map;
    static QStringList s_keys;
};

}
