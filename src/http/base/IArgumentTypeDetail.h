﻿#pragma once

#include "core/util/IHeaderUtil.h"
#include "IArgumentType.h"

$PackageWebCoreBegin

struct IArgumentTypeDetail : public IArgumentType
{
public:
    enum Position{
        Auto, Path, Query, Header, Cookie, Session, Body, Form, Json,
    };

public:
    IArgumentTypeDetail(int typeId, QByteArray typeName, QByteArray nameRaw);   // TODO: better to add signature,but skip here.

private:
    void resolveName();

private:// IRequest, IResponse, Jars
    bool createBasicType();
    void createRequestType();
    void createResponseType();
    void createMultiPartJarType();
    void createSessionJarType();
    void createCookieJarType();
    void createHeaderJarType();

private: // cookiepart, multipart
    bool createPartTypes();
    void createMultiPartType();
    void createCookiePartType();

private: // $Header, $Cookie, $Path, $Query, $Body, $Form, $Session,
    bool createDecorateTypes();
    void createQueryType();
    void createHeaderType();
    void createCookieType();
    void createSessionType();
    void createPathType();
    void createBodyType();
    void createFormType();
    void createJsonType();

private:    // bean, List<Bean>, Vector<Bean> ， Map<Bean>
    bool createBeanTypes();

private: // body, query, json 相关，
    bool createDataTypes();

private:
    bool m_optional{false};
    IString m_optionalString;
    Position m_position{Auto};
    IString m_nameRaw;

private:
    QVector<IString> makeTypes(const std::string&);
};

$PackageWebCoreEnd
