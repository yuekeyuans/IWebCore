#include "ICore/IApplication"
#include "core/config/IConfigAnnomacro.h"

$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    return app.exec();
}
