INCLUDE = -I include/
LIBS = -lsfml-graphics -lsfml-system -lsfml-window
all: antSim

antSim: main.o Game.o ant.o food.o pheromon.o 
	g++ main.o Game.o ant.o food.o  pheromon.o -o antSim $(LIBS)
main.o: ../src/main.cpp ../include/Game.hpp
	g++ -c ../src/main.cpp
Game.o: ../src/Game.cpp ../include/Game.hpp ../include/ant.hpp 
	g++ -c ../src/Game.cpp 
ant.o: ../src/ant.cpp ../include/ant.hpp ../include/pheromon.hpp ../include/food.hpp 
	g++ -c src/ant.cpp 
food.o: ../src/food.cpp ../include/food.hpp
	g++ -c ../src/food.cpp
pheromon.o: ../src/pheromon.cpp ../include/pheromon.hpp
	g++ -c ../src/pheromon.cpp