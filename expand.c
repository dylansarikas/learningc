void expand(s, t)
char s[], t[];
{
    int i, j;
    for(i=0, j=0; s[i]; i++) {
        switch (s[i]) {
        case '\n':
            s[i] = 'n';
            t[j] = '\\';
            j++;
            break;
        case '\t':
            s[i] = 't';
            t[j] = '\\';
            j++;
            break;
        }
        t[j++] = s[i];
    }
    t[j] = '\0';
}