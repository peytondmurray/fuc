#include <cstring>
#include <string>
#include <cctype>
#include "result.h"

// Copied from fzf source.
#define SCOREMATCH 16
#define SCOREGAPSTART -3
#define SCOREGAPEXTENSION -1

#define BONUSBOUNDARY SCOREMATCH/2
#define BONUSNONWORD SCOREMATCH/2
#define BONUSCAMEL123 BONUSBOUNDARY+SCOREGAPEXTENSION
#define BONUSCONSECUTIVE -(SCOREGAPSTART+SCOREGAPEXTENSION)
#define BONUSFIRSTCHARMULTIPLIER 2

Result fzmatch(std::string pattern, std::string input);
int asciiFuzzyIndex(std::string pattern, std::string input);
int trySkip(char pattern, std::string input, int from);

Result fzmatch(std::string pattern, std::string input) {
    int M = pattern.size();
    int N = input.size();

    if (M == 0) return Result();
    if (N == 0) return Result();

    // Optimized search for ASCII string
    int idx = asciiFuzzyIndex(pattern, input);
    if (idx < 0) return Result();

    // Calculate bonus for each point
    {
        int maxScore = 0;
        int maxScorePos = 0;
        int pidx = 0;
        int lastIdx = 0;
        char pchar0 = pattern[0];
        char pchar = pattern[0];
        int prevH0 = 0;
        int prefClass = 0;
        bool inGap = false;
        
        // TODO: Normalize characters: ä -> a, ö -> o, etc

        // Tally bonuses
        for (int i=idx; i<N-1; i++) {
            if input[i]
        }


        // Must iterate through entire pattern; otherwise, match fails
        if (pidx != M) return Result();
        if (M == 1) return Result(maxScorePos, maxScorePos+1, maxScore);
    }


    // Fill in score matrix. Do not allow skipping of characters in pattern.

    // (optional) backtrace to find character positions
}

int asciiFuzzyIndex(std::string pattern, std::string input) {
    int firstIdx = 0;
    int idx = 0;

    for (int pidx=0; pidx<pattern.size(); pidx++) {
        idx = trySkip(pattern[pidx], input, idx);
        if (idx == -1) return -1;
        if (pidx == 0 && idx > 0) firstIdx = idx-1;
        idx++;
    }
    return firstIdx;
}


// Get index of first appearance of pattern in input. If neither lowercase or uppercase
// is not found, then returns -1.
int trySkip(char pattern, std::string input, int from) {
    int idx = input.find(std::tolower(pattern), from);

    if (idx == std::string::npos) {
        // No lowercase pattern found. Try uppercase.
        int uidx = input.find(std::toupper(pattern), from);
        return uidx == std::string::npos ? -1 : uidx;
    } else {
        // Lowercase pattern found, but there could still have been uppercase.
        // Check the substring input[from:idx]
        int uidx = input.substr(from, idx-from).find(std::toupper(pattern));
        return uidx == std::string::npos ? idx : -1;
    }
}
