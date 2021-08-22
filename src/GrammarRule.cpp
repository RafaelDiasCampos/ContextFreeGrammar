#include "GrammarRule.h"
#include <iostream>

GrammarRule::GrammarRule(std::vector<GrammarObject*> o_rule_objects) : rule_objects(o_rule_objects){

}

GrammarRule::GrammarRule(const GrammarRule &other) : rule_objects(other.rule_objects){

}

std::vector<GrammarRule> GrammarRule::expand_rule(uint32_t size) {
    std::vector<GrammarRule> rules;

    // Expand the rule in every GrammarObject
    for (auto rule_objects_it = rule_objects.begin(); rule_objects_it != rule_objects.end(); rule_objects_it++) {

        // Ignore literals since they cannot be expanded
        if ((*rule_objects_it)->object_type == GrammarObject::ObjectType::Literal) {
            continue;
        }

        // Cast GrammarObject to a StateObject
        StateObject* state_transition = (StateObject*) (*rule_objects_it);

        // Generate a new rule expanded from every rule in the StateObject's state
        for (auto state_rule : state_transition->state->rules) {
            std::vector<GrammarObject*> expanded_rule_vec;

            // Copy rule before current position expanded_rule_pos
            if (rule_objects_it != rule_objects.begin()) {
                expanded_rule_vec.insert(expanded_rule_vec.end(), rule_objects.begin(), rule_objects_it);
            }

            // If rule isn't empty, copy it from transition
            if (std::string(*state_rule.rule_objects[0]) != "#") {
                expanded_rule_vec.insert(expanded_rule_vec.end(),  state_rule.rule_objects.begin(), state_rule.rule_objects.end());
            }

            // Copy rule after current position expanded_rule_pos
            if (rule_objects_it + 1 != rule_objects.end()) {                
                expanded_rule_vec.insert(expanded_rule_vec.end(), rule_objects_it + 1, rule_objects.end());
            }

            // Create GrammarRule from our rule and add it to the expanded rules
            GrammarRule expanded_rule (expanded_rule_vec);

            if (expanded_rule.rule_objects.size() <= size) {
                rules.push_back(expanded_rule);
            }            
        }     


    }
    
    return rules;
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
    auto this_size = this->rule_objects.size();
    auto ref_size = Ref.rule_objects.size();
    if (this_size != ref_size) {
        return this_size < ref_size;
    }
    
    return std::string(*this) < std::string(Ref);
}

GrammarRule& GrammarRule::operator=(const GrammarRule &other) {
    this->rule_objects = other.rule_objects;
    return *this;
}

GrammarRule::operator std::string() const{
    std::string out_string;

    for (auto rule_object : rule_objects) {
        out_string += *rule_object;
    }

    return out_string;
}