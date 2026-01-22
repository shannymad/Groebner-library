#pragma once

#include <vector>
#include "sparse_polynomial.hpp"

namespace groebner::ideals {

enum class BasisType {
    Any,
    Groebner,
    MinimalGroebner,
    ReducedGroebner
};

template<typename Poly>
class Ideal {
public:
    void insert(const Poly& p);
    void make_groebner_basis();

private:
    std::vector<Poly> basis_;
    BasisType type_ = BasisType::Any;
};

}
