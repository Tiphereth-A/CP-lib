SRCDIRS := usage test
SOURCES := $(foreach dir,$(SRCDIRS),$(wildcard $(dir)/*/*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)

%.o: %.cpp
	g++ -std=gnu++20 -O2 -Wall -Wextra -Wconversion -Wpedantic -Wparentheses -Wzero-as-null-pointer-constant -Wregister -Wvolatile -Wredundant-tags -Wmismatched-tags -Wstrict-null-sentinel -Woverloaded-virtual -Wenum-conversion -Wcomma-subscript -Wno-variadic-macros -Wno-extra-semi -Wno-useless-cast -fmax-errors=1 -c $< -o $@

.PHONY: all clean download-fonts

all: $(OBJECTS)

clean:
	rm -rf $(OUTDIR) $(OBJECTS)

download-fonts:
	rm -rf downloads fonts
	mkdir -p downloads fonts
	wget -O ./downloads/cm-unicode.zip "https://mirror.math.princeton.edu/pub/CTAN/fonts/cm-unicode.zip"
	wget -O ./downloads/fira.zip "https://github.com/mozilla/Fira/archive/refs/tags/4.202.zip"
	wget -O ./downloads/firacode.zip "https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip"
	wget -O ./downloads/notosans.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSans-hinted.zip"
	wget -O ./downloads/notosanscjksc.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKsc-hinted.zip"
	wget -O ./downloads/notosanscjkjp.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKjp-hinted.zip"
	wget -O ./downloads/notosanssymblos.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSansSymbols-hinted.zip"
	wget -O ./downloads/notosanssymblos2.zip "https://github.com/notofonts/symbols/releases/download/NotoSansSymbols2-v2.008/NotoSansSymbols2-v2.008.zip"
	unzip -jo ./downloads/cm-unicode.zip "cm-unicode/fonts/otf/*" -d ./fonts
	unzip -jo ./downloads/fira.zip "Fira-4.202/otf/*" -d ./fonts
	unzip -jo ./downloads/firacode.zip "*.ttf" -d ./fonts
	unzip -jo ./downloads/firacode.zip "*.woff2" -d ./fonts
	unzip -jo ./downloads/notosans.zip "*.ttf" -d ./fonts
	unzip -jo ./downloads/notosanscjksc.zip "*.otf" -d ./fonts
	unzip -jo ./downloads/notosanscjkjp.zip "*.otf" -d ./fonts
	unzip -jo ./downloads/notosanssymblos.zip "*.ttf" -d ./fonts
	unzip -jo ./downloads/notosanssymblos2.zip "NotoSansSymbols2/hinted/*.ttf" -d ./fonts
