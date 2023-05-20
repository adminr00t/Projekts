
# PdubG - Password Generator
# Generates a Password or a Passphrase based on what the user wants
# Pydocs Referenced:
# Secrets - https://docs.python.org/3/library/secrets.html
# String - https://docs.python.org/3/library/string.html
# Random - https://docs.python.org/3/library/random.html
# Authored by adminr00t, all rights reserved


import string
import secrets
import random

def userInput():
    "This function grabs initial user input for deciding which generation technique to take"

    decision = input("Would you like to generate a password (string of chars) or passphrase (string of words): ")

    if decision == "Password" or decision == "0" or decision == "password":
        passwordGen()
    elif decision == "Passphrase" or decision == "1" or decision =="passphrase":
        passphraseGen()
    else: 
        print("Incorrect input, please try again")
    return

def passwordGen():
    "This function randomly generates a cryptographically safe password with user-defined parameters"
    while True:
        try:
            capLetters = int(input("How many Uppercase letters should the PWD contain? "))
            lowerLetters = int(input("How many Lowercase letters should the PWD contain? "))
            specChars = int(input("How many Special Characters should the PWD contain? "))
            num = int(input("How many numbers should the PWD contain? "))
        except ValueError:
            print("Sorry, your input must of data type Integer only. Please try again")
            continue
        else: 
            break            

    
    totalPwdLength =  capLetters + lowerLetters + specChars + num

    print("The length of the password will be: ", totalPwdLength)

    numbers = string.digits
    uppercase = string.ascii_uppercase
    lowercase = string.ascii_lowercase
    punc = string.punctuation

    generatedPwd = ''
    generatedPwd = ''.join([secrets.choice(uppercase) for i in range(capLetters)] +
                [secrets.choice(lowercase) for i in range(lowerLetters)] +
                [secrets.choice(numbers) for i in range(num)] +
                [secrets.choice(punc) for i in range(specChars)])

    jumbler = list(generatedPwd)
    random.shuffle(jumbler)
    password = ''.join(jumbler)
            
    print("\nNew password is:", password)
    return


def passphraseGen():
    "This function generates a passphrase using a list of words that are 5< letters in length. Separated by _"
    wordCount = int(input("How many words would you like there to be? "))


    with open('filteredWords.txt') as filtered:
        words = [word.strip() for word in filtered]
        passphrase = '_'.join(secrets.choice(words) for i in range(wordCount))
        print("\nNew Passphrase is: ", passphrase)
    return

userInput()