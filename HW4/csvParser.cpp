#include <fstream>
#include <sstream>
#include "csvParser.hpp"

map<string, Student> parseCSV(const string& filename) {
    ifstream file(filename);
    map<string, Student> students;

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    string line;
    getline(file, line); 

    while (getline(file, line)) {
        stringstream ss(line);
        string username, not_want_to_work_with, want_to_work_with, cplusplus_exp, gdb_exp, algorithms_exp;
        getline(ss, username, ',');
        getline(ss, cplusplus_exp, ',');
        getline(ss, gdb_exp, ',');
        getline(ss, algorithms_exp, ',');
        getline(ss, not_want_to_work_with, ',');
        getline(ss, want_to_work_with, ',');

        Student student = { username, not_want_to_work_with, want_to_work_with, cplusplus_exp, gdb_exp, algorithms_exp };
        students[username] = student;
    }

    file.close();
    return students;
}

