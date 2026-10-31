#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

enum StyxType {
    STRING,
    NUMBER,
    COMMAND
};

class StyxObject {
protected:
    StyxType type;
public:
    StyxObject(StyxType type):type(type) {}
    virtual ~StyxObject() = default;
    virtual void repr() = 0;
};

class StyxString: public StyxObject {
protected:
    string data;
public:
    StyxString(string data):StyxObject(STRING),data(data) {}
    void repr() override {
        cout << "STRING: " << data << endl;
    }
};

class StyxNumber: public StyxObject {
protected:
    string data;
public:
    StyxNumber(string data):StyxObject(NUMBER),data(data) {}

    void repr() override {
        cout << "NUMBER: " << data << endl;
    }
};

class StyxCommand: public StyxObject {
protected:
    string data;
public:
    StyxCommand(string data):StyxObject(COMMAND),data(data) {}
    void repr () override {
        cout << "COMMAND: " << data << endl;
    }
};

vector<unique_ptr<StyxObject>> lexer(string source){
    size_t pos=0;
    vector<unique_ptr<StyxObject>> code;
    while (pos<source.size()){
        if (source[pos]=='"'){
            pos++;
            string temp;
            while(source[pos]!='"'){
                temp+=string(1,source[pos]);
                pos++;
            }
            code.push_back(make_unique<StyxString>(temp));
            pos++;
        }
        else if (source[pos]>='0' && source[pos]<='9'){
            string temp;
            while(source[pos]>='0' && source[pos]<='9'){
                temp+=string(1,source[pos]);
                pos++;
            }
            code.push_back(make_unique<StyxNumber>(temp));
        }
	else if (source[pos]==39){	
	    pos++;
	    code.push_back(make_unique<StyxString>(string(1,source[pos])));
	    pos++;
	}
        else {
            code.push_back(make_unique<StyxCommand>(string(1,source[pos])));
            pos++;
        }
    }    
    return code;
}

int main(int argc, char* argv[]){
    string source = "ty573'h5038\"poooo\"iyt23582too";
    auto code = lexer(source);
    for(auto& obj:code){
        obj->repr();
    }
    return 0;
}
