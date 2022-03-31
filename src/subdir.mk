# SPDX-License-Identifier: CC0-1.0

# src/subdir.mk

OBJECTS += \
bin/main.o \
bin/tic-tac-toe.o \
bin/utils.o

bin/%.o: src/%.cpp
	$(info Building file '$@' ...)
	@mkdir -p 'bin'
	@$(CXX) -std=c++14 -Iinclude -c '$<' -o '$@'
#bin/%.o

src/%.cpp:
	$(error $@: No such file)
#src%.c
