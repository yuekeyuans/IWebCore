#include "ITaskManage.h"

#include "assertion/IAssertPreProcessor.h"
#include "configuration/IConfigurationManage.h"

$PackageWebCoreBegin

void ITaskManage::run()
{
    QStringList arguments;
    run(arguments);
}

void ITaskManage::run(int argc, char **argv)
{
    QStringList arguments;
    for(int i=0; i<argc; i++){
        arguments << QString(argv[i]);
    }
    run(arguments);
}

void ITaskManage::run(const QStringList& arguments)
{
    auto inst = instance();
    inst->m_isStarted = true;

    inst->invokeArgumentParsers(arguments);
    inst->invokeConfigers();

    inst->invokeInitializers();

    inst->invokeControllers();
    inst->invokeBluePrint();
}

void ITaskManage::registerArgumentParser(ArgumentParserFunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $AssertFatal(defer_register_not_allowed, "registerConfiger")
    }

    inst->m_argumentParsers.append(fun);
}

void ITaskManage::registerConfigrator(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $AssertFatal(defer_register_not_allowed, "registerConfiger")
    }

    inst->m_configurators.append(fun);
}

void ITaskManage::registerInitializer(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $AssertFatal(defer_register_not_allowed, "registerInitializer")
    }

    inst->m_initializers.append(fun);
}

void ITaskManage::registerController(FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $AssertFatal(defer_register_not_allowed, "registerConfiger")
    }
    inst->m_controllers.append(fun);
}

void ITaskManage::registerBluePrint(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $AssertFatal(defer_register_not_allowed, "registerInitializer")
    }
    inst->m_blueprints.append(fun);
}

void ITaskManage::registerAsyncTask(ITaskManage::FunType fun)
{
    QTimer::singleShot(0, [=](){
        fun();
    });
}

void ITaskManage::invokeArgumentParsers(const QStringList& arguments)
{
    auto inst = instance();
    for(auto fun : inst->m_argumentParsers){
        fun(arguments);
    }
    inst->m_argumentParsers.clear();
}

void ITaskManage::invokeControllers()
{
    auto inst = instance();
    for(auto fun : inst->m_controllers){
        fun();
    }
    inst->m_controllers.clear();
}

void ITaskManage::invokeConfigers()
{
    auto inst = instance();
    for(FunType fun : inst->m_configurators){
        fun();
    }

    inst->m_configurators.clear();
    IConfigurationManage::instance()->m_isInited = true;
}

void ITaskManage::invokeInitializers()
{
    auto inst = instance();
    for(FunType fun : inst->m_initializers){
        fun();
    }

    inst->m_initializers.clear();
}

void ITaskManage::invokeBluePrint()
{
    auto inst = instance();
    for(FunType fun : inst->m_blueprints){
        fun();
    }

    inst->m_blueprints.clear();
}


$PackageWebCoreEnd
