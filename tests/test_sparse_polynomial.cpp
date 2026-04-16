#include "groebner/core/coefficient/rational.hpp"
#include "groebner/core/sparse_polynomial.hpp"
#include "groebner/core/variable.hpp"
#include <cassert>
#include <iostream>


int main() {

using term = groebner::core::Term<>;
using rational = groebner::core::coefficient::Rational<>;
using variable = groebner::core::Variable;
using Degree = groebner::core::Degree;
using Poly = groebner::core::SparsePolynomial<>;

  term t1({{variable('x'), Degree{2}}}, rational(3, 2)); // (3/2)*x^2
  term t2({{variable('y'), Degree{1}}}, rational(5));    // 5*y
  term t3({{variable('x'), Degree{1}}, {variable('y'), Degree{1}}},
          rational(-1)); // -x*y

  // (3/2)*x^2 + 5*y - x*y
  Poly p({t1, t2, t3});

  std::cout << "Polynomial: " << p << "\n";
  // Expecting "3/2*x^2 - x*y + 5*y"

  Poly zero;
  std::cout << "Zero: " << zero << "\n"; // "0"

  Poly p2({t1});                     // (3/2)*x^2
  p2 += Poly({t2});                  // + 5*y
  std::cout << "p2: " << p2 << "\n"; // "3/2*x^2 + 5*y"

  term a({{variable('x'), Degree{1}}}, rational(2)); // 2*x
  term b({{variable('y'), Degree{1}}}, rational(3)); // 3*y
  Poly pa(a), pb(b);
  auto prod = pa * pb;                      // 6*x*y
  std::cout << "Product: " << prod << "\n"; // "6*x*y"

  std::cout << "Leading term: " << p.leading_term() << "\n";

  term t4({{variable('x'), Degree{1}}}, rational(5));
  term t5({{variable('x'), Degree{1}}}, rational(2));
  Poly p1({t4}), p2_copy({t5});
  auto diff = p1 - p2_copy; // 3*x
  assert(diff.leading_term().coefficient() == rational(3));

  term f1({{variable('x'), Degree{2}}}, rational(1));
  term f2({{variable('x'), Degree{1}}}, rational(1));
  Poly f({f1, f2}); // x^2 + x
  Poly g({f2});     // x

  f.reduce_by_once(g); // x
  assert(f.leading_term().coefficient() == rational(1));
  assert(f.leading_term().variables().size() == 1);

  std::cout << "polynomial tests passed\n";
  return 0;
}