#ifndef A5_SOLN_HXX
#define A5_SOLN_HXX

#include <iostream>
#include <iomanip>
#include <variant>

struct special {
    std::string text;
};

std::istream& operator>>(std::istream& is, special& s) {
    return is >> std::quoted(s.text);
}

std::ostream& operator<<(std::ostream& os, special const& s) {
    return os << std::quoted(s.text);
}

using many = std::variant<std::monostate, long long, double, special>;

std::ostream& operator<<(std::ostream& os, many const& m) {
    auto idx = m.index();
    switch (idx) {
        case 1: std::cout << "integer " << std::get<1>(m) << " "; break;
        case 2: std::cout << "fltpt " << std::get<2>(m) << " "; break;
        case 3: std::cout << "string " << std::get<3>(m) << " "; break;
        default: break;
    }
    return os;
}

std::istream& operator>>(std::istream& is, many& m) {
    try {
        if (std::string word; is >> word) {
            if (word == "integer") {
                if (long long integer; is >> integer) {
                    m = integer;
                } else {
                    // these setstates are a bit redundant given the one at the end, but I wanted to make sure I precisely followed the instructions for this part
                    is.setstate(std::ios_base::failbit);
                }
            } else if (word == "fltpt") {
                if (double fltpt; is >> fltpt) {
                    m = fltpt;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            } else if (word == "string") {
                if (special str; is >> str) {
                    m = str;
                } else {
                    is.setstate(std::ios_base::failbit);
                }
            }
            if (word == "integer" || word == "fltpt" || word == "string")
                return is;
        }
        is.setstate(std::ios_base::failbit);
        return is;
    }
    catch (...) {
        if (m.valueless_by_exception()) 
            is.setstate(std::ios_base::badbit);
        throw;
    }
}

#endif
