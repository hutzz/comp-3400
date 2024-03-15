#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include "benchmark.hxx"

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
    // auto const& r = std::reduce(std::execution::par_unseq, v.begin(), v.end());


    return 0;
}