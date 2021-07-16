#ifndef _HTLL_to_html_hpp
#define _HTLL_to_html_hpp

#include <htll/element.hpp>
#include <ostream>

namespace htll {

void to_html(std::ostream &os, const element &root, bool ugly = true);

}

#endif
