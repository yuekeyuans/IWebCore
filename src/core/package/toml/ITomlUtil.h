#pragma once

#include <QString>
#include <QJsonObject>

namespace ITomlUtil
{

QJsonObject parseToml(const QString& path, bool& ok);

};

