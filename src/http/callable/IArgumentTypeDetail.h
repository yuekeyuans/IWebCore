﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    IArgumentTypeDetail(int typeId, QByteArray typeName, QByteArray nameRaw);   // TODO: better to add signature,but skip here now.

private:
    void resolveName();

private:// IRequest, IResponse, Jars
    void createBasicTypes();
    void createRequestType();
    void createResponseType();
    void createMultiPartJarType();
    void createSessionJarType();
    void createCookieJarType();
    void createHeaderJarType();

private: // cookiepart, multipart
    void createPartTypes();
    void createMultiPartType();
    void createCookiePartType();

private: // $Header, $Cookie, $Path, $Query, $Body, $Form, $Session, $Json
    void createDecorateTypes();
    void createQueryType();
    void createHeaderType();
    void createCookieType();
    void createSessionType();
    void createPathType();
    void createBodyType();
    void createFormType();
    void createJsonType();

private:    // bean, List<Bean>, Vector<Bean> ， Map<Bean> ...
    void createBeanTypes();

private:
    IString m_optionalString;
    IString m_nameRaw;
    void* m_optionalPtr{}; // NOTE: this wont be release till program exits

private:
    QVector<IString> makeTypes(const std::string&);
    IJson::json_pointer createJsonPointer(const IString&);
};

$PackageWebCoreEnd
