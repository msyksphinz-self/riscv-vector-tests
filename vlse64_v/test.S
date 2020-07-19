    .global     copy_data_ustride_vec
# void copy_data_ustride_vec(int64_t *dest_data, int64_t *source_data, int64_t stride, int data_num);
# a0=dest, a1=src, a2=stride, a3=data_num
#
copy_data_ustride_vec:
_loop:
    vsetvli     t0, a3, e64,m1  # Vectors of 8b
    slli        t2, t0, 3       # add step for 8-bit
    mul         t1, t0, a2      # define step
    vlse64.v    v1, (a1), a2    # Load bytes
    add         a1, a1, t1  	# Bump pointer
    sub         a3, a3, t0  	# Decrement count
    vse64.v     v1, (a0)     	# Store bytes
    add         a0, a0, t2  	# Bump pointer
    bnez        a3, _loop    	# Any more?
    ret                     	# Return
