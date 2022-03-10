#include "PostInterceptorTest.h"

PostInterceptorTest::PostInterceptorTest()
{
}

QString PostInterceptorTest::name()
{

}

bool PostInterceptorTest::match(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)

    return true;
}

bool PostInterceptorTest::action(IRequest &request, IResponse &response)
{
    Q_UNUSED(request)
    Q_UNUSED(response)

    return true;
}
