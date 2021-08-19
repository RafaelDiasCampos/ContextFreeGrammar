CXX=g++
CXXFLAGS=-g -ggdb -Ofast -Wall
TEST_ARGS=examples/math.json 4

TARGET=context_free_grammar
OBJS=src/ContextFreeGrammar.o \
	 src/Grammar.o \
	 src/GrammarState.o \
	 src/GrammarRule.o \
	 src/GrammarObject/LiteralObject.o \
	 src/GrammarObject/StateObject.o

all: $(TARGET)

clean: 
	rm -rf $(TARGET) $(OBJS)

install: 
	cp $(TARGET) /usr/local/bin

test:
	make; ./$(TARGET) $(TEST_ARGS)

src/ContextFreeGrammar.o: src/Grammar.h
src/Grammar.o: src/Grammar.h
src/GrammarState.o: src/GrammarState.h
src/GrammarRule.o: src/GrammarRule.h
src/GrammarObject/LiteralObject.o: src/GrammarObject/LiteralObject.h
src/GrammarObject/StateObject.o: src/GrammarObject/StateObject.h

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<