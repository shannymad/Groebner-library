# Groebner Basis F5 Library

A C++17 implementation of the F5 algorithm for computing Gröbner bases.

## Structure
- `core/`: fundamental algebraic objects (variables, terms, polynomials)
- `coefficient/`: number types (rational, modular integers)
- `orders/`: monomial orderings (lex, degrevlex, etc.)
- `ideals/`: ideal operations and basis computation
- `parsing/`: string-to-polynomial conversion

## Requirements
- C++17 compiler (GCC ≥ 9 or Clang ≥ 10)
- CMake ≥ 3.15