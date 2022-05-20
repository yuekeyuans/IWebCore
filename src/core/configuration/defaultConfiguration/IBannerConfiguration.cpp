#include "IBannerConfiguration.h"

$PackageWebCoreBegin

QJsonObject IBannerConfiguration::getConfigure() const
{
    QJsonObject obj;
    obj["banner"] =  R"(
 _____  _    _        _      _____
|_   _|| |  | |      | |    /  __ \
  | |  | |  | |  ___ | |__  | /  \/  ___   _ __  ___
  | |  | |/\| | / _ \| '_ \ | |     / _ \ | '__|/ _ \
 _| |_ \  /\  /|  __/| |_) || \__/\| (_) || |  |  __/
 \___/  \/  \/  \___||_.__/  \____/ \___/ |_|   \___|
)";
    return obj;
}

$PackageWebCoreEnd
