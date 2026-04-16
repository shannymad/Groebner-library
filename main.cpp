#include <iostream>
#include <exception>



namespace groebner {
  void react() {
    try {
      throw;
    } catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    } catch (...) {
      std::cerr << "Unknown critical error occured" << std::endl;
    }
  }
}
int main() {
  try {
  std::cout << "Groebner F5 library — structure initialized.\n";
  } catch (...) {
    groebner::react();
    return 1;
  }
  return 0;
}