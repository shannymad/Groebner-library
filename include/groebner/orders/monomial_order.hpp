#pragma once

#include "term.hpp"
#include <map>
#include <set>
#include <utility>

namespace groebner::orders {

template <typename Term>

typename Term::degree_type
degree_of_variable(const Term &t, const typename Term::variable_type var) {
  auto it = t.variables().find(var);
  if (it == t.variables().end()) {
    return 0;
  }
  return it->second;
}

struct LexOrder {
  template <typename Term> bool operator()(const Term &a, const Term &b) const {
    auto it_a = a.variables().begin();
    auto it_b = b.variables().begin();
    auto end_a = a.variables().end();
    auto end_b = b.variables().end();

    while (it_a != end_a && it_b != end_b) {
      if (it_a->first < it_b->first) {
        if (it_a->second != 0) {
          return true;
        }
        ++it_a;
      } else if (it_b->first < it_a->first) {
        if (it_b->second != 0) {
          return false;
        }
        ++it_b;
      } else {
        if (it_a->second < it_b->second)
          return true;
        if (it_a->second > it_b->second)
          return false;
        ++it_a;
        ++it_b;
      }
    }

    while (it_a != end_a) {
      if (it_a->second != 0)
        return true;
      ++it_a;
    }

    while (it_b != end_b) {
      if (it_b->second != 0)
        return false;
      ++it_b;
    }

    return false;
  }
};

struct DegRevLexOrder {
  template <typename Term> bool operator()(const Term &a, const Term &b) const {
    auto deg_a = a.total_degree();
    auto deg_b = b.total_degree();
    if (deg_a != deg_b) {
      return deg_a > deg_b;
    }

    auto it_a = a.variables().rbegin();
    auto it_b = b.variables().rbegin();
    auto end_a = a.variables().rend();
    auto end_b = b.variables().rend();

    while (it_a != end_a && it_b != end_b) {
      if (it_a->first == it_b->first) {
        if (it_a->second != it_b->second) {
          return it_a->second > it_b->second;
        }
        ++it_a;
        ++it_b;
      } else if (it_a->first < it_b->first) {
        if (it_b->second != 0)
          return false;
        ++it_b;
      } else {
        if (it_a->second != 0)
          return true;
        ++it_a;
      }
    }

    while (it_a != end_a) {
      if (it_a->second != 0)
        return true;
      ++it_a;
    }
    while (it_b != end_b) {
      if (it_b->second != 0)
        return false;
      ++it_b;
    }

    return false;
  }
};
}

