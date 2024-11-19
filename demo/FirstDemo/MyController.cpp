#include "MyController.h"

QString MyController::fun1()
{
    return "hello world";
}

QString MyController::fun2()
{
    return "$json:[1,2,3,4,5,6]";
}

IJsonResponse MyController::fun3($Param (UserTable, userTable))
{
    return userTable_param;
}

IJsonResponse MyController::fun4()
{
    QJsonObject obj;
    obj["name"] = "yuekeyuan";
    obj["masterPiece"] = "IWebCore";
    obj["expactation"] = "world famouse";
    return obj;
}

IJsonResponse MyController::fun5()
{
    QList<UserTable> tables;
    UserTable table1;
    tables.append(table1);
    tables.append(UserTable{});

    return tables;
}

void MyController::fun6(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)

    response.setStatus(IHttpStatus::OK_200);
    response.setMime(IHttpMime::TEXT_PLAIN_UTF8);
    response << "hello world";
}
