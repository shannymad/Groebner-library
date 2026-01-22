#include <iostream>
#include "groebner/core/sparse_polynomial.hpp"
#include "groebner/core/coefficient/rational.hpp"
#include "groebner/core/variable.hpp"

using term = groebner::core::Term<>;
using rational = groebner::core::coefficient::Rational<>;
using variable = groebner::core::Variable;

int main() {
    term t1({{variable('x'), 2}}, rational(3, 2)); // (3/2)*x^2
    term t2({{variable('y'), 1}}, rational(5));     // 5*y
    term t3({{variable('x'), 1}, {variable('y'), 1}}, rational(-1)); // -x*y

    // (3/2)*x^2 + 5*y - x*y
    groebner::core::SparsePolynomial p({t1, t2, t3});

    std::cout << "Polynomial: " << p << "\n";
    // Expecting "3/2*x^2 - x*y + 5*y" 

    groebner::core::SparsePolynomial zero;
    std::cout << "Zero: " << zero << "\n"; // "0"

    groebner::core::SparsePolynomial p2({t1}); // (3/2)*x^2
    p2 += groebner::core::SparsePolynomial({t2}); // + 5*y
    std::cout << "p2: " << p2 << "\n"; // "3/2*x^2 + 5*y"

    term a({{variable('x'), 1}}, rational(2)); // 2*x
    term b({{variable('y'), 1}}, rational(3)); // 3*y
    groebner::core::SparsePolynomial pa(a), pb(b);
    auto prod = pa * pb; // 6*x*y
    std::cout << "Product: " << prod << "\n"; // "6*x*y"

    std::cout << "Leading term: " << p.leading_term() << "\n";

    term t4({{variable('x'), 1}}, rational(5));
    term t5({{variable('x'), 1}}, rational(2));
    groebner::core::SparsePolynomial p1({t4}), p2_copy({t5});
    auto diff = p1 - p2_copy; //  3*x
    assert(diff.leading_term().coefficient() == rational(3));

    term f1({{variable('x'), 2}}, rational(1));
    term f2({{variable('x'), 1}}, rational(1));
    groebner::core::SparsePolynomial f({f1, f2}); // x^2 + x
    groebner::core::SparsePolynomial g({f2});     // x

    f.reduce_by_once(g); // x
    assert(f.leading_term().coefficient() == rational(1));
    assert(f.leading_term().variables().size() == 1);

    std::cout << "polynomial tests passed\n";
    return 0;
}