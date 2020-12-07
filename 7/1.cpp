#include <cstddef>
#include <functional>
#include <iostream>
#include <string>
#include <cstdint>
#include <algorithm>
#include <sstream>
#include <vector>
#include <array>
#include <set>
#include <map>
#include <functional>
#include <regex>


/*
 light gold mirrored brown
26	        std::string remainder{match_min.suffix()};
(gdb) 
27	        while (remainder != ".") {
(gdb) 
28	            std::cout << " "  <<  remainder << std::endl;
(gdb) 
 , 1 muted chartreuse bag, 2 wavy yellow bags.
29	            std::smatch match_rest{}; 
(gdb) 
30	            std::regex_search(remainder, match_rest, re_rest);
(gdb) 
31	            std::cout << "-" << match_rest[1] << std::endl;
(gdb) 
-muted chartreuse

Breakpoint 1, main () at 1.cpp:32
32	            remainder = match_rest.suffix();
(gdb) 
29	            std::smatch match_rest{}; 
(gdb) 
27	        while (remainder != ".") {
(gdb) 
28	            std::cout << " "  <<  remainder << std::endl;
(gdb) 
 , 2 wavy yellow bags.
29	            std::smatch match_rest{}; 
(gdb) 
30	            std::regex_search(remainder, match_rest, re_rest);
(gdb) 
31	            std::cout << "-" << match_rest[1] << std::endl;
(gdb) 
-wavy yellow

Breakpoint 1, main () at 1.cpp:32
32	            remainder = match_rest.suffix();
(gdb) 
29	            std::smatch match_rest{}; 
(gdb) 
27	        while (remainder != ".") {
(gdb) 
26	        std::string remainder{match_min.suffix()};
(gdb) 
22	        std::smatch match_min{}; 
(gdb) 
20	        auto re_rest = std::regex(", [0-9]+ (.*?) bags?");
(gdb) 
*/

int main() {

    std::string line{};
    while (std::getline(std::cin, line)){
        auto re_min = std::regex("(.*?) bags? contain [0-9]+ (.*?) bags?");
        auto re_rest = std::regex(", [0-9]+ (.*?) bags?");

        std::smatch match_min{}; 
        std::regex_search(line, match_min, re_min);
        std::cout << match_min[1] << " " << match_min[2] << std::endl;

        std::string remainder{match_min.suffix()};
        while (remainder != ".") {
            std::cout << " "  <<  remainder << std::endl;
            std::smatch match_rest{}; 
            std::regex_search(remainder, match_rest, re_rest);
            std::cout << "-" << match_rest[1] << std::endl;
            remainder = match_rest.suffix();
        }
    }
    return 0;
}
