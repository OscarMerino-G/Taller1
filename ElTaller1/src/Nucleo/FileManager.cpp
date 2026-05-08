#include "../../include/Nucleo/FileManager.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

bool FileManager::loadMusicSource(const std::string& filename, MusicLibrary& library) {
    return library.loadFromFile(filename);
}

bool FileManager::saveMusicSource(const std::string& filename, const MusicLibrary& library) {
    return library.saveToFile(filename);
}

bool FileManager::loadStatus(const std::string& filename, PlayerStatus& status, Playlist& playlist) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // Valores por defecto
        status.isPlaying = false;
        status.shuffleMode = false;
        status.repeatMode = 0;
        status.currentSongId = -1;
        status.currentSongName = "";
        status.currentSongArtist = "";
        status.playlistCurrentIndex = -1;
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) continue;
        
        std::string key = line.substr(0, equalPos);
        std::string value = line.substr(equalPos + 1);
        
        if (key == "IS_PLAYING") {
            status.isPlaying = (value == "1");
        } else if (key == "SHUFFLE_MODE") {
            status.shuffleMode = (value == "1");
        } else if (key == "REPEAT_MODE") {
            status.repeatMode = std::atoi(value.c_str());
        } else if (key == "CURRENT_SONG_ID") {
            status.currentSongId = std::atoi(value.c_str());
        } else if (key == "CURRENT_SONG_NAME") {
            status.currentSongName = value;
        } else if (key == "CURRENT_SONG_ARTIST") {
            status.currentSongArtist = value;
        } else if (key == "PLAYLIST_CURRENT_INDEX") {
            status.playlistCurrentIndex = std::atoi(value.c_str());
        } else if (key == "PLAYLIST_IDS") {
            
            // La playlist se carga con esta info
            // por ahora se guarda
        }
    }
    
    file.close();
    return true;
}

bool FileManager::saveStatus(const std::string& filename, const PlayerStatus& status, const Playlist& playlist) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    
    file << "IS_PLAYING=" << (status.isPlaying ? "1" : "0") << std::endl;
    file << "SHUFFLE_MODE=" << (status.shuffleMode ? "1" : "0") << std::endl;
    file << "REPEAT_MODE=" << status.repeatMode << std::endl;
    file << "CURRENT_SONG_ID=" << status.currentSongId << std::endl;
    file << "CURRENT_SONG_NAME=" << status.currentSongName << std::endl;
    file << "CURRENT_SONG_ARTIST=" << status.currentSongArtist << std::endl;
    file << "PLAYLIST_CURRENT_INDEX=" << status.playlistCurrentIndex << std::endl;
    file << "PLAYLIST_IDS=" << savePlaylistToIds(playlist) << std::endl;
    
    file.close();
    return true;
}

bool FileManager::loadPlaylistFromIds(const std::string& idsStr, MusicLibrary& library, Playlist& playlist) {
    if (idsStr.empty()) return false;
    
    std::stringstream ss(idsStr);
    std::string idStr;
    
    while (std::getline(ss, idStr, ';')) {
        if (idStr.empty()) continue;
        int id = std::atoi(idStr.c_str());
        Song* song = library.findSongById(id);
        if (song != nullptr) {
            playlist.addSong(*song);
        }
    }
    
    return !playlist.isEmpty();
}

std::string FileManager::savePlaylistToIds(const Playlist& playlist) {
    std::stringstream ss;
    for (size_t i = 0; i < playlist.size(); i++) {
        if (i > 0) ss << ";";
        ss << playlist.getSongAt(i).getId();
    }
    return ss.str();
}