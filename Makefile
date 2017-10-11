PROGRAM=kockaota

CC=g++
CFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb

all: compile doc

run: compile
	./$(PROGRAM)
compile: $(PROGRAM)

doc: src/Effect.cpp src/Attacker.cpp src/Attacker.h src/Effect.h src/EffectTower.cpp src/EffectTower.h src/Freeze.h src/Game.cpp src/Game.h src/Level.cpp src/main.cpp src/MapLoader.cpp src/MapLoader.h src/Position.h src/ShortestWays.cpp src/ShortestWays.h src/ShredArmor.h src/Tower.cpp src/Tower.h src/Wall.h src/Weaken.h
	doxygen Doxyfile 2>/dev/null
$(PROGRAM):obj/Effect.o obj/Attacker.o obj/EffectTower.o obj/Game.o obj/Level.o obj/main.o obj/MapLoader.o obj/ShortestWays.o obj/Tower.o
	$(CC) $(CFLAGS) $^ -lncurses -o $@

obj:

	mkdir obj

clean:
	rm -rf $(PROGRAM) obj/ doc/ 2>/dev/null
obj/Attacker.o: src/Attacker.cpp src/Attacker.h src/Tower.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/EffectTower.o: src/EffectTower.cpp src/EffectTower.h src/Attacker.h src/Freeze.h src/ShredArmor.h src/Weaken.h src/Effect.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/Game.o: src/Game.cpp src/Game.h src/Level.h src/Attacker.h src/MapLoader.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/Level.o: src/Level.cpp src/Level.h src/Wall.h src/Attacker.h src/Tower.h src/ShortestWays.h src/EffectTower.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/main.o: src/main.cpp src/Game.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/MapLoader.o: src/MapLoader.cpp src/MapLoader.h src/Level.h src/Attacker.h src/Wall.h src/Tower.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/ShortestWays.o: src/ShortestWays.cpp src/ShortestWays.h src/Level.h src/Position.h src/Attacker.h src/Wall.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/Tower.o: src/Tower.cpp src/Tower.h src/Attacker.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
obj/Effect.o: src/Effect.cpp src/Effect.h src/Attacker.h | obj
	$(CC) $(CFLAGS) -c $< -o $@
