CXX = g++

PREFIX ?= /usr/local
HEADER = QuinarySearchTree.hpp
DEMO_SOURCE = main.cpp 
DEMO_TARGET = demo

LIB += -L$(PREFIX)/lib
INCLUDE += -I$(PREFIX)/include
CPPFLAGS += -std=c++11 -O3 $(LDFLAGS) $(INCLUDE) -fPIC

demo :
	$(CXX) $(CPPFLAGS) $(OBJECT) $(DEMO_SOURCE) -o $(DEMO_TARGET)

install :
	install -m 644 $(HEADER) $(PREFIX)/include

uninstall :
	rm -f $(PREFIX)/include/$(HEADER)

