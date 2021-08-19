#include "LiteralObject.h"

LiteralObject::LiteralObject(std::string o_literal) : GrammarObject(GrammarObject::ObjectType::Literal) {
    literal = o_literal;
}

LiteralObject::operator std::string() const {
    return literal;
}