"""
Example code for testing.
Author: Sebastian Moraga Scheuermann
Date: July 6, 2024
Description:   This script contains the phonemes inputs to be used in the main code.
"""
from findwords import *
# Example usage
phonemes_input = ["T", "AH", "M", "EY", "T", "OW","T", "AH", "M", "AA", "T", "OW"]
file_path      = 'pronundic.txt'   #We can replace this for a larger example
combinations   = find_word_combos_with_pronunciation(phonemes_input, file_path)
print(combinations)