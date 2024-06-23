#ifndef DISPLAY_H
#define DISPLAY_H

#include "shop.h"

/*
 * THIS IS A SUGGESTED FUNCTION. IT IS IMPLEMENTED FOR YOU IN
 *		`display.cpp`
 * Name: get_option
 * Description: Prompt the user for their numbered option selection
 * Returns (int): The number associated with the option selected by the user
 */
int get_option();

/*
 * THIS IS A SUGGESTED FUNCTION. IT IS PARTIALLY IMPLEMENTED FOR YOU IN
 *		`display.cpp`.
 * Name: execute_option
 * Description: Execute the option selected by the user
 * parameters:
 *		s (shop&): A reference to the shop object
 *		option (int): The user's selected option to execute. Must be
 *			between 1 and 7 (inclusive).
 */
void execute_option(shop& s, int option);
/*
 * Name: display_shop_info
 * Description: output the shop info to terminal (phone, address)
 * parameters:
 *		s (shop&): A reference to the shop object
 */
void display_shop_info(shop& s);
/*
 * Name: display_menu
 * Description: output the menu to terminal
 * parameters:
 *		s (shop&): A reference to the shop object
 */
void display_menu(shop& s);
/*
 * Name: take_order
 * Description: Execute the option selected by the user
 * parameters:
 *		s (shop&): A reference to the shop object
 *		option (int): The user's selected option to execute. Must be
 *			between 1 and 7 (inclusive).
 */
#endif