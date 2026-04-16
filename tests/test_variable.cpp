#include "groebner/core/strong_typedef.hpp"
#include "groebner/core/variable.hpp"
#include <cassert>
#include <iostream>

void test_constructors() {
  variable x('x');
  assert(x.let() == 'x');
  assert(!x.has_index());

  variable y3('y', VariableIndex{3});
  assert(y3.let() == 'y');
  assert(y3.index().value == 3);
  assert(y3.has_index());
}

void test_comparison() {
  variable x('x');
  variable y('y');
  variable x0('x', VariableIndex{0});
  variable x1('x', VariableIndex{1});

  assert(x < y);
  assert(x < x0);  // 'x'  < 'x_0'
  assert(x0 < x1); // 'x_0' < 'x_1'
  assert(x == variable('x'));
}

void test_output() {
  variable x('x');
  variable z5('z', VariableIndex{5});

  std::cout << x << " " << z5 << "\n";
}

int main() {


using variable = groebner::core::Variable;
using VariableIndex = groebner::core::VariableIndex;
  test_constructors();
  test_comparison();
  test_output();
  std::cout << "variable tests passed\n";
  return 0;
}