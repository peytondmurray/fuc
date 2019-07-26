// https://unicode.org/Public/UNIDATA/NamesList.txt

#include "main.h"

namespace nlohmann = nlohmann;
namespace po = boost::program_options;
namespace fs = boost::filesystem;

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
        std::string configDir = std::string(xdg_config_home) + "/fucn/";

        if (fs::is_directory(configDir)) {
            if (fs::is_regular_file(configDir + "config.json")) {
                std::ifstream configFile(configDir + "config.json");
                nlohmann::json j;
                configFile >> j;
                configFile.close();
            } else {

            }

        } else {
            fs::create_directory(configDir);
            //make the path and the file
        }


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


void readConfig(std::string path) {
    if (fs::is_regular_file(path)) {

    }
}

void writeConfig(std::string path, nlohmann::json j) {
    return;
}

bool configExists() {
    char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    return (xdg_config_home != NULL && fs::exists(std::string(xdg_config_home) + "/fucn/config.json"));
}

void writeDefaultConfig() {
    char *xdg_config_home = std::getenv("XDG_CONFIG_HOME");
    std::string configDir = std::string(xdg_config_home) + "/fucn/";
    nlohmann::json j;

    j["url"] = "https://unicode.org/Public/UNIDATA/NamesList.txt";
    if (xdg_config_home == NULL) throw "Environment variable XDG_CONFIG_HOME not set.";
    else if (!fs::is_directory(configDir)) fs::create_directory(configDir);

    std::ofstream configFile(configDir + "config.json");
    configFile << std::setw(4) << j << std::endl;
    configFile.close();
    return;
}

