    .text
    .global     copy_data_vec
# void copy_data_vec(int8_t *dest_data, int8_t *source_data, int data_num);
# a0=dest, a1=src, a2=n
#
copy_data_vec:
    mv      a3, a0          # Copy destination
.loop:
    vsetvli t0, a3, e8,m1   # Vectors of 8b
    vle8.v  v0, (a1)        # Load bytes
    add     a1, a1, t0  	# Bump pointer
    sub     a2, a2, t0  	# Decrement count
    vse8.v  v0, (a3)    	# Store bytes
    add     a3, a3, t0  	# Bump pointer
    bnez    a2, .loop    	# Any more?
    ret                 	# Return


    .global     copy_data_mask_vec
# void copy_data_mask_vec(int8_t *dest_data, int8_t *source_data, int8_t *mask, int data_num);
# a0=dest, a1=src, a2=n
#
copy_data_mask_vec:
    li      t1, 8           # calculate element length of mask, VLEN=512 / ELEN=8 / 8-bit
_loop:
    vsetvli t0, t1, e8,m1   # Vectors of 8b
    vle8.v  v0, (a2)
    add     a2, a2, t0

    vsetvli t0, a3, e8,m1   # Vectors of 8b
    vle8.v  v1, (a1), v0.t  # Load bytes
    add     a1, a1, t0  	# Bump pointer
    sub     a3, a3, t0  	# Decrement count
    vse8.v  v1, (a0), v0.t 	# Store bytes
    add     a0, a0, t0  	# Bump pointer
    bnez    a3, _loop    	# Any more?
    ret                 	# Return
