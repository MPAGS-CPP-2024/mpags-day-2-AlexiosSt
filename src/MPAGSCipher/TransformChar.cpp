#include "TransformChar.hpp"
#include <cctype>

std::string transformChar(const char in_char){
    std::string out_char{""};

    if (std::isalpha(in_char)) {
        out_char = std::toupper(in_char);
    }
    else{
        switch (in_char) {
            case '0': out_char= "ZERO"; break;
            case '1': out_char= "ONE";  break;
            case '2': out_char= "TWO";  break;
            case '3': out_char= "THREE";break;
            case '4': out_char= "FOUR"; break;
            case '5': out_char= "FIVE"; break;
            case '6': out_char= "SIX";  break;
            case '7': out_char= "SEVEN";break;
            case '8': out_char= "EIGHT";break;
            case '9': out_char= "NINE"; break;
            default: break;
        }
    }
    return out_char;
 }
//===end of transliteration function===