#include <iostream>
#include <algorithm>
#include <fstream>
#include "team.hpp"

void writeTeamAssignments(const vector<vector<string>>& teams, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    file << "Group Number,Team Members" << endl;
    int group_number = 1;
    for (const auto& team : teams) {
        file << group_number++ << ",";
        for (size_t i = 0; i < team.size(); ++i) {
            file << team[i];
            if (i != team.size() - 1) file << ";";
        }
        file << endl;
    }

    file.close();
}

int calculateTeamScore(const vector<string>& team, const map<string, Student>& students) {
    int cplusplus_score = 0, gdb_score = 0, algorithms_score = 0;

    for (const string& username : team) {
        const Student& student = students.at(username);
        if (student.cplusplus_exp == "Beginner") cplusplus_score += 1;
        else if (student.cplusplus_exp == "Intermediate") cplusplus_score += 2;
        else if (student.cplusplus_exp == "Advanced") cplusplus_score += 3;

        if (student.gdb_exp == "Beginner") gdb_score += 1;
        else if (student.gdb_exp == "Intermediate") gdb_score += 2;
        else if (student.gdb_exp == "Advanced") gdb_score += 3;

        if (student.algorithms_exp == "Beginner") algorithms_score += 1;
        else if (student.algorithms_exp == "Intermediate") algorithms_score += 2;
        else if (student.algorithms_exp == "Advanced") algorithms_score += 3;
    }

    return cplusplus_score * 100 + gdb_score * 10 + algorithms_score;
}

