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
    explicit Text(std::string);
    ~Text() override;
    std::string encode() noexcept override;
private:
    std::string text;
};
// TODO: change on run childrens or another
class Break: public Text {
public:
    Break() : Text("") { }
    ~Break() override = default;
    
    std::string encode() noexcept override {
        return "<w:br/>";
    }
};

class RunProperty: Encodable {
public:
    std::string font = R"(<w:rFonts w:ascii="Times New Roman" w:hAnsi="Times New Roman" w:cs="Times New Roman" w:eatAsia="Times New Roman"/>)";
    
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
    ~RunProperty() override;
    
    std::string encode() noexcept override;
};

class Run: Encodable {
public:
    Run(std::shared_ptr<RunProperty>, const std::vector<Text*>&);
    Run(std::shared_ptr<RunProperty>, std::vector<std::shared_ptr<Text>>);
    ~Run() override;
    std::string encode() noexcept override;
private:
    std::shared_ptr<RunProperty> property;
    std::vector<std::shared_ptr<Text>> texts;
};
}

#endif /* Run_h */
