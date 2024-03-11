#!/bin/bash

if [ -d "OUTPUT" ]
then 
    echo "Directory /output exists."
    sleep 1
else
    echo "directory /output does not exist"
fi

#verifying marks.txt exists
FILE=marks.txt
if [[ -f $FILE && -s $FILE ]]; then
    echo "$FILE exists and is not empty."
    sleep 1
else 
    echo "$FILE does not exist or is empty."
    exit 1
fi

#verifying students.txt exists and is readable
FILE=students.txt
if [[ -f $FILE && -r $FILE ]]; then
    echo "$FILE exists and is readable."
    sleep 1
else 
    echo "$FILE does not exist."
    exit 1
fi

#verifyinng template.tex exists and is readable
FILE=feedbackTemplate.tex
if [[ -f $FILE ]]; then
    echo "$FILE exists."
    echo "Starting Grade Compilation..."
    echo
    sleep 1
else 
    echo "$FILE does not exist."
    exit 1
fi


# Remember the read command
while IFS=, read -u 4 studentID Q1Marks Q2Marks Q3Marks Comment && IFS=, read -u 5 studentID2 studentName  ; do
    if [[ $studentID = u* ]]
        then
            echo "Compiling: " $studentName
            sleep 1
            echo "Calculating grade..."
            declare -i Q1=$Q1Marks
            declare -i Q2=$Q2Marks
            declare -i Q3=$Q3Marks
            declare -i totalMarks=0

            totalMarks=$(( Q1 + Q2 + Q3 ))
            sleep 1
            echo -e "Creating tex file... "
            cat<< EndOfText > OUTPUT/$studentID.tex
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
                    Question 1 & $Q1Marks & Q1GRADE \\\\
                    \hline
                    Question 2 & $Q2Marks & Q2GRADE \\\\
                    \hline
                    Question 3 & $Q3Marks & Q3GRADE \\\\
                    \hline
                    \hline
                    \textbf{Total} & $totalMarks & TOTALGRADE \\\\
                    \hline
                \end{tabular}
                    

                \end{center}
                Comments: $Comment
                \end{document}
EndOfText
sleep 1
echo "Creating PDF..."
cd OUTPUT
pdflatex $studentID.tex > /dev/null

sleep 1

echo "Cleaning Up..."
rm -f *.tex *.log *.synctex.gz *.aux > /dev/null
cd ..
echo "Grading for $studentName complete!"
echo
        fi
done 4<marks.txt 5<students.txt

exit 0 