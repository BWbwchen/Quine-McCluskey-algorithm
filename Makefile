CC = g++
CFLAGS = -O1 -g -Wall -Werror

LIB = src/qm.cpp src/terms.cpp
# PROFILE = time
PROFILE =

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q := 
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif


all: clean scoring

clean :
	$(VECHO) " CLEAN\tpa1\n"
	$(Q)rm pa1 2>/dev/null; true

pa1 : 
	$(VECHO) " CC\t$@\n"
	$(Q)$(CC) $(LIB) src/main.cpp -o $@ 

execute: pa1
	$(VECHO) " EXE\t$<\n"
	$(Q) $(PROFILE) ./$< testcases/case00.in output/case00.out

scoring: prepare_input execute
	$(VECHO) " SCORE\t pa1\n"
	$(Q)cd verifier && ./verify.sh case00

prepare_input: 
	$(Q)cp output/*.out verifier/

test:
	$(VECHO) " TEST\t$@\n"
	$(Q)cd verifier && ./verify.sh case00
