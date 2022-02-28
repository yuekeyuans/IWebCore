#pragma once

#include "base/IHeaderUtil.h"
#include "orm/dialect/IDialect.h"

class IPostGreSqlDialect : public IDialect
{
public:
    IPostGreSqlDialect();
};

