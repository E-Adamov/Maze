CC=g++
NAME = A1_Maze
FLAGS=-lgtest -lstdc++ -std=c++17
WCHECK=-Werror -Wall -Wextra
BUILD_DIR = build
SOURCES = model/*.cc view/*.cpp
HEADERS = model/*.h view/*.h controller/*.h

OS=$(shell uname)
ifeq ($(OS), Linux)
APP=$(NAME)
LIBS=-lcheck -lpthread -lrt -lm -lsubunit
LEAKS = CK_FORK=no valgrind -s --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test.out
OPEN=xdg-open
else
APP=$(NAME).app
LIBS=-lcheck -lgtest -pthread
LEAKS = leaks --atExit -- ./test.out
OPEN=open
endif

all: build

build: clean
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR)/; qmake ../view/A1_Maze.pro
	make -C $(BUILD_DIR)/

install: uninstall build
	@mkdir -p $(HOME)/$(NAME)/
	cp -rf $(BUILD_DIR)/$(APP) $(HOME)/$(NAME)/
	cp -rf example/*.* $(HOME)/$(NAME)/

uninstall:
	rm -rf $(HOME)/$(NAME)/

tests:
	$(CC) test/test.cc $(FLAGS) $(LIBS) $(WCHECK) -o test.out
	./test.out

dist:
	mkdir -p ./dist
	tar -cvzf ./dist/$(NAME).tgz Makefile model/* controller/* view/* test/* *.html example/*

dvi:
	$(OPEN) text.html
	
style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i $(SOURCES) $(HEADERS)
	clang-format -n $(SOURCES) $(HEADERS)
	rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=unusedFunction --suppress=missingInclude $(SOURCES) $(HEADERS)

leaks: clean tests
	$(LEAKS)

clean:
	rm -rf ./report ./dist ./build
	rm -rf *.o *.out *.gcno *.gcda *.gcov *.info *.dSYM 
