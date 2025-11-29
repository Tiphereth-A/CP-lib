SRCDIRS := usage test test/_local
SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

# URL::pattern1|pattern2|...
FONT_ARCHIVES := \
	https://mirror.math.princeton.edu/pub/CTAN/fonts/cm-unicode.zip::cm-unicode/fonts/otf/* \
	https://github.com/mozilla/Fira/archive/refs/tags/4.202.zip::Fira-4.202/otf/* \
	https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip::ttf/*|variable_ttf/*|woff2/* \
	https://noto-website-2.storage.googleapis.com/pkgs/NotoSans-hinted.zip::*.ttf \
	https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKsc-hinted.zip::*.otf \
	https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKjp-hinted.zip::*.otf \
	https://noto-website-2.storage.googleapis.com/pkgs/NotoSansSymbols-hinted.zip::*.ttf \
	https://github.com/notofonts/symbols/releases/download/NotoSansSymbols2-v2.008/NotoSansSymbols2-v2.008.zip::NotoSansSymbols2/hinted/ttf/*.ttf

%.o: %.cpp
	g++ -std=gnu++20 -O2 -Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wzero-as-null-pointer-constant -Wregister -Wvolatile -Wredundant-tags -Wmismatched-tags -Wstrict-null-sentinel -Woverloaded-virtual -Wenum-conversion -Wcomma-subscript -Wno-variadic-macros -Wno-extra-semi -Wno-useless-cast -fmax-errors=1 -c $< -o $@

.PHONY: all clean download-fonts

all: $(OBJECTS)

clean:
	rm -rf $(OUTDIR) $(OBJECTS)
	rm -rf downloads fonts

download-fonts:
	mkdir -p downloads fonts
	$(foreach entry,$(FONT_ARCHIVES),\
		$(eval url := $(word 1,$(subst ::, ,$(entry))))\
		$(eval pats := $(subst |, ,$(word 2,$(subst ::, ,$(entry)))) )\
		$(eval file := downloads/$(notdir $(url)))\
		wget -O "$(file)" "$(url)"; \
		$(foreach pat,$(pats),\
			unzip -jo "$(file)" "$(pat)" -d fonts;\
		)\
	)
