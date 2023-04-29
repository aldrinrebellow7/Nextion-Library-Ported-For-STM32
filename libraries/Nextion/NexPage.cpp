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
    cmd += std::to_string(Pid);
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}
void NexPage::DrawLine(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour)
{
	std::string strCmd = "line " + std::to_string(X1) + ","
								 + std::to_string(Y1) + ","
								 + std::to_string(X2) + ","
								 + std::to_string(Y2) + ","
								 + std::to_string(Colour);//"line 20,30,170,200,BLUE"
	sendCommand(strCmd.c_str());
}

void NexPage::DrawReactange(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour)
{
	std::string strCmd = "draw " + std::to_string(X1) + ","
								 + std::to_string(Y1) + ","
								 + std::to_string(X2) + ","
								 + std::to_string(Y2) + ","
								 + std::to_string(Colour);//"line 20,30,170,200,BLUE"
	sendCommand(strCmd.c_str());
}

void NexPage::FillRectangle(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour)
{
	std::string strCmd = "fill " + std::to_string(X1) + ","
								 + std::to_string(Y1) + ","
								 + std::to_string(X2) + ","
								 + std::to_string(Y2) + ","
								 + std::to_string(Colour);//"line 20,30,170,200,BLUE"
	sendCommand(strCmd.c_str());
}
