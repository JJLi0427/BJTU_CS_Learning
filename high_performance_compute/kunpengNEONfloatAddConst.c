#include <stdio.h>
#include <time.h>
#include "arm_neon.h"
void add3(float32x4_t *data) {
    float32x4_t three = vmovq_n_f32(3.0);
    *data = vaddq_f32(*data, three);
}
void print_float32(float32x4_t data) {
    int i;
    static float32_t p[4];
    vst1q_f32(p, data);
    for (i = 0; i < 4; i++) {
        printf("%f ", p[i]);
    }
}
int main() {
    const float32_t float32_data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0};
    float32_t new_data[16] = {0.0};
    int nSize = sizeof(float32_data) / 4;
    float32x4_t data;
    int k;
    printf("data:");
    for (k = 0; k < nSize; k = k + 4) {
        data = vld1q_f32(float32_data + k);
        print_float32(data);
    }
    printf("\n");
    clock_t start_time = clock();
    for (k = 0; k < nSize; k = k + 4) {
        data = vld1q_f32(float32_data + k);
        add3(&data);
        vst1q_f32(new_data + k, data);
    }
    clock_t end_time = clock();
    printf("data new:");
    for (k = 0; k < nSize; k = k + 4) {
        data = vld1q_f32(new_data + k);
        print_float32(data);
    }
    printf("\n");
    double elapsed_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %lf seconds\n", elapsed_time);
    return 0;
}