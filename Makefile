SRCDIRS := src src/test_tinplate src/test_cpverifier
SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

%.o: %.cpp
	g++-12 -std=gnu++20 -O2 -Wall -Wextra -c $< -o $@

.PHONY: all clean

all: $(OBJECTS)

clean:
	rm -rf $(OUTDIR) $(OBJECTS)
