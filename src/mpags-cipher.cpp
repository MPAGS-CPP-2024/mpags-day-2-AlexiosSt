#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFileName{""};
    std::string outputFileName{""};
    bool status{false};

    status=processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFileName, outputFileName);
    if (status){
        cout<<"Parsing of command line arguments was completed!!\n";
    }
    else return 1;

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  -v|--version     Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n";
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "2.0.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFileName.empty()) {
        std::cout << "Input from file ('" << inputFileName
                  << "') started!\n";
        ifstream inFile{inputFileName};
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
    
    // NOW: Print out the transliterated text

    // Warn that output file option not yet implemented
    if (!outputFileName.empty()) {
        std::cout << "Writing output to file ('" << outputFileName
                  << "') started!\n";
        ofstream outFile{outputFileName};
        outFile<<inputText;
    }
    else{cout<<"OK, you entered sth like:\n";
        std::cout << inputText << std::endl;
    }
    
    cout<<"====DONE!====\n";

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}