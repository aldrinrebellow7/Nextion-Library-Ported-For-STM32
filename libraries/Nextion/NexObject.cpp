/*
 * NexObject.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexObject.h"
#include <string>
#include "main.h"
#include "NexTouch.h"
#include "NexHardware.h"

NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name)
{
    this->__pid = pid;
    this->__cid = cid;
    this->__name = name;
}

uint8_t NexObject::getObjPid(void)
{
    return __pid;
}

uint8_t NexObject::getObjCid(void)
{
    return __cid;
}

const char* NexObject::getObjName(void)
{
    return __name;
}

void NexObject::printObjInfo(void)
{
    dbSerialPrint("[");
    dbSerialPrint((uint32_t)this);
    dbSerialPrint(":");
    dbSerialPrint(__pid);
    dbSerialPrint(",");
    dbSerialPrint(__cid);
    dbSerialPrint(",");
    if (__name)
    {
        dbSerialPrint(__name);
    }
    else
    {
        dbSerialPrint("(null)");
    }
    dbSerialPrintln("]");
}

bool NexObject::setVisible(bool flag)
{
    //const char *name = getObjName();
	uint8_t Cid = getObjCid();
//    if (!Cid)
//    {
//        return false;
//    }
    std::string cmd = std::string("vis ");
    cmd += std::to_string(Cid);
    cmd += ",";
    if (flag) {
        cmd += "1";
    } else {
        cmd += "0";
    }
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}
