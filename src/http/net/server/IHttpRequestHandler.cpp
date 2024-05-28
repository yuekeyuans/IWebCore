#include "IHttpRequestHandler.h"
#include "http/net/IRequest.h"
#include "http/net/IResponse.h"
#include "http/invalid/IHttpInvalidManage.h"
#include "http/net/server/IHttpConnection.h"

$PackageWebCoreBegin

IHttpRequestHandler::IHttpRequestHandler()
{

}

void IHttpRequestHandler::handle(IRequest &request)
{
    IResponse response(&request);
    do{
        if(request.valid()){
            break;
        }

        handleRequest(request, response);
        if(!request.valid()){
            break;
        }
    }while(0);

    if(!request.valid()){
        auto process = IHttpInvalidManage::instance()->getWare(request.getRaw()->m_responseRaw->content.contentInvalid.tag);
        process->process(request, response);
    }
    request.m_connection->doWrite();
}

void IHttpRequestHandler::handleRequest(IRequest &request, IResponse &response)
{

}

$PackageWebCoreEnd
