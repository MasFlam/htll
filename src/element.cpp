#include <htll/element.hpp>

namespace htll {

std::ostream &
operator<<(std::ostream &os, const element &elem)
{
	if (elem.text.size() == 0) {
		os << '(' << elem.name;
		for (const auto &attr : elem.attributes) {
			os << " :" << attr.first;
			if (attr.second.has_value()) {
				os << " \"" << attr.second.value() << '"';
			} else {
				os << ':';
			}
		}
		for (const element &child : elem.children) {
			if (child.text.size() == 0) {
				os << '\n';
			} else {
				os << ' ';
			}
			os << child;
		}
		os << ')';
	} else {
		os << elem.text;
	}
	return os;
}

}
