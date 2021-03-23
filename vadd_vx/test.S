    .text
    .global     add_data_vec_8
# void add_data_vec_8(int8_t *dest_data, int8_t src1, int8_t *src2, int data_num);
# a0=dest, a1=src1, a2=src2, a3=n
#
add_data_vec_8:
    // mv      a3, a0          # Copy destination
.loop_8:
    vsetvli t0, a3, e8,m1   # Vectors of 8b
    vle8.v  v1, (a2)        # Load bytes
    add     a2, a2, t0  	# Bump pointer
    sub     a3, a3, t0  	# Decrement count
    vadd.vx v2, v1, a1      # Vector Add
    vse8.v  v2, (a0)    	# Store bytes
    add     a0, a0, t0  	# Bump pointer
    bnez    a3, .loop_8    	# Any more?
    ret                 	# Return

    .text
    .global     add_data_vec_16
# void add_data_vec_16(int16_t *dest_data, int16_t src1, int16_t *src2, int data_num);
# a0=dest, a1=src1, a2=src2, a3=n
#
add_data_vec_16:
.loop_16:
    vsetvli t0, a3, e16,m1   # Vectors of 8b
    slli    t1, t0, 1       # shift 1-bit
    vle16.v v1, (a2)        # Load bytes
    add     a2, a2, t1  	# Bump pointer
    sub     a3, a3, t0  	# Decrement count
    vadd.vx v2, v1, a1      # Vector Add
    vse16.v v2, (a0)    	# Store bytes
    add     a0, a0, t1  	# Bump pointer
    bnez    a3, .loop_16   	# Any more?
    ret                 	# Return


    .text
    .global     add_data_vec_32
# void add_data_vec_32(int32_t *dest_data, int32_t src1, int32_t *src2, int data_num);
# a0=dest, a1=src1, a2=src2, a3=n
#
add_data_vec_32:
.loop_32:
    vsetvli t0, a3, e32,m1   # Vectors of 8b
    slli    t1, t0, 2       # shift 2-bit
    vle32.v v1, (a2)        # Load bytes
    add     a2, a2, t1  	# Bump pointer
    sub     a3, a3, t0  	# Decrement count
    vadd.vx v2, v1, a1      # Vector Add
    vse32.v v2, (a0)    	# Store bytes
    add     a0, a0, t1  	# Bump pointer
    bnez    a3, .loop_32   	# Any more?
    ret                 	# Return


    .text
    .global     add_data_vec_64
# void add_data_vec_64(int64_t *dest_data, int64_t src1, int64_t *src2, int data_num);
# a0=dest, a1=src1, a2=src2, a3=n
#
add_data_vec_64:
.loop_64:
    vsetvli t0, a3, e64,m1   # Vectors of 8b
    slli    t1, t0, 3       # shift 3-bit
    vle64.v v1, (a2)        # Load bytes
    add     a2, a2, t1  	# Bump pointer
    sub     a3, a3, t0  	# Decrement count
    vadd.vx v2, v1, a1      # Vector Add
    vse64.v v2, (a0)    	# Store bytes
    add     a0, a0, t1  	# Bump pointer
    bnez    a3, .loop_64   	# Any more?
    ret                 	# Return
