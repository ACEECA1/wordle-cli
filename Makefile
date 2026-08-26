CXX = g++
CXXFLAGS = -std=c++17 -Wall -I$(HOME)/.local/include -I/usr/local/include
LDFLAGS = -L$(HOME)/.local/lib -L/usr/local/lib -lcpr -lcurl -lssl -lcrypto

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin

TARGET = wordle

all: $(TARGET)

$(TARGET):
	$(CXX) $(CXXFLAGS) *.cpp -o $(TARGET) $(LDFLAGS)

run: all
	./$(TARGET)

install: all
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 $(TARGET) $(DESTDIR)$(BINDIR)/$(TARGET)

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run install uninstall clean
