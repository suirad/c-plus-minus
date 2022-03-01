#pragma once

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
