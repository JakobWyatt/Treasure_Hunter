CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic -g -c
EXEC = TreasureHunter TreasureHunterAI TreasureHunterLog
DEFAULT_OBJ = list.o map.o movement.o Treasure_Hunter.o treasure.o types.o
NONE_OBJ = adventure.o
AI_OBJ = adventureAI.o
LOG_OBJ = adventureLog.o
ADV_DEPENDENCIES = types.h list.h adventure.h adventure.c treasure.h
OBJ = $(DEFAULT_OBJ) $(LOG_OBJ) $(AI_OBJ) $(NONE_OBJ)

all: TreasureHunter TreasureHunterAI TreasureHunterLog

TreasureHunter: $(DEFAULT_OBJ) $(NONE_OBJ)
	$(CC) $(DEFAULT_OBJ) $(NONE_OBJ) -o TreasureHunter

TreasureHunterAI: $(DEFAULT_OBJ) $(AI_OBJ)
	$(CC) $(DEFAULT_OBJ) $(AI_OBJ) -o TreasureHunterAI

TreasureHunterLog: $(DEFAULT_OBJ) $(LOG_OBJ)
	$(CC) $(DEFAULT_OBJ) $(LOG_OBJ) -o TreasureHunterLog


adventure.o: $(ADV_DEPENDENCIES)
	$(CC) $(CFLAGS) adventure.c

adventureAI.o: $(ADV_DEPENDENCIES)
	$(CC) $(CFLAGS) -DAI adventure.c -o adventureAI.o

adventureLog.o: $(ADV_DEPENDENCIES)
	$(CC) $(CFLAGS) -DLOG adventure.c -o adventureLog.o

list.o: list.c list.h
	$(CC) $(CFLAGS) list.c

map.o: map.c map.h types.h treasure.h
	$(CC) $(CFLAGS) map.c

movement.o: movement.c movement.h types.h list.h treasure.h
	$(CC) $(CFLAGS) movement.c

Treasure_Hunter.o: Treasure_Hunter.c map.h movement.h adventure.h types.h
	$(CC) $(CFLAGS) Treasure_Hunter.c

treasure.o: treasure.c treasure.h types.h
	$(CC) $(CFLAGS) treasure.c

types.o: types.c types.h
	$(CC) $(CFLAGS) types.c


clean:
	rm -rf $(EXEC) $(OBJ)
