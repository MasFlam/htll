#ifndef _HTLL_element_hpp
#define _HTLL_element_hpp

#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace htll {

struct element {
	std::string text; // empty if this is not a text element
	std::string name;
	std::vector<std::pair<std::string, std::optional<std::string>>> attributes;
	std::vector<element> children;
};

std::ostream &operator<<(std::ostream &os, const element &elem);

}

#endif
