#include "IHttpProcesser.h"
#include "IHttpSocketManage.h"
#include "base/ISocketUtil.h"
#include "base/ITicTacUtil.h"
#include "common/net/IRequest.h"
#include "common/net/IResponse.h"

$PackageWebCoreBegin

//namespace IHttpProcessorHelper{
//    bool preIntercept(IRequest& request, IResponse& response);
//    bool preProcess(IRequest& request, IResponse& repsonse);

//    bool postProcess(IRequest& request, IResponse& response);
//    bool postIntercept(IRequest& request, IResponse& response);
//}

IHttpProcesser::IHttpProcesser(qintptr handle)
    :handle(handle)
{
}

// TODO: 刚刚看了一下，如果要实现 长连接，下面的模型需要再分离， 即把 socket 的输入输出和 处理函数函数分离，
// 可以考虑使用异步处理
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
        // 再拦截请求，比如说静态路由
        if( IHttpSocketManage::preIntercept(request, response)){
            break;
        }

        // 预处理请求.
        IHttpSocketManage::preProcess(request, response);

        // 调用函数处理代码
        IHttpSocketManage::handleRequest(request, response);

        // 后 自定义拦截
        if(IHttpSocketManage::postIntercept(request, response)){       // "current response is been post intercepted";
            break;
        }

        // 拦截 socket
        if(!response.valid() || response.status() != IHttpStatus::OK_200){
            if(IHttpSocketManage::interceptStatusCode(request, response)){
                break;
            }
        }

        // 后处理请求
        IHttpSocketManage::postProcess(request, response);
    } while(0);

    // 响应
    if(!response.respond()){
        return ISocketUtil::handleInternalError(&socket);
    }
    ISocketUtil::closeTcpSocket(&socket);
}

bool IHttpProcesser::isSocketAlive(IRequest &request)
{
    Q_UNUSED(request)
    return false;
}


$PackageWebCoreEnd

