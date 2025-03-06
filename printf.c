/* printf implementation */
#include <unistd.h>
#include <x86args.h>

#define putchar(x)     write(1, chardup(x), 1)
#define Wait4char      1 // 00 01
#define Wait4fmt       2 // 00 01

typedef unsigned char State;

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

        return write(1, str, n);        //write(file_stream_code, pointer_to_string_to_write, length_of_string);
}

int printf(const char *fmt, ...)
{
        unsigned int *p;
        unsigned char c;
        State s;
        const chat *f;

        Args(p);
        s = Wait4char;
        f = fmt;

        while(*f)
                if( s & Wait4char)
                        switch(*f)
                        {
                                case '%':
                                        s = Wait4fmt;
                                        break;

                                default:
                                        putchar(*f);

                        }
                else if(s & Wait4fmt)
                        switch(*f)
                        {

                        }

        return 0;
}








int main()
{
        printf("%s\n", "SK 1\n");

        return 0;
}