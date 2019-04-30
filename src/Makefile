CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g -c
EXEC = TreasureHunter TreasureHunterAI TreasureHunterLog
OBJ = explore.o list.o map.o treasure.o Treasure_Hunter.o
SRC = explore.c list.c map.c treasure.c Treasure_Hunter.c

all: TreasureHunter TreasureHunterAI TreasureHunterLog

TreasureHunter: $(OBJ)
	$(CC) $(OBJ) -o TreasureHunter

$(OBJ):
	$(CC) $(CFLAGS) $(SRC)

clean:
rm -rf $(EXEC) $(OBJ)
