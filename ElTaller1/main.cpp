#include "include/Nucleo/Player.hpp"
#include <iostream>

int main() {
    std::cout << "******* REPRODUCTOR DE MUSICA ********" << std::endl;
    std::cout << "Iniciando..." << std::endl;
    
    Player player;
    
    if (!player.initialize()) {
        std::cerr << "Error al inicializar el reproductor" << std::endl;
        return 1;
    }
    
    player.run();
    
    std::cout << "Hasta luego" << std::endl;
    return 0;
}