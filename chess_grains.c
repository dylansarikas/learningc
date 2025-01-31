#include <stdint.h>
#include <math.h>

uint64_t square(uint8_t index)
{
    return pow(2, (index - 1));
}

uint64_t total(void)
{
    uint64_t i, ans=1;
    for (i = 1; i < 65; i++) {
        ans += pow(2, (i - 1));
    }
    return ans-1; 
}
