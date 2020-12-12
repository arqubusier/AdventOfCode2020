#include <string>

bool IsBlank(std::string const& str) {
    return (std::string::npos == str.find_first_not_of(" \n\t"));
}

