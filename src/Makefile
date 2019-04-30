CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g -c
EXEC = TreasureHunter TreasureHunterAI TreasureHunterLog
OBJ = types.o list.o map.o treasure.o movement.o Treasure_Hunter.o
SRC = types.c list.c map.c treasure.c movement.c Treasure_Hunter.c

all: TreasureHunter TreasureHunterAI TreasureHunterLog

TreasureHunter: $(OBJ)
	$(CC) $(OBJ) -o TreasureHunter

TreasureHunterAI:

TreasureHunterLog:

$(OBJ):
	$(CC) $(CFLAGS) $(SRC)

clean:
	rm -rf $(EXEC) $(OBJ)
