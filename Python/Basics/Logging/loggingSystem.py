from __future__ import annotations
# from asa.path import PathPrompt
from rich.console import Console
from rich.theme import Theme
from pathlib import Path

import atexit
import datetime
import logging
import os
import shutil
import re

LOGGING_THEME = Theme(
    {
        "info": "dark_cyan",
        "warning": "bright_yellow",
        "error": "orange3 underline",
        "critical": "bright_red underline2 bold",
    }
)

# Variables
__author__ = "Joshua Minniss"

# Major.Minor.Patch
__version__ = "1.0.0"

now = datetime.datetime.now()
today = now.strftime(r"%Y-%m-%d-%H-%M-%S")
rootFolder = "./Ops"
tempPath = rootFolder + "/Temp"  # placeholder path !TODO decide if this is needed or not
dataPath = rootFolder + "/Data"  # placeholder path !TODO replace with user chosen path
logPath = rootFolder + "/Logs"  # placeholder path !TODO replace with user chosen path
console = Console(tab_size=4, highlight=False, theme=LOGGING_THEME)

# If the program was to throw a critical error, this would change.
exitStatus = 0


# region Function Definitions
def infoLog(data):
    console.print(data, style="info")
    logging.info(data)
    return

def errorLog(data):
    console.print("Program ran into an error: " + data, style="error")
    logging.error(data)
    return

def warningLog(data):
    console.print(data, style="warning")
    logging.warning(data)
    return

def criticalLog(data):
    console.print(
        "Program ran into a critical error and cannot continue: " + data, style="critical"
    )
    logging.critical(data)
    return

def logCleaning():
    count = len(list(Path(logPath).glob("*.txt")))

    for path in os.listdir(logPath):
        if os.path.isfile(os.path.join(logPath, path)):
            count += 1

    print("Logs within directory: ", count)

    if count > 5:
        # print("Too many logs. Cleaning up...")
        for log_file in Path(logPath).glob("*.txt"):
            log_file.unlink()

        for path in os.listdir(logPath):
            if os.path.isfile(os.path.join(logPath, path)):
                os.remove(os.path.join(logPath, path))
    return

def initialize():

    # initialize via version print
    infoLog("Logging System " + __version__)
    infoLog("Created by " + __author__ + "\n\n")
    infoLog("Initializing and checking if required Directories and Files exist...")
    os.makedirs(tempPath, exist_ok=True)

    # make placeholder directories
    #!!TODO redirect directories to appdata

    # if os.path.exists(dataPath) is False:
    #     os.makedirs(dataPath)
    #     warningLog("File containing Path to BOMBOQ Template does not exist")
    # else:
    #     infoLog("Data path Exists. Checking if empty...")
    #     dir = os.listdir(dataPath)

    #     if len(dir) == 0:
    #         errorLog(
    #             "Directory exists, but is empty. BOMBOQ Templates are not copied into this directoy."
    #         )
    #     else:
    #         for root, _dirs, files in os.walk(dataPath):
    #             if templatesFound:
    #                 infoLog("Templates exist in this directory")
    #             else:
    #                 for name in files:
    #                     # r".*QTYS.*\.xlsx$"
    #                     if re.match(r".*Module As-Built \d+\.\d+\.xlsx", name):
    #                         os.path.join(root, name)
    #                         infoLog("v13 BOMBOQ Found")
    #                         v13Found = True
    #                     elif re.match(r".*BOMBOQ ODM \d+\.\d+\.xlsx", name):
    #                         os.path.join(root, name)
    #                         infoLog("v8 BOMBOQ Found")
    #                         v8Found = True
    #                     elif v13Found is True and v8Found is True:
    #                         templatesFound = True
    #                         break

    infoLog("Program Initialized, ready to begin...")
    return


def main():
    initialize()
    
    return

# creation of sessions log file
os.makedirs(logPath, exist_ok=True)
logCleaning()
logFileName = logPath + "/" + today + ".log"
logging.basicConfig(
    filename=logFileName,
    format=today + " " + "%(levelname)s: " + "%(message)s",
    level=logging.DEBUG,
)

# function calls
main()
# warningLog("Removing Temp folder...")
# shutil.rmtree(tempPath)
input("Exiting script, please press enter to continue...")
atexit.register
exit()
# endregion
