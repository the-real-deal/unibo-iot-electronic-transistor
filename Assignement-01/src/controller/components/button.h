#ifndef BUTTON_H
#define BUTTON_H

/*
 * Function that filters button debounce
 * Parameters:
 *  - int i: index of the button
 * Returns:
 *  - bool: true if the button press is valid (not bouncing), false otherwise
 */
bool button_no_bouncing(int i);

#endif