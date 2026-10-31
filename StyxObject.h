#pragma once 
#include <string>
#include <type_traits>

enum StyxType {
    STRING,
    NUMBER,
    COMMAND
};

class StyxObject {
protected:
    StyxType type;

public:
    StyxObject(StyxType type) : type(type) {}
    virtual void repr() = 0;
    virtual ~StyxObject = default;
};

class StyxString: public StyxObject {
protected:
    std::string data;

public:
    StyxString(std::string data) : StyxObject(STRING), data(data) {}
    std::string get();
    void repr() override;
};

class StyxNumber: public StyxObject {
protected:
    std::string data; // using a string until I incorporate a bigint library

public:
    StyxNumber(std::string data);

    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value>::type>
    StyxNumber(T data) : StyxObject(NUMBER), data(std::to_string(data)) {}

    std::string get();
    void repr() override;
};



