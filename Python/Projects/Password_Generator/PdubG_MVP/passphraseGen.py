import secrets

with open('filteredWords.txt') as filtered:
    words = [word.strip() for word in filtered]
    password = '_'.join(secrets.choice(words) for i in range(6))
    print(password)