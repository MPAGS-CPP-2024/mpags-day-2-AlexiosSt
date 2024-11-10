#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"
#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    bool encrypt{true};
    string cipherKey{""};
    std::string inputFileName{""};
    std::string outputFileName{""};

    bool status{false};
    status=processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName, encrypt, cipherKey);
    if (status){
        cout<<"Parsing of command line arguments was completed!!\n\n";
    }
    else return 1;

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>] [-k <key>] [--encrypt/--decrypt]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n"
            << "  -h|--help        Print this help message and exit\n"
            << "  -v|--version     Print version information\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n"
            << "  -k KEY           The Key (must be unsigned long integer!) to be used for en/decryption\n"
            << "                   Null key, i.e. no encryption, will be used if not supplied\n"
            << "  --encrypt        If we are encrypting the input text (default)\n"
            << "  --decrypt        If we are decrypting the input text\n\n";
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "2.3.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    if (!inputFileName.empty()) {
        std::cout << "Input from file ('" << inputFileName
                  << "') started!\n";
        ifstream inFile{inputFileName};
        if (!inFile.good()){
            cerr<<"[error] Could not open the input file '"<<inputFileName<<"' !!\n";
            return 1;
        }
        while (inFile>>inputChar){
            inputText+=transformChar(inputChar);
        }
        inFile.close();
    }
    else{   cout<<"HELLO... now give me some chars!\n";
        cout<<"[INFO] Press ENTER and then Ctrl+D to terminate your input!!"<<endl;
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText+=transformChar(inputChar);
        }
    }
    cout<<"==DONE with input transliteration!==\n";
    
    // NOW: we do the en/decryption on the transliterated text
    // First check the KEY!
    std::size_t caesarKey{0};
    if (!cipherKey.empty()) {
        for (const auto& elem : cipherKey) {
            if (!std::isdigit(elem)) {
                std::cerr
                    << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
                    << "        the supplied key (" << cipherKey
                    << ") could not be successfully converted" << std::endl;
                return 1;
            }
        }
        caesarKey = std::stoul(cipherKey);
        if (caesarKey>1000) {std::cerr<<"[error] Hey, relax... The key doesn't need to be higher than 1000!!\n";
            return 1;}
    }

    string outputText{""};
    outputText = runCaesarCipher(inputText, caesarKey, encrypt);

    // Use output file option if supplied
    if (!outputFileName.empty()) {
        std::cout << "Writing output to file ('" << outputFileName
                  << "') started!\n";
        ofstream outFile{outputFileName};
        if (!outFile.good()){
            cerr<<"[error] The output file '"<<outputFileName<<"' could not be opened!\n";
            return 1;
        }
        outFile<<outputText;
    }
    else{cout<<"OK, your text after the cipher has been run is sth like:\n";
        std::cout << outputText << std::endl;
    }
    
    cout<<"==DONE with the ";
    if (encrypt) cout<<"encryption ";
    else cout<<"decryption ";
    cout<<"of your input==\n";

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}