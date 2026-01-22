#pragma once

#include "sparse_polynomial.hpp"

namespace groebner::core {

template<typename Coeff>
bool are_coprime(
    const SparsePolynomial<Coeff>& f,
    const SparsePolynomial<Coeff>& g
) {
    if (f.is_zero() || g.is_zero()) {
        return false;
    }
    
    using TermType = typename SparsePolynomial<Coeff>::term_type;
    const TermType& lt_f = f.leading_term();
    const TermType& lt_g = g.leading_term();
    
    TermType gcd = TermType::monomial_gcd(lt_f, lt_g);
    return gcd.variables().empty();
}
template <typename Coeff>
SparsePolynomial<Coeff> s_polynomial(const SparsePolynomial<Coeff> &f,
                                     const SparsePolynomial<Coeff> &g) {
  using TermType = typename SparsePolynomial<Coeff>::term_type;

  if (f.is_zero() || g.is_zero()) {
    return {};
  }
  const TermType &lt_f = f.leading_term();
  const TermType &lt_g = g.leading_term();

  TermType lcm = TermType::monomial_lcm(lt_f, lt_g); 

  typename TermType::variable_map vars_f;
  for (const auto &[var, _] : lcm.variables()) {
    degree_type deg = lcm.degree_of(var) - lt_f.degree_of(var);
    if (deg > 0) {
      vars_f.emplace(var, deg);
    }
  }

  TermType mult_f(vars_f, Coeff{1} / lt_f.coefficient());


  typename TermType::variable_map vars_g;
  for (const auto &[var, _] : lcm.variables()) {
    degree_type deg = lcm.degree_of(var) - lt_g.degree_of(var);
    if (deg > 0) {
      vars_g.emplace(var, deg);
    }
  }
  TermType mult_g(vars_g, Coeff{1} / lt_g.coefficient());


  SparsePolynomial<Coeff> S;

  for (const auto &t : f.terms()) {
    S.add_term(mult_f * t);
  }

  for (const auto &t : g.terms()) {
    TermType neg = mult_g * t;
    neg.coefficient() = -neg.coefficient();
    S.add_term(neg);
  }
  return S;
}
}

