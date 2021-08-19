#include "GrammarRule.h"
#include <iostream>

GrammarRule::GrammarRule(std::vector<GrammarObject*> o_rule_objects) : rule_objects(o_rule_objects){

}

GrammarRule::GrammarRule(const GrammarRule &other) : rule_objects(other.rule_objects){

}

GrammarRule& GrammarRule::operator=(const GrammarRule &other) const {
    GrammarRule* obj = new GrammarRule(other);
    return *obj;
}

std::vector<GrammarRule> GrammarRule::expand_rule(uint32_t size) {
    std::vector<GrammarRule> rules;

    // Expand the rule in every GrammarObject
    for (size_t rule_objects_pos = 0; rule_objects_pos < rule_objects.size(); rule_objects_pos++) {

        // Ignore literals since they cannot be expanded
        if (rule_objects[rule_objects_pos]->object_type == GrammarObject::ObjectType::Literal) {
            continue;
        }

        // Cast GrammarObject to a StateObject
        StateObject* state_transition = (StateObject*) rule_objects[rule_objects_pos];

        // Generate a new rule expanded from every rule in the StateObject's state
        for (auto state_rule : state_transition->state->rules) {
            std::vector<GrammarObject*> expanded_rule_vec;

            // Copy rule before current position expanded_rule_pos
            for (size_t expanded_rule_pos = 0; expanded_rule_pos < rule_objects_pos; expanded_rule_pos++) {
                expanded_rule_vec.push_back(rule_objects[expanded_rule_pos]);
            }

            if (std::string(*state_rule.rule_objects[0]) != "#") {
                // Copy rule from transition
                for (auto state_rule_object : state_rule.rule_objects) {
                    expanded_rule_vec.push_back(state_rule_object);
                }
            }

            // Copy rule after current position expanded_rule_pos
            for (size_t expanded_rule_pos = rule_objects_pos + 1; expanded_rule_pos < rule_objects.size(); expanded_rule_pos++) {
                expanded_rule_vec.push_back(rule_objects[expanded_rule_pos]);
            }

            // Create GrammarRule from our rule and add it to the expanded rules
            GrammarRule expanded_rule (expanded_rule_vec);

            // std::cout << "Original Rule: " << std::string(*this) << "   New Rule: " << std::string(expanded_rule) << std::endl;
            if (expanded_rule.size() <= size) {
                rules.push_back(expanded_rule);
            }            
        }       


    }
    
    return rules;
}

uint32_t GrammarRule::size() const {
    uint32_t size = 0;

    for (size_t rule_objects_pos = 0; rule_objects_pos < rule_objects.size(); rule_objects_pos++) {

        if (rule_objects[rule_objects_pos]->object_type == GrammarObject::ObjectType::Literal) {
            size++;
        }
    }

    return size;
}

bool GrammarRule::is_literal() {
    for (size_t rule_objects_pos = 0; rule_objects_pos < rule_objects.size(); rule_objects_pos++) {

        if (rule_objects[rule_objects_pos]->object_type == GrammarObject::ObjectType::Rule) {
            return false;
        }
    }

    return true;
}

bool GrammarRule::operator == (const GrammarRule &Ref) {
    return (this->rule_objects == Ref.rule_objects);
}

bool GrammarRule::operator < (const GrammarRule&Ref) const{
    std::cout << std::string(*this) << " is less than " << std::string(Ref) << " ? ";
    if (this->size() < Ref.size()) {
        std::cout << "Yes. Length is smaller" << std::endl;
        return true;
    }
    bool result = std::string(*this) < std::string(Ref);

    if (result) {
        std::cout << "Yes. string sort says so" << std::endl;
    }
    else {
        std::cout << "No. string sort says so" << std::endl;
    }
    return result;
}

GrammarRule::operator std::string() const{
    std::string out_string;

    for (auto rule_object : rule_objects) {
        out_string += *rule_object;
    }

    return out_string;
}