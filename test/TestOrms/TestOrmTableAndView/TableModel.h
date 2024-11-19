#pragma once

#include <IWebCore>
#include <TableBean.h>

class TableModel : public IOrmTableModelInterface<TableBean>
{
public:
    TableModel();
};

