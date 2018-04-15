#pragma once
#include <string>
#include <map>

class SettingsParser {
private:
    std::string _fileName;
    std::map<std::string, std::string> _data;   
    std::pair<std::string, std::string> parseLine(const std::string& line) const;

    //converts to number types only I think!!!
    /*template<typename T>
    T convertToType(const std::string &input) const {
        T value;
        std::stringstream ss(input);
        ss >> value;
        
        return value;
    }*/

public:
    SettingsParser() = default;
    ~SettingsParser();

    void readFile(const std::string& file);
    void saveToFile(bool overwrite = true);

    std::string get(const std::string& key) const;
    void set(const std::string& key, const std::string& value);
    void put(const std::string& key, const std::string& value);

    void print() const;

    /*template<typename T>
    T get(const std::string& key) const {
        auto it = _data.find(key);
        if(it != _data.end()) {
            auto ret = it->second;
            return convertToType<T>(ret);
        }
            return 0;
    }*/  
};
