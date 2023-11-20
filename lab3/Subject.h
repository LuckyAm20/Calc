#pragma once
class Subject {
public:
    int f3(int arg1, int arg2) {
        return arg2 - arg1;
    }

    int f5(int arg1, int arg2, int arg3, int arg4) {
        return arg2 - arg1 + arg4 + 1000* arg3;
    }

    int f4(int arg1) {
        return arg1;
    }
};