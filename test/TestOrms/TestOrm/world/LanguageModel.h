#pragma once

#include <IWebCore>
#include "LanguageTable.h"

class LanguageModel : public IOrmTableModelInterface<LanguageTable>
{
public:
    LanguageModel();
};

