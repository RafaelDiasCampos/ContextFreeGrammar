#include "StateObject.h"

StateObject::StateObject(GrammarState* o_state) : GrammarObject(GrammarObject::ObjectType::Rule) {
    state = o_state;
}

StateObject::operator std::string() const {
    return state->name;
}