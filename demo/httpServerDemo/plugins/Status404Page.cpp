#include "Status404Page.h"
#include "common/IResponse.h"

Status404Page::Status404Page() : IStatusPageInterface()
{

}

bool Status404Page::isMatch(IHttpStatus status)
{
    if(status == IHttpStatus::NOT_FOND_404){
        return true;
    }
    return false;
}

void Status404Page::respond(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    response.setContent("not found");

    response.write(genFirstLine(response));
    response.write(getHeadersContent(response));
    response.write("\r\n");
    response.write(response.content());
    response.flush();
}

