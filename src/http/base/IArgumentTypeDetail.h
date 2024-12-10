#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    IArgumentTypeDetail(int typeId, QString typeName, QString name, QString m_methodSignature);


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

private:
    std::string m_methodSignature;
};

$PackageWebCoreEnd
