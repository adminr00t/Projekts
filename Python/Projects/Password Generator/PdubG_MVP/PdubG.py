
# PdubG - Password Generator

# 

#     User Input
#         -> Desired length
#         -> Amount of capital letters
#         -> Amount of lowercase letters
#         -> Amount of numbers
#         -> Amount of special characters

#     -> Generates a password of random chars that meets or exceeds desired length
import string
import secrets

def userInput():
    "This function grabs the Desired Length, # of capital and lowercase letters, numbers and special chars from the user"

    while True:
        try:
            dLength = int(input("How many characters should the PWD contain? "))
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
    
    print("The desired length of the generated PWD is: " , dLength)
    print("The actual length of the password will be: ", totalPwdLength)

    decider = str(input("Would you like to use Actual or the Desired length of the PWD? "))

    if decider == "Actual":
        print("PWD will be ", totalPwdLength, "characters long")
        lengthToUse = totalPwdLength
    elif decider == "Desired":
        print("PWD will be", dLength, "characters long")
        lengthToUse = dLength
    else:
        print("Incorrect input, defaulting to desired length")
        lengthToUse = dLength
    return lengthToUse, capLetters, lowerLetters, num, specChars

def generator(): 
    "This function takes the returned values of userInput() to generate a PWD String"

    length, caps, lows, nums, spec = userInput()

    alphabet = string.ascii_letters + string.digits + string.punctuation
    while True:
        password = ''

        for i in range(length):
            password += ''.join(secrets.choice(alphabet))
        if(any(char.islower() for char in password)) == lows:
            break
        if(any(char.isupper() for char in password)) == caps: 
            break
        if(any(char in alphabet for char in password)) == spec:
            break
        if(sum(char.isdigit() for char in password)) == nums:
            break
            
    print("\nNew password is: ", password)
    return

generator()

