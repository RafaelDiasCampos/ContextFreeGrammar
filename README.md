# Context Free Grammar

## About

This repository hosts an application that creates a derivation tree for an arbitrary Context Free Grammar.

## Compiling
``` bash
git@github.com:RafaelDiasCampos/ContextFreeGrammar.git
cd ContextFreeGrammar
git submodule init
git submodule update
make
```

## Testing
``` bash
./context_free_grammar examples/sameQuantity.json 4
```

## Running
``` bash
./context_free_grammar grammar_file max_size
```

## Issues
Grammars that contain at least one recursive rule without any literals will cause the program to hang. This happens because rule size calculation needs to only take literals into consideration, but by doing that recursive rules with no literals will have the same size after expansion and will keep expanding forever. Example:
``` json
{
    "glc": [
        ["P"],
        ["0", "1"],
        [
            ["P", "PP"],
            ["P", "0"],
            ["P", "1"]
        ],
        "P"
    ]
}
```