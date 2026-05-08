#include "../../include/Clases/Song.hpp"
#include <sstream>
#include <iomanip>

Song::Song() : id(0), year(0), duracion(0) {}

Song::Song(int id, const std::string& nombre, const std::string& artista,
           const std::string& album, int year, int duracion, const std::string& ruta)
    : id(id), nombre(nombre), artista(artista), album(album), 
      year(year), duracion(duracion), ruta(ruta) {}

int Song::getId() const { return id; }
std::string Song::getNombre() const { return nombre; }  // nOMBRE
std::string Song::getArtista() const { return artista; } // artista
std::string Song::getAlbum() const { return album; }
int Song::getYear() const { return year; }
int Song::getDuracion() const { return duracion; }
std::string Song::getRuta() const { return ruta; }

std::string Song::getDuracionFormateada() const { // duracion formato en segundos
    int minutos = duracion / 60;
    int segundos = duracion % 60;
    std::stringstream ss;
    ss << minutos << ":" << std::setw(2) << std::setfill('0') << segundos;
    return ss.str();
}

void Song::setId(int id) { this->id = id; }
void Song::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Song::setArtista(const std::string& artista) { this->artista = artista; }
void Song::setAlbum(const std::string& album) { this->album = album; }
void Song::setYear(int year) { this->year = year; }
void Song::setDuracion(int duracion) { this->duracion = duracion; }
void Song::setRuta(const std::string& ruta) { this->ruta = ruta; }

bool Song::operator==(const Song& other) const {
    return id == other.id;
}

bool Song::operator!=(const Song& other) const {
    return id != other.id;
}

std::string Song::toString() const {
    std::stringstream ss;
    ss << id << "," << nombre << "," << artista << "," << album << ","
       << year << "," << duracion << "," << ruta;
    return ss.str();
}

std::string Song::getDisplayString() const {
    std::stringstream ss;
    ss << nombre << " - " << artista;
    return ss.str();
}