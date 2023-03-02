#include "example_unique.cpp"
#include "example_shared.cpp"

#ifdef __linux__
  extern "C" {
    void setup_debug_handlers();
    void dump_stack_trace();
  }
#endif

int main() noexcept {
  
  #ifdef __linux__
    setup_debug_handlers();
  #endif
  example::unique_examples();
  example::shared_examples();

  return 0;
}