#include "NotFoundInvalidHandler.h"

NotFoundInvalidHandler::NotFoundInvalidHandler()
{
    qDebug() << "invokeddddddd";
}

void NotFoundInvalidHandler::handle(IRequest &) const
{
    qDebug() << "run here";
}
