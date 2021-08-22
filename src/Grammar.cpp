#include "Grammar.h"
#include <memory>

using json = nlohmann::json;

Grammar::Grammar(std::ifstream file) {
    json parsed_json = json::parse(file);

    // Data extracted from json
    std::vector<std::string> json_states = parsed_json["glc"][0];
    std::vector<std::string> json_vocabulary = parsed_json["glc"][1];
    std::vector<std::vector<std::string>> json_rules = parsed_json["glc"][2];
    std::string json_initial_state = parsed_json["glc"][3];

    // Create states
    for (auto state_name: json_states) {
        auto state = std::make_unique<GrammarState>(state_name);
        states.push_back(std::move(state));
        if (state_name == json_initial_state) {
            initial_state = states.back().get();
        }
    }

    // Create vocabulary
    for (auto literal: json_vocabulary) {
        auto literalObject = std::make_unique<LiteralObject>(literal);
        vocabulary.push_back(std::move(literalObject));
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

        // Don't insert # (empty rule)
        if (transition == "#") {
            continue;
        }

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
    initial_state->expandRules(size);
}


std::vector<GrammarRule> Grammar::get_derivation_tree() {
    std::vector<GrammarRule> derivation_tree = initial_state->get_expanded_rules();

    std::sort(derivation_tree.begin(), derivation_tree.end());
    derivation_tree.erase(std::unique(derivation_tree.begin(), derivation_tree.end()), derivation_tree.end());

    return derivation_tree;
}