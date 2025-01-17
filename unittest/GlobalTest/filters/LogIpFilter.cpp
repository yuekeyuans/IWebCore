#include "LogIpFilter.h"

bool LogIpFilter::filter(const asio::ip::tcp::socket &socket)
{
    qDebug() << "connect: " << QString::fromStdString(socket.remote_endpoint().address().to_string());
    return true;
}
