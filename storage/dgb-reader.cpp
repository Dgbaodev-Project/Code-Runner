#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <sstream>
#include <cctype>

using namespace std;

vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    stringstream ss(s);
    while(getline(ss, token, delimiter)) {
        size_t start = token.find_first_not_of(" \t\r\n");
        size_t end = token.find_last_not_of(" \t\r\n");
        if(start != string::npos && end != string::npos)
            tokens.emplace_back(token.substr(start, end - start + 1));
        else if(start != string::npos)
            tokens.emplace_back(token.substr(start));
        else
            tokens.emplace_back("");
    }
    return tokens;
}

bool isNumber(const string& s) {
    if(s.empty()) return false;
    return all_of(s.begin(), s.end(), ::isdigit);
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if(start == string::npos || end == string::npos)
        return "";
    return s.substr(start, end - start + 1);
}

int main(int argc, char* argv[]) {
    vector<string> args;
    for(int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }

    string configFilePath = "/input/config.dgb";

    ifstream configFile(configFilePath);
    if(!configFile.is_open()) {
        cerr << "Không thể mở tệp: " << configFilePath << endl;
        return 1;
    }

    map<string, vector<string>> configMap;
    string line;
    while(getline(configFile, line)) {
        if(line.empty() || line[0] == '#') continue;
        size_t pos = line.find('=');
        if(pos == string::npos) continue;
        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);
        key = trim(key);
        value = trim(value);
        vector<string> values = split(value, ';');
        for(auto &val : values) {
            val = trim(val);
        }

        configMap[key] = values;
    }

    configFile.close();

    if(args.empty()) {
        cerr << "Không có khóa nào được cung cấp." << endl;
        return 1;
    }

    bool hasIndex = false;
    int index = 0;
    if(isNumber(args.back())) {
        hasIndex = true;
        index = stoi(args.back());
        args.pop_back();
        if(args.empty()) {
            cerr << "Không có khóa nào được cung cấp sau chỉ số." << endl;
            return 1;
        }
    }

    string keyPath;
    for(size_t i = 0; i < args.size(); ++i) {
        keyPath += args[i];
        if(i != args.size() - 1) keyPath += ".";
    }

    auto it = configMap.find(keyPath);
    if(it == configMap.end()) {
        cerr << "Không tìm thấy khóa: " << keyPath << endl;
        return 1;
    }

    vector<string> values = it->second;
    if(hasIndex) {
        if(index < 0 || index >= (int)values.size()) {
            cerr << "Chỉ số " << index << " vượt quá phạm vi (0 - " << values.size()-1 << ")." << endl;
            return 1;
        }
        cout << values[index] << endl;
    }
    else {
        if(values.size() == 1) {
            cout << values[0] << endl;
        }
        else {
            for(const auto& val : values) {
                cout << val << endl;
            }
        }
    }

    return 0;
}
