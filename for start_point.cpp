//
// Created by milky on 03.07.2020.
//

#include "for start_point.h"
#define getchar()   getc(stdin)
#define putchar(c)  putc((c), stdout)
void kmain(void)
{
    const char *str = "start point";
    char *vidptr = (char*)0xb8000;
    unsigned int i = 0;
    unsigned int j = 0;
    puts("Start point lib-kevi? y/n");
    gets(vidptr);
    if (*vidptr = "y") {
           while (j < 80 * 25 * 2) {
            vidptr[j] = ' ';
            vidptr[j + 1] = 0x07;
            j = j + 2;
        }
        j = 0;
        while (str[j] != '\0') {
            vidptr[i] = str[j];
            vidptr[i + 1] = 0x07;
            ++j;
            i = i + 2;
        }
        else {
           printf("not true")
        }
    }
    return;

}