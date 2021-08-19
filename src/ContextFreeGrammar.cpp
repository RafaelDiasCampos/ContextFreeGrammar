#include <iostream>
#include <fstream>
#include "Grammar.h"

int main(int argc, const char** argv) {
    try {

        if (argc != 3) {
            std::cout << "Usage: " << argv[0] << " grammar_file max_size" << std::endl;
            exit(1);
        }

        std::ifstream grammar_file;
        grammar_file.open(argv[1]);

        if (!grammar_file.is_open()) {
            throw "Error while opening file" + std::string(argv[1]);
        }

        uint32_t max_size = atoi(argv[2]);

        Grammar grammar = Grammar(std::move(grammar_file));
        grammar.create_derivation_tree(max_size);

        std::vector<std::string> derivation_tree = grammar.get_derivation_tree();
        for (auto el : derivation_tree) {
            std::cout << std::string(el) << std::endl;
        }
    }
    catch (std::string e) {
        std::cout << "Exception: " << e << std::endl;
    }
    

    return 0;
}