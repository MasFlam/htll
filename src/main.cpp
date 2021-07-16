#include <cstdlib>
#include <fstream>
#include <iostream>
#include <htll/parsing.hpp>
#include <htll/to_html.hpp>

int
main(int argc, char **argv)
{
	if (argc < 2 || argc > 3) {
		std::cout << "Usage: htll [-ugly] <file>\n";
		return EXIT_FAILURE;
	}
	bool ugly;
	char *fname;
	if (argc == 3) {
		ugly = true;
		fname = argv[2];
	} else {
		ugly = false;
		fname = argv[1];
	}
	std::ifstream file(fname);
	if (!file.good()) {
		std::cout << "Failed to open file\n";
		return EXIT_FAILURE;
	}
	htll::element root = htll::parse_stream(file);
	file.close();
	htll::to_html(std::cout, root, ugly);
	return EXIT_SUCCESS;
}
