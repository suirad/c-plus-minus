#include <slimstd.hpp>
#include <unique.hpp>

#include "thing.hpp"

namespace example {
  void unique_examples() {
    namespace std = slimstd;

    // manually create and move
    puts("unique_ptr Create and move\n");
    {
      auto thing = std::unique_ptr<Thing>(new Thing);
      auto thing2 = move(thing);
      thing2->inner = 0;
    }
    puts("==========================\n");

    puts("unique_ptr arrays\n");
    {
      auto thing = std::unique_ptr<Thing, true>(new Thing[4]);
      thing[0]->inner = 0;
    }
    puts("==========================\n");

    puts("unique_ptr make_unique\n");
    {
      auto thing = std::make_unique<Thing>(1);
      thing->inner = 0;
      thing[25]->inner = 0;
      auto thing2 = std::make_unique<Thing[]>(2);
      thing[0]->inner = 0;
    }
    puts("==========================\n");
    }

}
