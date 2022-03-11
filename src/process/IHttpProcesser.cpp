#include "IHttpProcesser.h"
#include "IHttpSocketManage.h"
#include "base/ISocketUtil.h"
#include "base/ITicTacUtil.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"
#include "common/net/impl/IReqRespRaw.h"
#include "controller/IControllerManage.h"
#include "process/IHttpRunner.h"

$PackageWebCoreBegin

IHttpProcesser::IHttpProcesser(qintptr handle)
    :handle(handle)
{
}

// TODO: 刚刚看了一下，如果要实现 长连接，下面的模型需要再分离， 即把 socket 的输入输出和 处理函数函数分离，
void IHttpProcesser::run()
{
    socket = ISocketUtil::createTcpSocket(handle);
    if(!socket->waitForReadyRead()){        // TODO: 这里使用 epoll 后可以省略.
        return ISocketUtil::processReadError(&socket);
    }

    IRequest request(socket);
    IResponse response(&request);

    if(!request.valid()){
        response.respond();
        return;
    }

    do {
        if( IControllerManage::preIntercept(request, response)){
            break;
        }
        IControllerManage::preProcess(request, response);

        IHttpRunner::handleRequest(request, response);

        if(IControllerManage::postIntercept(request, response)){
            break;
        }
        IControllerManage::postProcess(request, response);

        // 拦截 socket
        if(!response.valid() || response.status() != IHttpStatus::OK_200){
            if(IHttpSocketManage::interceptStatusCode(request, response)){
                break;
            }
        }

    } while(0);

    // 响应
    if(!response.respond()){
        return ISocketUtil::handleInternalError(&socket);
    }
    ISocketUtil::closeTcpSocket(&socket);
}


$PackageWebCoreEnd

