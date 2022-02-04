#include "slimstd.hpp"
#include "type_traits.hpp"
////
// Unique class; same as std::unique_ptr
////
// TODO: distiguish between single item ptrs and arrays for destructors
namespace slimstd {
  template<typename T, bool Is_Array = false>
  struct unique_ptr {
    T* ptr = nullptr;

    unique_ptr(){}

    unique_ptr(T* p){
      this->ptr = p;
    }

    unique_ptr(unique_ptr&& old) : ptr(nullptr){
      this->ptr = old.ptr;
      old.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& old){
      if (this == &old){
        // same
        return this;
      }

      if (this->ptr){
        delete this->ptr;
      }

      this->ptr = old.ptr;
      old.ptr = nullptr;

      return this;
    }

    // Dereference forwarding
    T* operator*(){
      return this->ptr;
    }

    T* operator->(){
      return this->ptr;
    }

    T* operator[](int i) {
      if (Is_Array) {
        return &this->ptr[i];
      } 

      return this->ptr;
    }


    ~unique_ptr(){
      if (this->ptr){
        if (Is_Array){
          delete[] this->ptr;
        } else {
          delete this->ptr;
        }
      }
    }
  };

  // single item unique
  // make_unique<int>()
  template<class T, class... Args>
  enable_if_t<!is_array<T>::value, unique_ptr<T>> make_unique(Args&&... args) {
    return unique_ptr<T>(new T(forward<Args>(args)...));
  }

  // array unique
  // make_unique<int[]>(10)
  template<class T>
  enable_if_t<is_unbounded_array_v<T>, unique_ptr<remove_all_extents_t<T>, true>> make_unique(size_t n) {
    using inner = remove_all_extents_t<T>;
    return unique_ptr<inner, true>(new inner[n]());
  }

  // bounded array disallowed
  // make_unique<int[10]>()
  template<class T, class... Args>
  enable_if_t<is_bounded_array_v<T>> make_unique(Args&&...) = delete;
}
