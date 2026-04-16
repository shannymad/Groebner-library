#include "groebner/core/coefficient/rational.hpp"
#include "groebner/core/term.hpp"
#include <cassert>
#include <iostream>

int main() {

using term = groebner::core::Term<>;
using rational = groebner::core::coefficient::Rational<>;
using variable = groebner::core::Variable;
using Degree = groebner::core::Degree;

  term t1;
  assert(t1.is_zero());

  term t2({{variable('x'), Degree{2}}, {variable('y'), Degree{3}}},
          rational(3, 2));
  assert(!t2.is_zero());
  assert(t2.total_degree().value == 5);
  assert(t2.variables().size() == 2);

  term t3({{variable('x'), Degree{0}}, {variable('y'), Degree{2}}},
          rational(5));
  assert(t3.variables().size() == 1);
  assert(t3.variables().count(variable('x')) == 0);

  term t4({{variable('x'), Degree{2}}}, rational(2));
  term t5({{variable('x'), Degree{3}}, {variable('y'), Degree{1}}},
          rational(3));
  term t6 = t4 * t5;
  assert(t6.coefficient() == rational(6));
  assert(t6.variables().at(variable('x')).value == 5);
  assert(t6.variables().at(variable('y')).value == 1);

  term a({{variable('x'), Degree{2}}, {variable('y'), Degree{3}}});
  term b({{variable('x'), Degree{1}}, {variable('y'), Degree{2}}});
  term c({{variable('x'), Degree{3}}});

  assert(a.is_divisible_by(b)); // x^2y^3 / xy^2 = xy
  assert(!a.is_divisible_by(c));

  auto lcm1 = term::monomial_lcm(a, c);
  assert(lcm1.degree_of(variable('x')).value == 3);
  assert(lcm1.degree_of(variable('y')).value == 3);

  auto gcd1 = term::monomial_gcd(a, b);
  assert(gcd1.degree_of(variable('x')).value == 1);
  assert(gcd1.degree_of(variable('y')).value == 2);

  std::cout << "term tests passed\n";
  return 0;
}