MAKEFLAGS += --no-builtin-rules
MAKEFLAGS += --no-builtin-variables
.SUFFIXES:

GTEST_PATH=C:/Program Files (x86)/googletest-distribution
CC=g++ -Wall -Wextra --std=c++17 -isystem "${GTEST_PATH}/include"  -L"${GTEST_PATH}/bin"
LIBS=

RMRF=rm -rf
MKDIR=mkdir -p
CP=cp -rf
EXEC_EXT=
LIBS_TEST=-lgtest
WHICH=which
DYLIB=.so

# Determining target OS 
ifeq ($(OS),Windows_NT)
	RMRF=./../sane_windows/sane_rm.exe
	CP=./../sane_windows/sane_cp.exe -f
	MKDIR=./../sane_windows/sane_mkdir.exe
	EXEC_EXT=.exe
	WHICH=where.exe
	DYLIB=.dll

	CC+=-D WIN32
	GTEST_PATH=C:/Program Files (x86)/googletest-distribution
else
	UNAME_S := $(shell uname -s)
	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_S),Linux)
		CC += -D LINUX
	endif
	ifeq ($(UNAME_S),Darwin)
		CC += -D OSX
		DYLIB=.dylib
	endif
endif

# =====
# =
# ACTUAL MAKEFILE LOGIC
# =
# =====
HEADERS = $(wildcard *.hpp *.h */*.hpp */*.h)
TEST_BIN = test_bin${EXEC_EXT}

TEST_SRC = $(wildcard tests/*.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

CONTAINERS = s21_containers.h $(wildcard containers/*)

all: test

test: ${TEST_BIN}
	./${TEST_BIN}

${TEST_BIN}: ${TEST_OBJ} ${CONTAINERS}
	${CC} $^ ${LIBS} ${LIBS_TEST} -o $@

%.o: %.cpp ${HEADERS}
	${CC} -c $< -o $@

clean:
	${RMRF} *.o
	${RMRF} */*.o
	${RMRF} *.a
	${RMRF} .clang-format
	${RMRF} ${TEST_BIN}

valgrind: ${TEST_BIN}
	valgrind --tool=memcheck --leak-check=yes ./${TEST_BIN}

.clang-format: ../materials/linters/.clang-format
	${CP} $^ $@

format:
	clang-format -i  $(wildcard *.hpp *.h *.cpp */*.cpp */*.h */*.hpp)