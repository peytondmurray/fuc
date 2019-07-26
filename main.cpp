// https://unicode.org/Public/UNIDATA/NamesList.txt

#include "main.h"

namespace json = nlohmann::json;
namespace po = boost::program_options;

int main(int argc, char** argv) {

    po::options_description desc("Options");
    desc.add_options()
        ("help", "Print help message")
        ("update", "Pull the latest list of unicode symbols from unicode.org")
        ("update-url", po::value<std::string>(), "Set the url to use when updating the symbol list");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }
    
    if (vm.count("update")) {
        updateSymbols();
    }

    if (vm.count("update-url")) {
        updateURL(vm["update-url"].as<std::string>());
    }

    return 0;
}

void updateSymbols() {
    return;
}

void updateURL(std::string url) {
    // $XDG_CONFIG_HOME  ~/.config

    char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    if (xdg_config_home != NULL) {
        std::sstream configPath;
        configPath << xdg_config_home << "/fucn/config.json";
        if (!boost::filesystem::exists(configPath)) {
            //make the path
        else {
            //path already exists
            std::ifstream configFile(configPath);
            json j;
            j << configFile; //Might be configFile >> j;
        }
        j["url"] = url;
    }

    return;
}
