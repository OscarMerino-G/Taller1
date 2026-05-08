#include "../../include/Nucleo/Player.hpp"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>

Player::Player() : needsSave(false) {
    srand(time(nullptr));
}

Player::~Player() {
    saveIfNeeded();
}

bool Player::initialize() {
    // carga canciones
    if (!FileManager::loadMusicSource("music_source.txt", library)) {
        std::cout << "Advertencia: No se pudo cargar music_source.txt" << std::endl;
    }
    
    // carga configuracion
    if (!FileManager::loadStatus("status.cfg", status, playlist)) {
        std::cout << "Iniciando por primera vez..." << std::endl;
        status.isPlaying = false;
        status.shuffleMode = false;
        status.repeatMode = 0;
        status.currentSongId = -1;
        status.playlistCurrentIndex = -1;
        
        if (!library.isEmpty()) {
            generateRandomPlaylist();
        }
        needsSave = true;
    } else {
        // restaura configuracion actual
        if (status.currentSongId != -1) {
            Song* song = library.findSongById(status.currentSongId);
            if (song != nullptr && !playlist.isEmpty()) {
                // chequeo de indice valiod
                if (status.playlistCurrentIndex >= 0 && 
                    status.playlistCurrentIndex < static_cast<int>(playlist.size())) {
                    playlist.setCurrentIndex(status.playlistCurrentIndex);
                }
            } else {
                status.currentSongId = -1;
                status.isPlaying = false;
            }
        }
        
        if (status.shuffleMode && !playlist.isEmpty()) {
            playlist.shuffle();
        }
    }
    
    saveIfNeeded();
    return true;
}

void Player::run() {
    char option;
    do {
        clearScreen();
        displayNowPlaying();
        displayMainMenu();
        
        std::cout << "Ingrese Opción: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        handleMainMenuInput(option);
        
    } while (option != 'X' && option != 'x');
}

void Player::clearScreen() const {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Player::displayNowPlaying() const {
    std::cout << "\n========================================" << std::endl;
    
    // muestra estado de reproduccion
    if (!playlist.hasCurrentSong() || library.isEmpty()) {
        std::cout << "Reproducción Detenida" << std::endl;
    } else {
        // muestra estado de mezcla, [S] si esta activado
        if (status.shuffleMode) {
            std::cout << "Reproduciendo (S";
        } else {
            std::cout << "Reproduciendo (";
        }
        
        // muestra modo repeticion
        if (status.repeatMode == 1) {
            std::cout << "-R1";
        } else if (status.repeatMode == 2) {
            std::cout << "-R2";
        }
        std::cout << "): ";
        
        const Song& current = playlist.getCurrentSong();
        std::cout << current.getNombre() << std::endl;
        std::cout << "Artista: " << current.getArtista() << std::endl;
        std::cout << "Album: " << current.getAlbum() << " [" << current.getYear() << "]" << std::endl;
    }
    
    std::cout << "========================================" << std::endl;
}

void Player::displayMainMenu() const {
    std::cout << "\nOpciones:" << std::endl;
    std::cout << "  W - Reproducir/Pausar" << std::endl;
    std::cout << "  Q - Pista Anterior" << std::endl;
    std::cout << "  E - Pista Siguiente" << std::endl;
    std::cout << "  S - Activar/Desactivar modo aleatorio" << std::endl;
    std::cout << "  R - Repetición (Desactivado/Repetir una/Repetir todas)" << std::endl;
    std::cout << "  A - Ver lista de reproducción actual" << std::endl;
    std::cout << "  L - Listado de canciones" << std::endl;
    std::cout << "  X - Salir" << std::endl;
}

void Player::handleMainMenuInput(char option) {
    switch (option) {
        case 'W': case 'w':
            togglePlayPause();
            break;
        case 'Q': case 'q':
            previousTrack();
            break;
        case 'E': case 'e':
            nextTrack();
            break;
        case 'S': case 's':
            toggleShuffle();
            break;
        case 'R': case 'r':
            toggleRepeat();
            break;
        case 'A': case 'a':
            showPlaylistMenu();
            break;
        case 'L': case 'l':
            showSongListMenu();
            break;
        case 'X': case 'x':
            std::cout << "Saliendo..." << std::endl;
            saveIfNeeded();
            break;
        default:
            std::cout << "Opción inválida" << std::endl;
            std::cin.get();
    }
}

void Player::togglePlayPause() {
    if (library.isEmpty() || !playlist.hasCurrentSong()) {
        std::cout << "No hay canciones disponibles" << std::endl;
        std::cin.get();
        return;
    }
    
    status.isPlaying = !status.isPlaying;
    needsSave = true;
    std::cout << (status.isPlaying ? "Reproduciendo" : "En pausa") << std::endl;
    std::cin.get();
}

void Player::previousTrack() {
    if (library.isEmpty() || !playlist.hasCurrentSong()) {
        std::cout << "No hay canciones disponibles" << std::endl;
        std::cin.get();
        return;
    }
    
    // agrega cancion actual al historial
    history.push(playlist.getCurrentSong());
    
    playlist.previous();
    updateStatusFromPlaylist();
    
    status.isPlaying = true;
    needsSave = true;
    
    std::cout << "Reproduciendo canción anterior" << std::endl;
    std::cin.get();
}

void Player::nextTrack() {
    if (library.isEmpty()) {
        std::cout << "No hay canciones disponibles" << std::endl;
        std::cin.get();
        return;
    }
    
    if (!playlist.hasCurrentSong()) {
        generateRandomPlaylist();
    } else {
        // guardfa en historial
        history.push(playlist.getCurrentSong());
        playlist.next();
        updateStatusFromPlaylist();
    }
    
    // Verifica modo repeticion
    handleRepeatMode();
    
    status.isPlaying = true;
    needsSave = true;
    
    std::cout << "Reproduciendo siguiente canción" << std::endl;
    std::cin.get();
}

void Player::toggleShuffle() {
    if (library.isEmpty()) {
        std::cout << "No hay canciones disponibles" << std::endl;
        std::cin.get();
        return;
    }
    
    status.shuffleMode = !status.shuffleMode;
    
    if (status.shuffleMode && !playlist.isEmpty()) {
        playlist.shuffle();
        updateStatusFromPlaylist();
        std::cout << "Modo aleatorio ACTIVADO - Lista mezclada" << std::endl;
    } else {
        std::cout << "Modo aleatorio DESACTIVADO" << std::endl;
    }
    
    needsSave = true;
    std::cin.get();
}

void Player::toggleRepeat() {
    status.repeatMode = (status.repeatMode + 1) % 3;
    
    switch (status.repeatMode) {
        case 0:
            std::cout << "Repetición: DESACTIVADO" << std::endl;
            break;
        case 1:
            std::cout << "Repetición: REPETIR UNA" << std::endl;
            break;
        case 2:
            std::cout << "Repetición: REPETIR TODAS" << std::endl;
            break;
    }
    
    needsSave = true;
    std::cin.get();
}

void Player::showPlaylistMenu() {
    clearScreen();
    std::cout << "\n=== LISTA DE REPRODUCCIÓN ACTUAL ===" << std::endl;
    
    if (playlist.isEmpty()) {
        std::cout << "La lista de reproducción está vacía" << std::endl;
    } else {
        for (size_t i = 0; i < playlist.size(); i++) {
            if (static_cast<int>(i) == playlist.getCurrentIndex()) {
                std::cout << "  ▶ ";
            } else {
                std::cout << "     ";
            }
            std::cout << (i + 1) << ". " << playlist.getSongAt(i).getDisplayString() << std::endl;
        }
    }
    
    std::cout << "\nPresione Enter para continuar...";
    std::cin.get();
}

void Player::showSongListMenu() {
    char option;
    do {
        clearScreen();
        displaySongList();
        
        std::cout << "\nOpciones:" << std::endl;
        std::cout << "  R<num> - Reproducir canción seleccionada" << std::endl;
        std::cout << "  A<num> - Agregar canción seleccionada al final de la lista" << std::endl;
        std::cout << "  N - Agregar canción al registro" << std::endl;
        std::cout << "  D<num> - Eliminar canción seleccionada" << std::endl;
        std::cout << "  V - Volver al menú principal" << std::endl;
        std::cout << "Ingrese Opción: ";
        
        std::string input;
        std::getline(std::cin, input);
        
        if (input.empty()) continue;
        
        option = toupper(input[0]);
        
        if (option == 'R') {
            int num = std::atoi(input.substr(1).c_str());
            if (num > 0 && num <= static_cast<int>(library.size())) {
                playSpecificSong(num - 1);
                option = 'V';  // vuelve despues de reproducir
            } else {
                std::cout << "Número inválido" << std::endl;
                std::cin.get();
            }
        } else if (option == 'A') {
            int num = std::atoi(input.substr(1).c_str());
            if (num > 0 && num <= static_cast<int>(library.size())) {
                addSongToPlaylist(num - 1);
            } else {
                std::cout << "Número inválido" << std::endl;
                std::cin.get();
            }
        } else if (option == 'N') {
            addNewSong();
        } else if (option == 'D') {
            int num = std::atoi(input.substr(1).c_str());
            if (num > 0 && num <= static_cast<int>(library.size())) {
                deleteSong(num - 1);
            } else {
                std::cout << "Número inválido" << std::endl;
                std::cin.get();
            }
        }
        
    } while (option != 'V');
}

void Player::displaySongList() const {
    std::cout << "\n=== CANCIONES REGISTRADAS ===" << std::endl;
    
    if (library.isEmpty()) {
        std::cout << "No hay canciones registradas" << std::endl;
    } else {
        library.displayAll();
    }
}

void Player::playSpecificSong(int index) {
    Song* song = library.findSongByIndex(index);
    if (song == nullptr) return;
    
    // VACIA LA PLAYLIST Y CREA UNA NUEVA CON ORDEN ALEATORIO
    playlist.clear();
    LinkedList<Song>& allSongs = library.getAllSongs();
    
    // agrega todas las canciones a la playlist con orden aleatorio
    Node<Song>* current = allSongs.getHead();
    while (current != nullptr) {
        playlist.addSong(current->data);
        current = current->next;
    }
    
    playlist.shuffle();
    
    // Mueve la cancion seleccionada al inicio
    for (size_t i = 0; i < playlist.size(); i++) {
        if (playlist.getSongAt(i) == *song) {
            // intercambia por la primera cancion
            Song temp = playlist.getSongAt(0);
            playlist.getQueue().removeAt(0);
            playlist.getQueue().insertAt(0, playlist.getSongAt(i - 1));
            playlist.getQueue().removeAt(i);
            playlist.getQueue().insertAt(i, temp);
            break;
        }
    }
    
    playlist.setCurrentIndex(0);
    updateStatusFromPlaylist();
    status.isPlaying = true;
    status.shuffleMode = false;
    needsSave = true;
    
    std::cout << "Reproduciendo canción seleccionada" << std::endl;
    std::cin.get();
}

void Player::addSongToPlaylist(int index) {
    Song* song = library.findSongByIndex(index);
    if (song == nullptr) return;
    
    playlist.addSongAtEnd(*song);
    needsSave = true;
    
    std::cout << "Canción agregada al final de la lista de reproducción" << std::endl;
    std::cin.get();
}

void Player::addNewSong() {
    std::cout << "\n=== AGREGAR NUEVA CANCIÓN ===" << std::endl;
    
    std::string nombre = getInputString("Nombre de la canción: ");
    std::string artista = getInputString("Nombre del artista: ");
    std::string album = getInputString("Nombre del álbum: ");
    int year = getInputInt("Año de lanzamiento: ");
    int duracion = getInputInt("Duración en segundos: ");
    std::string ruta = getInputString("Ruta del archivo: ");
    
    library.addSong(nombre, artista, album, year, duracion, ruta);
    FileManager::saveMusicSource("music_source.txt", library);
    needsSave = true;
    
    std::cout << "Canción agregada exitosamente!" << std::endl;
    std::cin.get();
}

void Player::deleteSong(int index) {
    Song* song = library.findSongByIndex(index);
    if (song == nullptr) return;
    
    std::cout << "¿Eliminar \"" << song->getDisplayString() << "\"? (S/N): ";
    char confirm;
    std::cin >> confirm;
    std::cin.ignore();
    
    if (toupper(confirm) == 'S') {
        int songId = song->getId();
        library.removeSongAt(index);
        
        // si se encuentra, elimina de la playlist
        for (size_t i = 0; i < playlist.size(); i++) {
            if (playlist.getSongAt(i).getId() == songId) {
                playlist.removeSong(i);
                break;
            }
        }
        
        FileManager::saveMusicSource("music_source.txt", library);
        needsSave = true;
        
        std::cout << "Canción eliminada" << std::endl;
    }
    
    std::cin.get();
}

void Player::generateRandomPlaylist() {
    if (library.isEmpty()) return;
    
    playlist.clear();
    LinkedList<Song>& allSongs = library.getAllSongs();
    
    Node<Song>* current = allSongs.getHead();
    while (current != nullptr) {
        playlist.addSong(current->data);
        current = current->next;
    }
    
    playlist.shuffle();
    playlist.setCurrentIndex(0);
    updateStatusFromPlaylist();
}

void Player::updateStatusFromPlaylist() {
    if (playlist.hasCurrentSong()) {
        const Song& current = playlist.getCurrentSong();
        status.currentSongId = current.getId();
        status.currentSongName = current.getNombre();
        status.currentSongArtist = current.getArtista();
        status.playlistCurrentIndex = playlist.getCurrentIndex();
    } else {
        status.currentSongId = -1;
        status.currentSongName = "";
        status.currentSongArtist = "";
        status.playlistCurrentIndex = -1;
    }
}

void Player::updatePlaylistAfterShuffle() {
    if (status.shuffleMode && !playlist.isEmpty()) {
        playlist.shuffle();
        updateStatusFromPlaylist();
    }
}

void Player::handleRepeatMode() {
    if (!playlist.hasCurrentSong()) {
        if (status.repeatMode == 2 && !library.isEmpty()) {
            // Repite todas, genera playlist
            generateRandomPlaylist();
            if (status.shuffleMode) {
                playlist.shuffle();
            }
        }
        return;
    }
    
    if (status.repeatMode == 1) {
        // repite una, vuelve al cancion
        history.push(playlist.getCurrentSong());
        // reinicia
        playlist.previous();
        updateStatusFromPlaylist();
    }
}

void Player::saveIfNeeded() {
    if (needsSave) {
        updateStatusFromPlaylist();
        FileManager::saveStatus("status.cfg", status, playlist);
        needsSave = false;
    }
}

int Player::getInputNumber(const std::string& prefix) const {
    std::string input;
    std::cout << prefix;
    std::getline(std::cin, input);
    return std::atoi(input.c_str());
}

std::string Player::getInputString(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int Player::getInputInt(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return std::atoi(input.c_str());
}