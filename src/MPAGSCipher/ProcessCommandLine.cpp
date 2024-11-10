#include "ProcessCommandLine.hpp"
#include <iostream>
using namespace std;

bool processCommandLine(const vector<string>& args,
    bool& helpRequested, bool& versionRequested,
    string& inputFileName, string& outputFileName,
    bool& encrypt, string& key){
    
     // Status flag to indicate whether or not the parsing was successful
    bool processStatus{true};

    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    size_t nargs=args.size();
    for (size_t i{1}; i < nargs; ++i) {
        if (args[i] == "-h" || args[i] == "--help") {
            helpRequested = true;
        } else if (args[i] == "-v" || args[i] == "--version") {
            versionRequested = true;
        } else if (args[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nargs - 1) {
                cerr << "[error] -i requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                processStatus=false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = args[i + 1];
                ++i;
            }
        } else if (args[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nargs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                processStatus=false;
                break;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = args[i + 1];
                ++i;
            }
        }
        else if(args[i] == "-k"){
            if (i == nargs - 1){
                std::cerr << "[error] -k requires an unsigned integer as the cipher key argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                processStatus=false;
                break;
            }
            else {
                key=args[i+1];
                ++i;
            }
        }
        else if(args[i] == "--encrypt"){
                encrypt=true;
        }
        else if (args[i]=="--decrypt"){
                encrypt=false;
        }
        else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << args[i]
                      << "'\n";
            processStatus=false;
            break;
        }
    }
    return processStatus;
}
//===end of cmd line parsing function===