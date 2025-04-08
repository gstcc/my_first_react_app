#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

vector<int> create_clause(string s) {
    vector<int> literals;
    istringstream iss(s);
    string tmp;
    while (iss >> tmp) {
        int var;
        if (tmp == "v") {
            continue;
        } else if (tmp.front() == '~') {
            var = stoi(tmp.substr(2)); 
            var = -var;
        } else {
            var = stoi(tmp.substr(1));
        }
        literals.push_back(var);
    }
    return literals;
}

bool satisfies(int val, vector<int>& clause) {
    for (int literal : clause) {
        int var = abs(literal);
        bool isTrue = (val & (1 << var)) != 0; 

        if (literal < 0) {
            isTrue = !isTrue;
        }

        if (isTrue) {
            return true;
        }
    }
    return false;
}

int main() {
    int T, n, m;
    string s;
    cin >> T;
    while (T--) {
        cin >> n >> m;
        cin.ignore();

        vector<vector<int>> clauses;
        for (int i = 0; i < m; i++) {
            getline(cin, s);
            clauses.push_back(create_clause(s));
        }

        bool found = false;
        int val = (1 << n+1) - 1; // 1 based index, so set the n+1 first bits, could be make it slower but easier

        while (val >= 0) {
            bool sat = true;
            for (auto& clause : clauses) {
                if (!satisfies(val, clause)) {
                    sat = false;
                    break; 
                }
            }
            if (sat) {
                found = true;
                break;
            }

            val--;
        }

        if (!found) {
            cout << "unsatisfiable" << endl;
        } else {
            cout << "satisfiable" << endl;
        }
    }
}
