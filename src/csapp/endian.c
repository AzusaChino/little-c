#include <stdio.h>

int is_little_endian(void)
{
    union w
    {
        int a;
        char b;
    } c;
    c.a = 1;
    return (c.b == 1); // 小端返回TRUE,大端返回FALSE
}

int main(int argc, char *argv[])
{
    if (is_little_endian())
        printf("Little Endian\n");
    return 0;
}