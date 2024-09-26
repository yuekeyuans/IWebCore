#include <ICore/IApplication>
#include <ICore/IContext>
#include "NameBean.h"
#include "PersonBean.h"

$EnableTaskOutput(true)
int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

    bool ok;
//    NameBean bean;
//    std::cout << bean.toJson(&ok).dump(4) << std::endl;

    PersonBean person;

//    person.name2.append(NameBean{});

    person.name2.append(NameBean{});
    person.name2.append(NameBean{});

    auto json = person.toJson(&ok);
    std::cout << person.toJson(&ok).dump(4) << std::endl;

    PersonBean bean2;
    bean2.loadJson(json);

    std::cout << bean2.toJson(&ok).dump(4) << std::endl;

//    PersonBean bean2;

    return app.run();
}
