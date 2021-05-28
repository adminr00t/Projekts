#verifying marks.txt exists
FILE=sshCommand.sh
if [[ -f $FILE && -s $FILE ]]; then
    echo "$FILE exists and is not empty."
else 
    echo "$FILE does not exist or is empty."
    exit 1
fi

#verifying students.txt exists and is readable
FILE=sshCommand.sh
if [[ -f $FILE && -r $FILE ]]; then
    echo "$FILE exists and is readable."
else 
    echo "$FILE does not exist."
    exit 1
fi

#verifyinng template.tex exists and is readable
FILE=sshCommand.sh
if [[ -f $FILE ]]; then
    echo "$FILE exists."
else 
    echo "$FILE does not exist."
    exit 1
fi