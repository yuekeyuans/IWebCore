#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    IArgumentTypeDetail(int typeId, QString typeName, QString name, QString m_methodSignature);

//private:
//    void checkParamType();
//    void checkParamNameEmpty();
//    void checkParamDuplicated();
//    void checkAndSetParamPosition();
//    void checkAndSetParamOptional();
////    void checkAndSetParamRestrictions();
//    void checkContentPositionMustBeIStringView();
//    void checkBareResponseOrConstResponseRef(); // IResponse or const IResponse& is not allowed
//    void checkResponseAndRequestWithoutDecorators();    // IRequest and Response can not be decorated

//private: // TODO: check
//    void checkMethodSupportedParamArgType();
//    void checkMethodBodyContentArgs();
//    void checkMethodParamterWithSuffixProper();
//    bool isDefinedType();
//    bool isEmbendedType();

private:
    inline static const QStringList QualifierNames = {
        "auto", "query", "path", "header", "body", "content",  "cookie", "session"
    };
    inline static const QString NullableName = "nullable";
    inline static const QString NotnullName = "notnull";
    QStringList m_paramQualifiers;
    std::string m_methodSignature;
};

$PackageWebCoreEnd
