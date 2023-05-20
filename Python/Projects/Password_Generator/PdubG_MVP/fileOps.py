string = open('wordList.txt').read()
filteredWords = list()

for word in string.split():
    length = len(word) 
    
    if length <= 5:
        print(word, "erased")
    else:
        filteredWords.append(word)
        print(word, "added to list")

with open('filteredWords.txt', 'w') as outputFile:
  outputFile.write('\n'.join(str(i) for i in filteredWords))