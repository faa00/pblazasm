#
# makefile for compiling for Windoze using MinGW w/o eclipse
# 16-jul-09	hvk	initial
# 24-jul-09	hvk	fixed echo
# 15-oct-10	hvk	using ''tcc' of http://bellard.org/tcc/ and 'rm' of Xilinx/cygwin
#

## defines

INC = ../common

RM = rm
CC = gcc
 
C_SRCS += \
./pBlazDIS.c \
../common/dbuf.c \
../common/dbuf_string.c \
../common/pbLibgen.c \
../common/getopt.c

EXE = "./pBlazDIS"
OBJS = $(C_SRCS:.c=.o)
LIBS = 
INCS = -I$(INC)
CFLAGS = $(INCS) -g3 -Wall -c -O3 -DTCC -DHAVE_STRING_H

## rules

# All Target
all:	test

test:	$(EXE)
#	$(EXE) -v ../pBlazASM/pBlazASM_Syntax.mem
	$(EXE) -v -6 all_kcpsm6_syntax_disasm.hex

# Tool invocations
$(EXE):	$(OBJS)
	@echo Building: $(EXE)
	$(CC) -o $@ $^ $(LIBS)
	
%.o : %.c
	@echo Building: "$@"
	$(CC) $(CFLAGS) -o"$@" "$<"

# Other Targets
clean:
	-@echo Clean up: $(OBJS) $(EXE)
	-$(RM) $(OBJS) $(EXE)

.PHONY: all clean
.SECONDARY:
