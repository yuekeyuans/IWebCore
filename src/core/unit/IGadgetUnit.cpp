#include "IGadgetUnit.h"

#include "core/abort/IGlobalAbort.h"
#include "core/bean/IBeanTypeManage.h"
#include "core/util/IConstantUtil.h"
#include "core/util/IConvertUtil.h"
#include "core/util/IJsonUtil.h"
#include "core/util/IMetaUtil.h"

$PackageWebCoreBegin

// 这个是指在 bean 自动装配的过程中, 这一个 field 可以被忽略
const QStringList& IGadgetUnit::getIgnorableFieldNames() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static const QStringList names;
    return names;
}

const QVector<int>& IGadgetUnit::getIgnorableFieldIndexes() const
{
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    static const QVector<int> indexes;
    return indexes;
}

bool IGadgetUnit::isIgnorableField(const QString &name) const
{
    Q_UNUSED(name)
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

bool IGadgetUnit::isIgnorableField(int index) const
{
    Q_UNUSED(index)
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

QVariant IGadgetUnit::getFieldValue(const QString &name) const
{
    Q_UNUSED(name);
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
    return {};
}

void IGadgetUnit::setFieldValue(const QString &name, const QVariant &value)
{
    Q_UNUSED(name);
    Q_UNUSED(value);
    IGlobalAbort::abortUnImplimentedMethod($ISourceLocation);
}


$PackageWebCoreEnd
