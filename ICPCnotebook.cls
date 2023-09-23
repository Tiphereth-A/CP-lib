%-*- coding: utf-8 -*-

\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{ICPCnotebook}[2022/05/15 v0.1 Template class of Tifa's ICPC Notebook]

\LoadClass[a4paper, twoside]{report}

\RequirePackage{longtable}
\RequirePackage{multirow, multicol}
\RequirePackage{pdflscape}
\RequirePackage{tocloft}

\RequirePackage{color, xcolor}
\RequirePackage{algorithm}
\RequirePackage{algpseudocode}
\RequirePackage{amsfonts, amsmath, amssymb, amsthm}
\RequirePackage{bm}
\RequirePackage{bigdelim}
\RequirePackage{bigstrut}
\RequirePackage{bookmark}
\RequirePackage{booktabs}
\RequirePackage[scale=2]{ccicons}
\RequirePackage{cprotect}
\RequirePackage[UTF8]{ctex}
\RequirePackage{extpfeil}
\RequirePackage{hyperref}
\RequirePackage{ifthen}
\RequirePackage{subcaption}
\RequirePackage{tabularx}
\RequirePackage{tikz}
\RequirePackage{url}
\RequirePackage{xspace}
\RequirePackage{mathtools}
\RequirePackage{pgfplots}
\RequirePackage{pdfpages}
\RequirePackage{ucharclasses}

\usepgfplotslibrary{dateplot}


% Font setting
\RequirePackage{fontspec}
\setsansfont{Fira Sans}
\setmonofont{Fira Code}[Contextuals=Alternate]
\newfontfamily\cnfont{等线}
\setTransitionsForChinese{\cnfont}{}

% User defined command
\newcommand{\lcm}{\operatorname{lcm}}
\newcommand{\nequiv}{~{\equiv}\llap{/\,}~}
\newcommand{\subjectto}{~s.t.~}
\newcommand{\eulerian}[2]{{{#1} \atopwithdelims \langle \rangle {#2}}}
\newcommand{\beulerian}[2]{\left\langle\!\!{\eulerian{#1}{#2}}\!\!\right\rangle}
\newcommand{\stirlingfirst}[2]{{{#1} \brack {#2}}}
\newcommand{\stirlingsecond}[2]{{{#1} \brace {#2}}}

\newcommand{\fullref}[1]{\ref{#1}.\nameref{#1} (\pageref{#1} 页)}


% Page style
\XeTeXlinebreaklocale "zh"
\XeTeXlinebreakskip = 0pt plus 1pt

\setlength{\itemindent}{0em}
\setlength\parindent{0em}
\setlength{\columnsep}{13pt}

\RequirePackage{fancyhdr}
\RequirePackage[inner=1cm, outer=0.7cm, top=1.7cm, bottom=0.5cm]{geometry}

\setlength{\headsep}{0.1cm}
\setlength{\footskip}{0.7cm}

\fancypagestyle{fancy} {
    \fancyhead[L]{\nouppercase\leftmark}
	\fancyhead[R]{\nouppercase\rightmark}
	\fancyhead[C]{ICPC Notebook}
    \fancyfoot[C]{\thepage}
}

\renewcommand{\headrulewidth}{0.5pt}
\renewcommand{\footrulewidth}{0.5pt}


% Code style
\RequirePackage{minted}

\setminted[cpp]{
	style=default,
	mathescape,
	linenos,
	autogobble,
    breakanywhere,
    baselinestretch=0.9,
	tabsize=2,
	fontsize=\normalsize,
	frame=single,
	framesep=1mm,
	framerule=0.3pt,
	numbersep=1mm,
    breaklines=true,
}

\setminted[python]{
	style=default,
	mathescape,
	linenos,
	autogobble,
    breakanywhere,
    baselinestretch=0.9,
	tabsize=2,
	fontsize=\normalsize,
	frame=single,
	framesep=0.8mm,
	framerule=0.3pt,
	numbersep=0.8mm,
    breaklines=true,
}
