#include <IWeb/HttpRequest>

#include "StatusControllerTest.h"
#include <iostream>

void StatusControllerTest::testInt()
{
    try{
        http::Request req(url + "/int");
        auto res = req.send("GET");
        qDebug() << QString::fromStdString(std::string{res.body.begin(), res.body.end()});
        QVERIFY(res.status.code == http::Status::NotFound);
    }catch(...){
        qDebug() << "error occur";
    }
}

void StatusControllerTest::testIntString()
{

}

void StatusControllerTest::testStatus()
{

}

void StatusControllerTest::testStatusString()
{

}
