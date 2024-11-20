#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/invalid/IHttpInvalidWare.h"
//#include "http/invalid/IHttpInvalidUnit.h"
#include <array>

$PackageWebCoreBegin

class IResponseContentWare;
struct IResponseContent
{
public:
    void setContent(QString&& content);
    void setContent(const QString& content);
    void setContent(QByteArray&& content);
    void setContent(const QByteArray& content);
    void setContent(const char* content);
    void setContent(IHttpInvalidWare ware);
    void setFileContent(const QString& path);

    IStringView getContent();

public:
    bool isValid{true};
    std::list<IResponseContentWare*> m_contents;

    // TODO:
//    std::function<void(IRequest&)> invalidFunction{};
};

$PackageWebCoreEnd
