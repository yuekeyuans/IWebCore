#include "IHttpPathDetail.h"
#include "core/util/ISpawnUtil.h"
#include "http/controller/IHttpControllerAbort.h"

$PackageWebCoreBegin

IHttpPathDetail::IHttpPathDetail(const QStringList& args)
{
    QStringList m_urlPieces;
    for(const QString& arg : args){
        if(!arg.trimmed().isEmpty() && arg.trimmed() != "/"){
            m_urlPieces.append(arg.trimmed());
            m_fragments.emplace_back(ISpawnUtil::construct<IHttpPathFragment>(arg.trimmed()));
        }
    }
    this->m_path = m_urlPieces.join("/");

    checkMappingUrl();
}

void IHttpPathDetail::checkMappingUrl()
{
    for(const auto& fragement : m_fragments){
        if(fragement.m_fragment.isEmpty()){
            return;
        }
        if(isPieceWildCard(fragement.m_fragment)){
            CheckMappingUrlErrorWildCard(fragement.m_fragment);
        }else{
            checkMappingUrlErrorCommon(fragement.m_fragment);
        }
    }
}

void IHttpPathDetail::checkMappingUrlErrorCommon(const QString &piece)
{
    static QRegularExpression regexExclude(R"([^ \t\n\r\f\v~`!@#$%^&*()+=|\[\]{}\'\";:/?,.<>]+)");
    static QRegularExpression regexInclude(R"([a-zA-Z0-9\-\._\?\=\&\|/,\:;\'\"\-\~\#\*\+\[\]\(\)\|\$\!\@]+|%(?:[0-9a-fA-F]{2})+)");

    if(!regexExclude.match(piece).hasMatch() || !regexInclude.match(piece).hasMatch()){
        IHttpControllerAbort::abortUrlInvalidCharacter(QString("url: ").append(piece), $ISourceLocation);
    }
}

void IHttpPathDetail::CheckMappingUrlErrorWildCard(const QString &piece)
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

bool IHttpPathDetail::isPieceWildCard(const QString &piece)
{
    static QRegularExpression wildcard("^<.*>$");
    return wildcard.match(piece).hasMatch();
}

namespace ISpawnUtil
{
    template<>
    IHttpPath construct<IHttpPath, const QStringList&>(const QStringList& args)
    {
        return IHttpPathDetail(args);
    }

    template<>
    IHttpPath construct<IHttpPath, const std::vector<IHttpPathFragment>&>(const std::vector<IHttpPathFragment>& fragments_)
    {
        QStringList args;
        for(const auto& info : fragments_){
            args.push_back(info.m_fragment);
        }

        IHttpPath url;
        url.m_path = args.join("/");
        url.m_fragments = fragments_;
        return url;
    }
}

$PackageWebCoreEnd
