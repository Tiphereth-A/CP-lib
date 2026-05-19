SRCDIRS := src test/cpv test/cpv_local
rwildcard = $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
SOURCES := $(foreach dir,$(SRCDIRS),$(call rwildcard,$(dir)/,*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)
FLAGS = -std=gnu++20 -O2 -Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wzero-as-null-pointer-constant -Wregister -Wvolatile -Wredundant-tags -Wmismatched-tags -Wstrict-null-sentinel -Woverloaded-virtual -Wenum-conversion -Wcomma-subscript -Wno-variadic-macros -Wno-extra-semi -Wno-useless-cast -fmax-errors=1

# URL::pattern1|pattern2|...
FONT_ARCHIVES := \
	https://mirror.math.princeton.edu/pub/CTAN/fonts/cm-unicode.zip::cm-unicode/fonts/otf/* \
	https://github.com/mozilla/Fira/archive/refs/tags/4.202.zip::Fira-4.202/otf/* \
	https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip::ttf/*|variable_ttf/*|woff2/*

%.o: %.cpp
	g++ $(FLAGS) -c $< -o $@

.PHONY: all clean download-fonts

all: $(OBJECTS)

clean:
	rm -rf $(OUTDIR) $(OBJECTS)
	rm -rf .cp-lib

download-fonts:
	mkdir -p .cp-lib .cp-lib/downloads .cp-lib/fonts
	$(foreach entry,$(FONT_ARCHIVES),\
		$(eval url := $(word 1,$(subst ::, ,$(entry))))\
		$(eval pats := $(subst |, ,$(word 2,$(subst ::, ,$(entry)))) )\
		$(eval file := .cp-lib/downloads/$(notdir $(url)))\
		wget -O "$(file)" "$(url)"; \
		$(foreach pat,$(pats),\
			unzip -jo "$(file)" "$(pat)" -d .cp-lib/fonts;\
		)\
	)
