CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD
EXEC = sorcery
OBJECTS = Sorcery.o Card.o Minion.o Spell.o Enchantment.o Ritual.o Player.o Deck.o Board.o ascii_graphics.o Subject.o Component.o Decorator.o GiantStrength.o Enrage.o Haste.o MagicFatigue.o Silence.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
