TARGET = tic-tac-toe

OBJECTS=
include src/subdir.mk

all: $(OBJECTS)
	$(info Building executable '$(TARGET)' ...)
	@$(CXX) $(OBJECTS) -o '$(TARGET)' -lncurses
#all

clean:
	$(info Cleaning...)
	@rm -vrf 'bin' '$(TARGET)'
#clean

.PHONY: all clean
