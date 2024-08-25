#pragma once

#include "core/util/IHeaderUtil.h"
#include "core/config/IContextTaskInterface.h"
#include "core/config/IConfigPreProcessor.h"
#include "core/config/default/ILoadProfileFileUnit.h"

$PackageWebCoreBegin

class IContextJsonProfileTask final: public IContextTaskInterface<IContextJsonProfileTask> , public ILoadProfileFileUnit
{
public:
    virtual IJson config() final;

private:
    virtual double order() const;
    virtual QStringList nameFilters() const final;
    IJson parseJsonFile(const QString& path) const;
};

$PackageWebCoreEnd
