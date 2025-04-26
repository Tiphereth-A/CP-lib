SRCDIRS := usage test_cpverifier
SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

%.o: %.cpp
	g++ -std=gnu++20 -O2 -Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wzero-as-null-pointer-constant -Wregister -Wvolatile -Wredundant-tags -Wmismatched-tags -Wextra-semi -Wstrict-null-sentinel -Wuseless-cast -Woverloaded-virtual -Wenum-conversion -Wcomma-subscript -Wno-variadic-macros -fmax-errors=1 -c $< -o $@

.PHONY: all clean

all: $(OBJECTS)

clean:
	rm -rf $(OUTDIR) $(OBJECTS)
