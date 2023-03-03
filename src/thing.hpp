#pragma once

typedef unsigned char uint8_t;
extern "C" void puts(const char *fmt);

struct Thing {
  int inner = 0;

  Thing() {
    this->inner = 0;
    puts("Hi Thing\n");
  }

  Thing(size_t in) {
    this->inner = in;
    puts("Hi Thing\n");
  }

  ~Thing() { puts("Bye Thing\n"); }
};
