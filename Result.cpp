#include "Result.h"


// Result
Result::Result(std::string string, int value) : string(string), value(value) {
    if (value < 0) {
        std::stringstream errmsg;
        errmsg << "Result cannot have value < 0; result = " << value;
        throw std::invalid_argument(errmsg.str());
    }
    return;
}

std::string Result::str() {
    return this->string;
}

int Result::val() {
    return this->value;
}

Result::~Result() {
    return;
}


bool operator==(Result &a, Result &b) {
    return std::strcmp(a.str().c_str(), b.str().c_str()) == 0;
}

bool operator<(Result &a, Result &b) {
    return (a.val() < b.val());
}

bool operator<=(Result &a, Result &b) {
    return (a.val() <= b.val());
}

bool operator>(Result &a, Result &b) {
    return (a.val() > b.val());
}

bool operator>=(Result &a, Result &b) {
    return (a.val() >= b.val());
}


// ResultSet
ResultSet::ResultSet(int N) {
    this->results = std::vector<Result>(N);
    this->maxSize = N;
    return;
}

ResultSet::ResultSet(std::vector<std::string> strings, std::vector<int> values) {

    if (strings.size() != values.size()) throw "Number of strings must equal number of values.";
    else {

        this->results.reserve(strings.size());
        for (int i=0; i<strings.size(); i++) this->results.push_back(Result(strings[i], values[i]));
    }
    return;
}

ResultSet::~ResultSet() {
    // this-results.clear();
    return;
}

void ResultSet::append_best(std::string string, int value) {


    if ((this->results[this->size()-1] < value) || (this->size() < this->maxSize)) {
    }

    return;

    int i = this->size()-1;
    while (this->results[i] < value) i--;
    if (i < this->size()) this->results.insert(this->results.begin()+i, Result(string, value));
    return;
}

void ResultSet::append_best(Result result) {
    int i = 0;
    while (this->results[i] > result) i++;
    if (i < this->size()) this->results.insert(this->results.begin()+i, result);
    return;
}

std::vector<std::string> ResultSet::strs() {
    std::vector<std::string> strings(this->size());
    for (int i=0; i<this->size(); i++) strings.push_back(this->results[i].str());
    return strings;
}

std::vector<int> ResultSet::vals() {
    std::vector<int> values(this->size());
    for (int i=0; i<this->size(); i++) values.push_back(this->results[i].val());
    return values;
}

int ResultSet::size() {
    return results.size();
}

void ResultSet::sort() {
    std::sort(this->results.begin(), this->results.end());
    return;
}