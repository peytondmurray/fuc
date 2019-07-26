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
#include "json.hpp"

void updateSymbols();
void updateURL(std::string);

#endif