#pragma once

#include "term.hpp"
#include <cassert>
#include <initializer_list>
#include <set>

namespace groebner::core {

// Temporary comparator. TODO: replace with DegRevLexOrder
template <typename TermType> struct LexTermOrder {
  bool operator()(const TermType &a, const TermType &b) const { return a < b; }
};

template <typename Coeff = coefficient::Rational<>> class SparsePolynomial {
public:
  using term_type = Term<Coeff>;
  using term_set = std::set<term_type, LexTermOrder<term_type>>;
  // later: using term_set = std::set<term_type, orders::DegRevLexOrder>;

  SparsePolynomial() = default;

  SparsePolynomial(std::initializer_list<term_type> terms) {
    for (const auto &t : terms) {
      add_term(t);
    }
    remove_zero_terms();
  }

  explicit SparsePolynomial(const term_type &t) {
    add_term(t);
    remove_zero_terms();
  }

  const term_set &terms() const { return terms_; }

  SparsePolynomial &operator+=(const SparsePolynomial &other) {
    for (const auto &t : other.terms_) {
      add_term(t);
    }
    return *this;
  }



  SparsePolynomial &operator-=(const SparsePolynomial &other) {
    for (const auto &t : other.terms_) {
      term_type negated = t;
      negated.coefficient() = -negated.coefficient();
      add_term(negated);
    }
    return *this;
  }

   friend SparsePolynomial operator-(SparsePolynomial lhs, const SparsePolynomial& rhs) {
    lhs -= rhs;
    return lhs;
  }

  SparsePolynomial &operator*=(const SparsePolynomial &other) {
    SparsePolynomial result;
    for (const auto &t1 : terms_) {
      for (const auto &t2 : other.terms_) {
        result.add_term(t1 * t2);
      }
    }
    *this = std::move(result);
    return *this;
  }

  friend bool operator==(const SparsePolynomial &lhs,
                         const SparsePolynomial &rhs) {
    return lhs.terms_ == rhs.terms_;
  }

  friend bool operator!=(const SparsePolynomial &lhs,
                         const SparsePolynomial &rhs) {
    return !(lhs == rhs);
  }

  bool is_zero() const { return terms_.empty(); }

  const term_type &leading_term() const {
    assert(!is_zero());
    return *terms_.begin();
  }
  bool reduce_by_once(const SparsePolynomial &divisor) {
    if (divisor.is_zero() || this->is_zero()) {
      return false;
    }

    const term_type &lt_f = leading_term();
    const term_type &lt_g = divisor.leading_term();

    if (!lt_f.is_divisible_by(lt_g)) {
      return false;
    }

    typename term_type::variable_map mult_vars;
    for (const auto &[var, deg_f] : lt_f.variables()) {
    degree_type deg_g = lt_g.degree_of(var);
    if (deg_f > deg_g) {
      mult_vars.emplace(var, deg_f - deg_g);
    }
  }
  term_type multiplier(mult_vars, lt_f.coefficient() / lt_g.coefficient());
  for (const auto &term : divisor.terms_) {
    term_type to_sub = multiplier * term;
    to_sub.coefficient() = -to_sub.coefficient();
    add_term(to_sub);
  }
  return true;
}

  void reduce_by(const SparsePolynomial &divisor) {
    while (reduce_by_once(divisor)) {
    }
  }

  friend std::ostream &operator<<(std::ostream &os, const SparsePolynomial &p) {
    if (p.is_zero()) {
      return os << "0";
    }
    bool first = true;
    for (const auto &term : p.terms()) {
      if (first) {
        os << term;
        first = false;
      } else {
        if (term.coefficient() < Coeff{0}) {
          os << " - ";
          auto abs_coef = -term.coefficient();
          if (term.variables().empty()) {
            os << abs_coef;
          } else {
            if (abs_coef != Coeff{1}) {
              os << abs_coef << "*";
            }
            term.print_monomial(os);
          }
        } else {
          os << " + ";
          os << term;
        }
      }
    }
    return os;
  }


  void add_term(const term_type &t) {
    if (t.is_zero())
      return;
    auto it = terms_.find(t);
    if (it != terms_.end()) {
      auto node = terms_.extract(it);
      node.value().coefficient() += t.coefficient();
      if (!node.value().is_zero()) {
        terms_.insert(std::move(node));
      }
    } else {
      terms_.insert(t);
    }
  }

private:
  term_set terms_;

  void remove_zero_terms() {
    auto it = terms_.begin();
    while (it != terms_.end()) {
      if (it->is_zero()) {
        it = terms_.erase(it);
      } else {
        ++it;
      }
    }
  }
  

  void normalize() {
    if (is_zero()) {
      return;
    }
    const term_type &lt = leading_term();
    Coeff lc = lt.coefficient();
    if (lc == Coeff{1}) {
      return;
    }

    term_set new_terms;
    for (const auto &term : terms_) {
      term_type normalized = term;
      normalized.coefficient() /= lc;
      new_terms.insert(std::move(normalized));
    }
    terms_ = std::move(new_terms);
  }
};

template <typename Coeff>
SparsePolynomial<Coeff> operator+(SparsePolynomial<Coeff> lhs,
                                  const SparsePolynomial<Coeff> &rhs) {
  lhs += rhs;
  return lhs;
}

template <typename Coeff>
SparsePolynomial<Coeff> operator*(SparsePolynomial<Coeff> lhs,
                                  const SparsePolynomial<Coeff> &rhs) {
  lhs *= rhs;
  return lhs;
}
}
