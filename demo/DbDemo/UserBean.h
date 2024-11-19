#pragma once

#include "base/IHeaderUtil.h"
#include "orm/IOrmPreProcessor.h"
#include "orm/IOrmTableInfo.h"
#include "orm/IOrmTableInterface.h"
#include "base/IMetaUtil.h"
#include "base/IConvertUtil.h"
#include "base/IOrmUtil.h"

class UserBean : public IOrmTableInterface
{
    Q_GADGET
    $AsTable(UserBean)
public:
    UserBean();

    $Unique(name)
    $AutoGenerate(name)
    $PrimaryKey(name)
    $Column(int, name)

    $ColumnDeclare(QString, yue)
    QString yue {"hello world"};

    $NotNull(keyuan)
    $ColumnDeclare(QString, keyuan)
    QString keyuan = "keyuan";
};

//$RegisterTable(UserBean)
