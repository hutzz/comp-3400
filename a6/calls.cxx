#include <array>
#include <limits>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

template <std::size_t ID>
struct result_t : std::integral_constant<std::size_t,ID> { };

// some overloaded functions to consider...
struct foo
{
  auto operator()(...) const { return result_t<0>{}; }

  template <typename T>
  auto operator()(std::vector<T> const&) const { return result_t<1>{}; }

  template <typename T>
  auto operator()(T const&) const { return result_t<2>{}; }

  template <typename T>
  auto operator()(T&) const { return result_t<3>{}; }
 
  template <typename T>
  auto operator()(T&&) const { return result_t<4>{}; }

  auto operator()(int) const { return result_t<5>{}; }
  auto operator()(double) const { return result_t<6>{}; }
};

// some overloaded functions to consider...
struct bar
{
  template <typename T>
  auto operator()(T const&) const { return result_t<2>{}; }

  auto operator()(double const&) const { return result_t<7>{}; }

  template <typename T>
  requires (sizeof(T) <= 4)
  auto operator()(T const&) const { return result_t<8>{}; }

  template <typename T>
  requires std::numeric_limits<T>::is_integer &&
    (!std::numeric_limits<T>::is_signed)
  auto operator()(T const&) const { return result_t<9>{}; }

  template <typename T>
  requires std::numeric_limits<T>::is_integer &&
    std::numeric_limits<T>::is_signed
  auto operator()(T const&) const { return result_t<10>{}; }
};

template <std::size_t ID>
char const* id(result_t<ID> const&)
{
  switch (ID)
  {
    case 0: return "... overload";
    case 1: return "std::vector<T> const& overload";
    case 2: return "T const& overload";
    case 3: return "T& overload";
    case 4: return "T&& overload";
    case 5: return "int overload";
    case 6: return "double overload";
    case 7: return "double const& overload";
    case 8: return "T const& sizeof <= 4 overload";
    case 9: return "T const& unsigned integer overload";
    case 10: return "T const& signed integer overload";
    default: return "no string set";
  }
}

int main()
{
  using namespace std;

  // rvalues (e.g., variables without a name)...
  { using type = vector<int>; auto r = foo{}(type{}); cout << id(r) << '\n'; }
  { using type = vector<int> const; auto r = foo{}(type{}); cout << id(r) << '\n'; }
  { using type = int; auto r = foo{}(type{}); cout << id(r) << '\n'; }
  { auto r = bar{}(1LL); cout << id(r) << '\n'; }
  { auto r = bar{}(1ULL); cout << id(r) << '\n'; }
  //{ auto r = bar{}(-1); cout << id(r) << '\n'; } // ambiguous
  { auto r = bar{}(-1LL); cout << id(r) << '\n'; }
  { auto r = bar{}(1.3); cout << id(r) << '\n'; }
  { auto r = bar{}(5.2F); cout << id(r) << '\n'; }
  { auto r = bar{}(-2.23L); cout << id(r) << '\n'; }
  cout << '\n';

  // lvalues...
  { using type = vector<int>; type t; auto r = foo{}(t); cout << id(r) << '\n'; }
  { double d{}; auto r = bar{}(d); cout << id(r) << '\n'; }
  { float f{}; auto r = bar{}(f); cout << id(r) << '\n'; }
  { long double ld{}; auto r = bar{}(ld); cout << id(r) << '\n'; }
  cout << '\n';

  // exact match...
  { using type = vector<int> const; type t; auto r = foo{}(t); cout << id(r) << '\n'; }
  { auto r = foo{}(1); cout << id(r) << '\n'; }
  { auto r = foo{}(1.3); cout << id(r) << '\n'; }
  cout << '\n';

  // no argument, >1 argument...
  { using type = int; auto r = foo{}(); cout << id(r) << '\n'; }
  { using type = int; auto r = foo{}(1,4.2); cout << id(r) << '\n'; }
  cout << '\n';

  // 1 argument...
  { auto r = foo{}('a'); cout << id(r) << '\n'; }
  { auto r = foo{}(1.3F); cout << id(r) << '\n'; }
  cout << '\n';
}
