#include <chrono>
#include <filesystem>
#include <iostream>
#include <regex>
//As it can get tedious writing std::filesystem and std::chrono everyone consider using these namespace aliases:
namespace fs = std::filesystem;
namespace chr = std::chrono;
//You are only permitted to use two "using namespace" statements in your program:
using namespace std::literals::chrono_literals;
//To get the current FILESYSTEM time, use:
const auto cur_time = chr::file_clock::now();
//Then compute the two times you need storing these values in variables so you can use them later:
//cur_time - 7*24h
//cur_time - 24h
const auto one_Day = cur_time - 7 * chr::hours(24);
const auto oneWeek = cur_time - chr::hours(24);
//If no command line arguments are passed to this program
int main (int argc, char* argv[])
{
    //The rest of the code in main() will be all in a try ... catch ... block.
    try
    {
        //Store a fs::path holding the path passed in from the command line.
        //then the path used is the current directory, i.e., ".".
        fs::path start_directory = (argc == 1) ? fs::current_path() : argv[1];
        //Use a range-based for loop to iterate over the current directory only (i.e., don't do this recursively!).
        //Pass to the constructor of the iterator used fs::directory_options::skip_permission_denied
        for (const auto& entry:fs::directory_iterator(start_directory,fs::directory_options::skip_permission_denied))
        {
            //Inside the for loop declare a static std::regex variable passing the aforementioned regular expression and the std::regex_constants to that variable's constructor.
            //static regex matching_filenames("[[:alnum:]]+\\.txt", regex_constants::ECMAScript | regex_constants::icase);
            static std::regex example_regex("[[:alnum:]]+\\.txt", std::regex_constants::ECMAScript | std::regex_constants::icase);
            //Determine if there is a match (i.e., use std::smatch which matches std::string objects) and call std::regex_match passing in your fs::path variable's .path().filename().string() as the string to match and the
            //std::regex static variable you declared earlier.
            if (std::regex_match(entry.path().filename().string(), example_regex)) {
                if (one_Day < entry.last_write_time() && entry.last_write_time() < oneWeek) {
                    std::cout << "FOUND: " << entry.path() << " " << entry.last_write_time() << "\n";
                }
            }
        }
    }    
    //If a std::filesystem::filesystem_error exception occurs at anytime during processing,  
    catch (const std::filesystem::filesystem_error& e)
    {//"EXCEPTION: " follows by e.what() (where e is the caught exception) followed by a newline character all written to std::clog.
        std::clog << "EXCEPTION: " << e.what() << '\n';
        //the following must be output before exiting with an exit status of 1:
        exit(1);
    }
    //If any other exception occurs at anytime during processing,
    catch (const std::exception& e)
    {
        // the following must be output to std::clog: "EXCEPTION: unknown\n" and then the program must exit with an exit status of 2.
        std::clog << "EXCEPTION: unknown "<<'\n';
        exit(2);
    }
}