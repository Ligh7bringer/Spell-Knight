#include "settings_parsers.h"
#include "Log.h"
#include <fstream>
#include <vector>

using namespace std;

const char COMMENT = '#';
const char EQUALS = '=';

/*
* A settings parser which can read from and write to a text file. Values can be obtained and overwritten.
*/

//reads a text file and stores the settings in it as a key value pair in the _data map
void SettingsParser::readFile(const string& file) {
    //clear the map
    _data.clear();
    _fileName = file;
    
    //make sure the file is open
    std::ifstream in(file);
    if(!in.is_open()) {
        LOG(ERROR) << "Couldn't open settings file " << file << "!";
    } else {
        string line;
        //while not the end of the file
        while(getline(in, line)) {
            //get the pair
            pair<string, string> keyValue = parseLine(line);

            //if the line wasn't empty or a comment
            if(!keyValue.first.empty()) {
                //store it in the _data map
                _data[keyValue.first] = keyValue.second;
                LOG(DEBUG) << "Setting read: " << keyValue.first << " = " << keyValue.second;
            }
        }

        //close stream
        in.close();
        LOG(DEBUG) << "Settings file " << file << " read successfully!";
    }
}

//converts a line of text to a key value pair
pair<string, string> SettingsParser::parseLine(const string& line) const {
    //if line is not empty or a comment
    if(line.size() > 0 && line[0] != COMMENT) {
        size_t index = 0;
        //skip spaces
        while(isspace(line[index])) {
            index++;
        }
        //store the index of the first letter of the key
        const size_t keyStart = index;
        //skip spaces and equals sign
        while(!isspace(line[index]) && line[index] != EQUALS) {
            index++;
        }
        //get the actual key string
        const string key = line.substr(keyStart, index - keyStart);
        //skip more spaces
        while(isspace(line[index]) || line[index] == EQUALS) {
            index++;
        }
        
        //get the actual value
        const string value = line.substr(index, line.size() - index);

        //make the pair and return it
        return make_pair(key, value);
    }

    //if he line is empty or a comment, return an empty pair
    return make_pair(string(), string());
}

//returns a the value of setting with the given key
string SettingsParser::get(const string& key) const {
    auto it = _data.find(key);
    if(it != _data.end())
        return it->second;

    return string();
}

//sets the value of setting key 
void SettingsParser::set(const string& key, const string& value) {
    auto it = _data.find(key);
    if(it != _data.end()) {
        LOG(INFO) << "Overwriting setting " << key << ". New value: " << value;
        it->second = value;
    } else {
        LOG(INFO) << "Setting " << key << " couldn't be overwritten as it doesn't exist";
    }
}

//save the changes made to the settings file
void SettingsParser::saveToFile() {
    //temporary vector of values
    vector<pair<string, string>> fileContents;

    //open file
    std::ifstream in(_fileName);
    if(!in.is_open()) {
        LOG(ERROR) << "Couldn't open settings file " << _fileName << " for writing!";
    }

    if(in.is_open()) {
        string line;
        while(getline(in, line)) {
            pair<string, string> keyValue = parseLine(line);
            
            //get new value from the map
            if(!keyValue.first.empty()) {
                auto it = _data.find(keyValue.first);
                if(it != _data.end()) {
                    keyValue.second = it->second;
                }
            } else {
                //if line is empty or comment, just save it in the pair
                keyValue.first = line;
            }
            //add to the vector
            fileContents.push_back(keyValue);
        }
    } else {
        // can't open file, use available data in the map
        for (auto it = _data.begin(); it != _data.end(); ++it)
            fileContents.push_back(std::make_pair(it->first, it->second));
    }

    //close stream
    in.close();

    //open file for writing
    ofstream out(_fileName);
    if(!out.is_open()) {
        LOG(ERROR) << "Couldn't open file " << _fileName << " for writing!";
    } else {
        LOG(INFO) << "Saving to settings file " << _fileName << "...";
        //write everything from the fileContents vector to the file
        for (auto it = fileContents.begin() ; it != fileContents.end(); ++it) {
            out << it->first;


            if(!it->second.empty()) {
                out << EQUALS << it->second; 
            }

            out << endl;
        }

        //close stream
        out.close();
        LOG(INFO) << "Successfully wrote to settings file " << _fileName;
    }

}

//save to the file when object is destroyed just in case
SettingsParser::~SettingsParser() {
    saveToFile();
}

//prints all the loaded values from the settings file
void SettingsParser::print() const {
    LOG(INFO) << "Currently loaded settings:";
    for(auto keyValue : _data) {
        LOG(INFO) << keyValue.first << " = " << keyValue.second;
    }
}