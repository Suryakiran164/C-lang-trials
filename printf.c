/****************************************************************/
/* @Suryakiran164 - 08/03/2025                                  */
/* implementing my own printf function with mininmal options    */
/* Trying not to use any standard C header like stdio or stdlib */
/****************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <x86args.h>

#define putchar2(x)     write(1, chardup2(x), 1)
#define swapchar(x)     (x+0x30)

#define Wait4char      1 // 00 01
#define Wait4fmt       2 // 00 01

typedef unsigned char State;

char *chardup2(const char);
unsigned int strlen2(const char *str);
int puts2(const char *str);
int printf2(const char *fmt, ...);
char *itoa2(int n);
int main(void);


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
        const char *f;

        Args(p);
        p++;
        s = Wait4char;
        f = fmt;

        do
                if(s & Wait4char)
                        switch(*f)
                        {
                                case '%':
                                        s = Wait4fmt;
                                        break;

                                default:
                                        putchar2(*f);

                        }

                else if(s & Wait4fmt)
                        switch(*f)
                        {
                                case '%':
                                        putchar2(*f);
                                        s = Wait4char;
                                        break;

                                case 's':
                                        puts2((unsigned char *)*p);
                                        p++;
                                        s = Wait4char;
                                        break;

                                case 'd':
                                        puts2(itoa2((int)*p));
                                        p++;
                                        s = Wait4char;
                                        break;

                                case 'c':
                                        putchar2((unsigned char)*p);
                                        p++;
                                        s = Wait4char;
                                        break;

                                default:
                                        s = Wait4char;
                                        p++;
                                        break;
                        }
        while (*(f++));

        return 0;
}

char * itoa2(int n)
{
        unsigned int x, y;
        unsigned char *xs, *p;
        static char ret[10];

        y = n;
        xs = malloc(10);
        p = xs;

        while(y > 9)
        {
                x = y;
                y = x /10;
                *xs++ = x % 10;

        }
        *xs = y;

        for (x = 0; xs > p; x++, xs--)
                ret[x] = swapchar(*xs);
        ret[x] = swapchar(*xs);

        ret[++x] = 0;

        free(p);

        return ret;
}

int main()
{
        int x;

        x = 5090;
        printf2("Interger display: %d\n", x);

        return 0;
}