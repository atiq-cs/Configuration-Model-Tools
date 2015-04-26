# reference: http://stackoverflow.com/questions/2481269/how-to-make-simple-c-makefile

CC=gcc
CXX=g++
RM=rm -f
# CPPFLAGS=-g $(shell root-config --cflags)
CXXFLAGS=-std=c++11
# LDFLAGS=-g $(shell root-config --ldflags)
# LDLIBS=$(shell root-config --libs)

SRCS=ConfigurationModelGenerator.cpp RandomGraph.cpp DegreeSequenceGenerator.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
MAIN_SRC=Main.cpp
MAIN_OBJ=$(subst .cpp,.o,$(MAIN_SRC))


default: confmodelmain
all: confmodelmain

# This was the rule I had spent quite some time to figure out, Main won't be in list of definition of SRCS
confmodelmain: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_OBJ) $(MAIN_SRC) $(OBJS)

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) $(MAIN_OBJ)

dist-clean: clean
	$(RM) *~ .depend

include .depend

