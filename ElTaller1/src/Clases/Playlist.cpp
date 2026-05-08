#include "../../include/Clases/Playlist.hpp"
#include <iostream>

Playlist::Playlist() : currentIndex(-1) {}

Playlist::~Playlist() {
    clear();
}

bool Playlist::isEmpty() const {
    return songs.isEmpty();
}

size_t Playlist::size() const {
    return songs.size();
}

void Playlist::clear() {
    songs.clear();
    currentIndex = -1;
}

void Playlist::addSong(const Song& song) {
    songs.enqueue(song);
    if (currentIndex == -1 && songs.size() == 1) {
        currentIndex = 0;
    }
}

void Playlist::addSongAtEnd(const Song& song) {
    songs.enqueue(song);
}

void Playlist::insertAt(size_t index, const Song& song) {
    if (index <= songs.size()) {
        songs.insertAt(index, song);
        if (currentIndex != -1 && static_cast<int>(index) <= currentIndex) {
            currentIndex++;
        }
    }
}

void Playlist::removeSong(size_t index) {
    if (index < songs.size()) {
        if (static_cast<int>(index) == currentIndex) {
            // Si se elimina la cancion actual, se pasa a la siguiente canicon
            if (songs.size() > 1) {
                currentIndex = (currentIndex + 1) % songs.size();
            } else {
                currentIndex = -1;
            }
        } else if (static_cast<int>(index) < currentIndex) {
            currentIndex--;
        }
        songs.removeAt(index);
    }
}

void Playlist::removeCurrentSong() {
    if (currentIndex != -1) {
        removeSong(currentIndex);
    }
}

Song& Playlist::getCurrentSong() {
    return songs.at(currentIndex);
}

const Song& Playlist::getCurrentSong() const {
    return songs.at(currentIndex);
}

bool Playlist::hasCurrentSong() const {
    return currentIndex != -1 && !songs.isEmpty();
}

void Playlist::next() {
    if (songs.isEmpty()) return;
    
    if (currentIndex + 1 < static_cast<int>(songs.size())) {
        currentIndex++;
    } else {
        currentIndex = 0;  // vuelve al inicio
    }
}

void Playlist::previous() {
    if (songs.isEmpty()) return;
    
    if (currentIndex - 1 >= 0) {
        currentIndex--;
    } else {
        currentIndex = songs.size() - 1;  // va al final
    }
}

void Playlist::shuffle() {
    if (songs.size() <= 1) return;
    
    Song current = getCurrentSong();
    songs.shuffle();
    
    // encuentra el indice de la cancion actual
    for (size_t i = 0; i < songs.size(); i++) {
        if (songs.at(i) == current) {
            currentIndex = i;
            break;
        }
    }
}

Song& Playlist::getSongAt(size_t index) {
    return songs.at(index);
}

const Song& Playlist::getSongAt(size_t index) const {
    return songs.at(index);
}

void Playlist::setCurrentIndex(int index) {
    if (index >= 0 && index < static_cast<int>(songs.size())) {
        currentIndex = index;
    }
}

int Playlist::getCurrentIndex() const {
    return currentIndex;
}

void Playlist::display() const {
    for (size_t i = 0; i < songs.size(); i++) {
        std::cout << "  " << (i + 1) << ". " << songs.at(i).getDisplayString() << std::endl;
    }
}

Queue<Song>& Playlist::getQueue() {
    return songs;
}