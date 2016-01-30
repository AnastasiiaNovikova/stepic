#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main() {
    unordered_set<string> hash_map;
    char c;
    string s;
    while (cin >> c) {
        cin >> s;
        switch( c ) {
            case '+':
                if (hash_map.find(s) != hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                hash_map.insert(s);
                break;
            case '-':
                if (hash_map.find(s) == hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                hash_map.erase(s);
                break;
            case '?':
                if (hash_map.find(s) == hash_map.end()) {
                    cout << "FAIL\n";
                    continue;
                }
                break;
        }
        cout << "OK\n";
    }
    return 0;
}