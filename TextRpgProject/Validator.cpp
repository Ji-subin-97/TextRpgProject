#include "Validator.h"

bool Validator::IsBlank(const string& name)
{
    if (name == "") return true;
    else return false;
}

bool Validator::IsValidLength(const string& name, int min, int max)
{
    int length = (int)name.length();
    if (length >= min && length <= max) return true;
    return false;
}
