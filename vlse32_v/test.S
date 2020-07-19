    .global     copy_data_ustride_vec
# void copy_data_ustride_vec(int32_t *dest_data, int32_t *source_data, int32_t stride, int data_num);
# a0=dest, a1=src, a2=stride, a3=data_num
#
copy_data_ustride_vec:
_loop:
    vsetvli     t0, a3, e32,m1  # Vectors of 8b
    slli        t2, t0, 2       # add step for 32-bit
    mul         t1, t0, a2      # define step
    vlse32.v    v1, (a1), a2    # Load bytes
    add         a1, a1, t1  	# Bump pointer
    sub         a3, a3, t0  	# Decrement count
    vse32.v     v1, (a0)     	# Store bytes
    add         a0, a0, t2  	# Bump pointer
    bnez        a3, _loop    	# Any more?
    ret                      	# Return
