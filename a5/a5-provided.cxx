#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "a5-soln.hxx"
#include "a5-soln.hxx" // remember to use #include guards!

int main()
{
  using namespace std;

  vector<many> v;
  copy(
    istream_iterator<many>(cin), istream_iterator<many>(),
    back_inserter(v)
  );

  cout 
    << "Read in: "
    << count_if(v.cbegin(),v.cend(),
          [](many const& m) { return m.index() == 1; }) << " integers, "
    << count_if(v.cbegin(),v.cend(),
          [](many const& m) { return m.index() == 2; }) << " fltpts, "
    << count_if(v.cbegin(),v.cend(),
          [](many const& m) { return m.index() == 3; }) << " strings\n"
  ;

  copy(
    v.begin(), v.end(),
    ostream_iterator<many>(cout, "\n")
  );
}
