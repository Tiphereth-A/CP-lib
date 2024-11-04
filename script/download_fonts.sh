#!/usr/bin/env bash

wget -O ./downloads/cm-unicode.zip "https://mirror.math.princeton.edu/pub/CTAN/fonts/cm-unicode.zip"
wget -O ./downloads/fira.zip "https://github.com/mozilla/Fira/archive/refs/tags/4.202.zip"
wget -O ./downloads/firacode.zip "https://github.com/tonsky/FiraCode/releases/download/6.2/Fira_Code_v6.2.zip"
wget -O ./downloads/notosans.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSans-hinted.zip"
wget -O ./downloads/notosanscjksc.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKsc-hinted.zip"
wget -O ./downloads/notosanscjkjp.zip "https://noto-website-2.storage.googleapis.com/pkgs/NotoSansCJKjp-hinted.zip"

unzip -j ./downloads/cm-unicode.zip "cm-unicode/doc/OFL*" -d ./fonts/license-cm-unicode
unzip -j ./downloads/fira.zip "Fira-4.202/LICENSE*" -d ./fonts/license-Fira
wget -O ./fonts/license-FiraCode/LICENSE "https://github.com/tonsky/FiraCode/raw/refs/heads/master/LICENSE"
unzip ./downloads/notosans.zip "LICENSE*" -d ./fonts/license-NotoSans
unzip ./downloads/notosanscjksc.zip "LICENSE*" -d ./fonts/license-NotoSansCJKsc
unzip ./downloads/notosanscjkjp.zip "LICENSE*" -d ./fonts/license-NotoSansCJKjp

unzip -j ./downloads/cm-unicode.zip "cm-unicode/fonts/otf/*" -d ./fonts
unzip -j ./downloads/fira.zip "Fira-4.202/otf/*" -d ./fonts
unzip -j ./downloads/firacode.zip "{ttf,variable_ttf,woff2}/*" -d ./fonts
unzip ./downloads/notosans.zip "*.ttf" -d ./fonts
unzip ./downloads/notosanscjksc.zip "*.otf" -d ./fonts
unzip ./downloads/notosanscjkjp.zip "*.otf" -d ./fonts
