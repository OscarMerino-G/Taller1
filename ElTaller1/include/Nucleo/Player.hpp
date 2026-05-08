#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Clases/MusicLibrary.hpp"
#include "../Clases/Playlist.hpp"
#include "../Estructura_Datos/Stack.hpp"
#include "FileManager.hpp"

class Player {
private:
    MusicLibrary library;
    Playlist playlist;
    Stack<Song> history;  // Historial de canciones
    
    PlayerStatus status;
    
    bool needsSave;  // para saber si hay cambios que guardar
    
    void updateStatusFromPlaylist();
    void saveIfNeeded();
    void clearScreen() const;
    
public:
    Player();
    ~Player();
    
    bool initialize();
    void run();
    
private:
    void displayMainMenu() const;
    void displayNowPlaying() const;
    void handleMainMenuInput(char option);
    
    void togglePlayPause();
    void previousTrack();
    void nextTrack();
    void toggleShuffle();
    void toggleRepeat();
    void showPlaylistMenu();
    void showSongListMenu();
    
    void generateRandomPlaylist();
    void updatePlaylistAfterShuffle();
    void handleRepeatMode();
    
    // submenu de canciones
    void displaySongList() const;
    void handleSongListMenu();
    void playSpecificSong(int index);
    void addSongToPlaylist(int index);
    void addNewSong();
    void deleteSong(int index);
    
    // utiles
    int getInputNumber(const std::string& prefix) const;
    std::string getInputString(const std::string& prompt) const;
    int getInputInt(const std::string& prompt) const;
};

#endif