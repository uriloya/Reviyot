# All Targets
all: reviiot

# Tool invocations
# Executable "main" depends on the files Card.o and main.o.
reviiot:	bin/Card.o bin/Deck.o bin/Hand.o bin/Player.o bin/Game.o bin/reviiyot.o
	@echo 'Building target: reviiot'
	@echo 'Invoking: C++ Linker'
	g++ -o bin/reviiot bin/Card.o bin/Deck.o bin/Hand.o bin/Player.o bin/Game.o bin/reviiyot.o
	@echo 'Finished building target: reviiot'
	@echo ' '

# Depends on the source and header files
bin/Card.o: src/Card.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Card.o src/Card.cpp

# Depends on the source and header files 
bin/reviiyot.o: src/reviiyot.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/reviiyot.o src/reviiyot.cpp

# Depends on the source and header files
bin/Deck.o: src/Deck.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Deck.o src/Deck.cpp

# Depends on the source and header files
bin/Hand.o: src/Hand.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Hand.o src/Hand.cpp
	
# Depends on the source and header files
bin/Player.o: src/Player.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Player.o src/Player.cpp

# Depends on the source and header files
bin/Game.o: src/Game.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Game.o src/Game.cpp	

#Clean the build directory
clean: 
	rm -f bin/*
	
	
	