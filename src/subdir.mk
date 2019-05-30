# src/subdir.mk

OBJECTS += bin/utils.o

bin/%.o: src/%.cpp
	$(info Building file '$@' ...)
	@mkdir -p 'bin'
	@$(CXX) -std=c++14 -Iinclude -c '$<' -o '$@'
#bin/%.o

src/%.cpp:
	$(error $@: No such file)
#src%.c
