#include <iostream>
#include <fstream>
#include <string.h>
#include <regex>
#include <stdlib.h>
#define exit return 0
#define error_exit return 1
#define error(msg) std::cerr << msg << std::endl; \
                   error_exit;
using std::string;
using std::size_t;
using std::endl;
using std::cout;
using std::regex;
using std::regex_replace;

string readFile(const string &fileName);
string quoteString(string);
size_t countOccurances(string, string);
bool hasSuffix(string, string);
bool hasPrefix(string, string);

int main(int argc, char** argv){
    if(argc < 2){
        cout << "Compiles a jext program"
                  << endl << endl
                  << argv[0] << " [flags] filename [arguments]"
                  << endl << endl
                  << "  filename    the file to compile; must end in .jext"
                  << endl << endl
                  << "  -a           includes jext.ijs in the compiled source" << endl
                  << "  -c           removes compiled program after execution" << endl
                  << "  -cleanUp     same as -c"                               << endl
                  << "  -i           ignores extension type"                   << endl
                  << "  -ignoreExt   same as -i"                               << endl
                  << "  -inclExtern  same as -a"                               << endl
                  << "  -o           outputs compiled source but does not run" << endl
                  << "  -outSource   same as -o"                               << endl;
        error_exit;
    }
    // define options
    bool optionCleanUp    = false;
    bool optionIgnoreExt  = false;
    bool optionInclExtern = false;
    bool optionOutSource  = false;
    // process flags
    bool skip[argc] = { false };    // for compiling arguments
    for(int i = 1; i < argc; i++){
        string arg = "";
        char* str = argv[i];
        if(str[0] == '-' || str[0] == '/'){
            int len = strlen(str);
            if(len == 1){
                error("flag lengths must be more than 1");
            }
            for(int j = 1; j < len; j++){
                arg += str[j];
            }
        } else continue;
        if(arg == "ignoreExt" || arg == "i"){
            optionIgnoreExt = true;
            skip[i] = true;
        } else if(arg == "cleanUp" || arg == "c"){
            optionCleanUp = true;
            skip[i] = true;
        } else if(arg == "a" || arg == "inclExtern"){
            optionInclExtern = true;
            skip[i] = true;
        } else if(arg == "o" || arg == "outSource"){
            optionOutSource = true;
            skip[i] = true;
        } else {
            error("invalid flag `" << arg << "`");
        }
    }
    int fileLoc = 1;        // the location of the file to be read
    // find the first non-skipped argument, then set the file location to it
    for(int i = 1; i < argc; i++){
        if(skip[i]) continue;
        fileLoc = i;
        skip[i] = true;  // for future skipping
        break;
    }
    if(fileLoc >= argc){
        error("no file was passed");
    }
    char* fileName = argv[fileLoc];
    string destName = "";
    string fileExt = "";
    bool encounteredPeriod = false;
    for(int i = 0; i < strlen(fileName); i++){
        if(fileName[i] == '.') encounteredPeriod = true;
        if(!encounteredPeriod){
            destName += fileName[i];
        } else {
            fileExt += fileName[i];
        }
    }
    if(destName == "jext"){
        error("invalid name `" << destName << "`");
    } else if(fileExt == ".ijs" && !optionIgnoreExt){
        error("invalid file extension `" << fileExt << "`; "
                  << "use flag `-ignoreExt` to continue.");
    }
    destName += ".ijs";
    std::ofstream dest;
    const char *_destName = destName.c_str();
    dest.open(_destName);
    
    std::ifstream source;
    source.open(fileName);
    if(!source.is_open()){
        error("non-existant file '" << fileName << "'");
    }
    // now we can start doing actual compiling,
    // since this must be a valid-ish file
    
    // header
    if(optionInclExtern){
        dest << readFile("jext.ijs");
    } else {
        dest << "load 'jext.ijs'" << endl;
    }
    dest << readFile("header.ijs");
    dest << endl;
    
    // put source code into file
    string line;
    int lineNum = 0;
    while(getline(source, line)){
        lineNum++;
        // todo: ignore `monad.`s in strings; depth
        int monadCount = countOccurances(line, "monad.");
        if(monadCount == 0){
            continue;
        } else if(monadCount == 1){
            // read lines until stop.
            bool fileEmpty = false;
            string result = "";
            string add;
            while(true){
                fileEmpty = !getline(source, add);
                lineNum++;
                int stopCount = countOccurances(add, "stop.");
                if(stopCount == 1){
                    if(result.length() > 3)
                        result.erase(result.length() - 3);
                    else
                        result += "''";
                    result += ")" + regex_replace(add, (regex) "stop\\.", "\n");
                    break;
                } else if(stopCount > 1){
                    std::cerr << "compilte time error: too many `stop.`s on line " << lineNum << endl;
                } else {
                    result += quoteString(add) + " ; ";
                }
                if(fileEmpty){
                    std::cerr << "compile time error: EOF found, expected `stop.`.";
                    error_exit;
                }
            }
            dest << "  " << regex_replace(line, (regex)"monad\\.", "monad def (");
            dest << result << endl;
            continue;
        } else {
            std::cerr << "compilte time error: too many `monad.`s on line " << lineNum << endl;
            error_exit;
        }
        if(hasSuffix(line, "...")){
            int lastIndex = line.rfind("...");
            dest << line.substr(0, lastIndex);
        } else {
            dest << "  " << line << endl;
        }
    }
    source.close();
    
    // footer
    dest << ")"     << endl
         << "main ";
    // count number of non-skipped arguments
    int argsLeft = 0;
    for(int i = 1; i < argc; i++)
        if(!skip[i]) argsLeft++;
    // only one argument; box it to be sure
    if(argsLeft == 1){
       dest << "<"; 
    }
    // write the arguments for invoking main
    for(int i = 1; i < argc; i++){
        if(skip[i]) continue;
        string arg = argv[i];
        dest << quoteString(arg);
        // dest << "'";
        // // output chars one at a time
        // for(int j = 0; j < arg.length(); j++){
            // dest << arg[j];
            // if(arg[j] == '\'') dest << "'";
        // }
        // dest << "'";
        if(i < argc - 1){
            dest << " ; ";
        }
    }
    // no arguments passed to the function; provide empty arg set
    if(argsLeft == 0){
        dest << "''";
    }
    dest << endl;
    dest << "final ''" << endl;
    dest.close();
    if(optionOutSource){
        cout << readFile(_destName);
        exit;
    }
    // execute file; windows only
    system(_destName);
    if(optionCleanUp){
        std::remove(_destName);
    }
    return 0;
}

// modified from http://stackoverflow.com/a/524843/4119004
string readFile(const string &fileName){
    std::ifstream f(fileName.c_str());
    return string(std::istreambuf_iterator<char>(f),
            std::istreambuf_iterator<char>());
}

string quoteString(string toquote){
    string result = "'";
    for(int i = 0; i < toquote.length(); i++){
        result += toquote[i];
        if(toquote[i] == '\''){
            result += "'";
        }
    }
    result += "'";
    return result;
}

size_t countOccurances(string main, string sub){
    int count = 0;
    size_t nPos = main.find(sub);
    while(nPos != string::npos){
        count++;
        nPos = main.find(sub, nPos + 1);
    }
    return count;
}

// todo: ignore stuff inside comments, maybe? probably not
bool hasSuffix(string main, string suffix){
    int mainLen = main.length();
    int suffLen = suffix.length();
    int j = 0;
    while(main[mainLen - j - 1] == ' ') j++;
    for(int i = 0; i < suffLen; i++, j++){
        if(suffix[suffLen - i - 1] != main[mainLen - j - 1])
            return false;
    }
    return true;
}

bool hasPrefix(string main, string prefix){
    int mainLen = main.length();
    int prefLen = prefix.length();
    for(int i = 0; i < prefLen; i++){
        if(prefix[i] != main[i])
            return false;
    }
    return true;
}