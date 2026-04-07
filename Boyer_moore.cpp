#include <iostream>
#include <cstring>
using namespace std;

#define MAX_CHAR 256

// Function to build the bad character heuristic table
void badCharHeuristic(string pattern, int size, int badChar[MAX_CHAR]) {
    // Initialize all occurrences as -1
    for (int i = 0; i < MAX_CHAR; i++)
        badChar[i] = -1;

    // Fill the actual value of last occurrence
    for (int i = 0; i < size; i++)
        badChar[(int)pattern[i]] = i;
}

// Boyer-Moore search function
void boyerMooreSearch(string text, string pattern) {
    int m = pattern.size();
    int n = text.size();

    int badChar[MAX_CHAR];

    // Preprocessing
    badCharHeuristic(pattern, m, badChar);

    int shift = 0; // shift of the pattern

    while (shift <= (n - m)) {
        int j = m - 1;

        // Keep reducing index j while characters match
        while (j >= 0 && pattern[j] == text[shift + j])
            j--;

        // If pattern is found
        if (j < 0) {
            cout << "Pattern found at index: " << shift << endl;

            shift += (shift + m < n) ? m - badChar[text[shift + m]] : 1;
        }
        else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }
}

// Driver code
int main() {
    string text = "ABAAABCD";
    string pattern = "ABC";

    boyerMooreSearch(text, pattern);

    return 0;
}
