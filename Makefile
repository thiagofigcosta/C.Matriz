CC=g++
SRC=$(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
EXEC=C.Matrix
CFLAGS=-c -Wall  
LDFLAGS=

all: $(SCR) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXEC)

run: all
	./$(EXEC)

install: all
	@mv $(EXEC) $(bindir)/

rebuild: clean all
