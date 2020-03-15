#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "songList.h"

using std::ifstream;
using std::string;
using std::cerr;
using namespace std;

void getInputValues (string line, string &command, string &values);
void parseSongInfo (string values, string &song, string &artist);

// Deconstructor
songlist::~songlist(){
    size = 0;
    position = 0;
    delete [] list;
    list = nullptr;
}
// Definitions
string songlist::initSize(int n){
    size = n;
    list = new string* [size]{};
    return "success";
};

string songlist::addSong (string songInfo) {
    // if the current size exceeds the size of list - error
    if (position + 1 > size){
        return "can not insert " + songInfo;
    }
    string song {};
    string artist {};
    parseSongInfo(songInfo, song, artist);
    
    if (position > 0) {
        for (int i = 0; i < position; i++) {
            if (list[i][0] == song && list[i][1] == artist) {
                return "can not insert " + songInfo;
            }
        }
    }
    list[position] = new string[2]{song, artist};
    position += 1;
    return "success";
}

string songlist::playSong(string n) {
    int playPosition = stod(n);
    if (playPosition < position + 1) {
        return "played " + n + " " + list[playPosition-1][0] + ";" + list[playPosition-1][1];
    }
    return "can not play " + n;
}

string songlist::eraseSong (string n) {
    if (stod(n) > position || stod(n) > size || stod(n) < 1) {
        return "can not erase " + n;
    }
    int index = stod(n)-1;
    delete[] list[index];
    
    for (int i = index; i < size - 1; i++) {
        list[i] = list[i+1];
    }
    position -= 1;
    
    return "success";
}

int main() {
    // Open and read from input file
    string line{};
    songlist songlist;
    while(getline(std::cin, line) && !cin.eof()){
        // Splitting the input values - assuming the command will only be one letter
        string command {line[0]};
        string values {};
        string message {};
        int lineLength = line.length();
        int i = 1;
        // Incase of extra space between the command and values
        while (line[i] == ' '){
            i += 1;
        }
        // Get the values
        while (i < lineLength) {
            values += line[i];
            i++;
        }
        // Calling the appropriate functions
        if (command == "m") {
            int value = stod(values);
            message = songlist.initSize(value);
        } else if (command == "i") {
            message = songlist.addSong(values);
        } else if (command == "p") {
            message = songlist.playSong(values);
        } else if (command == "e") {
            message = songlist.eraseSong(values);
        }
        
        // incase of an empty line
        if (lineLength != 0){
             cout << message << endl;
        }
    }
    return 0;
}

void parseSongInfo (string values, string &song, string &artist) {
    int i = 0;
    int infoLength = values.length();
    
    while (values[i] != ';') {
        song += values[i];
        i++;
    }
    i += 1;
    while (values[i] == ' '){
        i += 1;
    }
    while (i < infoLength){
        artist += values[i];
        i++;
    }
}



