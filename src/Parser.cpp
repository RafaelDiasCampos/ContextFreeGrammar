#include "Parser.h"

using json = nlohmann::json;

int main(int argc, const char** argv) {
    FILE* json_file = fopen("../examples/sameQuantity.json", "r");

    json grammar = json::parse(json_file);

    std::cout << grammar.dump();

    return 0;
}