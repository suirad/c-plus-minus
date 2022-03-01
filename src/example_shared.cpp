#include <slimstd.hpp>
#include <shared.hpp>

#include "thing.hpp"

namespace example {
  void shared_examples() {
    namespace std = slimstd;

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

  }
}
