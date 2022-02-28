#pragma once

#include <IWebCore>
#include <TableBean.h>

class TableModel : public webCore::IOrmTableModelInterface<TableBean>
{
public:
    TableModel();
};

