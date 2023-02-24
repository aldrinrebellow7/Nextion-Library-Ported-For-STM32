/*
 * NexPage.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexPage.h"
#include <string>

NexPage::NexPage(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

bool NexPage::show(void)
{
	uint8_t Pid = getObjPid();
    if (0 > Pid)
    {
        return false;
    }

    std::string cmd = "page ";
    cmd += (Pid + '0');
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

