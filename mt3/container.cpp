#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 7, 3, 11, 2};
    std::sort(v.begin(), v.end());
    for (auto i : v) {
        std::cout << i << " ";
    }
    auto h = v.begin();
    auto k = std::find(v.begin(), v.end(), 3);
    std::advance(h, 3);
    std::cout << *h << " ";
    std::cout << *k;
    std::cout << '\n' << '\n';

    auto pos1 = std::find(v.begin(), v.end(), 3);
    auto pos2 = std::transform(pos1, v.end(), pos1, [](int elem) { return elem * 2; });

    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "pos1 = " << *(pos1);
    std::cout << '\n' << '\n';

    std::transform(std::next(pos1), pos2, std::next(pos1), [](int elem) { return elem * 3; });
    for (auto it = v.begin(); it != pos2; ++it) {
        std::cout << *it << " ";
    }
    std::cout << '\n' << '\n';

    std::transform(std::next(pos1), pos2, std::back_inserter(v), [](int elem) { return elem * 2; });
    for (auto it : v) {
        std::cout << it << " ";
    }
    std::cout << '\n' << '\n';

    return 0;
}