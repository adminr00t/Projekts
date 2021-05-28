#!/bin/bash

writeFile () {
     #if the file does exist
    
        echo "The file \"$1\" does exist!"
        sleep 1
        echo

        #makes two copies
        echo "Copying..."
        cp "$1" "copyof$2" 
        cp "copyof$2" "copyOfCopy.sh"
        echo

        #bug checking
        # cat copyof$2

        sleep 1 
        
        #removes comments from first copy, pastes updated code into second copy, deletes first copy
        echo "Removing comments..."
        sed -e '/^\s*#\([^!]\|$\)/d' copyof$2 > copyOfCopy.sh
        rm -f copyof$2
        echo 

        #bug checking
        # cat copyOfCopy.sh
    
        sleep 1

        #removes blanks lines from second copy, pastes updated code into the user called file, removes second copy
        echo "Removing Blank Lines..."
        grep -v -e '^$' copyOfCopy.sh > $2
        rm -f copyOfCopy.sh
        echo

        sleep 1

        echo "Complete!"       
}


#checks if the file exits
if [ ! -f "$1" ]; then
    echo "check if the file \"$1\" exists"
    exit 1
#checks if the file exists and asks for user input
elif [ -f "$2" ]; then
    read -r -p "$2 already exists. Overwrite it? " usrRes
    case "$usrRes" in
    [yY][eE][sS]|[yY]) 
        writeFile $1 $2
        ;;
    *)
        echo "Exiting..."
        sleep 1
        exit 1
        ;;
    esac

#if everything is clear, calls the writeFile function
else
   if [ -f "$1" ]; then
    writeFile $1 $2
   fi
fi