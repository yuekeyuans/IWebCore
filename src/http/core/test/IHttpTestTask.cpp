#include "IHttpTestTask.h"
#include "http/core/test/IHttpTestManage.h"
#include "core/config/IProfileImport.h"

void IWebCore::IHttpTestTask::task()
{
    std::thread thread([](){
        $Bool enabled{"/http/test/enabled", false};
        if(!enabled.value()){
            return;
        }
        $Int delay{"/http/test/delayDuration", 1000};
        std::this_thread::sleep_for(std::chrono::milliseconds(*delay));
        IHttpTestManage::instance()->invokeTests();
    });
    thread.detach();
}
