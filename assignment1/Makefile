CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
OBJ = main.o dict.o csv.o search.o patricia.o

%.o: src/%.c
    $(CC) $(CFLAGS) -c $< -o $@

dict1: $(OBJ)
    $(CC) $(OBJ) -o dict1

dict2: $(OBJ)
    $(CC) $(OBJ) -o dict2

dict4: $(OBJ)
    $(CC) $(OBJ) -o dict4

.PHONY: clean

clean:
    rm -f *.o dict1 dict2 dict4
