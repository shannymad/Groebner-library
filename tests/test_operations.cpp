#include <iostream>
#include <cassert>
#include "groebner/core/polynomial_operations.hpp"
#include "groebner/core/sparse_polynomial.hpp"
#include "groebner/core/coefficient/rational.hpp"
#include "groebner/core/variable.hpp"

using term = groebner::core::Term<>;
using rational = groebner::core::coefficient::Rational<>;
using variable = groebner::core::Variable;

int main() {
    term f1({{variable('x'), 2}}, rational(1)); // x^2
    term f2({{variable('y'), 1}}, rational(1)); // y
    groebner::core::SparsePolynomial f({f1, f2}); // x^2 + y

    term g1({{variable('x'), 1}, {variable('y'), 1}}, rational(1)); // xy
    term g2({{variable('x'), 1}}, rational(1)); // x
    groebner::core::SparsePolynomial g({g1, g2}); // xy + x

    auto s = groebner::core::s_polynomial(f, g);
    // S(f,g) = y*(x^2 + y) - x*(xy + x) = x^2y + y^2 - x^2y - x^2 = y^2 - x^2
    assert(!s.is_zero());

    term a({{variable('x'), 1}});
    term b({{variable('y'), 1}});
    groebner::core::SparsePolynomial pa(a), pb(b);
    assert(groebner::core::are_coprime(pa, pb));

    term c({{variable('x'), 1}});
    term d({{variable('x'), 2}});
    groebner::core::SparsePolynomial pc(c), pd(d);
    assert(!groebner::core::are_coprime(pc, pd));

    std::cout << "operations tests passed\n";
    return 0;
}