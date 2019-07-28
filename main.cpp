// https://unicode.org/Public/UNIDATA/NamesList.txt

#include "main.h"

namespace po = boost::program_options;
namespace fs = boost::filesystem;

int main(int argc, char** argv) {


    if (argc > 1) {
        parse(argv[1]);
    } else std::cout << "Invalid arguments" << std::endl;


    // vm.count doesn't seem to work at all, not even in the boost examples
    // std::cout << argv[1];

    // po::options_description desc("Options");
    // desc.add_options()
    //     ("help", "Print help message")
    //     ("parse", po::value<std::string>(), "Parse the unicode symbol list from unicode.org");

    // po::variables_map vm;
    // po::store(po::parse_command_line(argc, argv, desc), vm);
    // po::notify(vm);

    // if (vm.count("help")) {
    //     std::cout << "HELP!" << "\n";
    //     std::cout << desc << "\n";
    //     return 0;
    // }

    // if (vm.count("parse")) {
    //     parse(vm["parse"].as<std::string>());
    //     return 0;
    // }

    return 0;
}

void parse(std::string fname) {
    // $XDG_CONFIG_HOME  ~/.config

    char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_home == NULL) {
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
