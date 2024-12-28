#pragma once

#include <IHttp/IHttpControllerInterface>
#include "http/net/ICookiePart.h"
#include "bean/StudentBean.h"

class BasicArgument : public IHttpControllerInterface<BasicArgument>
{
    Q_GADGET
    $AsController(BasicArgument)
public:
    BasicArgument();

public:
    $GetMapping(irequest)
    QString irequest(IRequest& req){
        return req.url().toQString();
    }

    $PostMapping(multipart)
    QString multipart(const IMultiPart& name, const IMultiPart& file){
        Q_UNUSED(name)
        return file.m_content.toQString();
    }

    $GetMapping(cookiePart)
    QString cookiePart(ICookiePart name){
        return name.m_value.toQString();
    }

    $GetMapping(cookieString)
    QString cookieString(QString $Cookie(name)){
        return name;
    }

    $GetMapping(cookiesString)
    QString cookiesString(QStringList $Cookie(names)){
        return names.join(",");
    }

    $GetMapping(headerType)
    QString headerType(IString $Header(MyHeader));

    $GetMapping(headerTypeInt)
    QString headerTypeInt(int $Header(MyInt));

    $PostMapping(bodyType)
    QString bodyType(QString $Body(body)){
        return body;
    }

    $PostMapping(bodyJson)
    std::string bodyJson(IRequest& req){
        return req.bodyJson().dump();
    }

    $PostMapping(payloadJson)
    std::string payloadJson(IJson value){
        return value.dump();
    }

    $PostMapping(innerJson)
    std::string innerJson(IJson $Json(data))
    {
        return data.dump();
    }

    $PostMapping(formData)
    std::string formData(std::string $Form(name))
    {
        qDebug() << "name" << QString::fromStdString(name);
        return name;
    }

    $PostMapping(beanData)
    std::string beanData(StudentBean bean){
        return bean.toJson().dump();
    }

    $PostMapping(beanDatas)
    std::string beanDatas(QList<StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

    $PostMapping(beanDataStdList)
    std::string beanDataStdList(QList<StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

    $PostMapping(beanDataQMap)
    std::string beanDataQMap(QMap<IString, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

    $PostMapping(beanDataQMapQString)
    std::string beanDataQMapQString(QMap<QString, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

    $PostMapping(beanDataQMapStdString)
    std::string beanDataQMapStdString(QMap<std::string, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

    $PostMapping(beanDataStdMap)
    std::string beanDataStdMap(std::map<IString, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }
    $PostMapping(beanDataStdMapQString)
    std::string beanDataStdMapQString(std::map<QString, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }
    $PostMapping(beanDataStdMapStdString)
    std::string beanDataStdMapStdString(std::map<std::string, StudentBean> beans){
        return IJsonUtil::toJson(beans).dump();
    }

};

