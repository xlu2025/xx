#pragma once
#include <vector>
#include <string>
#include <map>
#include "student.hpp"

void writeTeamAssignments(const vector<vector<string>>& teams, const string& filename);
int calculateTeamScore(const vector<string>& team, const map<string, Student>& students);
