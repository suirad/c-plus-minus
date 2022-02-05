
#include <slimstd.hpp>
#include <unique.hpp>
#include <shared.hpp>

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
  printf("unique_ptr Create and move\n");
  {
    auto thing = std::unique_ptr<Thing>(new Thing);
    auto thing2 = move(thing);
    thing2->inner = 0;
  }
  printf("==========================\n");

  printf("unique_ptr arrays\n");
  {
    auto thing = std::unique_ptr<Thing, true>(new Thing[4]);
    thing[0]->inner = 0;
  }
  printf("==========================\n");

  printf("unique_ptr make_unique\n");
  {
    auto thing = std::make_unique<Thing>(1);
    thing->inner = 0;
    thing[25]->inner = 0;
    auto thing2 = std::make_unique<Thing[]>(2);
    thing[0]->inner = 0;
  }
  printf("==========================\n");

  printf("shared_ptr manual usage\n");
  {
    auto thing = std::shared_ptr<Thing>(new Thing);
    auto thing_array = std::shared_ptr<Thing, true>(new Thing[1]);

    {
      auto clone = thing.clone();
    }
  }
  printf("==========================\n");

  printf("shared_ptr make_shared\n");
  {
    auto thing = std::make_shared<Thing>(1);
    auto thing_array = std::make_shared<Thing[]>(2);

    {
      auto clone = thing.clone();
      auto clone_array = thing_array.clone();
    }
  }
  printf("==========================\n");


  return 0;
}


