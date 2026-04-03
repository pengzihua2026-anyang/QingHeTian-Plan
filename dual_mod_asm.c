// x86-64 内联汇编，一次计算一对
static inline void dual_mod_asm(uint64_t n, uint32_t a, uint32_t b,
                                 uint32_t* num, uint32_t* den) {
    __asm__ volatile(
        "lea    -0x1(%[n]), %%rax\n\t"     // rax = n-1
        "xor    %%edx, %%edx\n\t"
        "div    %[a]\n\t"                  // edx = (n-1) % a
        "inc    %%edx\n\t"
        "mov    %%edx, %[num]\n\t"
        
        "mov    %%rax, %%rcx\n\t"          // 恢复 n-1
        "xor    %%edx, %%edx\n\t"
        "div    %[b]\n\t"                  // edx = (n-1) % b
        "inc    %%edx\n\t"
        "mov    %%edx, %[den]\n\t"
        : [num] "=m" (*num), [den] "=m" (*den)
        : [n] "r" (n), [a] "r" (a), [b] "r" (b)
        : "rax", "rcx", "rdx"
    );
}

// 当a/b是2的幂时的超级优化版本（无除法）
static inline void dual_mod_pow2_asm(uint64_t n, uint32_t a_log2, uint32_t b_log2,
                                      uint32_t* num, uint32_t* den) {
    uint32_t a_mask = (1 << a_log2) - 1;
    uint32_t b_mask = (1 << b_log2) - 1;
    
    __asm__ volatile(
        "mov    %[n], %%rax\n\t"
        "dec    %%rax\n\t"
        "and    %[a_mask], %%eax\n\t"
        "inc    %%eax\n\t"
        "mov    %%eax, %[num]\n\t"
        
        "mov    %[n], %%rax\n\t"
        "dec    %%rax\n\t"
        "and    %[b_mask], %%eax\n\t"
        "inc    %%eax\n\t"
        "mov    %%eax, %[den]\n\t"
        : [num] "=m" (*num), [den] "=m" (*den)
        : [n] "r" (n), [a_mask] "r" (a_mask), [b_mask] "r" (b_mask)
        : "rax"
    );
}
