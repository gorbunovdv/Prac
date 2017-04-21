#ifndef TYPES
#define TYPES

#include <string>

#define len(a) ((int) (a).size())
#define all(a) (a).begin(), (a).end()

namespace {
std::string invtext(std::string text) {
    for (char& c : text) {
        if (c == ' ') {
            c = '_';
        }
    }
    return text;
}

std::string text(std::string txt) {
    for (char &c : txt) {
        if (c == '_') {
            c = ' ';
        }
    }
    return txt;
}
}

#endif // TYPES

