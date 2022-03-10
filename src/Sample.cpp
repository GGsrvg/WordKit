#include <iostream>
#include "Document.h"

using namespace std;
using namespace wordKit;

int main() {
    const auto fileName = "test.docx";
    std::shared_ptr<wordKit::Document> document(new wordKit::Document("", fileName));
    
    document->appendElements({
        new Paragraph(dsl([]() {
            auto property = new ParagraphProperty();
            property->horizontalTextAligmment = HACenter;
            return property;
        }), {
            new Run(dsl([]() {
                auto property = new RunProperty();
                property->size = 10;
                property->isBold = true;
                property->isCAPS = true;
                return property;
            }), {
                new Break(),
                new Break(),
                new Text("Official document")
            }),
            new Run(dsl([]() {
                auto property = new RunProperty();
                property->size = 10;
                property->isBold = true;
                return property;
            }), {
                new Break(),
                new Break(),
                new Text("Use the metric system worldwide"),
                new Break(),
                new Break(),
            })
        })
    });

    document->save();

    return 0;
}
