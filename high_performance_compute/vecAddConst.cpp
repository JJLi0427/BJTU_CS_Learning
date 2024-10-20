#include <stdio.h>
#include "arm_neon.h"
void add3 (uint8x16_t *data){
    uint8x16_t three = vmovq_n_u8(3);
    *data = vaddq_u8(*data, three);
}

void print_uint8(uint8x16_t data, char* name){
    int i;
    static uint8_t p[16];
    vst1q_u8(p, data);
    printf("%s = ", name);
    for(i = 0; i < 16; i++) printf("%02d ", p[i]);
    printf("\n");
}

int main(){
    const uint8_t uint8_data[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    uint8x16_t data;
    data = vld1q_u8(uint8_data);
    print_uint8(data, "data");
    add3(&data);
    print_uint8(data, "data(new)");
    return 0;
}