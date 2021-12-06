#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int MAX_BUFFER_SIZE = 50;

int main()
{
    FILE *fp_h264 = fopen("test.h264", "rb");
    if (fp_h264 == NULL)
    {
        printf("open failed...");
        return -1;
    }
    uint8_t *buf = (uint8_t *)malloc(MAX_BUFFER_SIZE);

    int buf_size = (int)fread(buf, sizeof(uint8_t), MAX_BUFFER_SIZE, fp_h264);

    printf("total size: %d\n", buf_size);
}

int find_na_unit(uint8_t *buff, int buff_size, int *cur_nal_start, int *cur_find_index)
{
    int *i = cur_find_index;
    //( next_bits( 24 ) != 0x000001 && next_bits( 32 ) != 0x00000001 )
    // 寻找起始码，只要有一位不满足，则继续向下寻找
    while (
        (buff[*i] != 0x00 || buff[*i + 1] != 0x00 || buff[*i + 2] != 0x01) &&
        (buff[*i] != 0x00 || buff[*i + 1] != 0x00 || buff[*i + 2] != 0x00 || buff[*i + 3] != 0x01))
    {
        *i = *i + 1;
        if (*i + 3 > buff_size)
        {
            return 0;
        } // 没有找到，退出函数
    }

    // 找到起始码，判断如果不是0x000001，则是0x00000001，则将读取索引加1
    // if( next_bits( 24 ) != 0x000001 )
    if (buff[*i] != 0x00 || buff[*i + 1] != 0x00 || buff[*i + 2] != 0x01)
    {
        *i = *i + 1; // 读取索引加1
    }

    *i += 3; // 读取索引加3
    *cur_nal_start = *i;

    int nalu_buf[sizeof(uint8_t)] = {};

    // 到达nalu部分
    int j = 0;
    // 寻找结尾
    //( next_bits( 24 ) != 0x000000 && next_bits( 24 ) != 0x000001 )
    while (
        (buff[*i] != 0x00 || buff[*i + 1] != 0x00 || buff[*i + 2] != 0x00) &&
        (buff[*i] != 0x00 || buff[*i + 1] != 0x00 || buff[*i + 2] != 0x01))
    {

        nalu_buf[j] = buff[*i]; // 将读取到的nalu存放在全局变量nalu当中
        j++;
        *i = *i + 1;
        if (*i + 3 >= buff_size)
        { // 寻找到文件结尾

            nalu_buf[j] = buff[*i];
            nalu_buf[j + 1] = buff[*i + 1];
            nalu_buf[j + 2] = buff[*i + 2];
            nalu_buf[j + 3] = buff[*i + 3];
            return buff_size - *cur_nal_start;
        }
    }
    return *cur_find_index - *cur_nal_start;
}