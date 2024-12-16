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

private: // cookiepart, multipart
    bool createPartType();
    void createMultiPartType();
    void createCookiePartType();

private: // 和 header 相关
    bool createHeaderType();
    

private: // body, query, json 相关，
    bool createDataType();

private: // bean 相关


private:
    QVector<IString> makeTypes(const std::string&);
};

$PackageWebCoreEnd
