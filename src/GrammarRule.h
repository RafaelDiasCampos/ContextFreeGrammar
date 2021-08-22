#pragma once

#include "GrammarObject/GrammarObject.h"
#include "GrammarObject/StateObject.h"
#include <stdint.h>
#include <vector>
#include <string>
#include <stdint.h>

class GrammarRule {
    public:
        GrammarRule(std::vector<GrammarObject*> o_rule_objects);
        GrammarRule(const GrammarRule &other);
        std::vector<GrammarRule> expand_rule(uint32_t size);
        bool is_literal();
        uint32_t size();
        
        operator std::string() const;
        bool operator == (const GrammarRule &Ref);
        bool operator < (const GrammarRule&Ref) const;
        GrammarRule& operator = (const GrammarRule &other);
        
    private:        
        std::vector<GrammarObject*> rule_objects;
};