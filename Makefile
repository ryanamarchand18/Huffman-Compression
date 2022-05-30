 # Variables----------------------------------------------------------------------
 # Assignment
 BASE_NAME = huffman
 ASG_NICKNAME = HW21
 
 # Executable
 EXECUTABLE = test_huffman
 EXECUTABLE_GCOV = $(BASE_NAME)_gcov
 
 # Source Filenames
 SRC_C = huffman.c priority_queue.c frequencies.c bit_writer.c
 TEST_C = test_huffman.c
 SRC_H = huffman.h priority_queue.h frequencies.h miniunit.h clog.h bit_writer.h
 SUBMIT_FILES = $(SRC_C) $(TEST_C) $(SRC_H) Makefile
 
 # System
 CC=gcc
 CFLAGS =-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
 SHELL = /bin/bash
 CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage
 
 # Rules---------------------------------------------------------------------------
 $(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
     $(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) 
 
 test: $(EXECUTABLE)
     valgrind ./$(EXECUTABLE)
 
 pretest: submit
test $(ASG_NICKNAME) 
 
 
 submit: $(SUBMIT_FILES)
submit $(ASG_NICKNAME) $(SUBMIT_FILES) test_simple.txt new_file.bits tableBits.bits 
 clean: 
     rm -f $(EXECUTABLE) *.c.gcov *.gcda *.gcno
 
 coverage: $(SRC_C) $(TEST_C)
     $(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV) 
     ./$(EXECUTABLE_GCOV)
     gcov  -f $(SRC_C)
 
 .PHONY: submit test pretest clean coverage