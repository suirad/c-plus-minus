#include <slimstd.hpp>
////
// Unique class; same as std::unique_ptr
////
// TODO: distiguish between single item ptrs and arrays for destructors
template<typename T> struct Uniq{
  T* ptr = nullptr;

  Uniq(){
    this->ptr = new T;
  }


  Uniq(T* p){
    this->ptr = p;
  }

  Uniq(Uniq&& old) : ptr(nullptr){
    this->ptr = old.ptr;
    old.ptr = nullptr;
  }

  Uniq& operator=(Uniq&& old){
    if (this == &old){
      // same
      return *this;
    }

    if (this->ptr){
      delete this->ptr;
    }

    this->ptr = old.ptr;
    old.ptr = nullptr;

    return *this;
  }

  // Dereference forwarding
  T* operator*(){
    return this->ptr;
  }

  T* operator->(){
    return this->ptr;
  }

  ~Uniq(){
    if (ptr){
      delete this->ptr;
    }
  }
};
