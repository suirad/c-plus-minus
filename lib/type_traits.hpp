#pragma once
#ifndef _SLIMSTD_TYPE_TRAITS
#define _SLIMSTD_TYPE_TRAITS

#include "slimstd.hpp"

namespace slimstd {
// integral_constant
template <class _Tp, _Tp __v> struct integral_constant {
  static const _Tp value = __v;
  typedef _Tp value_type;
  typedef integral_constant type;

  operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template <class _Tp, _Tp __v> const _Tp integral_constant<_Tp, __v>::value;

// bool_constant
template <bool _b> using bool_constant = integral_constant<bool, _b>;

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

// is array
template <class T> struct is_array : public false_type {};

template <class T> struct is_array<T[]> : public true_type {};

template <class T, size_t N> struct is_array<T[N]> : public true_type {};

// remove all extents
template <class _Tp> struct remove_all_extents { typedef _Tp type; };
template <class _Tp> struct remove_all_extents<_Tp[]> {
  typedef typename remove_all_extents<_Tp>::type type;
};
template <class _Tp, size_t _Np> struct remove_all_extents<_Tp[_Np]> {
  typedef typename remove_all_extents<_Tp>::type type;
};
template <class _Tp>
using remove_all_extents_t = typename remove_all_extents<_Tp>::type;

template <class> constexpr bool is_unbounded_array_v = false;
template <class T> constexpr bool is_unbounded_array_v<T[]> = true;

template <class> constexpr bool is_bounded_array_v = false;
template <class T, size_t N> constexpr bool is_bounded_array_v<T[N]> = true;

template <bool, class _Tp = void> struct enable_if {};
template <class _Tp> struct enable_if<true, _Tp> { typedef _Tp type; };

template <bool _Bp, class _Tp = void>
using enable_if_t = typename enable_if<_Bp, _Tp>::type;
} // namespace slimstd

#endif
