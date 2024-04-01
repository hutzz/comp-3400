#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <type_traits>
#include <concepts>
#include <execution>
#include <unordered_map>
#include "benchmark.hxx"


template <typename A, typename B>
concept same_type =
  std::same_as<
    std::remove_cvref_t<A>,
    std::remove_cvref_t<B>
  >
;

template <typename T, typename MapT = std::unordered_map<T,std::size_t>>
class histogram_reducer
{
public:
    using value_type = T;
    using histogram_type = MapT;

private:
    histogram_type hist_;

public:
    histogram_reducer() = default;
    histogram_reducer(histogram_reducer const&) = default;
    histogram_reducer& operator=(histogram_reducer const&) = default;
    histogram_reducer(histogram_reducer&&) = default;
    histogram_reducer& operator=(histogram_reducer&&) = default;

private:
    struct internal_t final { };
    static constexpr internal_t internal{};

    histogram_reducer(histogram_reducer const& h, internal_t);

private:
    void process(value_type const& v);
    void process(histogram_reducer const& h);

public:
    template <same_type<value_type> A>
    histogram_reducer(A&& a);
    
    template <same_type<value_type> A, same_type<value_type> B>
    histogram_reducer(A&& a, B&& b);

    template <same_type<value_type> A, same_type<histogram_reducer> B>
    histogram_reducer(A&& a, B&& b);

    template <same_type<histogram_reducer> A, same_type<value_type> B>
    histogram_reducer(A&& a, B&& b);

    template <same_type<histogram_reducer> A, same_type<histogram_reducer> B>
    histogram_reducer(A&& a, B&& b);
    
    histogram_type const& get() const;

    template <typename A, typename B>
    histogram_reducer operator()(A&& a, B&& b) const;
};

int main(int argc, char* argv[]) {
    try {
        auto loc = std::locale("en_CA");
        std::clog.imbue(loc);
        std::cout.imbue(loc);
    } 
    catch (const std::runtime_error& e) {
        std::clog << "  LOCALE EXCEPTION: " << e.what() << '\n';
    }
    catch (...) {
        std::clog << "  UNKNOWN EXCEPTION\n";
    }

    std::size_t N;
    int LO, HI;

    if (argc != 5 || std::string(argv[1]) != "gen") {
        std::clog << "Usage: " << argv[0] << " gen <N> <LO> <HI>" << '\n';
        return 1;
    }

    std::istringstream N_stream(argv[2]), LO_stream(argv[3]), HI_stream(argv[4]);

    if (!(N_stream >> N) || !(LO_stream >> LO) || !(HI_stream >> HI)) {
        std::clog << "Usage: " << argv[0] << " gen <N> <LO> <HI>" << '\n';
        return 1;
    }
    std::clog << "gen N = <" << N << ">, LO = <" << LO << ">, HI = <" << HI << ">" << '\n';

    std::cout << "generating random numbers... " << '\n';
    std::cout.flush();
    std::random_device r;
    std::default_random_engine eng(r());
    std::uniform_int_distribution<int> dist(LO, HI);
    std::vector<int> v;
    v.reserve(N);
    benchmark<> bench;
    std::generate_n(std::back_inserter(v), N, [&dist, &eng]() {
        return dist(eng);
    });
    auto const elapsed = bench.elapsed();
    std::cout << elapsed << " seconds elapsed\n";
    std::cout << "  max number of bins: " << dist.max() - dist.min() + 1 << '\n';

    std::cout << "computing histogram... " << '\n';
    std::cout.flush();
    benchmark<> bench2;
    // auto const& reduce = std::reduce(std::execution::par_unseq, v.begin(), v.end(), histogram_reducer<int>{},
    //     [](const histogram_reducer<int>& a, const histogram_reducer<int>& b) {
    //         histogram_reducer<int> result(a);
    //         result.process(b);
    //         return result;
    //     });
    // std::cout << elapsed << " seconds elapsed\n";
    // std::cout << "  computed number of bins: " << reduce.get().size();
    // std::size_t sum;
    // for (const auto& item : reduce.get()) {
    //     sum += item.second;
    // }
    // std::cout << "  number of values: " << sum << '\n';
    // (sum == v.size()) ? std::cout << "  values check: passed\n" : std::cout << "  values check: FAILED\n";

    return 0;
}
