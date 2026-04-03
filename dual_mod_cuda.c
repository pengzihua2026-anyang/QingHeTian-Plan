__global__ void dual_mod_cuda(uint32_t* n_values, uint32_t* num_out,
                              uint32_t* den_out, uint32_t a, uint32_t b,
                              size_t count) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < count) {
        uint32_t n = n_values[idx];
        // 当a和b是2的幂时，编译器会自动优化为位运算
        num_out[idx] = ((n - 1) % a) + 1;
        den_out[idx] = ((n - 1) % b) + 1;
    }
}
