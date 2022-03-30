CC = g++
CFLAGS = -march=native -O3 -pipe 

LIB = src/qm.cpp src/terms.cpp

CASE = case00

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



all: clean pa1 

testing: clean pa1 execute scoring

clean :
	$(VECHO) " CLEAN\tpa1\n"
	$(Q)rm pa1 2>/dev/null; true
	$(Q)rm verifier/*.out 2>/dev/null; true
	$(Q)rm verifier/*.blif 2>/dev/null; true
	$(Q)rm output/*.out 2>/dev/null; true

pa1 : 
	$(VECHO) " CC\t$@\n"
	$(Q)$(CC) $(CFLAGS) $(LIB) src/main.cpp -o $@ 

execute: 
	$(VECHO) " EXE\tpa1\n"
	$(Q) $(PF) ./pa1 testcases/$(CASE).in output/$(CASE).out
	# $(Q)cat output/$(CASE).out
	$(Q)-cp output/*.out verifier/

scoring: 
	$(VECHO) " SCORE\t pa1\n"
	$(Q)cd verifier && ./verify.sh $(CASE)

send_cases:
	scp -r testcases u107062115@ic:~/hw1
	scp -r verifier u107062115@ic:~/hw1

send:
	scp -r src u107062115@ic:~/hw1
	scp Makefile u107062115@ic:~/hw1

get_all_result: clean pa1
	$(VECHO) " EXE ALL\tpa1\n"
	$(Q) $(PF) ./pa1 testcases/case00.in output/case00.out
	$(Q)-cp output/case00.out verifier/
	$(Q)cd verifier && ./verify.sh case00
	$(Q) $(PF) ./pa1 testcases/case01.in output/case01.out
	$(Q)-cp output/case01.out verifier/
	$(Q)cd verifier && ./verify.sh case01
	$(Q) $(PF) ./pa1 testcases/case02.in output/case02.out
	$(Q)-cp output/case02.out verifier/
	$(Q)cd verifier && ./verify.sh case02
	$(Q) $(PF) ./pa1 testcases/case03.in output/case03.out
	$(Q)-cp output/case03.out verifier/
	$(Q)cd verifier && ./verify.sh case03
	$(Q) $(PF) ./pa1 testcases/case04.in output/case04.out
	$(Q)-cp output/case04.out verifier/
	$(Q)cd verifier && ./verify.sh case04
	$(Q) $(PF) ./pa1 testcases/case05.in output/case05.out
	$(Q)-cp output/case05.out verifier/
	$(Q)cd verifier && ./verify.sh case05
	$(Q) $(PF) ./pa1 testcases/case06.in output/case06.out
	$(Q)-cp output/case06.out verifier/
	$(Q)cd verifier && ./verify.sh case06
	$(Q) $(PF) ./pa1 testcases/case07.in output/case07.out
	$(Q)-cp output/case07.out verifier/
	$(Q)cd verifier && ./verify.sh case07

