#pragma once


namespace groebner::core::detail {
    template<typename Coeff>

    struct PrintHelper {
        static bool is_plus_needed(const Coeff& coeff, bool is_first) {
            return (coeff > Coeff{0}) && !is_first;
        }

        static bool should_print_coefficient(const Coeff& coeff, bool has_variables) {
            if ((coeff == Coeff{1} || coeff == Coeff{-1} && has_variables)) {
                return false;
            }
            return true;
        }
    };
}