#include <iostream>
#include <cassert>
#include "groebner/core/coefficient/rational.hpp"

using rational = groebner::core::coefficient::Rational<>;

void test_constructors() {
    rational r1;
    assert(r1.numerator() == 0 && r1.denominator() == 1);
    rational r2(5);
    assert(r2 == rational(5, 1));
    rational r3(6, -8);
    assert(r3 == rational(-3, 4));
    rational r4(0, 100);
    assert(r4 == rational(0, 1));
}

void test_arithmetic() {
    rational a(1, 2);
    rational b(1, 3);
    assert(a + b == rational(5, 6));
    assert(a - b == rational(1, 6));
    assert(a * b == rational(1, 6));
    assert(a / b == rational(3, 2));
    
    rational c(2);
    c += rational(1, 2);
    assert(c == rational(5, 2));
}

void test_comparison() {
    assert(rational(1, 2) == rational(2, 4));
    assert(rational(1, 2) < rational(2, 3));
    assert(rational(-1, 2) < rational(1, 2));
}

void test_normalize() {
    rational r(0, 5);
    assert(r.numerator() == 0 && r.denominator() == 1);
    rational s(-6, -9);
    assert(s == rational(2, 3));
}

int main() {
    test_constructors();
    test_arithmetic();
    test_comparison();
    test_normalize();
    std::cout << "rational tests passed\n";
    return 0;
}