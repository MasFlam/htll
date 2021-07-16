CXX := g++
CXXFLAGS := -std=c++17 -Iinclude
LDFLAGS :=

.PHONY: clean

htll: main.o element.o parsing.o to_html.o
	$(CXX) -o $@ $^ $(LDFLAGS)

main.o: src/main.cpp include/htll/element.hpp include/htll/parsing.hpp include/htll/to_html.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/main.cpp

element.o: src/element.cpp include/htll/element.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/element.cpp

parsing.o: src/parsing.cpp include/htll/parsing.hpp include/htll/element.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/parsing.cpp

to_html.o: src/to_html.cpp include/htll/to_html.hpp include/htll/element.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ src/to_html.cpp

clean:
	rm -f *.o
	rm -f htll
