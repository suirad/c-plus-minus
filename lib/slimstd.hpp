// g++ -nodefaultlibs -fno-exceptions -fno-rtti -std=c++17 -c <file.cpp> -o <outfile.o>
// gcc 

#pragma once
#ifndef _SLIMSTD_HPP
#define _SLIMSTD_HPP

extern "C" {
  #include <malloc.h>
  #include <stdint.h>
}

void* operator new(size_t sz){
  return malloc(sz);
}



void* operator new[](size_t sz){
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
template <class T> T&& move(T&& src){
  return (T&&) src;
}

template <class T> T && move(T& src){
  return (T &&) src;
}


template <class _Tp> struct remove_reference        {typedef _Tp type;};
template <class _Tp> struct remove_reference<_Tp&>  {typedef _Tp type;};
template <class _Tp> struct remove_reference<_Tp&&> {typedef _Tp type;};

template <class _Tp> using remove_reference_t = typename remove_reference<_Tp>::type;

// Forward funcs; same as std::forward
template <class T>
inline T&& forward(typename remove_reference<T>::type& t) noexcept
{
    return static_cast<T&&>(t);
}


#endif
