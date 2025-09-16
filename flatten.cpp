//this file just flattens some shit so i dont have to flatten the text in the program

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main() {
    string line, out;

    while (getline(cin, line)) {
        if (!out.empty()) out.push_back(' ');  //space between lines
        for (unsigned char ch : line) {
            if (isalpha(ch)) {
                out.push_back(toupper(ch));  //keep letters only
            }
            // digits, punctuation, brackets, etc. are skipped
        }
    }

    cout << out << "\n";
    return 0;
}
