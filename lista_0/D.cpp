#include <bits/stdc++.h>
using namespace std;

int main() {
    char letter, middleLetter = NULL;
    string input, prefix, suffix, result;
    unordered_map<char, int> dictionary;

    cin >> input;
    for (int i = 0; i < input.length(); i++) {
        letter = input[i];
        if (dictionary.count(letter) > 0) {
            dictionary[letter]++;
        } else {
            dictionary[letter] = 1;
        }
    }

    for (auto it = dictionary.begin(); it != dictionary.end(); ++it) {
        if (it->second % 2 != 0) {
            if (middleLetter != NULL) {
                cout << "NO SOLUTION" << endl;
                return 0;
            }
            middleLetter = it->first;
            it->second--;
        }

        prefix.append(string(it->second/2, it->first));
    }

    suffix = string(prefix);
    reverse(suffix.begin(), suffix.end());
    if (middleLetter != NULL) {
        result = prefix + middleLetter + suffix;
    } else {
        result = prefix + suffix;
    }

    cout << result << endl;
    
    return 0;
}