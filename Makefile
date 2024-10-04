###############################################################################
# Makefile for BOOM_BPU_attacks
###############################################################################

# Folders
SRC=src
INC=boom_attacks/inc
OBJ=obj
BIN=bin
DMP=dump
DEP=dep

# Commands and flags
GCC=riscv64-unknown-elf-gcc
OBJDUMP=riscv64-unknown-elf-objdump -S
CFLAGS=-g -O0 -I$(INC) -std=gnu11 -Wall -specs=htif_nano.specs -Wextra
DEPFLAGS=-MT $@ -MMD -MP -MF $(DEP)/$*.d

# Programs to compile
PROGRAMS=brad-a brad-b pink ploop
BINS=$(addprefix $(BIN)/,$(addsuffix .riscv,$(PROGRAMS)))
DUMPS=$(addprefix $(DMP)/,$(addsuffix .dump,$(PROGRAMS)))

# Include dependencies
-include $(addprefix $(DEP)/,$(addsuffix .d,$(PROGRAMS)))

all: $(BINS) $(DUMPS)
dumps: $(DUMPS)

# Build object files
#$(OBJ)/%.o: $(SRC)/%.S
#	@mkdir -p $(OBJ)
#	$(GCC) $(CFLAGS) -D__ASSEMBLY__=1 -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	@mkdir -p $(DEP)
	$(GCC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

# Build executable
$(BIN)/%.riscv: $(OBJ)/%.o
	@mkdir -p $(BIN)
	$(GCC) $(CFLAGS) $< $(OBJ)/stack.o -o $@

# Build dump
$(DMP)/%.dump: $(BIN)/%.riscv
	@mkdir -p $(DMP)
	$(OBJDUMP) -D $< > $@

# Remove all generated files
clean:
	rm -rf $(BIN) $(OBJ) $(DMP) $(DEP)
