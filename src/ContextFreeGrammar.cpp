#include <cstdint>
#include <climits>
#include <iostream>
#include <fstream>
#include <memory>
#include "Grammar.h"

void parse_cmd_args(int argc, const char** argv, std::ifstream &grammar_file, uint32_t &max_size) {

    // If number of arguments is wrong, print usage
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " grammar_file max_size" << std::endl;
        exit(1);
    }

    // Try to open grammar file and check if it was successful
    grammar_file.open(argv[1]);

    if (!grammar_file.is_open()) {
        std::cout << "Error while opening file '" + std::string(argv[1]) + "'." << std::endl;
        exit(1);
    }

    // Parse max_size argument
    long int converted_max_size = std::strtol(argv[2], nullptr, 10);
    if (converted_max_size == 0L || converted_max_size == LONG_MAX || converted_max_size == LONG_MIN) {
        std::cout << "Error while parsing max_size parameter." << std::endl;
        exit(1);
    }
    if (converted_max_size <= 0) {
        std::cout << "Parameter max_size has to be greater than 0." << std::endl;
        exit(1);
    }

    max_size = converted_max_size;
}

int main(int argc, const char** argv) {
    std::ifstream grammar_file;
    uint32_t max_size;

    parse_cmd_args(argc, argv, grammar_file, max_size);

    std::unique_ptr<Grammar> grammar;

    try {
        grammar = std::make_unique<Grammar>(Grammar(std::move(grammar_file)));
    }
    catch (std::string e) {
        std::cout << "Exception while creating grammar: " << e << std::endl;
        exit(1);
    }
    catch (nlohmann::detail::parse_error &e) {
        std::cout << "An error occurred when parsing the grammar file." << std::endl;
        exit(1);
    }
    catch (...) {
        std::cout << "An unexpected error occurred while creating grammar." << std::endl;
        exit(1);
    }

    grammar->create_derivation_tree(max_size);

    std::vector<GrammarRule> derivation_tree = grammar->get_derivation_tree();
    for (auto el : derivation_tree) {
        std::cout << std::string(el) << std::endl;
    }   

    return 0;
}