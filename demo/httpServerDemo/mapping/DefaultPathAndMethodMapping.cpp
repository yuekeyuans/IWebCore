#include "DefaultPathAndMethodMapping.h"

DefaultPathAndMethodMapping::DefaultPathAndMethodMapping()
{
    $ConstructController
}

QString DefaultPathAndMethodMapping::get()
{
    return "hello world get";
}

QString DefaultPathAndMethodMapping::post()
{
    return "hello world post";
}

QString DefaultPathAndMethodMapping::put()
{
    return "hello world put";
}

QString DefaultPathAndMethodMapping::deletes()
{
    return "hello world delete";
}
