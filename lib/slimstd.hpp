// g++ -nodefaultlibs -fno-exceptions -fno-rtti -std=c++17 -c <file.cpp> -o <outfile.o>
// gcc 

#ifndef _SLIMSTD_HPP
#define _SLIMSTD_HPP

extern "C" {
  #include <malloc.h>
  #include <stdio.h>
}

void* operator new(size_t sz){
  printf("made size: %zu\n", sz);
  return malloc(sz);
}

inline void* operator new(size_t sz, void* p) noexcept {
  return p;
}

void* operator new[](size_t sz){
  printf("made array size: %zu\n", sz);
  return malloc(sz);
}

inline void* operator new[](size_t sz, void* p) noexcept{
  return p;
}

void operator delete(void* ptr){
  free(ptr);
}

inline void operator delete(void* a, void* b) noexcept {}

void operator delete[](void* ptr){
  free(ptr);
}

inline void operator delete[](void* a, void* b) noexcept {}

// Move funcs; same as std::move
template <class T> T && move(T&& src){
  return (T &&) src;
}

template <class T> T && move(T& src){
  return (T &&) src;
}

#endif
