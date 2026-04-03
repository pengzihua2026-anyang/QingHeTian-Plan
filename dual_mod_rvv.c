#include <riscv_vector.h>

void dual_mod_rvv(uint32_t* n_values, uint32_t* num_out, uint32_t* den_out,
                  uint32_t a, uint32_t b, size_t count) {
    size_t vl;
    vuint32m8_t n_vec, n_minus_1, num, den;
    vuint32m8_t a_mask = vmv_v_x_u32m8(a - 1, count);
    vuint32m8_t b_mask = vmv_v_x_u32m8(b - 1, count);
    vuint32m8_t one = vmv_v_x_u32m8(1, count);
    
    for (size_t i = 0; i < count; i += vl) {
        vl = vsetvl_e32m8(count - i);
        n_vec = vle32_v_u32m8(&n_values[i], vl);
        n_minus_1 = vsub_vv_u32m8(n_vec, one, vl);
        num = vadd_vv_u32m8(vand_vv_u32m8(n_minus_1, a_mask, vl), one, vl);
        den = vadd_vv_u32m8(vand_vv_u32m8(n_minus_1, b_mask, vl), one, vl);
        vse32_v_u32m8(&num_out[i], num, vl);
        vse32_v_u32m8(&den_out[i], den, vl);
    }
}
