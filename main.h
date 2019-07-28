#ifndef MAIN_H
#define MAIN_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
// #include "json.hpp"
#include "fzmatch.h"

void parse(std::string fname);
void parse(std::string fname, std::string cfgDir);

#endif