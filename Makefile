CC = g++
CFLAGS = -O1 -g -Wall -Werror

LIB = src/qm.cpp src/terms.cpp

CASE = case01

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q := 
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

ifeq ("$(PROFILE)","1")
    PF := @time
else
	PF := 
endif



all: clean pa1 execute scoring

clean :
	$(VECHO) " CLEAN\tpa1\n"
	$(Q)rm pa1 2>/dev/null; true
	$(Q)rm verifier/*.out 2>/dev/null; true
	$(Q)rm verifier/*.blif 2>/dev/null; true
	$(Q)rm output/*.out 2>/dev/null; true

pa1 : 
	$(VECHO) " CC\t$@\n"
	$(Q)$(CC) $(LIB) src/main.cpp -o $@ 

execute: 
	$(VECHO) " EXE\tpa1\n"
	$(Q) $(PF) ./pa1 testcases/$(CASE).in output/$(CASE).out
	# $(Q)cat output/$(CASE).out
	$(Q)-cp output/*.out verifier/

scoring: 
	$(VECHO) " SCORE\t pa1\n"
	$(Q)cd verifier && ./verify.sh $(CASE)

test:
	$(VECHO) " TEST\t$@\n"
	$(Q)cd verifier && ./verify.sh case00

send_cases:
	scp -r testcases u107062115@ic:~/hw1
	scp -r verifier u107062115@ic:~/hw1

send:
	scp -r src u107062115@ic:~/hw1
	scp Makefile u107062115@ic:~/hw1
