CXX = g++
CXXFLAGS = -std=c++17 -Wall

all:
	$(CXX) $(CXXFLAGS) *.cpp -o wordle

run: all
	./wordle

clean:
	rm -f wordle
