#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include "Result.h"
#include "levmatch.h"

void parse(std::string fname);
void parse(std::string fname, std::string cfgDir);
std::string getCfgDir();
void findBest(std::string pattern, int N);
std::vector<std::string> readSymbols();
std::vector<std::string> readSymbols(std::string fname);
void rankAll(std::string pattern);
void vs(std::string pattern, std::string str, bool print_matrix);
void usage();
void status(std::string message);


#endif //MAIN_H
