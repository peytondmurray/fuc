/*
fuc: Find Unicode Characters

Instead of googling the name of a symbol to find
the unicode sequence, simply


Unicode symbols list was downloaded from
https://unicode.org/Public/UNIDATA/NamesList.txt
*/


#include "main.h"

namespace fs = boost::filesystem;

int main(int argc, char** argv) {

    if (argc == 1) {
        usage();
    } else if (argc == 3 && std::strcmp(argv[1], "-parse") == 0) {
        parse(argv[2]);
    } else if (std::strcmp(argv[1], "-vs") == 0) {
        if (std::strcmp(argv[2], "-p") == 0) vs(argv[3], argv[4], true);
        else vs(argv[2], argv[3], false);
    } else if (argc == 3 && std::strcmp(argv[1], "-rankall") == 0) {
        rankAll(argv[2]);
    } else {
        int n = 1;
        std::string pattern = "";

        if (std::strcmp(argv[1], "-n") == 0) {
            n = std::stoi(argv[2]);
            for (int i=2; i<argc; i++) pattern += argv[i];
        } else {
            for (int i=1; i<argc; i++) pattern += argv[i];
        }
        findBest(pattern, n);
    }

    return 0;
}

void usage() {
        std::cout << \
"Usage:\n\n\
\tfucq TARGET\n\
\t\tPrint the unicode sequence, character, and description which most\n\
\t\tclosely matches TARGET search pattern.\n\n\
\tfucq -parse FILE\n\
\t\tParse FILE, a list of unicode symbols. See\n\
\t\thttps://unicode.org/Public/UNIDATA/NamesList.txt\n\
\t\tfor the most up-to-date symbol list.\n\n\
\tfucq -vs [-p] TARGET PATTERN\n\
\t\tPrint the Levenshtein distance between TARGET and\n\
\t\tPATTERN strings.\n\n\
\t\t-p\tAlso print the Levenshtein matrix\n";
    return;
}

std::string getCfgDir() {

    status("Getting config directory...");

    std::string cfgDir;
    const char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");

    if (xdg_config_home == NULL) {
        std::cout << "XDG_CONFIG_HOME not set! Falling back to ~/.config" << std::endl;
        cfgDir = "/home/pdmurray/.config";
    } else {
        cfgDir = std::string(cfgDir.c_str());
    }

    return cfgDir + "/fuc/";
}

// Parse the given file as a unicode dictionary, and overwrite the current unicode dictionary.
void parse(std::string fname) {
    status("Parsing...");

    std::string cfgDir = getCfgDir();
    std::stringstream message;
    message << "The cfgDir is: " << cfgDir;
    status(message.str());

    parse(fname, cfgDir);
}

// Parse the given file as a unicode dictionary, and overwrite the unicode dictionary inside cfgDir.
void parse(std::string fname, std::string cfgDir) {


    std::stringstream message;
    message << "Parsing " << fname << " and writing to " << cfgDir << " ...";
    status(message.str());

    if (!fs::exists(cfgDir)) {
        fs::create_directory(cfgDir);
        std::cout << cfgDir << " has been created." << std::endl;
    } else {
        std::cout << cfgDir << " appears to exist already. Overwriting symbols file." << std::endl;
    }

    std::ofstream symbolsFile;
    std::ifstream rawSymbols(fname);
    std::string buffer;
    std::vector<std::string> symbols;

    while (std::getline(rawSymbols, buffer)) {
        if (buffer[0] != '\t' && buffer[0] != '@' && buffer[0] != ';') {
            symbols.push_back(buffer);
        }
    }
    rawSymbols.close();


    symbolsFile.open(cfgDir + "symbols.txt");
    symbolsFile << "# Total number of symbols: " << symbols.size() << "\n";
        for (auto const &symbol : symbols) {
        symbolsFile << symbol << "\n";
    }
    symbolsFile.close();

    std::cout << "Done!" << std::endl;
    return;
}

void findBest(std::string pattern, int N) {
    std::vector<Result> best(N);
    std::vector<std::string> symbols = readSymbols();

    ResultSet::ResultSet results(N);

}

void rankAll(std::string a) {
    return;
}


/*
void findBest(std::string pattern, int N) {

    std::vector<float> bestScores(N);
    std::vector<std::string> bestSymbols(N);
    std::vector<std::string> symbols = readSymbols();

    float scoreBuffer;

    bestScores[0] = fzmatch_normalized(pattern, symbols[0]);
    bestSymbols[0] = symbols[0];

    for (auto symbol : symbols) {
        scoreBuffer = fzmatch_normalized(pattern, symbol);
        if (scoreBuffer > bestScores[0]) {
            bestScores.insert(bestScores.begin(), scoreBuffer);
            bestSymbols.insert(bestSymbols.begin(), symbol);
        }
    }

    for (int i=0; i<N; i++) std::cout << bestSymbols[i] << "\t" << bestScores[i] << std::endl;
    return;
}
*/


std::vector<std::string> readSymbols() {
    return readSymbols(getCfgDir() + "symbols.txt");
}

std::vector<std::string> readSymbols(std::string fname) {
    std::ifstream symbolsFile(getCfgDir() + "symbols.txt");
    std::string buffer;
    std::getline(symbolsFile, buffer);
    int nSymbols = std::stoi(buffer.substr(buffer.rfind(" "), std::string::npos));
    std::vector<std::string> symbols(nSymbols);
    while (std::getline(symbolsFile, buffer)) symbols.push_back(buffer);
    symbolsFile.close();
    return symbols;
}

/*
void rankAll(std::string pattern) {
    std::vector<std::string> symbols = readSymbols();
    for (int i=0; i<symbols.size(); i++) {
        std::cout << symbols[i] << "\t\t\t" << fzmatch_normalized(pattern, symbols[i]) << std::endl;
    }
    return;
}
*/

void vs(std::string pattern, std::string str, bool print_matrix) {
    std::cout << pattern << " : " << str << std::endl;
    // std::cout << "Score: " << fzmatch(pattern, str) << std::endl;
    std::cout << "Score:\n" << levenshtein(pattern, str, print_matrix) << std::endl;

    return;
}

void status(std::string message) {
    std::cout << message << "\r";
    return;
}
