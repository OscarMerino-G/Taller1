#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <string>
#include "../Clases/MusicLibrary.hpp"
#include "../Clases/Playlist.hpp"

struct PlayerStatus {
    bool isPlaying;           // true: reproduciendo, false: en pausa
    bool shuffleMode;        // true: aleatorio activado
    int repeatMode;          // 0: desactivado, 1: repetir una, 2: repetir todas
    int currentSongId;       // id de la canción actual, -1 si no hay cancion
    std::string currentSongName;
    std::string currentSongArtist;
    int playlistCurrentIndex; // Índice actual en la playlist
    // El orden de la playlist se guarda como lista de IDs
};

class FileManager {
public:
    static bool loadMusicSource(const std::string& filename, MusicLibrary& library);
    static bool saveMusicSource(const std::string& filename, const MusicLibrary& library);
    
    static bool loadStatus(const std::string& filename, PlayerStatus& status, Playlist& playlist);
    static bool saveStatus(const std::string& filename, const PlayerStatus& status, const Playlist& playlist);
    
    static bool loadPlaylistFromIds(const std::string& idsStr, MusicLibrary& library, Playlist& playlist);
    static std::string savePlaylistToIds(const Playlist& playlist);
};

#endif