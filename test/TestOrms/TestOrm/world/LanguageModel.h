#pragma once

#include <IWebCore>
#include "LanguageTable.h"

extern const char SqliteConnectionName[];

class LanguageModel : public IOrmTableModelInterface<LanguageModel, SqliteConnectionName>
{
public:
    LanguageModel();
};

