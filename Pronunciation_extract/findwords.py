"""
Main code.
Author: Sebastian Moraga Scheuermann
Date: July 6, 2024
Description:  This code effectively finds all possible combinations of words from the pronunciation 
dictionary that can produce the given sequence of phonemes using preprocessing 
and a recursive backtracking approach.
"""

#======================================================================================

#Importing libraries.
# -typing     : specify types for better readability and type checking
# -defaultdict: is used to simplify dictionary operatios

from typing import List, Sequence
from collections import defaultdict

#======================================================================================
# Sample pronunciation dictionary
#  This function loads a dictionary containing the relationship betwee the words and 
#  their phoneme sequence. 
#  It is not a one-to-one mapping T: PHONEMA -> WORD (non-injective surjective).
#  It assumes each line contains a word followed by its phonemes separated by 
#  spaces: ABACUS AE B AH K AH S
#  The file must be a .txt with the format

def load_pronunciation_dict(file_path: str):
    pronunciation_dict = defaultdict(list)
    with open(file_path, 'r') as file:
        for line in file:
            parts    = line.strip().split()
            word     = parts[0]
            phonemes = parts[1:]
            pronunciation_dict[word].append(phonemes)
    return pronunciation_dict

#======================================================================================
# Function that uses  a loop through the pronunciation dictionary. 
# If the phoneme value is a list of lists (multiple pronunciations), loop through each
# sublist and add the word to the phoneme_to_words dictionary. If it's a single list, 
# add it directly. Convert phoneme lists to tuples as dictionary keys 
# because lists are not hashable.

def preprocess_pronunciation_dict(pronunciation_dict): 
    phoneme_to_words = defaultdict(list) #Storing phoneme sequences as keys and list of words as values
    for word, phonemes in pronunciation_dict.items():
        if isinstance(phonemes[0], list):
            for phoneme_seq in phonemes:
                phoneme_to_words[tuple(phoneme_seq)].append(word)
        else:
            phoneme_to_words[tuple(phonemes)].append(word)
    return phoneme_to_words # eg,. ('DH', 'EH', 'R'): ['THEIR', 'THERE']

#======================================================================================
# Define a function  that takes phonemes, the processed dictionary, a starting index, and a current path as inputs
def find_combinations(phonemes, phoneme_to_words, start=0, path=None):
    if path is None: # initialize it as an empty list. This is to handle the initial call.
        path = []

    #If the starting index equals the length of the phonemes, it means we have matched the entire sequence.
    if start == len(phonemes): 
        return [path[:]] #Return a copy of the current path (a valid combination)

    results = [] # store valid combinations found during the recursion.
    #Loop through possible end indices to form substrings of the phoneme sequence. Convert each substring to a tuple.
    for end in range(start + 1, len(phonemes) + 1):
        phoneme_seq = tuple(phonemes[start:end])
        #If the phoneme sequence is in the dictionary, loop through the corresponding words.
        if phoneme_seq in phoneme_to_words:
            for word in phoneme_to_words[phoneme_seq]:
                path.append(word)
                #Append each word to the current path
                results.extend(find_combinations(phonemes, phoneme_to_words, end, path))
                path.pop()

    return results

#======================================================================================

def find_word_combos_with_pronunciation(phonemes: Sequence[str], file_path: str) -> Sequence[Sequence[str]]:
    pronunciation_dict = load_pronunciation_dict(file_path)
    phoneme_to_words   = preprocess_pronunciation_dict(pronunciation_dict)
    return find_combinations(phonemes, phoneme_to_words)

#======================================================================================

