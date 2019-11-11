#include <string>
#include <vector>
#include <iostream>

int min(int a, int b) {
    return a < b ? a : b;
}

int min3(int a, int b, int c) {
    return min(min(a, b), c);
}

std::string format_matrix(std::string a, std::string b, std::vector<std::vector<int>> m) {

    std::string text = "\t";

    for (auto character : b) text += std::string("\t") + character;
    text += "\n";

    for (int i=0; i<m.size(); i++) {
        if (i > 0) text += a[i-1];
        for (int j=0; j<m[i].size(); j++) text += "\t" + std::to_string(m[i][j]);
        text += "\n";
    }

    return text;
}

int levenshtein(std::string a, std::string b, bool print_matrix) {

    std::vector<std::vector<int>> d(a.size()+1);
    int substitution_cost = 0;

    // Allocate rows
    for (int i=0; i<a.size()+1; i++) {
        d[i] = std::vector<int>(b.size()+1, 0);
        d[i][0] = i;
    }
    for (int j=0; j<b.size()+1; j++) d[0][j] = j;

    // Flood strategy to fill the matrix
    for (int j=0; j<b.size(); j++) {
        for (int i=0; i<a.size(); i++) {
            d[i+1][j+1] = min3(d[i][j+1]+1,
                               d[i+1][j]+1,
                               d[i][j]+(a[i] == b[j] ? 0 : 1));
        }
    }

    if (print_matrix) {
        std::cout << format_matrix(a, b, d) << std::endl;
    }

    return d[a.size()][b.size()];
}
