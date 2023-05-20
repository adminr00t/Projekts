import string
import secrets
import random

numbers = string.digits
uppercase = string.ascii_uppercase
lowercase = string.ascii_lowercase
specChars = string.punctuation

generatedPwd = ''
generatedPwd = ''.join([secrets.choice(uppercase) for i in range(4)] +
            [secrets.choice(lowercase) for i in range(4)] +
            [secrets.choice(numbers) for i in range(4)] +
            [secrets.choice(specChars) for i in range(4)])

jumbler = list(generatedPwd)
random.shuffle(jumbler)
password = ''.join(jumbler)
        
print("\nNew password is:", password)