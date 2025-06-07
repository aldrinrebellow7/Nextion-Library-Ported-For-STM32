/*
 * NexPage.h
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#ifndef __NEXPAGE_H__
#define __NEXPAGE_H__

#include "NexTouch.h"
#include "NexHardware.h"
/**
 * @addtogroup Component
 * @{
 */

/**
 * A special component , which can contain other components such as NexButton,
 * NexText and NexWaveform, etc.
 */
class NexPage: public NexTouch
{
public: /* methods */
    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name);
     */
    NexPage(uint8_t pid, uint8_t cid, const char *name);

    /**
     * Show itself.
     *
     * @return true if success, false for faileure.
     */
    bool show(void);
    void DrawLine(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour);
    void DrawReactange(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour);
    void FillRectangle(uint16_t X1 , uint16_t Y1 , uint16_t X2 , uint16_t Y2 , uint32_t Colour);
    void FilledCircle(uint16_t X1 , uint16_t Y1 , uint16_t radius, uint32_t Colour);
};
/**
 * @}
 */

#endif /* #ifndef __NEXPAGE_H__ */
