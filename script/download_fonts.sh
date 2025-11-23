#!/usr/bin/env bash

rm -rf downloads
rm -rf fonts

mkdir -p downloads
mkdir -p fonts

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
