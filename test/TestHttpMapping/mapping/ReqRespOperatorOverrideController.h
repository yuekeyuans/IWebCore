#pragma once

#include <IWebCore>

class ReqRespOperatorOverrideController : public IControllerInterface<ReqRespOperatorOverrideController>
{
    Q_GADGET
    $AsController(ReqRespOperatorOverrideController)
public:
    ReqRespOperatorOverrideController() = default;

    $GetMapping(testResp_getHeader, testRespOverride)
    void testResp_getHeader(IResponse& response);

    $GetMapping(testReq_getHeader, testReqOverride)
    QString testReq_getHeader(IRequest& request);

    $GetMapping(test_respInputOverrid, testRespInputOverride)
    void test_respInputOverrid(IResponse& response);

    $GetMapping(test_respInputRefOverride, testRespInputRefOverride)
    void test_respInputRefOverride(IResponse& response);
};

