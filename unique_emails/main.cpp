#include <iostream>
#include <string>

using namespace std;

void clean_email(string& email) {
    size_t j = 0;
    size_t i = 0;
    while (email[i] != '@' && email[i] != '+') {
        if (email[i] != '.') {
            email[j++] = email[i];
        }
        i++;
    }
    while (email[i] != '@') {
        i++;
    }
    while (i < email.size()) {
        email[j++] = email[i];
        i++;
    }
    email.resize(j);
}

int main() {
    string test = "testemail+david@lee.tcode.com";
    clean_email(test);
    cerr << test << endl;
}
