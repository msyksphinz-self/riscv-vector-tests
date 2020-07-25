#include <stdint.h>

extern "C" {
  void sub_data_vec_8 (int8_t  *dest_data, int8_t  src1, int8_t  *src2, int data_num);
  void sub_data_vec_16(int16_t *dest_data, int16_t src1, int16_t *src2, int data_num);
  void sub_data_vec_32(int32_t *dest_data, int32_t src1, int32_t *src2, int data_num);
  void sub_data_vec_64(int64_t *dest_data, int64_t src1, int64_t *src2, int data_num);
};

#include "data.h"

int32_t vec_data[DATA_NUM] = {0};
int32_t scalar_data[DATA_NUM] = {0};

void format_array()
{
  for (int i = 0; i < DATA_NUM; i++) {
    vec_data[i] = 0;
    scalar_data[i] = 0;
  }
}


int check_data (const int64_t *vec_data, const int64_t *scalar_data, const int data_num)
{
  for(int i = 0; i < data_num; i++) {
    if(vec_data[i] != scalar_data[i]) {
      return i + 1;
    }
  }
  return 0;
}


template <typename T>
void sub_data_scalar(T *dest_data, T src1, T *src2, const int data_num)
{
  for (int i = 0; i < data_num; i++) {
    dest_data[i] = src2[i] - src1;
  }
}


void sub_data_mask_scalar(int8_t *dest_data, int8_t *src1, int8_t *src2, int8_t *mask, const int data_num)
{
  for (int i = 0; i < data_num; i++) {
    dest_data[i] = ((mask[i/8] >> (i%8)) & 0x1) ? src1[i] + src2[i] : 0;
  }
}


int test_8();
int test_16();
int test_32();
int test_64();
// int test_vl();
// int test_mask();

int main()
{
  if (test_8 () != 0) { return 10; }
  if (test_16() != 0) { return 20; }
  if (test_32() != 0) { return 30; }
  if (test_64() != 0) { return 40; }

  // if (test_vl() != 0) {
  //   return 20;
  // }
  // if (test_mask() != 0) {
  //   return 30;
  // }
  return 0;
}


int test_8()
{
  format_array();

  const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int8_t);
  sub_data_vec_8 ((int8_t *)vec_data,    (int8_t)source_data1[0], (int8_t *)source_data2, data_num);
  sub_data_scalar((int8_t *)scalar_data, (int8_t)source_data1[0], (int8_t *)source_data2, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}


int test_16()
{
  format_array();

  const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int16_t);
  sub_data_vec_16((int16_t *)vec_data,    (int16_t)source_data1[0], (int16_t *)source_data2, data_num);
  sub_data_scalar((int16_t *)scalar_data, (int16_t)source_data1[0], (int16_t *)source_data2, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}


int test_32()
{
  format_array();

  const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int32_t);
  sub_data_vec_32((int32_t *)vec_data,    (int32_t)source_data1[0], (int32_t *)source_data2, data_num);
  sub_data_scalar((int32_t *)scalar_data, (int32_t)source_data1[0], (int32_t *)source_data2, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}


int test_64()
{
  format_array();

  const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int64_t);
  sub_data_vec_64((int64_t *)vec_data,    (int64_t)source_data1[0], (int64_t *)source_data2, data_num);
  sub_data_scalar((int64_t *)scalar_data, (int64_t)source_data1[0], (int64_t *)source_data2, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}

// int test_vl()
// {
//   format_array();
//
//   const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int8_t) - 10;
//   sub_data_vec   ((int8_t *)vec_data,    (int8_t *)source_data, data_num);
//   sub_data_scalar((int8_t *)scalar_data, (int8_t *)source_data, data_num);
//
//   return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
// }
//
// int test_mask()
// {
//   format_array();
//
//   const int data_num = DATA_NUM * sizeof(int32_t) / sizeof(int8_t);
//   sub_data_mask_vec((int8_t *)vec_data,    (int8_t *)source_data, (int8_t *)mask_data, data_num);
//   sub_data_mask_scalar ((int8_t *)scalar_data, (int8_t *)source_data, (int8_t *)mask_data, data_num);
//
//   return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
// }
