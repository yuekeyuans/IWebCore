#pragma once

#include "core/base/IHeaderUtil.h"
#include "core/base/IConvertUtil.h"
#include "core/base/IMetaUtil.h"
#include "core/base/IJsonUtil.h"
#include "core/bean/IBeanInterface.h"
#include "core/context/IConfigurationPreProcessor.h"

$PackageWebCoreBegin

class IOrmDataSource : public IBeanInterface<IOrmDataSource>
{
    Q_GADGET
    $AsBean(IOrmDataSource)
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
