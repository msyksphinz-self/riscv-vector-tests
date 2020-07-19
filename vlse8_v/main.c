#include <stdint.h>

void copy_data_ustride_vec(int8_t *dest_data, int8_t *source_data, int stride, int data_num);

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


void copy_data_scalar(int8_t *dest_data, int8_t *source_data, const int data_num)
{
  for (int i = 0; i < data_num; i++) {
    dest_data[i] = source_data[i];
  }
}


void copy_data_ustride_scalar(int8_t *dest_data, int8_t *source_data, int8_t stride, const int data_num)
{
  for (int i = 0; i < data_num; i++) {
    dest_data[i] = source_data[i*stride];
  }
}


int test_ustride(int stride);
int test_ustride_minus(int stride);

int main()
{
  int result = 0;
  if ((result = test_ustride(1)) != 0) {
    return (result << 8) | 1;
  }
  if ((result = test_ustride(2)) != 0) {
    return (result << 8) | 2;
  }
  if ((result = test_ustride(3)) != 0) {
    return (result << 8) | 3;
  }
  if ((result = test_ustride_minus(-1)) != 0) {
    return (result << 8) | 4;
  }
  if ((result = test_ustride_minus(-2)) != 0) {
    return (result << 8) | 5;
  }
  if ((result = test_ustride_minus(-3)) != 0) {
    return (result << 8) | 6;
  }

  return 0;
}


int test_ustride(int stride)
{
  format_array();

  const int data_num = (DATA_NUM / 4) * sizeof(int32_t) / sizeof(int8_t);
  copy_data_ustride_vec    ((int8_t *)vec_data,    (int8_t *)source_data, stride, data_num);
  copy_data_ustride_scalar ((int8_t *)scalar_data, (int8_t *)source_data, stride, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}


int test_ustride_minus(int stride)
{
  format_array();

  const int data_num = (DATA_NUM / 4) * sizeof(int32_t) / sizeof(int8_t);
  copy_data_ustride_vec    ((int8_t *)vec_data,    (int8_t *)(source_data+DATA_NUM-1), stride, data_num);
  copy_data_ustride_scalar ((int8_t *)scalar_data, (int8_t *)(source_data+DATA_NUM-1), stride, data_num);

  return check_data((int64_t *)vec_data, (int64_t *)scalar_data, DATA_NUM * sizeof(int32_t) / sizeof(int64_t));
}
