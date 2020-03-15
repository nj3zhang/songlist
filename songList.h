#ifndef songList_h
#define songList_h
#include <iostream>
#include <string.h>

class songlist {
private:
    // Default size (?)
    int size{0};
    int position{0};
    // 2D array
    std::string **list;
    
public:
    ~songlist();
    std::string initSize (int n);
    std::string addSong (std::string songInfo);
    std::string playSong (std::string n);
    std::string eraseSong (std::string n);
};

#endif

