#pragma once

#include "GrammarRule.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <algorithm>

class GrammarRule;

class GrammarState {
    public:
        GrammarState(std::string o_name, bool o_is_final);
        void addRule(GrammarRule rule);
        void expandRules(uint32_t size);
        std::vector<GrammarRule> get_expanded_rules();
        
        const std::string name;
        const bool is_final;
        std::vector<GrammarRule> rules;

        private:
        std::vector<GrammarRule> expanded_rules;
};