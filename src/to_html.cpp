#include <htll/to_html.hpp>

namespace htll {

static void to_html_internal(std::ostream &os, const element &elem, bool ugly);

void
to_html_internal(std::ostream &os, const element &elem, bool ugly)
{
	if (elem.text.size() == 0) {
		os << '<' << elem.name;
		for (const auto &attr : elem.attributes) {
			os << ' ' << attr.first;
			if (attr.second.has_value()) {
				os << "=\"" << attr.second.value() << '"'; // TODO: escape "
			}
		}
		if (elem.children.size() == 0) {
			os << "/>";
		} else {
			os << '>';
			if (!ugly) os << '\n';
			for (const element &child : elem.children) {
				to_html_internal(os, child, ugly);
			}
			if (!ugly) os << '\n';
			os << "</" << elem.name << '>';
		}
		if (!ugly) os << '\n';
	} else {
		os << elem.text; // TODO: escape <>
	}
}

void
to_html(std::ostream &os, const element &root, bool ugly)
{
	for (const element &child : root.children) {
		to_html_internal(os, child, ugly);
	}
	if (ugly) os << '\n';
}

}
