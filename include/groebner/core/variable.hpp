#pragma once

#include <cassert>
#include <iostream>
#include <type_traits>

namespace groebner::core {
using variable_index_type = std::int32_t;
inline constexpr variable_index_type kNoIndex = -1;

class Variable {
public:
  Variable() = default;

  explicit Variable(char l, variable_index_type index = kNoIndex)
      : letter(l), num(index) {
    assert(((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) &&
           "Expected [a-zA-Z] letter");
  }

  char let() const { return letter; }

  variable_index_type index() const { return num; }

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
    return os << v.letter << '_' << v.num;
  }

private:
  char letter;
  variable_index_type num = kNoIndex;
};

}
