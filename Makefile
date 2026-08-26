CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(HOME)/.local/include
LDFLAGS = -L$(HOME)/.local/lib -lcpr -lcurl -lssl -lcrypto

all:
	$(CXX) $(CXXFLAGS) *.cpp -o wordle $(LDFLAGS)

run: all
	./wordle

clean:
	rm -f wordle
