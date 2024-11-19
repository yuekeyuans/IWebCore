#include "IBannerTask.h"

$PackageWebCoreBegin

static const char BANNER[] = R"(
 _____  _    _        _      _____
|_   _|| |  | |      | |    /  __ \
  | |  | |  | |  ___ | |__  | /  \/  ___   _ __  ___
  | |  | |/\| | / _ \| '_ \ | |     / _ \ | '__|/ _ \
 _| |_ \  /\  /|  __/| |_) || \__/\| (_) || |  |  __/
 \___/  \/  \/  \___||_.__/  \____/ \___/ |_|   \___|
)";

void IBannerTask::$task()
{
    qDebug() << BANNER;
}

double IBannerTask::$order() const
{
    return 0;
}

$PackageWebCoreEnd
