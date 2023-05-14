
# PdubG - Password Generator
# Randomly generates a cryptographically safe password with user-defined parameters
# Pydocs Referenced:
# Secrets - https://docs.python.org/3/library/secrets.html
# String - https://docs.python.org/3/library/string.html
# Random - https://docs.python.org/3/library/random.html
# Authored by adminr00t, all rights reserved


import string
import secrets
import random

def userInput():
    "This function grabs the Desired Length, # of capital and lowercase letters, numbers and special chars from the user"

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
    return capLetters, lowerLetters, num, specChars


def generator(): 
    "This function takes the returned values of userInput() to generate a PWD String"

    caps, lows, nums, spec = userInput()


    numbers = string.digits
    uppercase = string.ascii_uppercase
    lowercase = string.ascii_lowercase
    specChars = string.punctuation

    generatedPwd = ''
    generatedPwd = ''.join([secrets.choice(uppercase) for i in range(caps)] +
                [secrets.choice(lowercase) for i in range(lows)] +
                [secrets.choice(numbers) for i in range(nums)] +
                [secrets.choice(specChars) for i in range(spec)])

    jumbler = list(generatedPwd)
    random.shuffle(jumbler)
    password = ''.join(jumbler)
            
    print("\nNew password is:", password)
    return

generator()

