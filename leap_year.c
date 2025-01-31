#include <stdbool.h>

bool leap_year(int year)
{
    bool ans;
    ans = false;
    if (year % 4 == 0){
        ans = true;
        if (year % 100 == 0 && !(year % 400 == 0)){
            ans = false;
        }
    }
    return ans;
}