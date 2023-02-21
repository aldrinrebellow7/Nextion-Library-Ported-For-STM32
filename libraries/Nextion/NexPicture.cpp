/*
 * NexPicture.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexPicture.h"
#include <string>

NexPicture::NexPicture(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

bool NexPicture::Get_background_image_pic(uint32_t *number)
{
    std::string cmd = "get ";
    cmd += getObjName();
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexPicture::Set_background_image_pic(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;

    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".pic=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexPicture::getPic(uint32_t *number)
{
    std::string cmd = "get ";
    cmd += getObjName();
    cmd += ".pic";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexPicture::setPic(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;

    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".pic=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}




