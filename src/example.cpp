
#include "example_shared.cpp"
#include "example_unique.cpp"


#if defined(__linux__) || defined(__APPLE__)
extern "C" {
void setup_debug_handlers();
void dump_stack_trace();
}
#endif

int main() noexcept {
#if defined(__linux__) || defined(__APPLE__)
  setup_debug_handlers();
#endif
  example::unique_examples();
  example::shared_examples();

  return 0;
}