#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void analyzeComplexity(const vector<string>& code) {
    int c_loop = 0;
    int m_loop = 0;
    int t_loops = 0;

    for (const string& line : code) {
        string lower = line;
        transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
        lower.erase(remove(lower.begin(), lower.end(), ' '), lower.end());

        if (lower.find("for(") != string::npos || lower.find("while(") != string::npos) {
            t_loops++;
            c_loop++;
            if (c_loop > m_loop)
                m_loop = c_loop;
        }

        if (lower.find("}") != string::npos) {
            c_loop--;
        }
    }

    int c = 0;
    string worst = "1";
    if (m_loop > 0) {
        worst = "n";
        c = 1;
        for (int i = 1; i < m_loop; i++) {
            worst += "*n";
            c++;
        }
        worst += "+" + to_string(c);
    }

    if (worst == "1") {
        cout << "Lower Bound \u03A9(g(n)) = \u03A9(1)\n";
        cout << "Upper Bound O(g(n)) = O(1)\n";
        cout << "Average Bound \u0398(g(n)) = \u0398(1)\n";
        return;
    }

    string core = worst.substr(0, worst.size() - 2); // remove +c

    cout << "\nOrder: " << worst << "\n\n";

    // Lower Bound
    cout << "For lower bound : f(x) ≥ C * g(n) where f(x) = " << worst << "\n";
    cout << "                 " << worst << " ≥ " << c + 1 << " * (" << core << ") or lower\n";
    cout << "                 Here, c = " << c + 1 << ", g(n) = " << core << "\n";
    cout << "Lower Bound \u03A9(g(n)) = \u03A9(" << core << ")\n\n";

    // Average Bound
    cout << "For average bound : C1 * g(n) ≤ f(x) ≤ C2 * g(n) where f(x) = " << worst << "\n";
    cout << "                    " << c << " * " << core << " ≤ " << worst << " ≤ " << c + 1 << " * " << core << "\n";
    cout << "                    Here, C1 = " << c << ", C2 = " << c + 1 << ", g(n) = " << core << "\n";
    cout << "Average Bound \u0398(g(n)) = \u0398(" << core << ")\n\n";

    // Upper Bound
    cout << "For upper bound : f(x) ≤ C * g(n) where f(x) = " << worst << "\n";
    cout << "                  " << worst << " ≤ " << c + 1 << " * (" << core << ") or greater\n";
    cout << "                  Here, c = " << c + 1 << ", g(n) = " << core << "\n";
    cout << "Upper Bound O(g(n)) = O(" << core << ")\n\n";
}

int main() {
    system("chcp 65001"); // Set console to UTF-8

    string line;
    vector<string> codeLines;

    cout << "Enter your code (type END to finish):\n";

    while (getline(cin, line)) {
        if (line == "END") break;
        codeLines.push_back(line);
    }

    analyzeComplexity(codeLines);

    return 0;
}
