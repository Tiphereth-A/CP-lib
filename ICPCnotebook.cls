%-*- coding: utf-8 -*-

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ICPCnotebook}[2022/05/15 v0.1 Template class of Tifa's ICPC Notebook]

\LoadClass[a4paper, twoside]{report}

\RequirePackage{algorithm}
\RequirePackage{algpseudocode}
\RequirePackage{amsfonts, amsmath, amssymb, amsthm}
\RequirePackage{bm}
\RequirePackage{bigdelim}
\RequirePackage{bigstrut}
\RequirePackage{bookmark}
\RequirePackage{booktabs}
\RequirePackage{color, xcolor}
\RequirePackage{cprotect}
\RequirePackage[UTF8]{ctex}
\RequirePackage{extpfeil}
\RequirePackage{hyperref}
\RequirePackage{ifthen}
\RequirePackage{longtable}
\RequirePackage{mathtools}
\RequirePackage{multirow, multicol}
\RequirePackage{pgfplots}
\RequirePackage{pdflscape}
\RequirePackage{pdfpages}
\RequirePackage{qrcode}
\RequirePackage{seqsplit}
\RequirePackage{subcaption}
\RequirePackage{svg}
\RequirePackage{tabularx,diagbox}
\RequirePackage{tikz}
\RequirePackage{tocloft}
\RequirePackage{xspace}
\RequirePackage{xurl}

\usepgfplotslibrary{dateplot}


% Font setting
\RequirePackage{fontspec,unicode-math}
\RequirePackage[CJK,Latin,DominoTiles,MahjongTiles]{ucharclasses}
\setmainfont{Noto Sans}
\setsansfont{Fira Sans}
\setmonofont[Contextuals=Alternate]{Fira Code}
\setmathfont{CMU Serif}
\setmathrm{CMU Serif}
\setmathsf{CMU Sans Serif}
\newfontfamily\cnfont{Noto Sans CJK SC}
\newfontfamily\jpfont{Noto Sans CJK JP}
\newfontfamily\symbolfont{Noto Sans Symbols 2}
\setTransitionsForChinese{\begingroup\cnfont}{\endgroup}
\setTransitionTo{Hiragana}{\begingroup\jpfont}
\setTransitionFrom{Hiragana}{\endgroup}
\setTransitionTo{Katakana}{\begingroup\jpfont}
\setTransitionFrom{Katakana}{\endgroup}
\setTransitionTo{DominoTiles}{\begingroup\symbolfont}
\setTransitionFrom{DominoTiles}{\endgroup}
\setTransitionTo{MahjongTiles}{\begingroup\symbolfont}
\setTransitionFrom{MahjongTiles}{\endgroup}

% User defined command
\newcommand{\lcm}{\operatorname{lcm}}
\DeclareMathOperator*{\argmin}{arg\,min}
\DeclareMathOperator*{\argmax}{arg\,max}

\newcommand{\geneulerian}[3]{\genfrac<>{0pt}{#1}{#2}{#3}}
\newcommand{\eulerian}[2]{\geneulerian{}{#1}{#2}}
\newcommand{\deulerian}[2]{\geneulerian{0}{#1}{#2}}
\newcommand{\teulerian}[2]{\geneulerian{1}{#1}{#2}}

\newcommand{\geneulerianII}[3]{\left\langle\mathchoice{\!\!\!}{\!}{\!}{\!}\genfrac<>{0pt}{#1}{#2}{#3}\mathchoice{\!\!\!}{\!}{\!}{\!}\right\rangle}
\newcommand{\eulerianII}[2]{\geneulerianII{}{#1}{#2}}
\newcommand{\deulerianII}[2]{\geneulerianII{0}{#1}{#2}}
\newcommand{\teulerianII}[2]{\geneulerianII{1}{#1}{#2}}

\newcommand{\genstirlingI}[3]{\genfrac{[}{]}{0pt}{#1}{#2}{#3}}
\newcommand{\stirlingI}[2]{\genstirlingI{}{#1}{#2}}
\newcommand{\dstirlingI}[2]{\genstirlingI{0}{#1}{#2}}
\newcommand{\tstirlingI}[2]{\genstirlingI{1}{#1}{#2}}

\newcommand{\genstirlingII}[3]{\genfrac{\{}{\}}{0pt}{#1}{#2}{#3}}
\newcommand{\stirlingII}[2]{\genstirlingII{}{#1}{#2}}
\newcommand{\dstirlingII}[2]{\genstirlingII{0}{#1}{#2}}
\newcommand{\tstirlingII}[2]{\genstirlingII{1}{#1}{#2}}

\newcommand{\sech}{\operatorname{sech}}
\newcommand{\csch}{\operatorname{csch}}
\newcommand{\arccot}{\operatorname{arccot}}
\newcommand{\arcsec}{\operatorname{arcsec}}
\newcommand{\arccsc}{\operatorname{arccsc}}
\newcommand{\arcsinh}{\operatorname{arcsinh}}
\newcommand{\arccosh}{\operatorname{arccosh}}
\newcommand{\arctanh}{\operatorname{arctanh}}
\newcommand{\arccoth}{\operatorname{arccoth}}
\newcommand{\arcsech}{\operatorname{arcsech}}
\newcommand{\arccsch}{\operatorname{arccsch}}

\newcommand{\md}{\mathrm{d}}

\newcommand{\fullref}[1]{\ref{#1}.\nameref{#1} (\pageref{#1} 页)}


% Page style
% \XeTeXlinebreaklocale "zh"
% \XeTeXlinebreakskip = 0pt plus 1pt

\setlength{\itemindent}{0em}
\setlength{\parindent}{0em}
\setlength{\columnsep}{13pt}
\setlength{\cftsecnumwidth}{3em}

\RequirePackage{fancyhdr}
\RequirePackage[inner=2cm, outer=0.9cm, top=1.7cm, bottom=0.0cm]{geometry}

\setlength{\headsep}{0.1cm}
\setlength{\footskip}{0.7cm}

\fancypagestyle{fancy} {
	\fancyhead[L]{\nouppercase\leftmark}
	\fancyhead[R]{\nouppercase\rightmark}
	\fancyhead[C]{\thepage}
	\fancyfoot{}
}

\renewcommand{\headrulewidth}{0.5pt}
\renewcommand{\footrulewidth}{0.5pt}

\RequirePackage{titlesec}
\titlespacing*{\section}{0pt}{0.6ex}{0.6ex}
\titlespacing*{\subsection}{0pt}{0.6ex}{0.6ex}
\titlespacing*{\subsubsection}{0pt}{0.6ex}{0.6ex}
\titlespacing*{\paragraph}{0pt}{0.6ex}{0.6ex}

\qrset{link, height=1cm}

% Code style
\RequirePackage{minted}

\setminted{
	style=default,
	mathescape,
	linenos,
	autogobble,
	breakanywhere,
	baselinestretch=0.9,
	tabsize=2,
	fontsize=\footnotesize,
	frame=single,
	framesep=0.8mm,
	framerule=0.3pt,
	numbersep=0.8mm,
	breaklines=true,
}
