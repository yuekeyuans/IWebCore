﻿#include <ICore/IApplication>
#include <ICore/IContext>
#include "NameBean.h"
#include "PersonBean.h"

//$SetConfigFilesPath("D:/image/")
$EnableConfigFiles(true)
$SetConfigFileFilters("*.toml", "*.json", "*.tml")
$SetConfigFilePaths("C:/Users/Yue/.vscode/extensions/bodil.prettier-toml-0.1.0/node_modules/@toml-tools/parser/benchmark/samples/lolbench")
$EnableTaskOutput(true)

int main(int argc, char *argv[])
{
    IApplication app(argc, argv);

//    TestJson bean;
//    bool ok;
////    std::cout << json.toJson(nullptr).dump(4) << std::endl;
//    auto json = bean.toJson(&ok);

//    TestJson bean2;
//    bean2.loadJson(json);


//    std::cout << bean2.toJson(&ok).dump(4);

    NameBean bean;
    bean.val2["hello"] = {};

    PersonBean person;

    person.name2.push_back(NameBean{});
    person.name2.push_back(NameBean{});
    person.name2.push_back(NameBean{});

//    std::cout << person.toJson().dump(4) << std::endl;

    auto json = person.toJson();
    std::cout << "before" << json.dump(4) << std::endl;

    PersonBean bean2;
    bean2.loadJson(json);

    std::cout << "after" << bean2.toJson().dump(4) << std::endl;

    return app.run();
}
