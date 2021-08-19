#include "GrammarState.h"

GrammarState::GrammarState(std::string o_name, bool o_is_final) : name(o_name), is_final(o_is_final){

}

void GrammarState::addRule(GrammarRule rule) {
    rules.push_back(rule);
}

void GrammarState::expandRules(uint32_t size) {
    expanded_rules.clear();

    for (auto rule : rules) {
        expanded_rules.push_back(rule);
    }

    for (size_t expanded_rules_pos = 0; expanded_rules_pos < expanded_rules.size(); expanded_rules_pos++) {
        std::vector<GrammarRule> new_rules = expanded_rules[expanded_rules_pos].expand_rule(size);

        for (auto new_rule : new_rules) {
            if (std::count(expanded_rules.begin(), expanded_rules.end(), new_rule) == 0) {
                expanded_rules.push_back(new_rule);
            }            
        }        
    }
}

std::vector<GrammarRule> GrammarState::get_expanded_rules() {
    std::vector<GrammarRule> literal_rules;

    for (auto rule : expanded_rules) {
        if (rule.is_literal()) {
            literal_rules.push_back(rule);
        }
    }

    return literal_rules;
}