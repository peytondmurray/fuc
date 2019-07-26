#ifndef FUZZYMATCH_H
#define FUZZYMATCH_H

//https://github.com/forrestthewoods/lib_fts/blob/master/code/fts_fuzzy_match.h

#include <cstring>
#include <string>

static int fuzzy_match(const char *pattern, const char *str) {
    int score = 0;
    while (*pattern != '\0' && *str != '\0') {
        if (std::tolower(*pattern) == std::tolower(*str)) {
               
            pattern++;
        }
        str++;
    }
    // return *pattern == '\0' ? true : false;
    return score;
}


static bool fuzzy_match_recursive(const char *pattern,
                                  const char *str, 
                                  int &outScore, 
                                  const char *strBegin, 
                                  uint8_t const *srcMatches, 
                                  uint8_t *matches,
                                  int maxMatches, 
                                  int nextMatch, 
                                  int &recursionCount, 
                                  int recursionLimit) {

    // Count recursions
    if (recursionCount++ >= recursionLimit) return false;

    // Detect end of strings
    if (*pattern == '\0' || *str == '\0') return false;

    // Recursion parameters
    bool recursiveMatch = false;
    uint8_t bestRecursiveMatches[256];
    int bestRecursiveScore = 0;

    // Loop through pattern and str looking for a match
    bool first_match = true;
    while (*pattern != '\0' && *str != '\0') {

        // Found match
        if (std::tolower(*pattern) == std::tolower(*str)) {

            // Supplied matches buffer was too short
            if (nextMatch >= maxMatches) return false;

            // "Copy-on-write" srcMatches into matches
            if (first_match && srcMatches) {
                std::memcpy(matches, srcMatches, nextMatch);
                first_match = false;
            }

            // Recursive call that "skips" this match
            uint8_t recursiveMatches[256];
            int recursiveScore;
            if (fuzzy_match_recursive(pattern,
                                      str+1,
                                      recursiveScore, 
                                      strBegin, 
                                      matches, 
                                      recursiveMatches, 
                                      sizeof(recursiveMatches), 
                                      nextMatch, 
                                      recursionCount, 
                                      recursionLimit)) {

                // Pick the best recursive score
                if (!recursiveMatch || recursiveScore > bestRecursiveScore) {
                    std::memcpy(bestRecursiveMatches, recursiveMatches, 256);
                    bestRecursiveScore = recursiveScore;
                }
                recursiveMatch = true;
            }

            // Advance
            matches[nextMatch++] = (uint8_t)(str - strBegin);
            pattern++;
        }
        str++;
    }

    bool matched = *pattern == '\0' ? true : false;

    if (matched) {

        // Factors which contribute to the matching score
        const int sequential_bonus = 15;
        const int separator_bonus = 30;
        const int camel_bonus = 30;
        const int first_letter_bonus = 15;
        const int leading_letter_penalty = -5;
        const int max_leading_letter_penalty = -15;
        const int unmatched_letter_penalty = -1;

        // Iterate str to end
        while (*str != '\0') str++;

        // Initialize score
        outScore = 100;

        // Apply leading letter penalty
        int penalty = leading_letter_psenalty*matches[0];
        if (penalty < max_leading_letter_penalty) penalty = max_leading_letter_penalty;
        outScore += penalty;

        // Apply unmatched penalty
        int unmatched = (int)(str - strBegin) - nextMatch;
        outScore += unmatched_letter_penalty*unmatched;

        // Apply ordering bonuses
        for (int i=0; i<nextMatch; i++) {
            uint8_t currIdx = matches[i];

            if (i > 0) {
                uint8_t prevIdx = matches[i-1];

                // Sequential
                if (currIdx == (prevIdx + 1)) outScore += sequential_bonus;
            }

            // Check for bonuses based on neighbor character value
            if (currIdx > 0) {

                // Camel case
                char neighbor = strBegin[currIdx - 1];
                char curr = strBegin[currIdx];
                if (std::islower(neighbor) && std::isupper(curr)) outScore += camel_bonus;

                // Separator
                if (neighbor == '_' || neighbor == ' ') outScore += separator_bonus;
            } else {

                // First letter
                outScore += first_letter_bonus;
            }
        }
    }

    // Return best result
    if (recursiveMatch && (!matched || bestRecursiveScore > outScore)) {
        // Recursive score is better than "this"
        std::memcpy(matches, bestRecursiveMatches, maxMatches);
        outScore = bestRecursiveScore;
        return true;
    } else if (matched) {
        // "this" score is better than recursive
        return true;
    }
    else {
        // no match
        return false;
    }
}


#endif