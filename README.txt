Franklin Pinnock 
Autocorrect Program

This program reads from standard command line input and then compares the words that it sees with words in a dictionary file, which has a set of known words and their accompanying frequencies. 

If the word was not found it would compare the word with all possible permutations of a possible correct word, using insertion, replacement, and deletion, and try to find one of those permutations in the dictionmary. If more than one possible permutation was found in the dictionary file, the choice that is lexicographically smallest is chosen to correct the incorrect word.

If no words can be found to correct the word, it is then added to the dictionary file.