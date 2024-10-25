#include <arm_neon.h>
#include <iostream>

// Example of using ARM NEON for SIMD

void vector_addition(const float* a, const float* b, float* result, int size) {
    for (int i = 0; i < size; i += 4) { // Process 4 floats at a time
        float32x4_t va = vld1q_f32(&a[i]); // Load 4 floats from array a
        float32x4_t vb = vld1q_f32(&b[i]); // Load 4 floats from array b
        float32x4_t vresult = vaddq_f32(va, vb); // Add the vectors
        vst1q_f32(&result[i], vresult); // Store the result
    }
}

int main() {
    float a[4] = {1.0f, 2.0f, 3.0f, 4.0f};
    float b[4] = {5.0f, 6.0f, 7.0f, 8.0f};
    float result[4];

    vector_addition(a, b, result, 4);

    for (int i = 0; i < 4; i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
