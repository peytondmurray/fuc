#ifndef RESULT_H
#define RESULT_H
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

class Result {

    public:
        Result(std::string string, int value);
        ~Result();
        std::string str();
        int val();
    private:
        int value;
        std::string string;
};

bool operator>(Result &a, Result &b);
bool operator<(Result &a, Result &b);
bool operator==(Result &a, Result &b);
bool operator<=(Result &a, Result &b);
bool operator>=(Result &a, Result &b);


class ResultSet {

    public:
        ResultSet(int N);
        ResultSet(std::vector<std::string> strings, std::vector<int> values);
        ResultSet(std::vector<Result> results) : results(results) {};
        ~ResultSet();
        void append_best(std::string string, int value);
        void append_best(Result result);
        void sort();
        std::vector<std::string> strs();
        std::vector<int> vals();
        int size();
    private:
        std::vector<Result> results;
        int maxSize = -1;
};


#endif //RESULT_H
