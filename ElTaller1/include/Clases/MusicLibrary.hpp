#ifndef MUSICLIBRARY_HPP
#define MUSICLIBRARY_HPP

#include "../Estructura_Datos/LinkedList.hpp"
#include "Song.hpp"

class MusicLibrary {
private:
    LinkedList<Song> songs;
    int nextId;
    
public:
    MusicLibrary();
    ~MusicLibrary();
    
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    void addSong(const Song& song);
    void addSong(const std::string& nombre, const std::string& artista,const std::string& album, int year, int duracion, const std::string& ruta);
    bool removeSong(int id);
    bool removeSongAt(int index);
    
    Song* findSongById(int id);
    Song* findSongByIndex(int index);
    Song* findSongByName(const std::string& nombre);
    
    int getNextId() const;
    void setNextId(int id);
    
    size_t size() const;
    bool isEmpty() const;
    void clear();
    
    void displayAll() const;
    
    LinkedList<Song>& getAllSongs();
    const LinkedList<Song>& getAllSongs() const;
};

#endif