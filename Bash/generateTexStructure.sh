#!/bin/bash
    cat<< EndOfText > test.tex
                \documentclass[10pt, a4paper]{article}

                \begin{document}
                \begin{center}
                CSC3333 Software Engineering 3

                Assignment 1

                Student ID: $studentID

                Student name: $studentName

                \vspace{1cm}

                \begin{tabular}{|c|c|c|}
                    \hline
                    Questions & \textit{Marks} & Grade \\\\
                    \hline
                    Question 1 & MARKS1 & Q1GRADE \\\\
                    \hline
                    Question 2 & MARKS2 & Q2GRADE \\\\
                    \hline
                    Question 3 & MARKS3 & Q3GRADE \\\\
                    \hline
                    \hline
                    \textbf{Total} & TOTALMARKS & TOTALGRADE \\\\
                    \hline
                \end{tabular}
                    

                \end{center}
                Comments: MYCOMMENTS
                \end{document}
                
EndOfText
 
###############