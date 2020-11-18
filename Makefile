# Universal makefile for multiple C++ programs
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependences among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ searcher | phil ]

########## Variables ##########

CXX = g++					# compiler
CXXFLAGS = -g -std=c++11 -Wall -MMD		# compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = CardsDriver.o Cards.o Player.o Map.o Orders.o				# object files forming 1st executable
EXEC1 = CardsDriver				# 1st executable name

# OBJECTS2 = a.o b.o c.o				# object files forming 2nd executable
# EXEC2 = MapDriver					# 2nd executable name

# OBJECTS2 = a.o b.o c.o				# object files forming 2nd executable
# EXEC2 = OrdersDriver					# 2nd executable name

# OBJECTS2 = a.o b.o c.o				# object files forming 2nd executable
# EXEC2 = PlayerDriver					# 2nd executable name

OBJECTS = ${OBJECTS1} # ${OBJECTS2} ${OBJECTS3} ${OBJECTS4}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1} # ${EXEC2} ${EXEC3} ${EXEC4}			# all executables

########## Targets ##########

.PHONY : all clean				# not file names

all : ${EXECS}					# build all executables

${EXEC1} : ${OBJECTS1}				# link step 1st executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${EXEC2} : ${OBJECTS2}				# link step 2nd executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${EXEC3} : ${OBJECTS3}				# link step 2nd executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${EXEC4} : ${OBJECTS4}				# link step 2nd executable
	${CXX} ${CXXFLAGS} $^ -o $@		# additional object files before $^

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}				# include *.d files containing program dependences

clean :						# remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXECS}
