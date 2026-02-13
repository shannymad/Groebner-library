#pragma once
#include <functional>

namespace groebner::core {

template <typename Tag, typename T> struct StrongTypedef {
  T value;
  explicit constexpr StrongTypedef(T v) : value(v) {}

  StrongTypedef &operator+=(const StrongTypedef &other) {
    value += other.value;
    return *this;
  }

  friend constexpr bool operator==(const StrongTypedef &a,
                                   const StrongTypedef &b) {
    return a.value == b.value;
  }

  friend constexpr auto operator<=>(const StrongTypedef &a,
                                    const StrongTypedef &b) = default;

  friend constexpr StrongTypedef operator+(const StrongTypedef &a,
                                           const StrongTypedef &b) {
    return StrongTypedef{a.value + b.value};
  }

  friend constexpr StrongTypedef operator-(const StrongTypedef &a,
                                           const StrongTypedef &b) {
    return StrongTypedef{a.value - b.value};
  }
};
}