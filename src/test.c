#include "../lib/vector/vector.h"
#include <math.h>

int main()
{
  t_vec a = new_vec(1, 2, 3);
  print_vec(a);
  t_vec b = new_vec(4, 5, 6);
  print_vec(b);
  t_vec c = add_vec(a, b);
  print_vec(c);
  return 0;
}