# Set g++ as the C++ compiler
CC=g++

# Enforce C++ 2011 as the language standard
CXXFLAGS=-std=c++11 

# Enable all standard warnings, uninitialized variable warnings, 
# and treat all warnings as errors
CXXFLAGS+= -Wall -Wuninitialized -Werror

# NOTE: comment following line temporarily if 
# your development environment is failing
# due to these settings - it is important that 
# you fix your environment at some point.
CXXFLAGS+=-fsanitize=address -fsanitize=undefined

# Object Files
OBJS=linkedmatrix.o matcomp.o main.o
# Target
TARGET=matcomp

$(TARGET): $(OBJS)
	@echo "Linking: $(OBJS) -> $@"
	$(CC) $(CXXFLAGS) $(OBJS) -o $(TARGET)
linkedmatrix.o:	linkedmatrix.h linkedmatrix.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(CXXFLAGS) -c linkedmatrix.cpp
matcomp.o: matcomp.h matcomp.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(CXXFLAGS) -c  matcomp.cpp
main.o:	main.cpp
	@echo "Compiling: $< -> $@"
	$(CC) $(CXXFLAGS) -c  main.cpp
clean:
	@echo "Deleting: $(OBJS) $(TARGET)"
	rm -rf $(OBJS) $(TARGET)
