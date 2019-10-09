#include <vector>
#include <string>

int generate_H(std::string, std::string);
int first_possible_match(std::string, std::string);
int fill_value(std::string, std::string, std::vector<std::vector<int>>, int, int);
int gap(int);
int substitution(char, char);
int maxval(std::vector<int>);

// Search all the elements of symbols for pattern, using a modified Smith-Waterman algorithm.
// https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm
// Returns the highest value of the H-matrix for each item in symbols.
std::vector<int> fzmatch(std::string pattern, std::vector<std::string> symbols) {

    std::vector<int> Hmax(symbols.size());
    for (int i=0; i<symbols.size(); i++) {
        Hmax[i] = generate_H(pattern, symbols[i]);

    }
    return Hmax;
}

int fzmatch(std::string pattern, std::string symbol) {
    return generate_H(pattern, symbol);
}


// Find the maximum value of the scoring matrix H. A return value of -1 indicates no match.
int generate_H(std::string A, std::string B) {

    int Hmax = 0;
    std::vector<std::vector<int>> H(A.size());

    int skip_j = first_possible_match(A, B);
    if (skip_j == std::string::npos) return -1;

    for (int i=0; i<A.size(); i++) {

        H[i] = std::vector<int>(B.size(), 0);
        for (int j=skip_j; j<B.size(); j++) {
            H[i][j] = fill_value(A, B, H, i, j);
            if (H[i][j] > Hmax) Hmax = H[i][j];
        }
    }
    return Hmax;
}

// To cut down the amount of ties we call fill_value, we do a quick search to find where the
// first character in A can be found in B. If there is no match, we don't need to any more work
// to determine the score.
int first_possible_match(std::string A, std::string B) {
    return B.find(B[0]);
}

// Determines the value of H[i][j] according to the (modified) Smith-Waterman algorithm.
// See https://en.wikipedia.org/wiki/Smith%E2%80%93Waterman_algorithm for details.
int fill_value(std::string A, std::string B, std::vector<std::vector<int>> H, int i, int j) {

    return maxval(std::vector<int>{H[i-1][j-1] + substitution(A[i-1], B[j-1]),
                                   H[i-1][j] - gap(1),
                                   H[i][j-1] - gap(1),
                                   0});

}

// Substitution matrix. Gives a bonus if the characters match (less if the case doesn't match),
// or penalizes a mismatch.
int substitution(char a, char b) {
    if (a == b) {
        return 30;
    } else if (std::tolower(a) == std::tolower(b)) {
        return 20;
    } else {
        return -30;
    }
}

// Gap penalty
int gap(int g) {
    return 10*g;
}

// Return the maximum value of a vector of ints
int maxval(std::vector<int> v) {
    int max = v[0];
    for (auto val : v) if (max < val) max = val;
    return max;
}