#import <slimstd.hpp>
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

  ~Thing(){
    printf("Bye Thing\n");
  }
};

int main() noexcept {
  auto num = new int;
  delete num;

  auto thing = Uniq<Thing>();
  auto thing2 = move(thing);
  auto thing3 = Uniq<Thing>(new Thing[4]);

  return 0;
}


