#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#define exit return 0

int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "usage: " << argv[0] << " <name> [<arguments>]" << std::endl;
        exit;
    }
    char* file_name = argv[1];
    std::string dest_name = "";
    for(int i = 0; i < strlen(file_name); i++){
        if(file_name[i] == '.') break;
        dest_name += file_name[i];
    }
    if(dest_name == "jext"){
        std::cout << "invalid name `" << dest_name << "`" << std::endl;
        exit;
    }
    dest_name += ".ijs";
    std::ofstream dest;
    const char *_dest_name = dest_name.c_str();
    dest.open(_dest_name);
    
    std::ifstream source;
    source.open(file_name);
    if(!source.is_open()){
        std::cout << "non-existant file '" << file_name << "'";
        exit;
    }
    // header
    dest << "load 'jext.ijs'"                      << std::endl
         << "final =: monad : 'exit 0'"            << std::endl
         << "main =: monad define"                 << std::endl
         << "  argv =: y"                          << std::endl
         << "  try. arge =: >@(\".&.>) argv"       << std::endl
         << "  catch. arge =: i.0 0"               << std::endl
         << "  end."                               << std::endl
         << "  open_arg =: \".@>"                  << std::endl
         << "  arg =: monad : 'open_arg y { argv'" << std::endl;
    // put source code into file
    std::string line;
    while(getline(source, line)){
        dest << "  " << line << std::endl;
    }
    source.close();
    // footer
    dest << ")"     << std::endl
         << "main ";
    // write the arguments for invoking main
    for(int i = 2; i < argc; i++){
        std::string arg = argv[i];
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
    dest << std::endl;
    dest << "final ''" << std::endl;
    dest.close();
    // execute file
    system(_dest_name);
    return 0;
}