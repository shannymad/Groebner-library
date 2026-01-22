#pragma once

#include <cassert>
#include <iostream>
#include <numeric>
#include <type_traits>

namespace groebner::core::coefficient {

template <typename T = std::int64_t> class Rational {
public:
  static_assert(std::is_integral_v<T>, "T must be an integral type");
  static_assert(std::is_signed_v<T>, "T must be a signed type");

  Rational() : numerator_{0}, denominator_{1} {}

  Rational(T num) : numerator_{num}, denominator_{1} { normalize(); }

  Rational(T num, T denum) : numerator_{num}, denominator_{denum} {
    assert(denum != 0);
    normalize();
  }

  T numerator() const { return numerator_; }

  T denominator() const { return denominator_; }

  Rational &operator+=(const Rational &other) {
    numerator_ =
        numerator_ * other.denominator_ + denominator_ * other.numerator_;
    denominator_ = denominator_ * other.denominator_;
    normalize();
    return *this;
  }

  Rational &operator-=(const Rational &other) {
    numerator_ =
        numerator_ * other.denominator_ - denominator_ * other.numerator_;
    denominator_ = denominator_ * other.denominator_;
    normalize();
    return *this;
  }

  Rational &operator*=(const Rational &other) {
    numerator_ = numerator_ * other.numerator_;
    denominator_ = denominator_ * other.denominator_;
    normalize();
    return *this;
  }

  Rational &operator/=(const Rational &other) {
    assert(other.numerator_ != 0);
    numerator_ = numerator_ * other.denominator_;
    denominator_ = denominator_ * other.numerator_;
    normalize();
    return *this;
  }

  Rational operator-() const { return Rational{-numerator_, denominator_}; }

  friend bool operator==(const Rational &lhs, const Rational &rhs) {
    return lhs.numerator_ * rhs.denominator_ ==
           rhs.numerator_ * lhs.denominator_;
  }

  friend bool operator!=(const Rational &lhs, const Rational &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const Rational &lhs, const Rational &rhs) {
    return lhs.numerator_ * rhs.denominator_ <
           rhs.numerator_ * lhs.denominator_;
  }

  friend bool operator>(const Rational &lhs, const Rational &rhs) {
    return rhs < lhs;
  }

  friend bool operator<=(const Rational &lhs, const Rational &rhs) {
    return !(rhs < lhs);
  }

  friend bool operator>=(const Rational &lhs, const Rational &rhs) {
    return !(lhs < rhs);
  }

  friend Rational operator+(Rational lhs, const Rational &rhs) {
    lhs += rhs;
    return lhs;
  }

  friend Rational operator-(Rational lhs, const Rational &rhs) {
    lhs -= rhs;
    return lhs;
  }

  friend Rational operator*(Rational lhs, const Rational &rhs) {
    lhs *= rhs;
    return lhs;
  }

  friend Rational operator/(Rational lhs, const Rational &rhs) {
    lhs /= rhs;
    return lhs;
  }

  friend std::ostream &operator<<(std::ostream &os, const Rational &r) {
    if (r.denominator_ == 1) {
      return os << r.numerator_;
    }
    return os << r.numerator_ << "/" << r.denominator_;
  }

private:
  static T abs_value(T x) { return std::abs(x); }

  static T gcd_safe(T a, T b) { return std::gcd(abs_value(a), abs_value(b)); }

  void normalize() {
    if (numerator_ == 0) {
      denominator_ = 1;
      return;
    }
    if (denominator_ < 0) {
      numerator_ = -numerator_;
      denominator_ = -denominator_;
    }
    T g = gcd_safe(numerator_, denominator_);
    numerator_ /= g;
    denominator_ /= g;
  }

  T numerator_;
  T denominator_;
};

}
