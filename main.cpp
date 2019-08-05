// https://unicode.org/Public/UNIDATA/NamesList.txt

#include "main.h"

namespace fs = boost::filesystem;

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "Usage: fucn <pattern>" << std::endl;
        std::cout << "       fucn -parse <symbols file>" << std::endl;
    } else if (argc == 3 && std::strcmp(argv[1], "-parse") == 0) {
        parse(argv[2]);
    } else if (argc == 4 && std::strcmp(argv[1], "-vs") == 0) {
        vs(argv[3], argv[4]);
    } else if (argc == 3 && std::strcmp(argv[1], "-rankall") == 0) {
        rankAll(argv[2]);
    } else {
        std::string pattern = "";
        for (int i=1; i<argc; i++) pattern += argv[i];
        findBest(pattern, 10);
    }

    return 0;
}

std::string getCfgDir() {
    // $XDG_CONFIG_HOME  ~/.config

    std::string cfgDir;
    const char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");

    if (xdg_config_home == NULL) {
        std::cout << "XDG_CONFIG_HOME not set! Falling back to ~/.config" << std::endl;
        cfgDir = "/home/pdmurray/.config";
    } else {
        cfgDir = std::string(cfgDir.c_str());
    }

    return cfgDir + "/fucn/";
}

void parse(std::string fname) {
    std::string cfgDir = getCfgDir();
    std::cout << "The cfgDir is: " << cfgDir << std::endl;
    parse(fname, cfgDir);
}

void parse(std::string fname, std::string cfgDir) {

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
    
    std::vector<int> bestScores(N);
    std::vector<std::string> bestSymbols(N);
    std::vector<std::string> symbols = readSymbols();

    int scoreBuffer;

    bestScores[0] = fzmatch(pattern.c_str(), symbols[0].c_str());
    bestSymbols[0] = symbols[0];

    for (auto str : symbols) {
        scoreBuffer = fzmatch(pattern.c_str(), str.c_str());
        if (scoreBuffer > bestScores[0]) {
            bestScores.insert(bestScores.begin(), scoreBuffer);
            bestSymbols.insert(bestSymbols.begin(), str);
        }
    }

    for (int i=0; i<N; i++) std::cout << bestSymbols[i] << "\t" << bestScores[i] << std::endl;
    return;
}

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

void rankAll(std::string pattern) {
    std::vector<std::string> symbols = readSymbols();
    for (int i=0; i<symbols.size(); i++) {
        std::cout << symbols[i] << "\t\t\t" << fzmatch(pattern.c_str(), symbols[i].c_str()) << std::endl;
    }
    return;
}

void vs(std::string pattern, std::string str) {
    std::cout << fzmatch(pattern.c_str(), str.c_str());
    return;
}