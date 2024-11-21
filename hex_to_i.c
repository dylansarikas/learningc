int htoi(s) /* convert h to integer */
char s[];
{
    int i, n, digit, total, power;

    total = 0;
    power = 0;
    for (i = (strlen(s) - 1); i >= 0; i--) {
        switch (s[i]) {
        case 'A':
            digit = 10;
            break;
        case 'a':
            digit = 10;
            break;
        case 'B':
            digit = 11;
            break;
        case 'b':
            digit = 11;
            break;
        case 'C':
            digit = 12;
            break;
        case 'c':
            digit = 12;
            break;
        case 'D':
            digit = 13;
            break;
        case 'd':
            digit = 13;
            break;
        case 'E':
            digit = 14;
            break;
        case 'e':
            digit = 14;
            break;
        case 'F':
            digit = 15;
            break;
        case 'f':
            digit = 15;
            break;
        default:
            digit = s[i] - 48; /*  -48 because ASCII 48 == 0 */
        }

        total = total + (digit * (pow(16, power)));
        power++;  
    }      
  		
    return(total);
}