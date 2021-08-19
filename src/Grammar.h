#pragma once

#include "GrammarState.h"
#include "GrammarObject/LiteralObject.h"
#include "GrammarObject/StateObject.h"
#include <cstdint>
#include <vector>
#include <fstream>
#include <exception>
#include <memory>
#include <string>
#include <algorithm>
#include "../deps/nlohmann/json/single_include/nlohmann/json.hpp"

class Grammar {
    public:
        Grammar(std::ifstream file);
        void create_derivation_tree(uint32_t size);
        std::vector<std::string> get_derivation_tree();

    private:
        std::vector<std::unique_ptr<LiteralObject>> vocabulary;
        std::vector<std::unique_ptr<StateObject>> stateObjects;
        std::vector<std::unique_ptr<GrammarState>> states;

        StateObject* get_create_state_object(std::string character);
        LiteralObject* get_literal(std::string character);
        GrammarState* get_state(std::string character);
        GrammarRule create_rule(std::string str_rule);
};