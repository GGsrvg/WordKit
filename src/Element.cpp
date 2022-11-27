//
//  Element.cpp
//
//  Created by GGsrvg on 25.12.2021.
//

#include <WordKit/Element.h>


std::string wordKit::VAlignmentEncode(wordKit::VAlignment verticalAlignment) {
    switch (verticalAlignment) {
        case wordKit::VAAuto:
            throw "unknown return value";
        case wordKit::VABaseline:
            throw "unknown return value";
        case wordKit::VABottom:
            return "bottom";
        case wordKit::VACenter:
            return "center";
        case wordKit::VATop:
            return "top";
    }
}

std::string wordKit::HAlignmentEncode(wordKit::HAlignment horizontalTextAlignment) {
    std::string hAlignment;
    switch (horizontalTextAlignment) {
        case wordKit::HAStart:
            hAlignment = "left";
            break;
        case wordKit::HAEnd:
            hAlignment = "right";
            break;
        case wordKit::HACenter:
            hAlignment = "center";
            break;
        case wordKit::HABoth:
            hAlignment = "both";
            break;
        case wordKit::HADistribute:
            hAlignment = "distribute";
            break;
        default:
            throw "Unknown type";
            break;
    }
    
    // TODO: return only hAlignment
    return "<w:jc w:val=\"" + hAlignment + "\"/>";
}
