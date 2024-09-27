##############################################################################
# Makefile for graph library
# CMP_SC 4050
# Fall 2024
# By Jim Ries (RiesJ@missouri.edu)
##############################################################################
CC = gcc
CPP = g++
CFLAGS = -Wall -Werror -c -g -std=c11 -I.
CPPFLAGS = -Wall -Werror -c -g -I.
LDFLAGS = -lm -lcs4050 -L.

default: test

lib : libcs4050.a

%.o : %.c 
	@echo Compiling $^ 
	@$(CC) $(CFLAGS) $^

%.o : %.cc
	@echo Compiling $^ 
	@$(CPP) $(CPPFLAGS) $^

test : main.o MST.o UtilC.o
	@echo Linking $@ 
	@$(CPP) $^ $(LDFLAGS) -o $@

libcs4050.a : cs4050.o
	@echo Building library $@
	@ar -crs libcs4050.a $^

clean : 
	@rm -rf *.o
	@rm -rf test
	@echo All Clean!

cleanlib :
	@rm -rf *.a
