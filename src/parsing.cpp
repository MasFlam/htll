#include <cctype>
#include <htll/parsing.hpp>
#include <stack>

namespace htll {

enum state_t {
	STATE_NONE,
	STATE_IN_TAG_NAME,
	STATE_IN_TAG_HEAD,
	STATE_IN_ATTR_NAME,
	STATE_AFTER_ATTR_NAME,
	STATE_IN_ATTR_VAL_UNQUOTED,
	STATE_IN_ATTR_VAL,
	STATE_TEXT,
};

element
parse_stream(std::istream &is)
{
	state_t state = STATE_NONE;
	std::stack<element> elstack;
	std::vector<char> buf, buf2;
	elstack.emplace(); // root element
	char c;
	while (!is.eof()) {
		c = is.get();
		switch (state) {
		case STATE_NONE: {
			if (c == '(') {
				state = STATE_IN_TAG_NAME;
			} else if (c == ')') {
				if (elstack.size() == 1) {
					// TODO: syntax error
				} else {
					element elem = elstack.top();
					elstack.pop();
					elstack.top().children.push_back(elem);
				}
			} else if (!std::isspace(c)) {
				state = STATE_TEXT;
				buf.push_back(c);
			}
		} break;
		case STATE_IN_TAG_NAME: {
			if (std::isspace(c)) {
				elstack.emplace().name = std::string(buf.data(), buf.size());
				buf.clear();
				state = STATE_IN_TAG_HEAD;
			} else if (c == ')') {
				elstack.top().children.emplace_back().name = std::string(buf.data(), buf.size());
				buf.clear();
				state = STATE_NONE;
			} else {
				buf.push_back(c);
			}
		} break;
		case STATE_IN_TAG_HEAD: {
			if (c == ':') {
				state = STATE_IN_ATTR_NAME;
			} else if (c == '(') {
				state = STATE_IN_TAG_NAME;
			} else if (c == ')') {
				element elem = elstack.top();
				elstack.pop();
				elstack.top().children.push_back(elem);
				state = STATE_NONE;
			} else if (!std::isspace(c)) {
				state = STATE_TEXT;
				elstack.emplace();
				buf.push_back(c);
			}
		} break;
		case STATE_IN_ATTR_NAME: {
			if (c == ':') {
				elstack.top().attributes.emplace_back(
					std::string(buf.data(), buf.size()),
					std::optional<std::string>()
				);
				buf.clear();
				state = STATE_IN_TAG_HEAD;
			} else if (std::isspace(c)) {
				state = STATE_AFTER_ATTR_NAME;
			} else {
				buf.push_back(c);
			}
		} break;
		case STATE_AFTER_ATTR_NAME: {
			if (c == '"') {
				state = STATE_IN_ATTR_VAL;
			} else if (!std::isspace(c)) {
				state = STATE_IN_ATTR_VAL_UNQUOTED;
				buf2.push_back(c);
			}
		} break;
		case STATE_IN_ATTR_VAL_UNQUOTED: {
			if (std::isspace(c) || c == ')') {
				elstack.top().attributes.emplace_back(
					std::string(buf.data(), buf.size()),
					std::make_optional(std::move(std::string(buf2.data(), buf2.size())))
				);
				buf.clear();
				buf2.clear();
				if (c == ')') {
					element elem = elstack.top();
					elstack.pop();
					elstack.top().children.push_back(elem);
					state = STATE_NONE;
				} else {
					state = STATE_IN_TAG_HEAD;
				}
			} else {
				buf2.push_back(c);
			}
		} break;
		case STATE_IN_ATTR_VAL: { // TODO: escapes
			if (c == '"') {
				elstack.top().attributes.emplace_back(
					std::string(buf.data(), buf.size()),
					std::make_optional(std::move(std::string(buf2.data(), buf2.size())))
				);
				buf.clear();
				buf2.clear();
				state = STATE_IN_TAG_HEAD;
			} else {
				buf2.push_back(c);
			}
		} break;
		case STATE_TEXT: {
			if (c == '(' || c == ')') {
				element text_elem = elstack.top();
				elstack.pop();
				text_elem.text = std::string(buf.data(), buf.size());
				buf.clear();
				elstack.top().children.push_back(text_elem);
				if (c == ')' && elstack.size() != 1) {
					element elem = elstack.top();
					elstack.pop();
					elstack.top().children.push_back(elem);
					state = STATE_NONE;
				} else {
					state = STATE_IN_TAG_NAME;
				}
			} else {
				buf.push_back(c);
			}
		} break;
		}
	}
	if (elstack.size() != 1) {
		// TODO: syntax error -- unfinished element(s)
	}
	return elstack.top();
}

}
