CXXFLAGS=-std=c++1z -Wall -DLOCAL -fsanitize=undefined -D_GLIBCXX_DEBUG -g -Wshadow -g -fdiagnostics-color -Wno-unused-result -Wno-address
%.e: %.cpp
	g++ -std=c++1z -Wall -O2 -o $@ $< -Wshadow -DLOCAL2 -g -fdiagnostics-color -Wno-unused-result -Wno-address -Wno-nonnull-compare

