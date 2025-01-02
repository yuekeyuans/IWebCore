#pragma once

#include "http/controller/IHttpPath.h"

$PackageWebCoreBegin

struct IHttpPathFragmentDetail : public IHttpPathFragment
{
public:
    IHttpPathFragmentDetail(const QString& fragment);

private:
    bool evaluatePlainText(const QString& nodeName);
    bool evaluateTypeEmptyNode(const QString &nodeName);
    bool evaluateNameOnlyNode(const QString &nodeName);
    bool evaluateNameTypeNode(const QString &nodeName);
    bool evaluateRegTypeNode(const QString &nodeName);
    bool evaluateUnMatchedNode(const QString &nodeName);
};

$PackageWebCoreEnd
