#pragma once


class ITcpServerInterface
{
public:
    ITcpServerInterface();

public:
    virtual void accept(qintptr handle) = 0;
};

