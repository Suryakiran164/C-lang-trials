/* XOR Encryptor and Decryptor tool written in C language */
#include <stdio.h>
#include <string.h>

void readInput(char *ipfile, char *key);
int encrypt(char *ipfile, char *key);

void readInput(char *ipfile, char *key)
{
        printf("Enter the file name to Encypt: ");
        scanf(" %255s", ipfile);

        if((fopen(ipfile, "r")) == NULL)
        {
                printf("File not found\n");
                return;
        }

        printf("Enter secret key: ");
        scanf(" %255s", key);
}

int encrypt(char *ipfile, char *key)
{
        FILE *to_encrypt = fopen(ipfile, "r");
        char opfile[256];

        printf("Enter name to save encrypted file: ");
        scanf(" %255s", opfile);

        FILE *encrypted = fopen(opfile, "w");
        if(encrypted == NULL)
        {
                fclose(to_encrypt);
                return 1;
        }

        char c, temp;
        int i = 0;
        while((c = fgetc(to_encrypt)) != EOF)
        {
                temp = c ^ key[i % strlen(key)];
                fputc(temp, encrypted);
                i++;
        }

        fclose(to_encrypt);
        fclose(encrypted);
        return 0;
}

int main()
{
        char ipfile[256];
        char    key[256];

        readInput(ipfile, key);
        encrypt(ipfile, key);
}
