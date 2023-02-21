/*
 * NexCheckbox.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexCheckbox.h"
#include <string>

NexCheckbox::NexCheckbox(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

uint32_t NexCheckbox::getValue(uint32_t *number)
{
    std::string cmd = "get ";
    cmd += getObjName();
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexCheckbox::setValue(uint32_t number)
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

uint32_t NexCheckbox::Get_background_color_bco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".bco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexCheckbox::Set_background_color_bco(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;

    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".bco=";
    cmd += buf;
    sendCommand(cmd.c_str());

    cmd="";
    cmd += "ref ";
    cmd += getObjName();
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexCheckbox::Get_font_color_pco(uint32_t *number)
{
    std::string cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".pco";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexCheckbox::Set_font_color_pco(uint32_t number)
{
    char buf[10] = {0};
    std::string cmd;

    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".pco=";
    cmd += buf;
    sendCommand(cmd.c_str());

    cmd = "";
    cmd += "ref ";
    cmd += getObjName();
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}


