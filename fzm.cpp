#include "fzmatch.h"
#include <iostream>


int main(int argc, char *argv[]) {

    int score = 0;

    if (argc == 3) fzmatch(argv[1], argv[2], score);
    // fzmatch("hey", "hey", score);

    // fzmatch("a", "taft", score);

    // for (int i=0; i<argc; i++) {
    //     std::cout << argv[i] << ",";
    // }
    // std::cout << std::endl;

    std::cout << score << std::endl;
    return 0;

}