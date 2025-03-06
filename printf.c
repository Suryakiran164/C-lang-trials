/* printf implementation */
#include <unistd.h>
#include <x86args.h>

#define putchar(x)     write(1, chardup(x), 1)

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

int printf(const char *fmt, ...)
{
        unsigned int *p;
        Args(p);

        puts((unsigned char *)*p);
        p += 4;
        puts((unsigned char *)*p);

        return;
}








int main()
{
        printf("%s\n", "SK 1\n");

        return 0;
}