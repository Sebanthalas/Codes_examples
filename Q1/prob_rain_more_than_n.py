"""
Main code.
Author: Sebastian Moraga Scheuermann
Date: July 6, 2024
Description:  This script is the function that accepts p (probabilities of rain on a given calendar day) and n as input arguments and returns the
possibility of raining at least n days.
"""

import numpy as np
from poibin import PoiBin
from typing import Sequence

def prob_rain_more_than_n(p: Sequence[float], n: int) -> float:

	# Verify that the vector has length 365
	if len(p)==365 and n<365:
		# Create the Poisson Binomial distribution object
		pb   = PoiBin(p) 
		# Calculate the probability of having more than n successes
		prob_more_than_n = 1 - pb.cdf(n)
		return prob_more_than_n
	else:
		raise RuntimeError("Input values not accepted")


if __name__ == "__main__":
    pass



