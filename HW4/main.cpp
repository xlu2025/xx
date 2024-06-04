#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "student.hpp"
#include "csvParser.hpp"
#include "team.hpp"

int main() {
	string filename = "students.csv";
	map<string, Student> students = parseCSV(filename);
	// Prompt user for team size
	int team_size;
	while (1) {
		cout << "Enter team size (3 or 4): ";
		cin >> team_size;
		if (team_size == 3 || team_size == 4)break;
		cout << "Input does not meet the requirements, please re-enter" << endl;
	}
	// Assume number of students in the file are divisible by team size
	int num_students = students.size();
	int num_teams = num_students / team_size;

	vector<vector<string>> teams(num_teams);
	// Assign students to teams
	vector<string> student_names;
	for (const auto& pair : students) {
		student_names.push_back(pair.first);
	}
	// Sort the students based on their experience levels
	sort(student_names.begin(), student_names.end(), [&](const string& a, const string& b) {
			const Student& sa = students.at(a);
			const Student& sb = students.at(b);
			int sa_score = sa.cplusplus_exp == "Advanced" ? 3 : (sa.cplusplus_exp == "Intermediate" ? 2 : 1);
			sa_score += sa.gdb_exp == "Advanced" ? 3 : (sa.gdb_exp == "Intermediate" ? 2 : 1);
			sa_score += sa.algorithms_exp == "Advanced" ? 3 : (sa.algorithms_exp == "Intermediate" ? 2 : 1);
			int sb_score = sb.cplusplus_exp == "Advanced" ? 3 : (sb.cplusplus_exp == "Intermediate" ? 2 : 1);
			sb_score += sb.gdb_exp == "Advanced" ? 3 : (sb.gdb_exp == "Intermediate" ? 2 : 1);
			sb_score += sb.algorithms_exp == "Advanced" ? 3 : (sb.algorithms_exp == "Intermediate" ? 2 : 1);
			return sa_score > sb_score;
			});
	// Ask user for priority: 1 for "want to work with" and "do not want to work with", 2 for skill balance
	int priority;
	while(1){
		cout << "Enter priority (1 for 'want to work with'/'do not want to work with', 2 for skill balance): ";
		cin >> priority;
		if(priority==1||priority==2)break;
		else cout << "Input does not meet the requirements, please re-enter" << endl;
	}	
	if (priority == 1) {
		// Assign students to teams, honoring "do not want to work with" and "want to work with"
		for (int i = 0; i < num_teams; ++i) {
			for (int j = 0; j < team_size; ++j) {
				string username = student_names[i * team_size + j];
				bool can_add = true;
				for (const auto& team_member : teams[i]) {
					if (students.at(team_member).not_want_to_work_with.find(username) != string::npos) {
						can_add = false;
						break;
					}
				}
				if (can_add) {
					teams[i].push_back(username);
					for (const auto& teammate : teams[i]) {
						if (students.at(username).want_to_work_with.find(teammate) != string::npos) {
							break;
						}
					}
				}
				else {
					j--;
				}
			}
		}
	}
	else {
		// Assign students to teams, prioritizing skill balance
		vector<vector<int>> team_scores(num_teams, vector<int>(3, 0));
		for (int i = 0; i < num_students; ++i) {
			string username = student_names[i];
			int min_score =1000;  // Use a large initial value for min_score
			int min_team = -1;

			for (int j = 0; j < num_teams; ++j) {
				if (teams[j].size() < team_size) {  // Ensure team can accommodate more students
					bool can_add = true;
					for (const auto& team_member : teams[j]) {
						if (students.at(team_member).not_want_to_work_with.find(username) != string::npos) {
							can_add = false;
							break;
						}
					}
					if (can_add) {
						int team_score = team_scores[j][0] + team_scores[j][1] + team_scores[j][2];
						if (team_score < min_score) {
							min_score = team_score;
							min_team = j;
						}
					}
				}
			}
			if (min_team != -1) {
				teams[min_team].push_back(username);
				const Student& student = students.at(username);
				if (student.cplusplus_exp == "Beginner") team_scores[min_team][0] += 1;
				else if (student.cplusplus_exp == "Intermediate") team_scores[min_team][0] += 2;
				else if (student.cplusplus_exp == "Advanced") team_scores[min_team][0] += 3;

				if (student.gdb_exp == "Beginner") team_scores[min_team][1] += 1;
				else if (student.gdb_exp == "Intermediate") team_scores[min_team][1] += 2;
				else if (student.gdb_exp == "Advanced") team_scores[min_team][1] += 3;

				if (student.algorithms_exp == "Beginner") team_scores[min_team][2] += 1;
				else if (student.algorithms_exp == "Intermediate") team_scores[min_team][2] += 2;
				else if (student.algorithms_exp == "Advanced") team_scores[min_team][2] += 3;
			}
			else {
				// Handle the case where no valid team is found
				cout << "Error: No valid team found for student " << username << endl;
				return 1;  // Exit with an error code
			}
		}
	}
	// Write team assignments to CSV file
	string output_filename = "team_assignments.csv";
	writeTeamAssignments(teams, output_filename);
	// Print team scores
	for (int i = 0; i < num_teams; ++i) {
		int team_score = calculateTeamScore(teams[i], students);
		cout << "Team " << i + 1 << " Score: " << team_score << endl;
	}

	return 0;
}

