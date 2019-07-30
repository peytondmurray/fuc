// https://unicode.org/Public/UNIDATA/NamesList.txt

#include "main.h"

namespace fs = boost::filesystem;

int main(int argc, char** argv) {

    if (argc == 1) {
        std::cout << "Usage: fucn <pattern>" << std::endl;
        std::cout << "       fucn -parse <symbols file>" << std::endl;
        return 0;
    }

    for (int i=0; i<argc-1; i++) {
        if (std::strcmp(argv[i], "-parse") == 0) parse(argv[i+1]);
        return 0;
    }

    // return fzmatch()

    return 0;
}

void parse(std::string fname) {
    // $XDG_CONFIG_HOME  ~/.config

    std::string xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_home == "") {
        std::cout << "XDG_CONFIG_HOME not set! Falling back to ~/.config" << std::endl;
        xdg_config_home = std::string("/home/pdmurray/.config");
    }

    std::string cfgDir = std::string(xdg_config_home).append(std::string("/fucn/"));
    std::cout << "The cfgDir is: " << cfgDir << std::endl;

    parse(fname, std::string(xdg_config_home) + "/fucn/");

}

void parse(std::string fname, std::string cfgDir) {

    if (!fs::exists(cfgDir)) {
        fs::create_directory(cfgDir);
        std::cout << cfgDir << " has been created." << std::endl;
    } else {
        std::cout << cfgDir << " appears to exist already." << std::endl;
    }
    // try {
    // } catch (...) {
    //     std::cout << "Can't create directory.";
    // }

    std::ofstream symbolsFile(cfgDir + "symbols.txt");
    std::ifstream rawSymbols(fname);
    std::string buffer;
    while (std::getline(rawSymbols, buffer)) {
        if (buffer[0] != '\t' || buffer[0] != '@' || buffer[0] != ';') {
            symbolsFile << buffer;
        }
    }
    rawSymbols.close();
    symbolsFile.close();

    return;
}
