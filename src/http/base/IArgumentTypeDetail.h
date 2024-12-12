#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    IArgumentTypeDetail(int typeId, QByteArray typeName, QByteArray nameRaw);   // TODO: better to add signature,but skip here.

private:
    void resolveName();

private:
    bool createBasicType();         // IRequest, IResponse, Jar
    void createRequestType();
    void createResponseType();
    void createMultiPartJarType();
    void createSessionJarType();
    void createCookieJarType();
    void createHeaderJarType();

private:
    bool createPartType();
    void createMultiPartType();
    void createCookiePartType();

private:
    QVector<IString> makeTypes(const std::string&);
};

$PackageWebCoreEnd
