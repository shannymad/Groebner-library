#pragma once
#include "strong_typedef.hpp"
#include <cassert>
#include <iostream>
#include <type_traits>

namespace groebner::core {

struct VariableIndexTag;

using VariableIndex =
    groebner::core::StrongTypedef<VariableIndexTag, std::int32_t>;

inline constexpr VariableIndex kNoIndex{-1};

class Variable {
public:
  Variable() = default;

  explicit Variable(char l, VariableIndex index = kNoIndex)
      : letter(l), num(index) {
    assert(((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) &&
           "Expected [a-zA-Z] letter");
  }

  char let() const { return letter; }

  VariableIndex index() const { return num; }

  bool has_index() const { return num != kNoIndex; }

  friend bool operator==(const Variable &lhs, const Variable &rhs) {
    return lhs.letter == rhs.letter && lhs.num == rhs.num;
  }

  friend bool operator!=(const Variable &lhs, const Variable &rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const Variable &lhs, const Variable &rhs) {
    if (lhs.letter != rhs.letter) {
      return lhs.letter < rhs.letter;
    }
    return lhs.num < rhs.num;
  }

  friend std::ostream &operator<<(std::ostream &os, const Variable &v) {
    if (v.num == kNoIndex) {
      return os << v.letter;
    }
    return os << v.letter << '_' << v.num.value;
  }

private:
  char letter;
  VariableIndex num = kNoIndex;
};

}
