#include <iostream>
#include <cstdint>
#include <tuple>
#include <map>
#include <chrono>

class ackermann {
public:
    using ret_type = std::intmax_t;
    using args_type = std::tuple<std::intmax_t, std::intmax_t>;
    using cache_type = std::map<args_type, ret_type>;

    static cache_type cache;

    ret_type operator()(std::intmax_t const m, std::intmax_t const n) const {
        ackermann a;
        if (m == 0) {
            return n + 1;
        } else if (m > 0 && n == 0) {
            auto key = std::make_tuple(m - 1, 1);
            if (cache.find(key) != cache.end()) {
                return cache[key];
            } else {
                cache[key] = a(m - 1, 1);
                return cache[key];
            }
        } else {
            auto innerKey = std::make_tuple(m, n - 1);
            if (cache.find(innerKey) != cache.end()) {
                auto outerKey = std::make_tuple(m - 1, cache[innerKey]);
                if (cache.find(outerKey) != cache.end()) {
                    return cache[outerKey];
                } else {
                    cache[outerKey] = a(m - 1, cache[innerKey]);
                    return cache[outerKey];
                }
            } else {
                cache[innerKey] = a(m, n - 1);
                cache[std::make_tuple(m - 1, cache[innerKey])] = a(m - 1, cache[innerKey]);
                return cache[std::make_tuple(m - 1, cache[innerKey])];
            }
        }
    }
};
ackermann::cache_type ackermann::cache;

int main() {
    using namespace std;
    using namespace chrono;

    ackermann a;
    auto start_time = high_resolution_clock::now();

    for (int m = 0; m != 5; ++m) {
        cout << "m = " << m << ": ";
        intmax_t last_result = 0;
        for (int n = 0; n != 10 && last_result < 65533; ++n) {
            last_result = a(m,n);
            cout << last_result << ' ';
        }
        cout << '\n';
    }
    
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end_time - start_time);
    cout << "\nTime taken: " << duration.count() / 1000 << " ms\n";
}
