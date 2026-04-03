#include <immintrin.h>

// 一次处理16个n值（AVX2）
void dual_mod_avx2(uint32_t* n_values, uint32_t* num_out, uint32_t* den_out,
                   uint32_t a, uint32_t b, int count) {
    // 假设 a=16, b=32 (2的幂)
    __m256i n_vec = _mm256_loadu_si256((__m256i*)n_values);
    __m256i a_mask = _mm256_set1_epi32(a - 1);  // 15
    __m256i b_mask = _mm256_set1_epi32(b - 1);  // 31
    __m256i one = _mm256_set1_epi32(1);
    
    // num = ((n-1) & (a-1)) + 1
    __m256i n_minus_1 = _mm256_sub_epi32(n_vec, one);
    __m256i num_tmp = _mm256_and_si256(n_minus_1, a_mask);
    __m256i num = _mm256_add_epi32(num_tmp, one);
    
    // den = ((n-1) & (b-1)) + 1
    __m256i den_tmp = _mm256_and_si256(n_minus_1, b_mask);
    __m256i den = _mm256_add_epi32(den_tmp, one);
    
    _mm256_storeu_si256((__m256i*)num_out, num);
    _mm256_storeu_si256((__m256i*)den_out, den);
}

// AVX-512版本（一次16个，但位宽512位）
#ifdef __AVX512F__
void dual_mod_avx512(uint32_t* n_values, uint32_t* num_out, uint32_t* den_out,
                     uint32_t a, uint32_t b, int count) {
    __m512i n_vec = _mm512_loadu_si512(n_values);
    __m512i a_mask = _mm512_set1_epi32(a - 1);
    __m512i b_mask = _mm512_set1_epi32(b - 1);
    __m512i one = _mm512_set1_epi32(1);
    
    __m512i n_minus_1 = _mm512_sub_epi32(n_vec, one);
    __m512i num = _mm512_add_epi32(_mm512_and_si512(n_minus_1, a_mask), one);
    __m512i den = _mm512_add_epi32(_mm512_and_si512(n_minus_1, b_mask), one);
    
    _mm512_storeu_si512(num_out, num);
    _mm512_storeu_si512(den_out, den);
}
#endif
