#pragma once

#include <IWebCore>
#include "ViewBean.h"

class ViewModel : public IOrmViewModelInterface<ViewBean>
{
public:
    ViewModel();
};

