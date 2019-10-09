# Implementation of Smith-Waterman algorithm, but without allowing mismatches or omissions.

import sys
import numpy as np


def main():

    A = 'bryptic'
    B = 'one man stole the Covery ryo container'

    tb, H = fzmatch(A, B, substitution, gap_penalty)

    if tb is None:
        print('No match.')
        return

    # print_H(A, B, H)

    print(np.max(H))

    # traceback_compare(A, B, tb)

    # print(fzmatch(sys.argv[0], sys.argv[1], substitution, gap_penalty))

    return


def print_H(A, B, H):

    print('\t\t'+'\t'.join(B))
    for i in range(H.shape[0]):

        line = ''
        if i > 0:
            line += A[i-1]

        for j in range(H.shape[1]):
            line += f'\t{int(H[i, j])}'

        print(line)

    return


def traceback(H, ij=None):

    if ij is None:
        ijmax = argmax2d(H)
        return [ijmax] + traceback(H, ijmax)
    else:
        i, j = ij[0], ij[1]
        _ij = ((i-1, j), (i, j-1), (i-1, j-1))
        _H = [H[_index] for _index in _ij]
        ijmax = _ij[np.argmax(_H)]

        if H[ijmax] == 0:
            return []
        else:
            return [ijmax] + traceback(H, ijmax)


def gap_penalty(size):
    return size*3


def fzmatch(A, B, s, W):

    # Fill the scoring matrix
    H = generate_H(A, B, s, W)

    if H is None:
        return None, None

    # Trace back the scoring matrix
    return traceback(H), H


def generate_H(A, B, s, W):
    H = np.zeros((len(A)+1, len(B)+1))

    skip_j = first_possible_match(A, B)

    if skip_j == -1:
        return None
        # skip_j = 0

    for i in range(1, H.shape[0]):
        for j in range(1+skip_j, H.shape[1]):
            H[i, j] = np.max([H[i-1, j-1] + s(A[i-1], B[j-1]),
                              gap_i(A, B, W, H, i, j),
                              gap_j(A, B, W, H, i, j),
                              0])
    return H


def first_possible_match(A, B):
    return B.find(f'{A[0]}')


def gap_i(A, B, W, H, i, j):
    # return H[i-1, j] - W(1)
    return 0  # No gaps along i (the search string) allowed


def gap_j(A, B, W, H, i, j):
    return H[i, j-1] - W(1)


def substitution(a, b):
    """Substitution matrix for characters a and b.

    Parameters
    ----------
    a : string
        Character to compare
    b : string
        Character to compare

    Returns
    ----------
    string
        Score
    """

    # return 3 if a == b else -3

    if a == b:
        return 30
    elif a.lower() == b.lower():
        return 20
    else:
        return -30


def argmax2d(a):

    i_amax = (0, 0)
    amax = a[i_amax]
    for i in range(a.shape[0]):
        for j in range(a.shape[1]):
            if amax < a[i, j]:
                i_amax = (i, j)
                amax = a[i_amax]

    return i_amax


def traceback_compare(A, B, tb):

    tb_r = np.array(list(reversed(tb)))

    lineA = A[tb_r[0, 0]-1]
    lineB = B[tb_r[0, 1]-1]

    for i in range(1, tb_r.shape[0]):
        if tb_r[i, 0] == tb_r[i-1, 0]:
            lineA += '-'
        else:
            lineA += A[tb_r[i, 0]-1]

        if tb_r[i, 1] == tb_r[i-1, 1]:
            lineB += '-'
        else:
            lineB += B[tb_r[i, 1]-1]

    print(tb_r)
    print(f'A: {A}\nB: {B}')
    print(lineA)
    print(lineB)

    return


main()
