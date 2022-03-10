#pragma once

#include <IWebCore>

class PostInterceptorTest : public IPostInterceptorInterface<PostInterceptorTest>
{
    $AsMiddleWare(PostInterceptorTest)
public:
    PostInterceptorTest();

    virtual bool match(IRequest& request, IResponse& response) final;
    virtual bool action(IRequest& request, IResponse& response) final;
};
