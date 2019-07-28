#include <cstring>
#include <string>
#include <cctype>

// Bonuses
#define CONSECUTIVE_BONUS 5
#define MATCHED_CHAR_BONUS 1
#define SEPARATOR_BONUS 10
#define CAMEL_BONUS 10
#define FIRST_CHAR_BONUS 15

// Penalties
#define LEADING_CHAR_PENALTY -3
#define MAX_NUMBER_LEADING_CHAR_PENALTIES 3
#define UNMATCHED_LETTER_PENALTY -1

// Function declarations

// Wrapper for the fuzzy matching function.
int fzmatch(const char *patter, const char *str);
void _fzmatch(const char *pattern, const char *str, int &topScore, int nConsecutive, int nLeadingPenalties, int recursionDepth, int maxRecursion);


int fzmatch(const char *pattern, const char *str) {
    int topScore = 0;
    _fzmatch(pattern, str, topScore, 0, 0, 0, 10);
    return topScore;
}

void _fzmatch(const char *pattern, const char *str, int &topScore, int nConsecutive, int nLeadingPenalties, int recursionDepth, int maxRecursion) {

    // If we are at the max recursion depth, or at the end of either of the strings, get out
    if ((recursionDepth >= maxRecursion) || (*pattern == '\0' || *str == '\0')) return;

    if (std::tolower(*pattern) == std::tolower(*str)) {
        nLeadingPenalties = 0;

        int topScoreMatch = 0;
        int topScoreSkip = 0;

        // Tally the bonuses from matching
        if (nConsecutive > 0){
            topScoreMatch += CONSECUTIVE_BONUS;
            if (std::isupper(*pattern) && std::islower(*(pattern - 1))) topScoreMatch += CAMEL_BONUS;
        }
        if (*pattern == ' ' || *pattern == '_') topScoreMatch += SEPARATOR_BONUS;
        if (recursionDepth == 0) topScoreMatch += FIRST_CHAR_BONUS;


        // Set topScore equal to the
        _fzmatch(pattern+1, str+1, topScoreMatch, nConsecutive+1, 0, recursionDepth+1, maxRecursion);
        _fzmatch(pattern, str+1, topScoreSkip, 0, 0, recursionDepth+1, maxRecursion);
        topScore += (topScoreMatch > topScoreSkip) ? topScoreMatch : topScoreSkip;
    } else {
        if ((recursionDepth == nLeadingPenalties) && nLeadingPenalties < MAX_NUMBER_LEADING_CHAR_PENALTIES) {
            topScore += LEADING_CHAR_PENALTY;
            nLeadingPenalties++;
        } else nLeadingPenalties = 0;
        topScore += UNMATCHED_LETTER_PENALTY;
        _fzmatch(pattern, str+1, topScore, 0, nLeadingPenalties, recursionDepth+1, maxRecursion);
    }

    return;
}