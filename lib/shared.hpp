#pragma once
#ifndef _SLIMSTD_SHARED
#define _SLIMSTD_SHARED

#include "slimstd.hpp"
#include "type_traits.hpp"
////
// Shared ptr class; same as std::shared_ptr
//  however without support for weak_ptr or deleters
////
//TODO: Support atomics
namespace slimstd {
  template<typename T, bool Is_Array = false>
  class shared_ptr {
    public:
      shared_ptr(){}

      shared_ptr(T* p){
        this->ptr = p;
        this->ref_count = new size_t(0);
      }

      shared_ptr(shared_ptr& old) {
        if (!old)
          return;

        if (old.ptr && old.ref_count) {
          this->ptr = old.ptr;
          this->ref_count = old.ref_count;
          inc_ref();
        }
      }
      
      shared_ptr(shared_ptr&& old) : ptr(nullptr) {
        this->ptr = old.ptr;
        this->ref_count = old.ref_count;
        old.ptr = nullptr;
        old.ref_count = nullptr;
      }

      shared_ptr& operator=(shared_ptr& old) {
        if (this == &old) {
          return;
        }

        if (this->ptr) {
          dec_ref();
          if (this->ref_count[0] == 0)
            this->shared_ptr::~shared_ptr();
        }

        if (old.ptr && old.ref_count) {
          this->ptr = old.ptr;
          this->ref_count = old.ref_count;
          inc_ref();
        }
      }
      
      shared_ptr& operator=(shared_ptr&& old) {
        if (this->ptr) {
          dec_ref();
          if (this->ref_count[0] == 0)
            this->shared_ptr::~shared_ptr();
        }

        this->ptr = old.ptr;
        this->ref_count = old.ref_count;
        old.ptr = nullptr;
        old.ref_count = nullptr;
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

      explicit operator bool() const noexcept {
        return this->ref_count[0] > 0;
      }

      shared_ptr clone() {
        auto copy = shared_ptr<T, Is_Array>(*this);
        return copy;
      }

      size_t count() {
        if (this->ref_count == nullptr)
          return 0;

        return this->ref_count[0];
      }

      bool unique() {
        return count() > 1;
      }

      ~shared_ptr(){
        if (!this->ptr)
          return;

        dec_ref();

        if (this->ref_count[0] == 0) {
          if (Is_Array){
            delete[] this->ptr;
            this->ptr = nullptr;
          } else {
            delete this->ptr;
            this->ptr = nullptr;
          }
          delete this->ref_count;
        }
      }

    private:
      inline void inc_ref() {
        this->ref_count[0] += 1;
      }

      inline void dec_ref() {
        if (this->ref_count[0] > 0) {
          this->ref_count[0] -= 1;
        }
      }

      T* ptr = nullptr;
      size_t* ref_count = nullptr;
  };

  // single item unique
  // make_shared<int>()
  template<class T, class... Args>
  enable_if_t<!is_array<T>::value, shared_ptr<T>> make_shared(Args&&... args) {
    return shared_ptr<T>(new T(forward<Args>(args)...));
  }

  // array unique
  // make_shared<int[]>(10)
  template<class T>
  enable_if_t<is_unbounded_array_v<T>, shared_ptr<remove_all_extents_t<T>, true>> make_shared(size_t n) {
    using inner = remove_all_extents_t<T>;
    return shared_ptr<inner, true>(new inner[n]());
  }

  // bounded array disallowed
  // make_shared<int[10]>()
  template<class T, class... Args>
  enable_if_t<is_bounded_array_v<T>> make_shared(Args&&...) = delete;
}

#endif
