##
## EPITECH PROJECT, 2022
## make
## File description:
## desc
##

SRC = \
	src/main.c

OBJ = $(SRC:.c=.o)

GCC = gcc

INCLUDE_FLAGS = \
	-I include

C_WARNING_FLAGS = -Wextra -Wall
C_FLAGS = $(C_WARNING_FLAGS) $(INCLUDE_FLAGS)

.c.o:
	@echo "$(notdir $(CURDIR)): C '$<'"
	@$(GCC) $(C_FLAGS) -c -o $*.o $<

all: stcp.a
.PHONY : all

stcp.a: $(OBJ)
	@ar rc $@ $(OBJ)
.PHONY : tools_box.a

clean:
	@find . \( -name "*.o" -or -name "*.a" \) -delete
.PHONY : clean
