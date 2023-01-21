##
## EPITECH PROJECT, 2022
## make
## File description:
## desc
##

SRC = \
	src/stcp_hand_check.c \
	src/stcp_init.c \
	src/stcp_listener.c \
	src/stcp_send.c \
	src/stcp_receive.c \
	src/stcp_destroy_packet.c \
	src/stcp_create_packet.c \
	src/stcp_sync.c \
	src/utils/data_to_binary.c \
	src/stcp_time_out.c \
	src/stcp_packet_drop.c

OBJ = $(SRC:.c=.o)

GCC = gcc

INCLUDE_FLAGS = \
	-I include \
	-I ../tools_box/include/

C_WARNING_FLAGS = -Wextra -Wall -g
C_FLAGS = $(C_WARNING_FLAGS) $(INCLUDE_FLAGS)

.c.o:
	@echo "$(notdir $(CURDIR)): C '$<'"
	@$(GCC) $(C_FLAGS) -c -o $*.o $<

all: stcp.a
.PHONY : all

stcp.a: $(OBJ)
	@ar rc $@ $(OBJ)
.PHONY : stcp.a

clean:
	@find . \( -name "*.o" -or -name "*.a" \) -delete
.PHONY : clean

re: clean all
.PHONY: re
