#pragma once
#include "coefficient/rational.hpp"
#include "variable.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <map>
#include <numeric>

namespace groebner::core {

using degree_type = std::uint32_t;

// TODO: replace map with vector
// std::vector<std::pair<Variable, degree_type>>

// using variable_power = std::pair<Variable, degree_type>;
// using variable_vector = std::vector<variable_power>;

template <typename Coeff = coefficient::Rational<>> class Term {
public:
  using variable_map = std::map<Variable, degree_type>;
  using variable_type = Variable;

  Term() : coeff{Coeff{0}} {}

  Term(const variable_map& vars, const Coeff& coeff) 
  : coeff(coeff), vars(coeff == Coeff{0} ? variable_map{} : vars) {}

  explicit Term(std::initializer_list<std::pair<Variable, degree_type>> var,
                const Coeff &coef = Coeff{1})
      : coeff{coef} {
    for (const auto &pair : var) {
      if (pair.second != 0) {
        vars.insert(pair);
      }
    }
  }

  const Coeff &coefficient() const { return coeff; }
  Coeff &coefficient() { return coeff; }



  const variable_map &variables() const { return vars; }

  bool is_zero() const { return coeff == Coeff{0}; }

  degree_type total_degree() const {
    return std::accumulate(
        vars.begin(), vars.end(), degree_type{0},
        [](degree_type sum, const auto &pair) { return sum + pair.second; });
  }

  degree_type degree_of(const Variable &var) const {
    auto it = vars.find(var);
    return (it != vars.end()) ? it->second : 0;
  }

  friend bool operator==(const Term &lhs, const Term &rhs) {
    return lhs.vars == rhs.vars;
  }

  friend bool operator!=(const Term &lhs, const Term &rhs) {
    return !(lhs == rhs);
  }

  // Temporary lex order on variables (TODO: external comparator)
  friend bool operator<(const Term &lhs, const Term &rhs) {
    return lhs.vars < rhs.vars;
  }

  Term operator*(const Term &other) const {
    Coeff new_coeff = coeff * other.coeff;
    variable_map new_vars = vars;

    for (const auto &[var, deg] : other.vars) {
      auto [it, inserted] = new_vars.try_emplace(var, deg);
      if (!inserted) {
        it->second += deg;
      }
    }

    return Term(std::move(new_coeff), std::move(new_vars));
  }

  Term operator*(const Coeff &c) const { return Term(coeff * c, vars); }

  bool is_divisible_by(const Term &divisor) const {
    for (const auto &[var, deg_div]: divisor.vars) {
      if (degree_of(var) < deg_div) {
        return false;
      }
    }
    return true;
  }

  void print_monomial(std::ostream &os) const {
    bool first = true;
    for (const auto &[var, deg] : vars) {
      if (!first)
        os << "*";
      os << var;
      if (deg != 1)
        os << "^" << deg;
      first = false;
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const Term &t) {
    if (t.is_zero()) {
      return os << "0";
    }

    bool first = true;
    if (t.coeff != Coeff{1} || t.vars.empty()) {
      os << t.coeff;
      first = false;
    }

    for (const auto &[var, deg] : t.vars) {
      if (!first) {
        os << "*";
      }
      os << var;
      if (deg != 1) {
        os << "^" << deg;
      }
      first = false;
    }

    return os;
  }

  static Term monomial_gcd(const Term &a, const Term &b) {
    variable_map result;
    for (const auto &[var, deg_a] : a.vars) {
      degree_type deg_b = b.degree_of(var);
      degree_type min_deg = std::min(deg_a, deg_b);
      if (min_deg > 0) {
        result.emplace(var, min_deg);
      }
    }
    return Term(Coeff{1}, std::move(result));
  }

  static Term monomial_lcm(const Term &a, const Term &b) {
    variable_map result = a.vars;
    for (const auto &[var, deg_b] : b.vars) {
      auto it = result.find(var);
      if (it != result.end()) {
        it->second = std::max(it->second, deg_b);
      } else {
        result.emplace(var, deg_b);
      }
    }

    return Term(Coeff{1}, std::move(result));
  }

private:
  Coeff coeff;
  variable_map vars;

  Term(Coeff c, variable_map v) : coeff(std::move(c)), vars(std::move(v)) {}
};

}
