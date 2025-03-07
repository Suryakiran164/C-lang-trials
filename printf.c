/* printf2 implementation */
#include <unistd.h>
#include <x86args.h>

#define putchar2(x)     write(1, chardup2(x), 1)
#define Wait4char      1 // 00 01
#define Wait4fmt       2 // 00 01

typedef unsigned char State;

char *chardup2(const char s)
{
        static char buf[2];
        char *p;

        p = buf;
        *p++ = s;
        *p-- = 0;

        return buf;
}

unsigned int strlen2(const char *str)
{
        unsigned int n;
        const char *p;

        for(p = str, n = 0; *p; *p++, n++);

        return n;
}

int puts2(const char *str)
{
        unsigned int n;

        n = strlen2(str);
        if(n < 1) return -1;

        return write(1, str, n);        //write(file_stream_code, pointer_to_string_to_write, length_of_string);
}

int printf2(const char *fmt, ...)
{
        unsigned int *p;
        State s;
        const chat *f;

        Args(p);
        s = Wait4char;
        f = fmt;

        do
                if( s & Wait4char)
                        switch(*f)
                        {
                                case '%':
                                        s = Wait4fmt;
                                        break;

                                case 10:
                                case 13:
                                        if ((*(f+1) == 10) || (*(f+1) == 13)) f++;
                                        putchar2(10);
                                        break;

                                default:
                                        putchar2(*f);

                        }
                else if(s & Wait4fmt)
                        switch(*f)
                        {
                                case '%':
                                        putchar2(*f);
                                        s = Wait4cahr;
                                        break;

                                default:
                                        s = Wait4char;
                                        break;
                        }
        while (*(f++));

        return 0;
}








int main()
{
        printf2("Hello world\n");

        return 0;
}