#
# Makefile for CSE 30 -- PA4
# You should not need to change anything in this file.
#

HEADERS		= pa4.h pa4Strings.h test.h

C_SRCS		= evenOddHash.c pushToList.c freeLinkedList.c
CREATE_C_SRCS	= populateTables.c create.c writeTables.c pa4Globals.c
SEARCH_C_SRCS	= getFromTable.c checkTables.c search.c readTables.c\
		  beginUserQuery.c pa4Globals.c
ASM_SRCS	= hash.s revHash.s isInRange.s


SEARCH_EC_SRCS	= getFromTable.c checkTables.c search.c readTables.c\
		  beginUserQueryEC.c pa4Globals.c

CREATE_C_OBJS	= $(CREATE_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
SEARCH_C_OBJS	= $(SEARCH_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
C_OBJS		= $(CREATE_C_SRCS:.c=.o) $(SEARCH_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
CREATE_OBJS	= $(CREATE_C_OBJS) $(ASM_OBJS)
SEARCH_OBJS	= $(SEARCH_C_OBJS) $(ASM_OBJS)

SEARCH_EC_OBJS	= $(SEARCH_EC_SRCS:.c=.o) $(C_SRCS:.c=.o) $(ASM_OBJS)

CREATE_EXE	= create
SEARCH_EXE	= search
SEARCH_EC_EXE	= searchEC

TEST_EXES	= testhash testrevHash testevenOddHash testpushToList \
		  testpopulateTables testwriteTables 

GCC		= gcc
ASM		= $(GCC)
RM		= rm

GCC_FLAGS	= -c -g -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Target to create both programs (create and search). This is the default target
# that gets run when you type 'make' with no target specified
#

all:
	@echo "-----------------------------------------------------------"
	@echo "| Compile Create:                                         |"
	@echo "-----------------------------------------------------------"
	make $(CREATE_EXE)
	@echo ""
	@echo ""
	@echo "-----------------------------------------------------------"
	@echo "| Compile SEARCH:                                         |"
	@echo "-----------------------------------------------------------"
	make $(SEARCH_EXE)

#
# Target to make the create executable.
#

$(CREATE_EXE):	$(CREATE_OBJS)
	$(RM) -f test*.o test*.ln
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(CREATE_EXE) $(CREATE_OBJS)
	@echo ""
	@echo "Compilation Successful!"

#
# Target to make the search executable.
#

$(SEARCH_EXE):	$(SEARCH_OBJS)
	$(RM) -f test*.o test*.ln
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(SEARCH_EXE) $(SEARCH_OBJS)
	@echo ""
	@echo "Compilation Successful!"

#
# Target to make the EC executable
#

$(SEARCH_EC_EXE):	$(SEARCH_EC_OBJS)
	$(RM) -f test*.o test*.ln
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(SEARCH_EC_EXE) $(SEARCH_EC_OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)


clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f $(CREATE_EXE) $(SEARCH_EXE) $(SEARCH_EC_EXE) $(TEST_EXES) \
		*.o *.ln core a.out
	@echo ""
	@echo "Clean."

#
# Unit test targets
#

# --- Test for hash ---
testhash: $(HEADERS) hash.o testhash.o pa4Globals.o
	@echo "Compiling testhash.c"
	$(GCC) $(LD_FLAGS) -o testhash testhash.o hash.o pa4Globals.o
	@echo "Compilation Successful!"

# --- Test for revHash ---
testrevHash: $(HEADERS) revHash.o testrevHash.o pa4Globals.o
	@echo "Compiling testrevHash.c"
	$(GCC) $(LD_FLAGS) -o testrevHash testrevHash.o revHash.o pa4Globals.o
	@echo "Compilation Successful!"

# --- Test for evenOddHash ---
testevenOddHash: $(HEADERS) evenOddHash.o testevenOddHash.o
	@echo "Compiling testevenOddHash.c"
	$(GCC) $(LD_FLAGS) -o testevenOddHash testevenOddHash.o evenOddHash.o
	@echo "Compilation Successful!"

# --- Test for pushToList ---
testpushToList: $(HEADERS) pushToList.o testpushToList.o
	@echo "Compiling testpushToList.c"
	$(GCC) $(LD_FLAGS) -o testpushToList testpushToList.o pushToList.o
	@echo "Compilation Successful!"

# --- Test for populateTables ---
testpopulateTables: $(HEADERS) populateTables.o testpopulateTables.o \
	pushToList.o hash.o revHash.o evenOddHash.o pa4Globals.o
	@echo "Compiling testpopulateTables.c"
	$(GCC) $(LD_FLAGS) -o testpopulateTables testpopulateTables.o \
	populateTables.o pushToList.o hash.o revHash.o evenOddHash.o \
	pa4Globals.o
	@echo "Compilation Successful!"

# --- Test for writeTables ---
testwriteTables: $(HEADERS) writeTables.o testwriteTables.o populateTables.o \
	pushToList.o hash.o revHash.o evenOddHash.o pa4Globals.o
	@echo "Compiling testwriteTables.c"
	$(GCC) $(LD_FLAGS) -o testwriteTables testwriteTables.o writeTables.o \
	populateTables.o pushToList.o hash.o revHash.o evenOddHash.o \
	pa4Globals.o
	@echo "Compilation Successful!"



