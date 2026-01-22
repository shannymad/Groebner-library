#include "groebner/core/variable.hpp"
#include <cassert>
#include <iostream>

using variable = groebner::core::Variable;

void test_constructors() {
    variable x('x');
    assert(x.let() == 'x' && !x.has_index());

    variable y3('y', 3);
    assert(y3.let() == 'y' && y3.index() == 3 && y3.has_index());
}

void test_comparison() {
  variable x('x'), y('y'), x0('x', 0), x1('x', 1);
  assert(x < y);
  assert(x < x0);
  assert(x0 < x1);
  assert(x == variable('x'));
}

void test_output() {
  variable x('x');
  variable z5('z', 5);
}

int main() {
  test_constructors();
  test_comparison();
  std::cout << "variable tests passed\n";
  return 0;
}