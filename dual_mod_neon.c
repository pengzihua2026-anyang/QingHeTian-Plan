#include <arm_neon.h>

// NEON 一次处理4个32位整数
void dual_mod_neon(uint32_t* n_values, uint32_t* num_out, uint32_t* den_out,
                   uint32_t a, uint32_t b, int count) {
    uint32x4_t n_vec = vld1q_u32(n_values);
    uint32x4_t a_mask = vdupq_n_u32(a - 1);
    uint32x4_t b_mask = vdupq_n_u32(b - 1);
    uint32x4_t one = vdupq_n_u32(1);
    
    uint32x4_t n_minus_1 = vsubq_u32(n_vec, one);
    uint32x4_t num = vaddq_u32(vandq_u32(n_minus_1, a_mask), one);
    uint32x4_t den = vaddq_u32(vandq_u32(n_minus_1, b_mask), one);
    
    vst1q_u32(num_out, num);
    vst1q_u32(den_out, den);
}
