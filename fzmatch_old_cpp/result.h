#ifndef RESULT_H
#define RESULT_H

class Result {
    public:
        int start;
        int end;
        int score;
        bool valid;

        // By default, initialize the class as invalid.
        Result() {
            valid = false;
        };

        Result(int _start, int _end, int _score) {
            start = _start;
            end = _end;
            score = _score;
            valid = true;
        };
};

#endif
