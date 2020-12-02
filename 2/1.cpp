#include <cstddef>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>

int main(int argc, char* argv[]) {

    size_t valid = 0;
    for(;;) {
        std::string range;
        std::cin >> range;

        if (std::cin.eof()) {
        break;
        }

        size_t range_delim = range.find('-');
        int lower = std::stoi(range.substr(0, range_delim));
        int higher = std::stoi(range.substr(range_delim+1));

        std::string char_token;
        std::cin >> char_token;
        char_token.pop_back();
        char target = char_token[0];

        std::string pass;
        std::cin >> pass;

        std::cout << lower << " " << higher << " " << target << " " << pass << std::endl;

        int count = 0;
        // part 1
#if 0
        count = std::count(pass.begin(), pass.end(), target);
        if ( (lower <= count) && (higher >= count) )  {
            ++valid;
        }
        // part 2
#else
        if (target == pass[lower-1]) ++count;
        if (target == pass[higher-1]) ++count;
        if (1 == count) {
            ++valid; 
            std::cout << "valid" << std::endl;
        }
#endif
    }
    std::cout << valid << std::endl;
    return 0;
}
