CXX := g++
CXX_FLAGS := -std=c++11

all: clean build

build:
	$(CXX) linerewrite.cpp -o rewrite $(CXX_FLAGS)

install:
	cp ./rewrite /usr/local/bin

uninstall:
	rm -f /usr/local/bin/rewrite

clean:
	rm -f rewrite