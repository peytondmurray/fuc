import numpy as np
import sys


def levenshtein(a, b, print_matrix=False):
    """Wagner-Fischer algorithm for calculating the Levenshtein distance (or edit distance) between two strings a and b.
    The segement `a[:i]` can be transformed to `b[:j]` using a minimum of `d[i, j]` operations.

    Parameters
    ----------
    a : str
        'source' string to be compared against the target string. Characters in this string correspond to rows in the
        matrix `d`.
    b : str
        'target' string to be compared against the source string. Characters in this string correspond to columns in
        the matrix `d`.

    Returns
    -------
    int
        Integer representing the Levenshtein distance.
    """

    d = np.zeros((len(a)+1, len(b)+1))

    d[1:, 0] = np.arange(1, len(a)+1)
    d[0, 1:] = np.arange(1, len(b)+1)

    for j in range(len(b)):
        for i in range(len(a)):
            if a[i] == b[j]:
                substitution_cost = 0
            else:
                substitution_cost = 1

            d[i+1, j+1] = min(d[i, j+1]+1,
                              d[i+1, j]+1,
                              d[i, j] + substitution_cost)

    if print_matrix:
        print(d, '\n')

    return d[len(a), len(b)]


def main():

    print(sys.argv[1], sys.argv[2])

    print(levenshtein(sys.argv[1], sys.argv[2], print_matrix=True))

    return


if __name__ == "__main__":
    main()
