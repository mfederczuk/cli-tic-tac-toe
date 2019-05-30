# src/subdir.mk

OBJECTS +=

bin/%.o: src/%.cpp
	$(info Building file '$@' ...)
	@mkdir -p 'bin'
	@$(CXX) -Iinclude -c '$<' -o '$@'
#bin/%.o

src/%.cpp:
	$(error $@: No such file)
#src%.c
