
## defines

RM = rm
INC = ../common
CC = gcc

C_SRCS += \
./pBlazASM.c \
./pbLexer.c \
./pbParser.c \
./pbSymbols.c \
../common/dbuf.c \
../common/dbuf_string.c \
../common/pbLibgen.c \
../common/pbLib.c

#../common/getopt.c

EXE = "./pBlazASM"
OBJS = $(C_SRCS:.c=.o)
LIBS = 
INCS = -I$(INC)
CFLAGS = $(INCS) -g3 -Wall -c -O3 -DHAVE_STRING_H

## rules

# All Target
all:	$(EXE) test

# Tool invocations
$(EXE):	$(OBJS)
	@echo Building: $(EXE)
	$(CC) -o $@ $^ $(LIBS)
	
%.o: %.c %.h
	@echo Building: "$@"
	$(CC) $(CFLAGS) -o"$@" "$<"

# Other Targets
clean:
	$(RM) $(OBJS)
	$(RM) $(EXE)

.PHONY: all clean test
.SECONDARY:
