#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define exit return 0
#define error_exit return 1
#define string std::string
#define error(msg) std::cerr << msg << std::endl;\
                   error_exit;

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "Compiles a jext program"
                  << std::endl << std::endl
                  << argv[0] << " [flags] filename [arguments]"
                  << std::endl << std::endl
                  << "  filename    the file to compile; must end in .jext"
                  << std::endl << std::endl
                  << "  -a           includes jext.ijs in the compiled source" << std::endl
                  << "  -c           removes compiled program after execution" << std::endl
                  << "  -cleanUp     same as -c"                               << std::endl
                  << "  -i           ignores extension type"                   << std::endl
                  << "  -ignoreExt   same as -i"                               << std::endl
                  << "  -inclExtern  same as -a"                               << std::endl;
        error_exit;
    }
    // define options
    bool optionCleanUp    = false;
    bool optionIgnoreExt  = false;
    bool optionInclExtern = false;
    // process flags
    bool skip[argc] = { false };    // for compiling arguments
    int fileLoc = 1;                // the location of the file to be read
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
        } else {
            error("invalid flag `" << arg << "`");
        }
        fileLoc = i + 1;
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
        std::ifstream jext;
        jext.open("jext.ijs");
        string line;
        while(getline(jext, line)){
            dest << line << std::endl;
        }
    } else {
        dest << "load 'jext.ijs'" << std::endl;
    }
    dest << "final =: monad def 'exit 0'"          << std::endl
         << "main =: monad define"                 << std::endl
         << "  argv =: y"                          << std::endl
         << "  try. arge =: >@(\".&.>) argv"       << std::endl
         << "  catch. arge =: i.0 0"               << std::endl
         << "  end."                               << std::endl
         << "  open_arg =: \".@>"                  << std::endl
         << "  arg =: monad def 'open_arg y { argv'" << std::endl;
    // put source code into file
    string line;
    while(getline(source, line)){
        dest << "  " << line << std::endl;
    }
    source.close();
    // footer
    dest << ")"     << std::endl
         << "main ";
    
    if(argc < 4){
       dest << "<"; 
    }
    // write the arguments for invoking main
    for(int i = 2; i < argc; i++){
        if(skip[i]) continue;
        string arg = argv[i];
        dest << "'";
        // output chars one at a time
        for(int j = 0; j < arg.length(); j++){
            dest << arg[j];
            if(arg[j] == '\'') dest << "'";
        }
        dest << "'";
        if(i < argc - 1){
            dest << " ; ";
        }
    }
    // no arguments passed to the function; provide empty arg set
    if(argc < 3){
        dest << "''";
    }
    dest << std::endl;
    dest << "final ''" << std::endl;
    dest.close();
    // execute file; windows only
    system(_destName);
    if(optionCleanUp){
        std::remove(_destName);
    }
    return 0;
}