//
//  Run.h
//
//  Created by GGsrvg on 02.12.2021.
//

#ifndef Run_h
#define Run_h

#include <string>
#include <vector>
#include <iostream>

#include "Element.h"

namespace wordKit {
class Text: Encodable {
public:
    Text(std::string);
    ~Text();
    std::string encode() noexcept override;
private:
    std::string text;
};
// TODO: change on run childrens or another
class Break: public Text {
public:
    Break() : Text("") {
    }
    ~Break() {}
    
    std::string encode() noexcept {
        return "<w:br/>";
    }
};

class RunProperty: Encodable {
public:
    std::string font = "<w:rFonts w:ascii=\"Times New Roman\" w:hAnsi=\"Times New Roman\" w:cs=\"Times New Roman\" w:eatAsia=\"Times New Roman\"/>";
    
    bool isBold = false;
    
    bool isItalics = false;
    
    bool isCAPS = false;
    
    bool isStrike = false;
    
//    bool isDoubleStrike;
    
    bool isUnderline = false;
    
    // change to object or int
    std::string color = "000000";
    
    /**
     Set size
     
     Set property sz and szCs
     */
    int size = 0;
    
    RunProperty();
    ~RunProperty();
    
    std::string encode() noexcept override;
};

class Run: Encodable {
public:
    Run(RunProperty*, const std::vector<Text*>);
    ~Run();
    std::string encode() noexcept override;
private:
    RunProperty* property;
    std::vector<Text*> texts;
};
}

#endif /* Run_h */
