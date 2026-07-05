#include<bits/stdc++.h>
using namespace std;

class DocumentElement {
    public:
        virtual string render() = 0;
};

class TextElement : public DocumentElement {
    string text;
    public:
        TextElement(string text) {
            this->text = text;
        }
        string render() override {
            return text;
        }
};

class ImageElement : public DocumentElement {
    string imgPath;
    public:
        ImageElement(string imgPath) {
            this->imgPath = imgPath;
        }
        string render() override {
            return "[Image:" + imgPath + "]";
        }
};

class NewLine : public DocumentElement {
    public:
        string render() override {
            return "\n";
        }
};

class TabSpace : public DocumentElement {
    public:
        string render() override {
            return "\t";
        }
};

class Document {
        vector<DocumentElement*> elements;
    public:
        void addElement(DocumentElement* d){
            elements.push_back(d);
        }

        string render() {
            string document = "";
            for(auto &element : elements){
                document += element->render();
            }
            return document;
        }
};

class Persistence {
    public:
        virtual void save(string data) = 0;

};

class FileStorage : public Persistence  {
    public: 
        void save(string data) override {
            ofstream file("document.txt");
            file << data;
            file.close();
        }
};

class DocumentEditor {
private:
    Document* document;
    Persistence* storage;
    string renderedDocument;

public:
    DocumentEditor(Document* document, Persistence* storage) {
        this->document = document;
        this->storage = storage;
    }

    void addText(string text) {
        document->addElement(new TextElement(text));
    }

    void addImage(string imagePath) {
        document->addElement(new ImageElement(imagePath));
    }

    // Adds a new line to the document.
    void addNewLine() {
        document->addElement(new NewLine());
    }

    // Adds a tab space to the document.
    void addTabSpace() {
        document->addElement(new TabSpace());
    }

    string renderDocument() {
        return document->render();
    }

    void saveDocument() {
        storage->save(renderDocument());
    }
};

int main() {
    Document* doc = new Document();
    Persistence* storage = new FileStorage();
    DocumentEditor* editor = new DocumentEditor(doc, storage);
    editor->addText("Hello, world!");
    editor->addNewLine();
    editor->addText("This is a real-world document editor example.");
    editor->addNewLine();
    editor->addTabSpace();
    editor->addText("Indented text after a tab space.");
    editor->addNewLine();
    editor->addImage("picture.jpg");

    cout << "Rendered Document:\n" << editor->renderDocument() << endl;
    editor->saveDocument();
    return 0;
}