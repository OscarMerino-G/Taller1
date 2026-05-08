#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include "../Estructura_Datos/Queue.hpp"
#include "Song.hpp"

class Playlist {
private:
    Queue<Song> songs;
    int currentIndex;  // index de la cancion actual | "-1" si no hay canciones;
    
public:
    Playlist();
    ~Playlist();
    
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    void addSong(const Song& song);
    void addSongAtEnd(const Song& song);
    void insertAt(size_t index, const Song& song);
    void removeSong(size_t index);
    void removeCurrentSong();
    
    Song& getCurrentSong(); 
    const Song& getCurrentSong() const;
    bool hasCurrentSong() const;
    
    void next(); // pasa a la siguiente cancion
    void previous(); // vuelve a la cancion anterior
    void shuffle(); // Mezcla la playlist
    
    Song& getSongAt(size_t index);
    const Song& getSongAt(size_t index) const;
    
    void setCurrentIndex(int index);
    int getCurrentIndex() const;
    
    void display() const;
    
    Queue<Song>& getQueue();
};

#endif