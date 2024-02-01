#include <iostream>
#include <chrono>
#include <filesystem>
#include <regex>

namespace fs = std::filesystem;
namespace chr = std::chrono;

int main(int argc, char* argv[]) {
    const fs::path filePath = (argc == 1) ? "." : argv[1];
    const auto cur_time = chr::file_clock::now();
    const auto minTime = cur_time - 7 * chr::hours(24);
    const auto maxTime = cur_time - chr::hours(24);

    try {
        for (const auto& file : fs::directory_iterator(filePath, fs::directory_options::skip_permission_denied)) {
            static const std::regex matchFile("[[:alnum:]]+\\.txt", std::regex_constants::ECMAScript | std::regex_constants::icase);
            if (std::regex_match(file.path().filename().string(), matchFile) && minTime < file.last_write_time() && file.last_write_time() < maxTime) {
                std::cout << "FOUND: " << file.path() << " " << file.last_write_time() << "\n";
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::clog << "EXCEPTION: " << e.what() << "\n";
        return 1;
    }
    catch (...) {
        std::clog << "EXCEPTION: unknown\n";
        return 2;
    }
    return 0;
}
