#pragma once

#include "core/util/IHeaderUtil.h"
#include "http/controller/detail/IHttpControllerActionNode.h"

$PackageWebCoreBegin

struct IHttpControllerInfo
{
public: //: public IGadgetInfo
    void* handler{};
    QString className;
    QMap<QString, QString> classInfo;
    QVector<QMetaMethod> classMethods;

public:
    QVector<IHttpControllerActionNode> m_urlNodes;
};

$PackageWebCoreEnd
