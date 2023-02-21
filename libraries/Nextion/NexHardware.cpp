/*
 * NexHardware.cpp
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#include "NexHardware.h"

#include <string.h>

#define NEX_RET_CMD_FINISHED            (0x01)
#define NEX_RET_EVENT_LAUNCHED          (0x88)
#define NEX_RET_EVENT_UPGRADED          (0x89)
#define NEX_RET_EVENT_TOUCH_HEAD            (0x65)
#define NEX_RET_EVENT_POSITION_HEAD         (0x67)
#define NEX_RET_EVENT_SLEEP_POSITION_HEAD   (0x68)
#define NEX_RET_CURRENT_PAGE_ID_HEAD        (0x66)
#define NEX_RET_STRING_HEAD                 (0x70)
#define NEX_RET_NUMBER_HEAD                 (0x71)
#define NEX_RET_INVALID_CMD             (0x00)
#define NEX_RET_INVALID_COMPONENT_ID    (0x02)
#define NEX_RET_INVALID_PAGE_ID         (0x03)
#define NEX_RET_INVALID_PICTURE_ID      (0x04)
#define NEX_RET_INVALID_FONT_ID         (0x05)
#define NEX_RET_INVALID_BAUD            (0x11)
#define NEX_RET_INVALID_VARIABLE        (0x1A)
#define NEX_RET_INVALID_OPERATION       (0x1B)

UART_HandleTypeDef *huart_disp;
static uint8_t FF_DATA = 0xFF;
/*
 * Receive uint32_t data.
 *
 * @param number - save uint32_t data.
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed.
 *
 */
bool recvRetNumber(uint32_t *number, uint32_t timeout)
{
    bool ret = false;
    uint8_t temp[8] = {0};

    if (!number)
    {
        goto __return;
    }

	if (HAL_OK !=  HAL_UART_Receive(huart_disp, temp, sizeof(temp), timeout))
    {
        goto __return;
    }

    if (temp[0] == NEX_RET_NUMBER_HEAD
        && temp[5] == 0xFF
        && temp[6] == 0xFF
        && temp[7] == 0xFF
        )
    {
        *number = ((uint32_t)temp[4] << 24) | ((uint32_t)temp[3] << 16) | (temp[2] << 8) | (temp[1]);
        ret = true;
    }

__return:

    if (ret)
    {
        dbSerialPrint("recvRetNumber :");
        dbSerialPrintln(*number);
    }
    else
    {
        dbSerialPrintln("recvRetNumber err");
    }

    return ret;
}


/*
 * Receive string data.
 *
 * @param buffer - save string data.
 * @param len - string buffer length.
 * @param timeout - set timeout time.
 *
 * @return the length of string buffer.
 *
 */
uint16_t recvRetString(char *buffer, uint16_t len, uint32_t timeout)
{
    uint16_t ret = 0;
    bool str_start_flag = false;
    uint8_t cnt_0xff = 0;
    char temp[50] = {0};
    const char c = 0;
    long start;

    if (!buffer || len == 0)
    {
        goto __return;
    }

    start = HAL_GetTick();
    while(HAL_GetTick() - start <= timeout)
    {
    	while (__HAL_UART_GET_FLAG(huart_disp, UART_FLAG_RXNE) == SET)
    	{
        	 HAL_UART_Receive(huart_disp, (uint8_t *)&c, sizeof(c), timeout);
            if (str_start_flag)
            {
                if (0xFF == c)
                {
                    cnt_0xff++;
                    if (cnt_0xff >= 3)
                    {
                        break;
                    }
                }
                else
                {
                	strcat(temp, &c);
                }
            }
            else if (NEX_RET_STRING_HEAD == c)
            {
                str_start_flag = true;
            }
        }

        if (cnt_0xff >= 3)
        {
            break;
        }
    }
    strncat(temp, "\\0", 1);
    ret = strlen(temp);
    ret = ret > len ? len : ret;
    strncpy(buffer, temp, ret);

__return:

    dbSerialPrint("recvRetString[");
    dbSerialPrint(temp.length());
    dbSerialPrint(",");
    dbSerialPrint(temp);
    dbSerialPrintln("]");

    return ret;
}

/*
 * Send command to Nextion.
 *
 * @param cmd - the string of command.
 */
void sendCommand(const char* cmd)
{
	while (__HAL_UART_GET_FLAG(huart_disp, UART_FLAG_RXNE) == SET)
	{
	    uint8_t tmp = (uint8_t)(huart_disp->Instance->DR & (uint8_t)0x00FF);
	    (void) tmp;
	}

	HAL_UART_Transmit(huart_disp, (const uint8_t*)cmd, strlen(cmd), 1000);
    HAL_UART_Transmit(huart_disp, &FF_DATA, 1, 1000);
    HAL_UART_Transmit(huart_disp, &FF_DATA, 1, 1000);
    HAL_UART_Transmit(huart_disp, &FF_DATA, 1, 1000);
}


/*
 * Command is executed successfully.
 *
 * @param timeout - set timeout time.
 *
 * @retval true - success.
 * @retval false - failed.
 *
 */
bool recvRetCommandFinished(uint32_t timeout)
{
    bool ret = false;
    uint8_t temp[4] = {0};

	if (HAL_OK !=  HAL_UART_Receive(huart_disp, temp, sizeof(temp), timeout))
	{
		ret = false;
	}

    if (temp[0] == NEX_RET_CMD_FINISHED
        && temp[1] == 0xFF
        && temp[2] == 0xFF
        && temp[3] == 0xFF
        )
    {
        ret = true;
    }

    if (ret)
    {
        dbSerialPrintln("recvRetCommandFinished ok");
    }
    else
    {
        dbSerialPrintln("recvRetCommandFinished err");
    }

    return ret;
}


bool nexInit(UART_HandleTypeDef *huart, uint32_t baudrate)
{
	huart_disp = huart;
    bool ret1 = false;
    bool ret2 = false;


    huart_disp->Init.BaudRate = baudrate;
    if (HAL_UART_Init(huart_disp) != HAL_OK)
    {
      Error_Handler();
    }

//    dbSerialBegin(9600);
    sendCommand("");
    sendCommand("bkcmd=1");
    ret1 = recvRetCommandFinished();
    sendCommand("page 0");
    ret2 = recvRetCommandFinished();
    return ret1 && ret2;
}

void nexLoop(NexTouch *nex_listen_list[])
{
    static uint8_t __buffer[10];

    uint16_t i;
    uint8_t c;

	while (__HAL_UART_GET_FLAG(huart_disp, UART_FLAG_RXNE) == SET)
	{
        HAL_Delay(10);
        HAL_UART_Receive(huart_disp, (uint8_t *)&c, sizeof(c), 1000);

        if (NEX_RET_EVENT_TOUCH_HEAD == c)
        {
        	if (huart_disp->RxXferCount >= 6)
            {
                __buffer[0] = c;
                for (i = 1; i < 7; i++)
                {
                    HAL_UART_Receive(huart_disp, (uint8_t *)&__buffer[i], sizeof(__buffer[i]), 1000);

                }
                __buffer[i] = 0x00;

                if (0xFF == __buffer[4] && 0xFF == __buffer[5] && 0xFF == __buffer[6])
                {
                    NexTouch::iterate(nex_listen_list, __buffer[1], __buffer[2], (int32_t)__buffer[3]);
                }

            }
        }
    }
}


