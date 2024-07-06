"""
Example code for testing.
Author: Sebastian Moraga Scheuermann
Date: July 6, 2024
Description: This script creates a vector of probabilities "p" from a .txt file of 365 entries (days)
and takes n (days) as input from the user.
"""
from prob_rain_more_than_n import *
import numpy as np

# Example usage:
p = []   # Total number of days, must be 365 as in Q1.
# Open and read the file
with open('p.txt', 'r') as file:
    # Iterate over each line in the file
    for line in file:
        # Convert the line to float and append to the list
        p.append(float(line.strip()))
p = np.array(p)        
n = int(input("Enter the number of days: "))  # Prompt user for input
print(f"The probability of raining more than {n} times is: {prob_rain_more_than_n(p, n)}")
