#string generator
#objective: generate a string (user-given length) of random numbers, letters (caps and lowercase) and special characters

import string
import secrets

alphabet = string.ascii_letters + string.digits + string.punctuation
while True:
    password = ''

    for i in range(20):
        password += ''.join(secrets.choice(alphabet))
    if (any(char.islower() for char in password)
            and any(char.isupper() for char in password)
            and sum(char.isdigit() for char in password) >= 6):
            break
        
print("\nNew password is:", password)