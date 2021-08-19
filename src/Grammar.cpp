#include "Grammar.h"
#include <iostream>

using json = nlohmann::json;

Grammar::Grammar(std::ifstream file) {
    json parsed_json = json::parse(file);

    // Data extracted from json
    std::vector<std::string> json_final_states = parsed_json["glc"][0];
    std::vector<std::string> json_vocabulary = parsed_json["glc"][1];
    std::vector<std::vector<std::string>> json_rules = parsed_json["glc"][2];
    std::string json_initial_state = parsed_json["glc"][3];

    // Create vocabulary
    for (auto literal: json_vocabulary) {
        auto literalObject = std::make_unique<LiteralObject>(literal);
        vocabulary.push_back(std::move(literalObject));
    }
    auto literalObject = std::make_unique<LiteralObject>("#");
    vocabulary.push_back(std::move(literalObject));

    // Create states
    for (auto json_rule: json_rules) {
        std::string str_state = json_rule[0];

        if (!get_state(str_state)) {
            bool is_final = false;
            if (std::count(json_final_states.begin(), json_final_states.end(), str_state)) {
                is_final = true;
            }
            auto state = std::make_unique<GrammarState>(str_state, is_final);
            states.push_back(std::move(state));         
        }
    }

    // Create rules and add them to the states
    for (auto json_rule: json_rules) {
        std::string str_state = json_rule[0];
        std::string str_rule = json_rule[1];

        auto state = get_state(str_state);
        auto rule = create_rule(str_rule);

        state->addRule(rule);
    }
    
}

LiteralObject* Grammar::get_literal(std::string character) {
    for (size_t i = 0; i < vocabulary.size(); i++) {
        if (vocabulary[i].get()->literal == character) {
            return vocabulary[i].get();
        }
    }
    return nullptr;
}

GrammarState* Grammar::get_state(std::string character) {
    for (size_t i = 0; i < states.size(); i++) {
        if (states[i].get()->name == character) {
            return states[i].get();
        }
    }
    return nullptr;
}

StateObject* Grammar::get_create_state_object(std::string character) {
    auto state = get_state(character);

    if (!state) {
        throw "Invalid state transition. State " + character + " doesn't exist.";
    }

    for (size_t i = 0; i < stateObjects.size(); i++) {
        if (stateObjects[i].get()->state == state) {
            return stateObjects[i].get();
        }
    }

    auto stateObject = std::make_unique<StateObject>(state);
    stateObjects.push_back(std::move(stateObject));

    return stateObjects.back().get();
}

GrammarRule Grammar::create_rule(std::string str_rule) {
    std::vector<GrammarObject*> rule;

    for (auto c_transition : str_rule) {
        std::string transition = std::string(1, c_transition); 
        auto literal = get_literal(transition);
        if (literal) {
            rule.push_back(literal);
            continue;
        }

        auto stateObject = get_create_state_object(transition);
        rule.push_back(stateObject);
    }

    return GrammarRule(rule);
}

void Grammar::create_derivation_tree(uint32_t size) {
    for (size_t i = 0; i < states.size(); i++) {
        if (states[i].get()->is_final) {
            states[i].get()->expandRules(size);
        }
    }
}


std::vector<std::string> Grammar::get_derivation_tree() {
    std::vector<std::string> derivation_tree;

    for (size_t i = 0; i < states.size(); i++) {
        std::vector<GrammarRule> expanded_rules = states[i]->get_expanded_rules();
        for (auto rule : expanded_rules) {
            derivation_tree.push_back(rule);
        }
    }

    std::sort(derivation_tree.begin(), derivation_tree.end());
    derivation_tree.erase(std::unique(derivation_tree.begin(), derivation_tree.end()), derivation_tree.end());

    return derivation_tree;
}