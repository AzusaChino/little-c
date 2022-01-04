#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
    size_t i;
    for (i = 0; i < len; ++i)
    {
        printf("%.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x)
{
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
    show_bytes((byte_pointer)&x, sizeof(void *));
}

// win10 64bit
// 39 30 00 00
// 00 e4 40 46
// dc fd 61 00 00 00 00 00
void test_show_bytes(int val)
{
    int i_val = val;
    float f_val = (float)i_val;
    int *p_val = &i_val;
    show_int(i_val);
    show_float(f_val);
    show_pointer(p_val);
}

int main()
{
    printf("Hello C \n");
    // function must be defined before call
    test_show_bytes(12345);
    return 0;
}