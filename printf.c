/****************************************************************
 * @Suryakiran164 - 08/03/2025                                  *
 * implementing my own printf function with mininmal options    *
 * Trying not to use any standard C header like stdio or stdlib *
/****************************************************************/

#include <unistd.h>
#include <x86args.h>

#define Wait4char       1
#define Wait4fmt        2

//macros
#define putchar2(x)     write(1, chardup2(x), 1)
#define swapchar(x)     (x+0x30)

//custom malloc() and free() impementation
char *malloc2(unsigned int size)
{
        _alloc += size;
        return sbrk(size);
}

void freeall(unsigned int size)
{
        sbrk(-(size));
        _alloc -= size;
}

typedef unsigned char State;
unsigned int _alloc = 0;

//function prototypes
char *chardup2(const char s);
unsigned int strlen2(const char *str);
int puts2(const char *str);
int printf2(const char *fmt, ...);
char *itoa2(int n);
int main(void);

//chardup: converts a single character to a string i.e, a -> ['a','\0']
char *chardup2(const char s)
{
        static char buf[2];
        char *p;

        p = buf;
        *p++ = s;
        *p-- = 0;

        return buf;
}

//custom function to calculate length of given string
unsigned int strlen2(const char *str)
{
        unsigned int n;
        const char *p;

        for(p = str, n = 0; *p; *p++, n++);

        return n;
}

//puts2: prints given string on to screen
int puts2(const char *str)
{
        unsigned int n;

        n = strlen2(str);
        if(n < 1) return -1;

        return write(1, str, n);        //write(file_stream_code, pointer_to_string_to_write, length_of_string);
}

//custom printf implementation with minimal error handling and utilities
int printf2(const char *fmt, ...)
{
        unsigned int *p;
        State s;
        const char *f;

        Args(p);
        s = Wait4char;
        f = fmt;

        do
        {
                if(s & Wait4char)
                {
                        switch(*f)
                        {
                                case '%':
                                        s = Wait4fmt;
                                        break;

                                default:
                                        putchar2(*f);

                        }

                }
                else if(s & Wait4fmt)
                {
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
                }
        } while (*(f++));

        return 0;
}

//itoa2: converts given number into string and returns it
char * itoa2(int n)
{
        unsigned int x, y;
        unsigned char *xs, *p;
        static char ret[10];

        y = n;
        xs = malloc2(10);
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

        freeall(10);

        return ret;
}

//main: all test cases here!
int main()
{
        int x;

        x = 5090;
        printf2("Interger display: %d\n", x);           //integer

        char c;
        c = 'X';
        char *p;
        p = "SK";
        printf2("Welcome :%s, you wrote:%c\n", p, c);   //character and string

        printf2("An empty %%? Did it print ?\n");       //empty &


        return 0;
}