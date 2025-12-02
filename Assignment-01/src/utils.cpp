#include "utils.h"
int indexof(int value, int *array, int length)
{
    for (int i = 0; i < length; i++)
    {
        if (array[i] == value)
            return i;
    }
    return -1;
}