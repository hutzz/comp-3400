#include "a2-soln.hxx"

#include <algorithm>              // for std::copy, std::sort
#include <iterator>               // for std::back_inserter
#include <iostream>               // for std::cin, std::cout
#include <fstream>                // for std::ifstream
#include <format>                 // for std::format
#include <vector>                 // for std::vector

//=============================================================================

int main()
{
  using namespace std;

  for (int i=1; i<=3; ++i) {
    vector<card> cards; // declare an empty vector of cards

    // read in cards from standard input appending to cards...
    ifstream ifs {format("a2-input{}.dat", i)};
    copy(istream_iterator<card>(ifs), istream_iterator<card>(),
    back_inserter(cards));
    ifs.close();

    // sort the cards...
    sort(cards.begin(), cards.end());

    // write out the cards to standard output from cards...
    ofstream ofs {"temp.dat"};
    copy(cards.begin(), cards.end(), ostream_iterator<card>(ofs," "));
    ofs << '\n';
    ofs.close();

    int result = system(format("diff temp.dat a2-output{}.dat > /dev/null", i).c_str());
    cout << "Test " << i << ": " << (result ? "FAIL" : "PASS") << '\n';
    // system("rm temp.dat");
  }
}

//=============================================================================