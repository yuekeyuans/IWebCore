#pragma once

#include "orm/clause/IOrmClause.h"
$PackageWebCoreBegin

class IOrmQueryClause : public IOrmClause
{
public:
    using IOrmClause::IOrmClause;
};

$PackageWebCoreEnd
