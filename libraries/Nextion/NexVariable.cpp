/*
 * NexVariable.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexVariable.h"
#include <string>

NexVariable::NexVariable(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

uint32_t NexVariable::getValue(uint32_t *number)
{
    std::string cmd = "get ";
    cmd += getObjName();
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexVariable::setValue(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;

    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".val=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexVariable::getText(char *buffer, uint32_t len)
{
    std::string cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

bool NexVariable::setText(const char *buffer)
{
    std::string cmd;
    cmd += getObjName();
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}



