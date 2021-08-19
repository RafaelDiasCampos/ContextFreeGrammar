#pragma once

#include "GrammarObject.h"
#include <string>

class LiteralObject:public GrammarObject {
    public:
        LiteralObject(std::string o_literal);
        operator std::string() const;
        
        std::string literal;
};