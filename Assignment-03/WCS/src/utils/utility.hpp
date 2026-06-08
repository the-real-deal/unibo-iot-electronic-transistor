#pragma once
#include <Arduino.h>

bool isInteger(const String &s)
{
    if (s.length() == 0)
        return false;
    int start = (s[0] == '-') ? 1 : 0;
    if (start == 1 && s.length() == 1)
        return false; // just a minus sign
    for (unsigned int i = start; i < s.length(); i++)
    {
        if (!isDigit(s[i]))
            return false;
    }
    return true;
}