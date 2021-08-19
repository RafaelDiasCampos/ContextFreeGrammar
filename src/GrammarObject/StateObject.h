#pragma once

#include "GrammarObject.h"
#include "../GrammarState.h"

class GrammarState;

class StateObject:public GrammarObject {
    public:
        StateObject(GrammarState* o_state);
        operator std::string() const;
        
        GrammarState* state;
};