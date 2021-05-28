#!/bin/bash
# Program to output a system information page
echo " \documentclass{article}
       \title{System Information Report}
       \author{${USER}}
       \begin{document}
       \maketitle
       A report about the current system will be here.
       \end{document}" > sysinfo.tex
       sleep 1
       pdflatex sysinfo.tex