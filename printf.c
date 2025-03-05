/* printf implementation */
#include <unistd.h>


char *chardup(const char s)
{
        static char buf[2];
        char *p;

        p = buf;
        *p++ = s;
        *p-- = 0;

        return buf;
}

unsigned int strlen(const char *str)
{
        unsigned int n;
        const char *p;

        for(p = str, n = 0; *p; *p++, n++);

        return n;
}

int puts(const char *str)
{
        unsigned int n;

        n = strlen(str);
        if(n < 1) return -1;

        return write(1, str, n);
}

int main()
{
        puts("hello  world\n");

        return 0;
}