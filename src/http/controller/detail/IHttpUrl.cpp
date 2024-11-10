#include "IHttpUrl.h"
#include "core/util/ISpawnUtil.h"

$PackageWebCoreBegin

struct IHttpUrlDetail : public IHttpUrl
{
public:
    IHttpUrlDetail(const QStringList& args);
private:
    /*


void IHttpControllerInfoDetail::checkMappingUrl()
{
    for(const IHttpMethodMappingInfo& info : m_mappingInfos){
        std::for_each(info.path.begin(), info.path.end(), [&](const QString& piece){
            if(piece.isEmpty()){
                return;
            }
            if(isPieceWildCard(piece)){
                CheckMappingUrlErrorWildCard(piece);
            }else{
                checkMappingUrlErrorCommon(piece);
            }
        });
    }
}

void IHttpControllerInfoDetail::checkMappingUrlErrorCommon(const QString &piece)
{
//    static QRegularExpression urlPieceReg("^[0-9a-zA-Z\\$\\.\\+\\*\\(\\)\\,!_\\$']+$");    // TODO: I don`t know whether it right or not see: https://www.cnblogs.com/cxygg/p/9278542.html
//    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-_.]+|%(?:[0-9a-fA-F]{2})+)");
    static QRegularExpression regexExclude(R"([^ \t\n\r\f\v~`!@#$%^&*()+=|\[\]{}\'\";:/?,.<>]+)");
    // 允许字母（大小写）、数字、连字符、下划线、点号、问号、等号、与号、斜杠、逗号、分号、冒号、破折号、波浪线、井号、星号、加号、方括号、圆括号、竖线、反斜杠、竖线、单引号、双引号、尖括号、美元符号、感叹号、at 符号以及百分号编码（%XX 形式）
    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-\._\?\=\&\|/,\:;\'\"\-\~\#\*\+\[\]\(\)\|\$\!\@]+|%(?:[0-9a-fA-F]{2})+)");

    if(!regexExclude.match(piece).hasMatch() || !regexInclude.match(piece).hasMatch()){
        IHttpControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(piece), $ISourceLocation);
    }
}

void IHttpControllerInfoDetail::CheckMappingUrlErrorWildCard(const QString& piece)
{
    static QRegularExpression validName("^[0-9a-zA-Z_]+$");
    static QRegularExpression expression0("^<(.*)>$");
    static QRegularExpression expression1("^<(.*):(.*)>$");
    static QRegularExpression expression2("^<(reg)?:(.*):(.*)>$");

    if(!(piece.startsWith('<') && piece.endsWith('>'))){
        return;
    }

    int colonCount = piece.count(':');
    if(colonCount == 0){
        auto result = expression0.match(piece);
        if(result.hasMatch()){
            auto name = result.captured(1);
            if(!validName.match(name).isValid()){
                QString info = "not a valid name in wideCard expression:\n\t" + piece;
                qFatal(info.toUtf8());
            }
        }
    } else if(colonCount == 1){
        auto result = expression1.match(piece);
        auto name = result.captured(1);
        auto validator = result.captured(2);
        if(!validName.match(name).isValid() || !validName.match(validator).isValid()){
            QString info = "not a valid name or validator name in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
    } else if(colonCount == 2){
        auto result = expression2.match(piece);
        if(!result.hasMatch()){
            QString info = "not a valid regexpression wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
        auto name = result.captured(2);
        auto regexp = result.captured(3);
        if(!validName.match(name).isValid()){
            QString info = "not a valid name in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
        QRegularExpression exp(regexp);
        if(!exp.isValid()){
            QString info = "not a valid regexp in wideCard expression:\n\t" + piece;
            qFatal(info.toUtf8());
        }
    }else {
        QString info = "wideCard do not supoort for expression more than two conos: \n\t" + piece;
        qFatal(info.toUtf8());
    }

}

bool IHttpControllerInfoDetail::isPieceWildCard(const QString &piece)
{
    static QRegularExpression wildcard("^<.*>$");
    return wildcard.match(piece).hasMatch();
}
     * */
};

IHttpUrlDetail::IHttpUrlDetail(const QStringList& args)
{
    QStringList m_urlPieces;
    for(const QString& arg : args){
        if(!arg.trimmed().isEmpty() && arg.trimmed() != "/"){
            m_urlPieces.append(arg.trimmed());
        }
    }

    this->path = m_urlPieces.join("/").prepend("/");
    for(const QString piece : m_urlPieces){
        fragments.emplace_back(ISpawnUtil::construct<IHttpUrlFragment>(piece));
    }
}

namespace ISpawnUtil
{
    template<>
    IHttpUrl construct(QStringList args)
    {
        return IHttpUrlDetail(args);
    }
}

$PackageWebCoreEnd


