#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IMetaUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/bean/IBeanInterface.h"

$PackageWebCoreBegin

class IOrmDataSource //: public IBeanInterface<IOrmDataSource>
{
    Q_GADGET
//    $AsBean(IOrmDataSource)
public:
    IOrmDataSource() = default;

    $BeanField(QString, driverName)

    $BeanField(QString, databaseName)

    $BeanFieldDeclare(QString, connectionName)
    QString connectionName = "default";

    $BeanField(int, port)

    $BeanField(QString, host)

    $BeanField(QString, userName)

    $BeanField(QString, password)
};

$PackageWebCoreEnd
