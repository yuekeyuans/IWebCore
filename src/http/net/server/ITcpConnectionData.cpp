#include "ITcpConnectionData.h"

$PackageWebCoreBegin

ITcpConnectionData::ITcpConnectionData()
{
    if(m_data){
        totalLength = 1024*10;
        m_data = new char[1024*10];
    }
}

ITcpConnectionData::Data::Data()
{
}

ITcpConnectionData::Data::~Data()
{
    if(m_data){
        delete []m_data;
        m_data = nullptr;
    }
}

void ITcpConnectionData::Data::init()
{
    if(m_data){
        totalLength = 1024*10;
        m_data = new char[1024*10];
    }
}

$PackageWebCoreEnd
