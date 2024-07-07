Made in New Westminster, Canada by  [Sebanthalas](https://sites.google.com/view/sebanthalas), July 2024
 


This folder contains the solution to the screen questions for the Picovoice job application Deep Learning Researcher.

All the files  should run locally. The first step is to download the .zip file and try to run it.

* Made on Linux (x86_64)
 
 
# **Q1:Chance it rains more than n days in Vancouver**

# Theoretical solution to Q1:



---

To calculate the probability that it rains in Vancouver more than $n$ times with given probabilities $p_1,p_2,\ldots,p_{365}$, we use the cumulative distribution function (CDF) for the Poisson Binomial distribution.

Let $X_i$ be a Bernoulli random variable representing the event of rain on a day $i$, with $P(X_i =1)=p_i$ and $P(X_i =0)=1-p_i$. Note that the total number of rainy days $S$ in Vancouver is the sum of these Bernoulli random variables. Our goal is to compute $P(S>n)$.

To do so, we first compute the cumulative distribution function (CDF)  $F_S(k)$, which represents the probability that $S$ is less than or equal to $k$. This is given by

$$F_S(k)= \sum_{j=0}^{k} \sum_{A \subseteq \lbrace 1,\ldots 365\rbrace,|A|=j } \prod_{i \in A} p_i \prod_{i \not \in A} (1-p_i),$$
where $A \subseteq \lbrace 1,\ldots 365\rbrace$ represents all subsets of the set $\lbrace 1,\ldots 365\rbrace$, $|A|$ denotes the cardinality (number of elements) of subset $A$, $\prod_{i \in A} p_i$
is the product of success probabilities $p_i$​ for all $i$ in subset $A$ and $\prod_{i \not \in A} (1-p_i)$ is the product of failure probabilities $1-p_i$ for all $i$ not in $A$.

Hence, our goal is to compute the following quantity
$$P(S>n)=1- F_S(n).$$
We do this below  using an implementation in Python.

# Implementation of the solution in python:

  The function that accepts $p$ (probabilities of rain on a given calendar day) and $n$ as input arguments and returns the
possibility of raining at least $n$ days is in: 
 * Q1/prob_rain_more_than_n.py*

Documentation:


---


Files


*   example.py: Example script to test the main code. This script reads a vector of probabilities $p$ from a .txt file of 365 entries (days) and takes n (days) as input from the user.
*  p.txt: This file is for testing. It contains the probabilities of rain for 365 days. If needed, replace this with the real data.
* poibin.py: Implementation of the Poisson Binomial distribution by Mika Straka see [Hong2013](https://doi.org/10.1016/j.csda.2012.10.006).
* prob_rain_more_than_n.py: Function that accepts $p$ (rain probabilities on a given calendar day) and $n$ as input arguments, returning the possibility of raining at least $n$ days.

Assumptions
* The vector $p$ must have 365 days and $n$ must be less than $365$.
           

Requirements

* Operating System: Developed and tested on Unix-based systems (Linux). Should work on Windows and MacOS with appropriate adjustments.

* Dependencies: Standard Python libraries (numpy, poibin, typing, collections).

Features

* User Input: Allows users to input the number of days n.

* Testing: For testing purposes, a random vector p with 365 entries in the range [0, 1] is saved in a file p.txt. Replace this file with real-world data for testing.

Usage from Terminal

1.  Navigate to the Folder Location:

 
    $ cd Q1

2. Execution of Example:


    $ python3 example.py

Example


    $ cd Q1
    $ python3 example.py
    Enter the number of days: 2
    The probability of raining more than 2 times is: 0.9999999999999768


---
---

# **Q2: Find Word Combos with Pronunciation**

#  Solution coded in python:

  The script that finds all possible combinations is in : 
 * Q2/findwords.py*

Documentation:


---


 Files  
   
* example.py     : example script to test the main code. Imports the main function from findwords.py and gives as input the file path to the dictionary and the sequence of phonemes.
* findwords.py   : main code that  finds all possible combinations of words from the pronunciation dictionary.
* pronundic.txt  : File containing the dictionary with words and phonemes.

Requirements
 
* Operating System: Developed and tested on Unix-based systems (Linux). Should work on Windows and MacOS with appropriate adjustments.
* Dependencies: Standard python libraries (typing, collections).

Features
 
* User Input: Allows users to replace the dictionary of words and phonemes.

* In case of having a larger dictionary of words and phonemes, replace the file  pronundic.txt with the complete dictionary. 

Usage from terminal: 
 
1.  Navigate to the Folder Location:

 
    $ cd Q2

2. Execution of example 


    $ python3 example.py



Example

 
    $ cd Q2
    $ python3 example.py
    [['THEIR', 'THEIR'], ['THEIR', 'THERE'], ['THERE', 'THEIR'], ['THERE', 'THERE']]

 
 

To test other inputs:
---------------------

Modify line 9 in examply.py from

    phonemes_input = ["DH", "EH", "R", "DH", "EH", "R"]  
to (or as needed)


    phonemes_input = ["T", "AH", "M", "EY", "T", "OW","T", "AH", "M", "AA", "T", "OW"] 

we get the output

    [['TOMATO', 'TOMATO']]

----

---

# **Q3: Shakespearean Word Frequency Counter**

#   Solution coded in C:
This code in C reads a text file containing the Shakespeare dataset, computes the frequency of each word, and identifies the top N most frequent words. It utilizes a hash table for efficient word counting and sorting algorithms to find the most frequent words.
  The script that finds all possible combinations is in : 
 * Q3/main.c*
   
Documentation:


---

Files and folder
   
* main.c         : main "C" code.
* shakespear.txt : source dataset (the Shakespear text).
* bin            : Folder that contains the bild of the code once it is compiled.

Requirements
 
* Operating System: Developed and tested on Unix-based systems (Linux). Should work on Windows and MacOS with appropriate adjustments.

* Dependencies: Standard C libraries (stdio.h, stdlib.h, string.h, ctype.h, stdint.h, time.h).

Features
 
* User Input: Allows users to specify the number of top frequent words ($N$) to find.

* Efficient Word Counting: Uses a hash table to efficiently count occurrences of each word in the input text.

* Sorting:  Sorts words based on their frequency in descending order using quicksort algorithm.

* Outputs the computational time for efficiency.

Performance
 
* Time Complexity: The program performs efficiently with a time complexity of $\mathcal{O}(W\log ⁡W)$, where $W$ is the number of unique words in the document.

* Memory Usage: Memory usage is moderate and scales with the number of unique words and the number of top frequent words ($N$).


Usage from terminal: 
 
1.  Navigate to the Folder Location:

 
    $ cd Q2

2. Compilation: Compile the program using a C compiler (e.g., gcc) (This creates a file in bin):  
    
    
    $ gcc main.c -o bin/word_frequency_counter


3. Execution: Run the compiled executable with the path to the Shakespearean text file:


    $ ./bin/word_frequency_counter shakespeare.txt

4. Enter the number of top frequent words to find


    Enter the number of top frequent words to find: 
 
 Example:
 
    $ cd Q3
    $ gcc main.c -o bin/word_frequency_counter
    $ ./bin/word_frequency_counter shakespeare.txt
    Enter the number of top frequent words to find: 5
    The 5 most frequent words are:
    the
    and
    i
    to
    of
    Time taken to find the most frequent words: 0.035793 seconds
 
