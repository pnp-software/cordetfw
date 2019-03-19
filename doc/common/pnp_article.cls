\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{pnp_article}[1995/10/30 Standard document class at PnP]

\LoadClass[a4paper,10pt]{article}

% total: width and height of text part of a page; 
% headsep: distance between the bottom of the header and the top of the non-header text
% head: height of the header
% top: distance of something (I am not sure what) from the top of the page
% NB: as usual with Latex commands interact with each other in unpredictable ways
\usepackage[a4paper, total={5.5in, 8.5in}, headsep=0.7cm, head=36pt, top=4.5cm]{geometry}	

\usepackage[utf8x]{inputenc}
\usepackage[T1]{fontenc}
\usepackage{array}
\usepackage[pdftex]{graphicx}
\usepackage{listings}
\usepackage{enumitem}
\usepackage{color, colortbl}
\usepackage{longtable}
\usepackage{float}
\usepackage[ddmmyyyy]{datetime}
\usepackage[compact]{titlesec}		% The 'compact' argument reduces spacing before and after headings
\setcounter{secnumdepth}{5}% Allow numbering for paragaphs and subparagraphs.

% Start ---- Fix for bug in issue 2.10.1 of titlesec package
\usepackage{etoolbox}

\makeatletter
\patchcmd{\ttlh@hang}{\parindent\z@}{\parindent\z@\leavevmode}{}{}
\patchcmd{\ttlh@hang}{\noindent}{}{}{}
\makeatother
% End ---- Fix for bug in issue 2.10.1 of titlesec package

\usepackage{verbatim}
\usepackage{fancyhdr}
\usepackage{datatool}	% Management of external databases
\usepackage{chngcntr}	% Management of figure and table numberings
\usepackage{pdflscape}	% Provides 'landscape mode' for selected pages
\usepackage{hyperref}
\usepackage{csvsimple}
\usepackage{calc}
\usepackage{ifthen}


\usepackage{underscore}  % Allows underscores to be used in non-math text (use of
                         % of this package apparently is not compatible with use of
                         % underscores in labels and other 'special' text

\newcolumntype{x}[1]{>{\centering\let\newline\\\arraybackslash\hspace{0pt}}p{#1}}

%---------------------------------------------
% Management of Figure and Table Numbering
%---------------------------------------------
\counterwithin{figure}{section}
\counterwithin{table}{section}

%---------------------------------------------
% Management of Captions (options interact with each other in unpredictable ways)
%---------------------------------------------
\usepackage[labelfont=bf]{caption}	% The caption label for tables and figures is bolded
\setlength{\abovecaptionskip}{2pt}	% Bring caption close to figure or table
\setlength{\belowcaptionskip}{-8pt}	% Bring caption close to text after it
\renewcommand{\figurename}{Fig.}	% The caption label for figures is: "Fig."
%\captionsetup[table]{singlelinecheck=off,justification=raggedright}	% Justify the table captions to the left
\captionsetup[table]{position=bottom,skip=-1pt}	% controls spacing between caption and table
%\captionsetup[figure]{position=bottom,skip=40pt}	

\pagestyle{fancy}

%---------------------------------------------
% Paragraph Layout
%---------------------------------------------
\setlength{\parindent}{0in}			% No indentation on first line of a new paragraph
\setlength{\parskip}{3mm}

%---------------------------------------------
% Table Layout
%---------------------------------------------
\setlength{\extrarowheight}{1.5pt}	% Add vertical space at a table row

%------------------------------------------------------------------------------------------
% Management of Headings
%------------------------------------------------------------------------------------------
% Define spacing to the left, before and after a subsection heading
%\titlespacing\subsubsection{8pt}{12pt plus 4pt minus 2pt}{-10pt plus 0pt minus 0pt}
\titlespacing\subsubsection{0pt}{5pt}{0pt}
\titlespacing\subsection{0pt}{5pt}{0pt}

%---------------------------------------------
% Headers and Footers
%---------------------------------------------
\makeatletter

\def\SetDocIssue#1{\def\@docIssue{#1}}
\def\GetDocIssue{\@docIssue}
\def\SetDocRefNumber#1{\def\@docRefNumber{#1}}
\def\GetDocRefNumber{\@docRefNumber}
\def\SetCheckedBy#1{\def\@checkedBy{#1}}
\def\GetCheckedBy{\@checkedBy}

\SetDocIssue{0.0}
\SetDocRefNumber{Document Reference}

\renewcommand{\headrulewidth}{0.4pt}
\renewcommand{\footrulewidth}{0.4pt}

%\lhead{\includegraphics[scale=0.25,keepaspectratio=true]{logoPnP_1.jpg}}
\lhead{ \includegraphics[scale=0.25,keepaspectratio=true]{logoPnP_2.png}}
\chead{\url{www.pnp-software.com} \\}
\rhead{\GetDocRefNumber \\ Revision \GetDocIssue \\ Date \today}
\lfoot{\textcopyright2019 P\&P Software GmbH. All Rights Reserved.}
\cfoot{\vspace{5mm}
%{\color{red}\verbatiminput{../commercial/LicensedTo.txt}}
}
\rfoot{\thepage}

\makeatother

%---------------------------------------------
% Management of lists
%---------------------------------------------
\setlist{nolistsep}								% No extra vertical space around a list	

\let\olditemize\itemize	
\let\oldenditemize\enditemize
\renewenvironment{itemize}
{\olditemize%
  \setlength{\itemsep}{1mm}
  \setlength{\parskip}{0pt}
  \setlength{\parsep}{0pt}}
{\oldenditemize}

\let\oldenumerate\enumerate
\let\oldendenumerate\endenumerate
\renewenvironment{enumerate}
{\oldenumerate%
  \setlength{\itemsep}{1mm}
  \setlength{\parskip}{0pt}
  \setlength{\parsep}{0pt}}
{\oldendenumerate}

\let\olddescription\description
\let\oldenddescription\enddescription
\renewenvironment{description}
{\olddescription%
  \setlength{\itemsep}{1mm}
  \setlength{\parskip}{5pt}			% Line spacing between paragraphs in an item
  \setlength{\parsep}{0pt}}
{\oldenddescription}


\newenvironment{fw_itemize}
{\begin{itemize}}
{\end{itemize}}

\newenvironment{fw_enumerate}
{\begin{enumerate}}
{\end{enumerate}}

\newenvironment{fw_description}					
{\begin{description}}
{\end{description}}

%---------------------------------------------
% Definition of colours
%---------------------------------------------
\definecolor{dkgreen}{rgb}{0,0.6,0}
\definecolor{gray}{rgb}{0.5,0.5,0.5}
\definecolor{light-gray}{gray}{0.85}
\definecolor{mauve}{rgb}{0.58,0,0.82}
\definecolor{lightblue}{RGB}{128,179,255}
\definecolor{blue}{RGB}{41,85,204}
\definecolor{lbcolor}{rgb}{0.9,0.9,0.9}

%---------------------------------------------
% Options for the code listing boxes
%---------------------------------------------
\lstset{ 
  language=C,                % the language of the code
  aboveskip=\bigskipamount,			% vertical space above listing box
  belowskip=0pt,					% vertical space below listing box
  basicstyle=\scriptsize\ttfamily,    % use small size and mono-space font
  numbers=left,                   % where to put the line-numbers
  numberstyle=\tiny\color{gray},  % the style that is used for the line-numbers
  stepnumber=1,                   % the step between two line-numbers. If it's 1, each line 
                                  % will be numbered
  numbersep=5pt,                  % how far the line-numbers are from the code
  backgroundcolor=\color{lbcolor},      % choose the background color. You must add \usepackage{color}
  showspaces=false,               % show spaces adding particular underscores
  showstringspaces=false,         % underline spaces within strings
  showtabs=false,                 % show tabs within strings adding particular underscores
  frame=single,                   % adds a frame around the code
  rulecolor=\color{black},        % if not set, the frame-color may be changed on line-breaks within not-black text (e.g. commens (green here))
  tabsize=2,                      % sets default tabsize to 2 spaces
  captionpos=b,                   % sets the caption-position to bottom
  breaklines=true,                % sets automatic line breaking
  breakatwhitespace=false,        % sets if automatic breaks should only happen at whitespace
  title=\lstname,                   % show the filename of files included with \lstinputlisting;
                                  % also try caption instead of title
  keywordstyle=\color{blue},          % keyword style
  commentstyle=\color{dkgreen},       % comment style
  stringstyle=\color{mauve},         % string literal style
  escapeinside={\%*}{*)},            % if you want to add a comment within your code
  morekeywords={*,...}               % if you want to add more keywords to the set
}


%CHANGE TITLE PAGE
\makeatletter

\def\SetDocTitle#1{\def\@docTitle{#1}}
\def\GetDocTitle{\@docTitle}

\def\SetDocSubtitle#1{\def\@docSubtitle{#1}}
\def\GetDocSubtitle{\@docSubtitle}

\def\SetDocAuthor#1{\def\@docAuthor{#1}}
\def\GetDocAuthor{\@docAuthor}

% ------------------------------------------------------------------------
% Redefine the title page
% ------------------------------------------------------------------------
\renewcommand{\maketitle}{

% Set the style for the first page to 'fancy'. This will cause header and footer to be present on the first page. Command must be after \maketitle because \maketitle resets page styles.
\thispagestyle{fancy}

\vspace*{3cm}
\begin{center}
\textsc{\LARGE \GetDocTitle} \\
\vspace*{0.5cm}
{\LARGE \GetDocSubtitle}
\end{center}


\vspace{1cm}

\begin{center}
P\&P Software GmbH \\
High Tech Center 1 \\
8274 T\"{a}gerwilen (CH)\\
\vspace{2mm}
Web site: \url{www.pnp-software.com}\\
E-mail: \href{mailto:pnp-software@pnp-software.com}{\nolinkurl{pnp-software@pnp-software.com}} 
\end{center}

\vspace*{3cm}

% Table where the authors and the document reference, issue and date are
% placed. 
% In order to improve the look of the table, two extra empty lines are added
% at the top and at the bottom of the table and their height is set to a 
% small value.
\begin{tabular}{p{3cm} p{10cm}}
\hline
 & \\[-4pt]		% Reduce row height by 4 points
\textbf{Written By}: & \GetDocAuthor \\
\textbf{Checked By}: & \GetCheckedBy \\
\textbf{Document Ref.}: & \GetDocRefNumber{} \\
\textbf{Issue}: & \GetDocIssue{} \\
\textbf{Created On}: & \today{}, at: \currenttime{} \\
 & \\[-4pt]
\hline
\end{tabular}


}
\makeatother


% pnptable 
% Our own table environment.
% arg[1] - Table spec
% arg[2] - Caption
% arg[3] - Label
% arg[4] - Header columns
% 
% Example: 
% \begin{pnptable}{lll}{Example table}{tab:exp}{Col1 & Col2 & Col3}
%   data1 & data2 & data3 \hline
% \end{pnptable}
%
\makeatletter
\newenvironment{pnptable}[4]{
  \begin{longtable}{#1}
  \ifx\foo#2\foo\else\caption{#2}\label{#3}\\\fi%
  \hline
  \rowcolor{light-gray}#4\\\hline\hline\endfirsthead
  \rowcolor{light-gray}#4\\\hline\hline\endhead
  }
  {
  \end{longtable}
  }

% pnpcsvtable
% arg[1] - optional argument in square brackets: a filter argument, or the comma/semicolon separator (default is the pipe), or
%          "respect underscore=true". The latter will cause unwanted separators to be appended at the bottom of the table
% arg[2] - Table spec
% arg[3] - Caption
% arg[4] - Label
% arg[5] - Header columns
% arg[6] - CSV file name
% arg[7] - Columns
%
% Examples:
% \pnpcsvtable[filter equal={\col}{abcd}]{|l|l|l|}{Example CSV table}{tab:exp}{Col1 & Col2 & Col3}{mydata.csv}{\col1 & \col2 & \col3}
%
% \pnpcsvtable[filter not equal={\col}{abcd}]{|l|l|l|}{Example CSV table}{tab:exp}{Col1 & Col2 & Col3}{mydata.csv}{\col1 & \col2 & \col3}
%
% \pnpcsvtable[separator=semicolon]{|l|l|l|}{Example CSV table}{tab:exp}{Col1 & Col2 & Col3}{mydata.csv}{\col1 & \col2 & \col3}
%
\newcommand{\pnpcsvtable}[7][head to column names]{
  \begin{pnptable}{#2}{#3}{#4}{#5}
  \csvreader[head to column names, separator=pipe, late after line=\\\hline, #1]{#6}{}
  {#7}
  \end{pnptable}}

\newcommand{\listofchanges}{
  \section*{Change Record}	
  \pnpcsvtable{|c|c|p{10.5cm}|}{}{}{Issue & Section & Description}{./changes.csv}{\issue & \sect & \desc}}

\makeatother

% Some other useful definitions / makros
\makeatletter
\def\InputNoExpand#1{\csname @@input\endcsname #1.tex}

\renewcommand{\section}{
  \newpage%
%  \setlength{\parskip}{3mm}
% \@startsection{<name>}{<level>}{<indent>}{<beforeskip>}{<afterskip>}{<style>}
  \@startsection{section}{1}{\z@}{-3.5ex \@plus -1ex \@minus -.2ex}{2.3ex \@plus.2ex}{\normalfont\Large\bfseries}%
}

\let\oldparagraph\paragraph
\renewcommand{\paragraph}[1]{
	\oldparagraph{#1}\mbox{}\\
}

\let\oldsubparagraph\subparagraph
\renewcommand{\subparagraph}[1]{
	\oldsubparagraph{#1}\mbox{}\\
}

%------------------------------------------------------------------------------------------
% Directories holding image files:
% \graphicspath{ {../images/} {another directory} {yet another directory} }	
\graphicspath{ {../images/} {../../lib/cordetfw/doc/images/} }	


%------------------------------------------------------------------------------------------
% pnpfigure
% Command to include a figure
% arg[1] - optional positioning selector
% arg[2] - optional scale factor
% arg[3] - Caption of the figure. Leave empty for no caption.
% arg[4] - Label of the figure. Only available when caption is given.
% arg[5] - Image file
%
% Example: 
% \pnpfigure[ht][scale=0.5]{A nice figure}{fig:whatever1}{diagram.png}
%
\newcommand{\pnpfigure}[4][scale=1]{
  \begin{figure}[H]
    \begin{center} 
    \includegraphics[#1]{#4}
    \ifx\foo#2\foo\else\caption{#2}\label{#3}\fi       
    \end{center}
  \end{figure}  
}

\let\oldtableofcontents\tableofcontents
\renewcommand{\tableofcontents}{
  \setlength{\parskip}{0mm}
  \oldtableofcontents
  \setlength{\parskip}{3mm}
}

\let\oldlistoffigures\listoffigures
\renewcommand{\listoffigures}{
  \setlength{\parskip}{0mm}
  \oldlistoffigures
  \setlength{\parskip}{3mm}
}

\let\oldlistoftables\listoftables
\renewcommand{\listoftables}{
  \setlength{\parskip}{0mm}
  \oldlistoftables
  \setlength{\parskip}{3mm}
}

\newcommand{\listofabbreviations}[1][../common/abbreviations.csv]{
  \pnpcsvtable{|p{2cm}|p{\linewidth-3cm}|}{Abbreviations and acronyms}{tab:abbrev}{Abbreviation & Description}{#1}{\abbr & \desc}
}

\newcommand{\listofapplicabledocs}[2][../common/RefDoc.csv]{
The following documents of the exact issue and/or revision shown form a part of this document to the extent specified herein. Where no issue is shown the latest issue is applicable.
\pnpcsvtable[filter equal={#2}{AD}]{|c|p{6cm}|p{4.3cm}|c|}{Applicable documents}{tab:appdoc}{Ref & Description & Doc. Number & Iss.}{#1}
{\Id & \Title & \Nr & \Issue}
}                                   

\newcommand{\listofreferencedocs}[2][../common/RefDoc.csv]{
The following documents are for reference and/or guideline only.
\pnpcsvtable[filter equal={#2}{RD}]{|c|p{7.5cm}|c|c|}{Referenced documents}{tab:refdoc}{Ref & Description & Doc. Number & Iss.}{#1}
{\Id & \Title & \Nr & \Issue}
}

\makeatother
                                   
