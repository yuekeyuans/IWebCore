#include "IHttpPath.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAbort.h"

$PackageWebCoreBegin

struct IHttpUrlDetail : public IHttpPath
{
public:
    IHttpUrlDetail(const QStringList& args);
private:


void checkMappingUrl()
{
    for(const auto& fragement : fragments){
        if(fragement.fragment.isEmpty()){
            return;
        }
        if(isPieceWildCard(fragement.fragment)){
            CheckMappingUrlErrorWildCard(fragement.fragment);
        }else{
            checkMappingUrlErrorCommon(fragement.fragment);
        }
    }

}

void checkMappingUrlErrorCommon(const QString &piece)
{
    static QRegularExpression regexExclude(R"([^ \t\n\r\f\v~`!@#$%^&*()+=|\[\]{}\'\";:/?,.<>]+)");
    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-\._\?\=\&\|/,\:;\'\"\-\~\#\*\+\[\]\(\)\|\$\!\@]+|%(?:[0-9a-fA-F]{2})+)");

    if(!regexExclude.match(piece).hasMatch() || !regexInclude.match(piece).hasMatch()){
        IHttpControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(piece), $ISourceLocation);
    }
}

void CheckMappingUrlErrorWildCard(const QString& piece)
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

bool isPieceWildCard(const QString &piece)
{
    static QRegularExpression wildcard("^<.*>$");
    return wildcard.match(piece).hasMatch();
}

};

IHttpUrlDetail::IHttpUrlDetail(const QStringList& args)
{
    QStringList m_urlPieces;
    for(const QString& arg : args){
        if(!arg.trimmed().isEmpty() && arg.trimmed() != "/"){
            m_urlPieces.append(arg.trimmed());
            fragments.emplace_back(ISpawnUtil::construct<IHttpPathFragment>(arg.trimmed()));
        }
    }
    this->path = m_urlPieces.join("/");

    checkMappingUrl();
}

namespace ISpawnUtil
{
    template<>
    IHttpPath construct<IHttpPath, const QStringList&>(const QStringList& args)
    {
        return IHttpUrlDetail(args);
    }

    template<>
    IHttpPath construct<IHttpPath, const std::vector<IHttpPathFragment>&>(const std::vector<IHttpPathFragment>& fragments_)
    {
        QStringList args;
        for(const auto& info : fragments_){
            args.push_back(info.fragment);
        }

        IHttpPath url;
        url.path = args.join("/");
        url.fragments = fragments_;
        return url;
    }
}

$PackageWebCoreEnd


