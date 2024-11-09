#include "RunCaesarCipher.hpp"
#include <vector>
using namespace std;

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt){

    string abc{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    string outTxt{""};
    char newch{'x'};

    for (const auto& v : inputText){
        for (size_t i{0}; i<abc.size(); i++){
            if (v==abc[i]){
                if (encrypt){
                    newch=abc[(i+key)%26];}
                else {
                    newch=abc[(i-key+26)%26];}
                break;
            }
        }
        outTxt+=newch;
    }
    return outTxt;
}
