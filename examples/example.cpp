#include <memory>
#include "Document.h"

using namespace std;
using namespace wordKit;

void generateDocument() {
    const auto fileName = "test.docx";
    std::shared_ptr<wordKit::Document> document(new wordKit::Document("", fileName));

    document->appendElements({
        new Paragraph(dsl([]() {
            auto property = make_shared<ParagraphProperty>();
            property->horizontalTextAlignment = HACenter;
            return property;
        }), {
            new Run(dsl([]() {
                auto property = make_shared<RunProperty>();
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
                auto property = make_shared<RunProperty>();
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
}

int main() {
    generateDocument();
    return 0;
}
