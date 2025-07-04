/*
 * NexButton.h
 *
 *  Created on: Jan 28, 2023
 *      Author: Alvin
 */

#ifndef __NEXBUTTON_H__
#define __NEXBUTTON_H__
#include <string>
#include "NexTouch.h"
#include "NexHardware.h"
/**
 * @addtogroup Component
 * @{
 */
#define ALPHA_MEDIUM 	(80)
#define ALPHA_LOW 		(0)
/**
 * NexButton component.
 *
 * Commonly, you want to do something after push and pop it. It is recommanded that only
 * call @ref NexTouch::attachPop to satisfy your purpose.
 *
 * @warning Please do not call @ref NexTouch::attachPush on this component, even though you can.
 */
class NexButton: public NexTouch
{
public: /* methods */

    /**
     * @copydoc NexObject::NexObject(uint8_t pid, uint8_t cid, const char *name);
     */
    NexButton(uint8_t pid, uint8_t cid, const char *name);

    /**
     * Get text attribute of component.
     *
     * @param buffer - buffer storing text returned.
     * @param len - length of buffer.
     * @return The real length of text returned.
     */
    uint16_t getText(char *buffer, uint16_t len);

    /**
     * Get text attribute of component.
     *
     * @param number - buffer storing text returned.
     * @return The real length of text returned.
     */
    uint16_t getValue(uint32_t *number);

    /**
     * Set text attribute of component.
     *
     * @param buffer - text buffer terminated with '\0'.
     * @return true if success, false for failure.
     */
    bool setText(const char *buffer);
    bool setCbPath(const char *buffer);
    bool setValue(uint32_t number);
    bool setAlpha(uint32_t number);
    /**
     * Get bco attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_background_color_bco(uint32_t *number);

    /**
     * Set bco attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_background_color_bco(uint32_t number);

    /**
     * Get bco2 attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_press_background_color_bco2(uint32_t *number);

    /**
     * Set bco2 attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_press_background_color_bco2(uint32_t number);

    /**
     * Get pco attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_font_color_pco(uint32_t *number);

    /**
     * Set pco attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_font_color_pco(uint32_t number);

    /**
     * Get pco2 attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_press_font_color_pco2(uint32_t *number);

    /**
     * Set pco2 attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_press_font_color_pco2(uint32_t number);

    /**
     * Get xcen attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_place_xcen(uint32_t *number);

    /**
     * Set xcen attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_place_xcen(uint32_t number);

    /**
     * Get ycen attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_place_ycen(uint32_t *number);

    /**
     * Set ycen attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_place_ycen(uint32_t number);

    /**
     * Get font attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t getFont(uint32_t *number);

    /**
     * Set font attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool setFont(uint32_t number);

    /**
     * Get picc attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_background_cropi_picc(uint32_t *number);

    /**
     * Set picc attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_background_crop_picc(uint32_t number);

    /**
     * Get picc2 attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_press_background_crop_picc2(uint32_t *number);

    /**
     * Set picc2 attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_press_background_crop_picc2(uint32_t number);

    /**
     * Get pic attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_background_image_pic(uint32_t *number);

    /**
     * Set pic attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_background_image_pic(uint32_t number);

    /**
     * Get pic2 attribute of component
     *
     * @param number - buffer storing data return
     * @return the length of the data
     */
    uint32_t Get_press_background_image_pic2(uint32_t *number);

    /**
     * Set pic2 attribute of component
     *
     * @param number - To set up the data
     * @return true if success, false for failure
     */
    bool Set_press_background_image_pic2(uint32_t number);
};
/**
 * @}
 */


#endif /* #ifndef __NEXBUTTON_H__ */
