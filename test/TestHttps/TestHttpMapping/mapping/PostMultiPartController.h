#pragma once

#include <IWebCore>

// test multipart transmission
class PostMultiPartController : public IControllerInterface<PostMultiPartController>
{
    Q_GADGET
    $AsController(PostMultiPartController)

public:
    PostMultiPartController();

    $PostMapping(fun1, /multipart1)
    QString fun1(IMultiPart name);

    $PostMapping(fun2, /multipart2)
    QString fun2(IMultiPart name);

    $PostMapping(fun3, /multipart3)
    QString fun3(IMultiPart name);

    $PostMapping(funMultiPart, /multipart4)
    QString funMultiPart(IMultiPart name);

    $PostMapping(funMultiPartRef, /multipart5)
    QString funMultiPartRef(IMultiPart& name);
};
