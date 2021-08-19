#pragma once

#include <string>

class GrammarObject {
    public: 
        enum ObjectType {Rule, Literal};
        GrammarObject(ObjectType _object_type) {object_type = _object_type;};
        virtual operator std::string() const = 0;

        ObjectType object_type;        
};