# This script uses 2 directories, /backup/ and /vers/. Backup is used to mirror /home/ and store files
# for the archive process. /vers/ is where the archived versions, named after the time of creation
# are stored and kept. At the end of the script, the archived version of the current /backup/ directory
# is moved to /vers/ and /backup/ and all files within are removed. /backup/ is then recreated, fresh
# for the next run
# For clarification, every command in else sections execute on first run.

#!/bin/bash

#Part 1 - Asks user for drive letter, verifies drive and folders exist. Creates missing folders
    
    #prompts user for drive letter
    printf "Enter the directory for backup:\n"
    read DRLT

    #debugging
    # pwd 

    #checks if directory exists, if it does, cd is changed. Else program exits
    if [ -d $DRLT ]
    then 
        cd $DRLT
    else
        echo "directory $DRLT does not exist"
        exit 1
    fi

    #debugging
    # pwd

    #checks if version directory exists
    if [ -d "vers" ]
    then 
        printf "Directory /vers/ exists.\n"
    else
        printf "Directory /vers/ does not exist. Assuming first set up\n"
        printf "Creating /vers/...\n"
        mkdir vers
        printf "Creating /backup/...\n"
        mkdir backup
    fi

#Part 2- Checking for Out-of-Date Archives, removes out of date archives
    cd /mnt/$DRLT/vers/

    #TESTING FOR FILES OLDER THAN 2 MINUTES
    # if [[ $(find *.tgz -mmin +2 -print 2>/dev/null) ]]
    # then
    #     printf "Some archives are older than 2 minutes\n"
    #     printf "Removing outdated archives...\n"
    #     find /mnt/$DRLT/vers/ -type f -mmin +2 -name '*.tgz' -execdir rm -rf '{}' \;  
    #     printf "Removed outdated archives\n"
    # else
    #     printf "Archives are less than 2 minutes old\n"
    # fi

    #tests if archives are older than 30 days
    if [[ $(find *.tgz -mtime +30 -print 2>/dev/null) ]]
    then
        printf "Some archives are older than 30 days\n"
        printf "Removing outdated archives...\n"
        find /mnt/$DRLT/vers/ -type f -mtime +30 -name '*.tgz' -execdir rm -rf '{}' \; #finds files older than 30 days and then removes them
        printf "Removed outdated archives\n"
    else
        printf "Archives are less than 30 days old\n"
    fi

#Part 3 - Verfies if previous archived versions exist
    
    #Variables for this section
    A=$(ls -Art | tail -n 1) #stores name of latest backup
    B=$(ls -1 *.tgz 2>/dev/null | wc -l) #stores number of backups within /vers/
    
    #checks if a tgz file exists in version directory, if it does, it is copied into /backup/
    if [ $B != 0 ]
    then 
        printf "Backup file(s) exists\n"
        printf "Most recent backup: "
        printf "$A\n"
        printf "Copying $A...\n"
        rsync -a --info=progress2 /mnt/$DRLT/vers/$A /mnt/$DRLT/backup
    else
        printf "No previous backup found. Assuming first backup process...\n"
    fi

#Part 4- Previous Version Extraction and /home/ mirroring

    #variables
    C=$(ls -1 *.tgz 2>/dev/null | wc -l) #stores number of backups within /backup/
    D=$(date '+%Y%m%d%H%M') #sets variable as current year, hour and minute

    cd /mnt/$DRLT/backup

    #if tar file is found it is extracted, else mirrored /home/ is tarballed
    if [ $C != 0 ]
    then 
        #extracts archive
        printf "Extracting $A...\n"
        tar -xzf $A #wish you could see progress without verbose output or seperate packages
            
        #moves contents of extracted backup to previous folder
        rsync -a backup/* . #throws out weird error sometimes, no idea what goes on
    
        #removes archive
        rm $A

        #removes duplicate /backup/ and its contents
        rm -rf /mnt/$DRLT/backup/backup


        # Mirrors /home/
        printf "Mirroring /home/...\n"
            rsync -a --info=progress2 /home/ /mnt/$DRLT/backup
    else
        printf "Mirroring /home/...\n"
            rsync -a --info=progress2 /home/ /mnt/$DRLT/backup
        printf "Archiving /backup/...\n"
            cd /mnt/$DRLT/
            tar -czf $D.tgz backup/ 2>/dev/null
        printf "Moving new archive to /vers/...\n"
            mv $D.tgz /mnt/$DRLT/vers/
        printf "Cleaning Up...\n"
        cd /mnt/$DRLT/
        rm -rf backup
        mkdir backup
        printf "Archiving /home/ complete!\n"
        exit 0
    fi

#Part 5- Archiving mirrored /home/ and extracted previous version, cleaning up
    printf "Archiving new version...\n"
    cd ..
    tar -czf $D.tgz backup/  #archives /home/ not mirrored home (solved)
    printf "Moving new archive to /vers/...\n"
    mv $D.tgz /mnt/$DRLT/vers/
    printf "Cleaning Up...\n"
    cd /mnt/$DRLT/
    rm -rf backup
    mkdir backup
    printf "Archiving /home/ complete!\n"
    exit 0

#end