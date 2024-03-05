#include "utils.hxx" // intentionally placed first in provided code

#include <array>
#include <concepts>
#include <csignal>
#include <type_traits>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//
// test_*() functions are used to easily invoke test code.
// You are expected to ensure that all commented and #if 0'd out
// code does not compile and any other illegal uses of the zero
// function defined in utils.hxx does not compile.
//

template <typename T>
void test_zero_init_return()
{
  [[maybe_unused]] auto v = zero<T>();
}

template <typename T>
void test_zero_ref()
{
  T v; zero(v);
}

template <typename T>
void test_all_zeros()
{
  test_zero_init_return<T>();
  test_zero_ref<T>();
}

int main()
{
  // some built-in types...
  test_all_zeros<double>();
  test_all_zeros<int>();
  test_zero_init_return<int*>();
  //test_zero_ref<int*>(); // ERROR: prohibited by design

  using fixed_length_array_type = char[1024];
  //test_all_zeros<fixed_length_array_type>(); 
    // ERROR: illegal in language since C++ does not permit returning a language
    //        array by value from a function call; is prohibited in code due to
    //        requires clause
  test_zero_ref<fixed_length_array_type>();

  using unknown_length_array_type [[maybe_unused]] = char[];
  //test_zero_init_return<unknown_length_array_type>();
    // ERROR: arrays of unknown bound decay to pointers which utils.hxx
    //        prohibits to be used with zero*().

  // struct addrinfo (e.g., network programming)...
  test_all_zeros<struct addrinfo>();

  // struct sigaction (e.g., signal programming)...
  test_all_zeros<struct sigaction>();

  // a "plain-old-data" (POD) type...
  struct A { int a; };
  static_assert(std::is_trivial_v<A> && std::is_standard_layout_v<A>);
  test_all_zeros<A>();

  // a type that does not have standard layout...
  struct B : public A { int b; };
  static_assert(std::is_trivial_v<B> && !std::is_standard_layout_v<B>);
  //test_zero_init_return<B>();
  //test_zero_ref<B>();

  // a type that does not have standard layout...
  struct C { virtual void c() { } };
  static_assert(!std::is_trivial_v<C> && !std::is_standard_layout_v<C>);
  //test_zero_init_return<C>();
  //test_zero_ref<C>();

  // a type that has standard layout but is not trivial...
  struct D { D() {} D(D const&) { } int d; };
  static_assert(!std::is_trivial_v<D> && std::is_standard_layout_v<D>);
  //test_zero_init_return<D>();
  //test_zero_ref<D>();

  // std::array...
  using array_type = std::array<int,3>;
  static_assert(std::is_trivial_v<array_type> && std::is_standard_layout_v<array_type>);
  test_all_zeros<array_type>();

  // std::vector...
  using vector_type = std::vector<int>;
  static_assert(!std::is_trivial_v<vector_type> && std::is_standard_layout_v<vector_type>);
  //test_zero_init_return<vector_type>();
  //test_zero_ref<vector_type>();
}

