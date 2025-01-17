﻿#include "IHttpNotFoundInvalid.h"
#include "http/detail/IResponseRaw.h"

$PackageWebCoreBegin

IHttpNotFoundInvalid::IHttpNotFoundInvalid()
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404)
{
}

IHttpNotFoundInvalid::IHttpNotFoundInvalid(const std::string& description)
    : IHttpInvalidInterface(IHttpStatus::NOT_FOUND_404, description)
{
}

void IHttpNotFoundInvalid::process(const IHttpInvalidWare &ware, IResponseRaw & raw)
{
    raw.setContent(new IResponseContent(ware.description.m_view.toStdString() + " hahahahah"));
}

$PackageWebCoreEnd
