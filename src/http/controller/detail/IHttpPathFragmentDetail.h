#pragma once

#include "http/controller/IHttpPath.h"

$PackageWebCoreBegin

struct IHttpPathFragmentDetail : public IHttpPathFragment
{
public:
    IHttpPathFragmentDetail(const QString& m_fragment);

private:
    bool evaluatePlainText(const QString& nodeName);
    bool evaluateTypeEmptyNode(const QString &nodeName);
    bool evaluateNameOnlyNode(const QString &nodeName);
    bool evaluateNameTypeNode(const QString &nodeName);
    bool evaluateRegTypeNode(const QString &nodeName);
};

$PackageWebCoreEnd
