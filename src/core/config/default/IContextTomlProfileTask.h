#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"
#include "core/config/default/ILoadProfileFileUnit.h"

$PackageWebCoreBegin

class IContextTomlProfileTask : public IContextTaskInterface<IContextTomlProfileTask>, public ILoadProfileFileUnit
{
public:
    virtual double order() const;
    virtual IJson config();

private:
    virtual QStringList nameFilters() const final;
    IJson parseToml(const QString &path, bool &ok);
};

$PackageWebCoreEnd

// TODO: not tested !!!
