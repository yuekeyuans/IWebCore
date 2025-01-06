#include "IConstantUtil.h"

$PackageWebCoreBegin

const IString IConstantUtil::CommaSpace = ": ";
const IString IConstantUtil::Semicolon = ";";
const IString IConstantUtil::NewLine = "\r\n";
const IString IConstantUtil::Equal = "=";
const IString IConstantUtil::Empty = {};
const IStringView IConstantUtil::EmptyView = {};
const IString IConstantUtil::Space = " ";

const IString IConstantUtil::Type = "Type";
const IString IConstantUtil::Name = "Name";
const IString IConstantUtil::True = "True";
const IString IConstantUtil::False = "False";

const std::vector<IString> IConstantUtil::EmptyVector {};
const std::vector<IString> IConstantUtil::StringTypes = {"IString", "IStringView", "std::string", "QString", "QByteArray"};

$PackageWebCoreEnd
