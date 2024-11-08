#include "NotFoundInvalidHandler.h"

NotFoundInvalidHandler::NotFoundInvalidHandler()
{
}

void NotFoundInvalidHandler::handle(IRequest &) const
{
    qDebug() << "run here";
}
