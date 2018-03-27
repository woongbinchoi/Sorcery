CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = sorcery
OBJECTS = window.o graphicsdisplay.o textdisplay.o ascii_graphics.o emptycard.o spelllist.o spell.o rituallist.o ritual.o player.o minionlist.o minion.o main.o exceptions.o enchantment.o enchantlist.o cardfactory.o card.o board.o deck.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
