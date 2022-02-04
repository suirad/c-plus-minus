
#include <slimstd.hpp>
#include <unique.hpp>

extern "C" {
  #include <stdio.h>
}

struct Thing {
  int inner = 0;

  Thing(){
    this->inner = 0;
    printf("Hi Thing\n");
  }

  Thing(size_t in){
    this->inner = in;
    printf("Hi Thing\n");
  }

  ~Thing(){
    printf("Bye Thing\n");
  }
};

namespace std = slimstd;

int main() noexcept {
  // manually create and move
  {
    auto thing = std::unique_ptr<Thing>(new Thing);
    auto thing2 = move(thing);
    thing2->inner = 0;
  }

  // manually handle arrays
  {
    auto thing = std::unique_ptr<Thing, true>(new Thing[4]);
    thing[0]->inner = 0;
  }

  // make_unique
  {
    auto thing = std::make_unique<Thing>(1);
    thing->inner = 0;
    thing[25]->inner = 0;
    auto thing2 = std::make_unique<Thing[]>(2);
    thing[0]->inner = 0;
  }

  return 0;
}


