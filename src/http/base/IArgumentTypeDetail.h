#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    // TODO: better to add signature,but skip here.
    IArgumentTypeDetail(int typeId, QByteArray&& typeName, QByteArray&& name);

private:
    bool createBasicType();
    void createRequestType();
    void createResponseType();
    void createMultiPartJarType();
    void createSessionJarType();
    void createCookieJarType();
    void createHeaderJarType();

private:


private:
    QVector<std::string> makeTypes(const std::string&);

//private:
//    std::string m_methodSignature;
};

$PackageWebCoreEnd
