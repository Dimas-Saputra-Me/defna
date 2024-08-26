// cmake -S . -B build/ && cmake --build build/ && clear && ./build/defna test.dfn
// ./out
// echo $?

// NOTE 30:00

#include <iostream>
#include <fstream>
#include <sstream>

#include "./generation.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc!=2){
        cerr << "Incorrect Usage" << endl;
        cerr << "defna <input.dfn>" << endl;
        return EXIT_FAILURE;
    }

     std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(move(contents));
    vector<Token> tokens = tokenizer.tokenize();

    Parser parse(move(tokens));
    optional<NodeExit> tree = parse.parse();

    if(!tree.has_value()){
        cerr << "No exit statement found" << endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());
    {
        fstream file("./build/out.asm", ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 ./build/out.asm");
    system("ld -o out ./build/out.o");

    return EXIT_SUCCESS;
}