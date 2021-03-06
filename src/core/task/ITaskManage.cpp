#include "ITaskManage.h"

#include "core/configuration/IConfigurationManage.h"
#include "core/assert/IGlobalAssert.h"

$PackageWebCoreBegin

$UseGlobalAssert()

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

    inst->invokeFirstInvokers();

    inst->invokeArgumentTasks(arguments);
    inst->invokeConfigers();

    inst->invokeInitializers();

    inst->invokeControllers();
    inst->invokeMiddleWares();

    inst->invokeBluePrint();

    inst->invokeLastInvokers();
}

void ITaskManage::registerArgumentTask(ArgumentTaskFunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_ArgumentTasks.append(fun);
}

void ITaskManage::registerConfigrator(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }

    inst->m_configurators.append(fun);
}

void ITaskManage::registerInitializer(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerInitializer");
    }

    inst->m_initializers.append(fun);
}

void ITaskManage::registerController(FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_controllers.append(fun);
}

void ITaskManage::registerMiddleWare(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_middleWares.append(fun);
}

void ITaskManage::registerFirstInvoker(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_firstInvokers.append(fun);
}

void ITaskManage::registerLastInvoker(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_lastInvokers.append(fun);
}

void ITaskManage::registerBluePrint(ITaskManage::FunType fun)
{
    auto inst = instance();
    if(inst->m_isStarted){
        $GlobalAssert->fatal(IGlobalAssert::TaskDeferRegisterNotAllowed,  "registerConfiger");
    }
    inst->m_blueprints.append(fun);
}

void ITaskManage::registerAsyncTask(ITaskManage::FunType fun)
{
    QTimer::singleShot(0, [=](){
        fun();
    });
}

void ITaskManage::invokeArgumentTasks(const QStringList& arguments)
{
    auto inst = instance();
    for(auto fun : inst->m_ArgumentTasks){
        fun(arguments);
    }
    inst->m_ArgumentTasks.clear();
}

void ITaskManage::invokeControllers()
{
    auto inst = instance();
    for(auto fun : inst->m_controllers){
        fun();
    }
    inst->m_controllers.clear();
}

void ITaskManage::invokeMiddleWares()
{
    auto inst = instance();
    for(auto fun : inst->m_middleWares){
        fun();
    }
    inst->m_middleWares.clear();
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

void ITaskManage::invokeFirstInvokers()
{
    auto inst = instance();
    for(FunType fun : inst->m_firstInvokers){
        fun();
    }
    inst->m_firstInvokers.clear();
}

void ITaskManage::invokeLastInvokers()
{
    auto inst = instance();
    for(FunType fun : inst->m_lastInvokers){
        fun();
    }
    inst->m_lastInvokers.clear();
}

$PackageWebCoreEnd
