#include "../../include/Clases/MusicLibrary.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

MusicLibrary::MusicLibrary() : nextId(1) {}

MusicLibrary::~MusicLibrary() {
    clear();
}

bool MusicLibrary::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    clear();
    nextId = 1;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string idStr, nombre, artista, album, yearStr, duracionStr, ruta;
        
        std::getline(ss, idStr, ',');
        std::getline(ss, nombre, ',');
        std::getline(ss, artista, ',');
        std::getline(ss, album, ',');
        std::getline(ss, yearStr, ',');
        std::getline(ss, duracionStr, ',');
        std::getline(ss, ruta, ',');
        
        int id = std::atoi(idStr.c_str());
        int year = std::atoi(yearStr.c_str());
        int duracion = std::atoi(duracionStr.c_str());
        
        Song song(id, nombre, artista, album, year, duracion, ruta);
        songs.pushBack(song);
        
        if (id >= nextId) {
            nextId = id + 1;
        }
    }
    
    file.close();
    return true;
}

bool MusicLibrary::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    Node<Song>* current = songs.getHead();
    while (current != nullptr) {
        file << current->data.toString() << std::endl;
        current = current->next;
    }
    
    file.close();
    return true;
}

void MusicLibrary::addSong(const Song& song) {
    songs.pushBack(song);
    if (song.getId() >= nextId) {
        nextId = song.getId() + 1;
    }
}

void MusicLibrary::addSong(const std::string& nombre, const std::string& artista,
                           const std::string& album, int year, int duracion, const std::string& ruta) {
    Song song(nextId++, nombre, artista, album, year, duracion, ruta);
    songs.pushBack(song);
}

bool MusicLibrary::removeSong(int id) {
    Node<Song>* current = songs.getHead();
    int index = 0;
    while (current != nullptr) {
        if (current->data.getId() == id) {
            songs.removeAt(index);
            return true;
        }
        current = current->next;
        index++;
    }
    return false;
}

bool MusicLibrary::removeSongAt(int index) {
    if (index >= 0 && index < static_cast<int>(songs.size())) {
        songs.removeAt(index);
        return true;
    }
    return false;
}

Song* MusicLibrary::findSongById(int id) {
    Node<Song>* current = songs.getHead();
    while (current != nullptr) {
        if (current->data.getId() == id) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

Song* MusicLibrary::findSongByIndex(int index) {
    if (index >= 0 && index < static_cast<int>(songs.size())) {
        return &(songs.at(index));
    }
    return nullptr;
}

Song* MusicLibrary::findSongByName(const std::string& nombre) {
    Node<Song>* current = songs.getHead();
    while (current != nullptr) {
        if (current->data.getNombre() == nombre) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

int MusicLibrary::getNextId() const {
    return nextId;
}

void MusicLibrary::setNextId(int id) {
    nextId = id;
}

size_t MusicLibrary::size() const {
    return songs.size();
}

bool MusicLibrary::isEmpty() const {
    return songs.isEmpty();
}

void MusicLibrary::clear() {
    songs.clear();
    nextId = 1;
}

void MusicLibrary::displayAll() const {
    Node<Song>* current = songs.getHead();
    int index = 1;
    while (current != nullptr) {
        std::cout << "  " << index++ << ". " << current->data.getDisplayString() << std::endl;
        current = current->next;
    }
}

LinkedList<Song>& MusicLibrary::getAllSongs() {
    return songs;
}

const LinkedList<Song>& MusicLibrary::getAllSongs() const {
    return songs;
}