#pragma once

#include "http/controller/IHttpPath.h"

$PackageWebCoreBegin

struct IHttpPathFragmentDetail : public IHttpPathFragment
{
public:
    IHttpPathFragmentDetail(const QString& m_fragment);

private:
    bool evaluatePlainText();
    bool evaluateTypeEmptyNode();
    bool evaluateNameOnlyNode();
    bool evaluateNameTypeNode();
    bool evaluateRegTypeNode();
};

$PackageWebCoreEnd
