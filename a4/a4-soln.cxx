#include <iostream>
#include <cstdint>
#include <tuple>
#include <map>
#include <chrono>

class ackermann {
private:
    using ret_type = std::intmax_t;
    using args_type = std::tuple<std::intmax_t, std::intmax_t>;
    using cache_type = std::map<args_type, ret_type>;
    static cache_type cache;
public:
    ret_type operator()(std::intmax_t const m, std::intmax_t const n) const {
        ret_type result;
        if (auto it = cache.find(args_type{m, n}); it != cache.end())
            return it->second;
        if (m == 0)
            return n + 1;
        else if (m > 0 && n == 0)
            result = (*this)(m - 1, 1);
        else {
            ret_type inner = (*this)(m, n - 1);
            cache[args_type{m, n}] = inner;
            result = (*this)(m - 1, inner);
        }
        cache[args_type{m, n}] = result;
        return result;
    }
};
ackermann::cache_type ackermann::cache;

int main() {
    using namespace std;
    using namespace chrono;

    ackermann a;

    for (int m = 0; m != 5; ++m) {
        cout << "m = " << m << ": ";
        intmax_t last_result = 0;
        for (int n = 0; n != 10 && last_result < 65533; ++n) {
            last_result = a(m,n);
            cout << last_result << ' ';
        }
        cout << '\n';
    }
}
