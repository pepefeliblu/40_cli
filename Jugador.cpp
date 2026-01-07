#include "Jugador.h"
#include <algorithm>
#include <iostream>
#include <random>
// El constructor asigna 0 puntos y el estado de ganar como falso, asigna el
// nombre dado
Jugador::Jugador(std::string nombre_) {
  ganar = false;
  setNombre(nombre_);
  puntaje = 0;
}

void Jugador::jugarCarta(Carta40 &escogida, std::vector<Carta40> &mesa) {
  // Declara a la carta escogida como la última lanzada
  escogida.setUltima(true);
  // Si la mesa no está vacia...
  if (!mesa.empty()) {
    // Se asegura de que todas las cartas no sean las últimas en ser lanzadas
    for (int i = 0; i < mesa.size(); i++) {
      mesa[i].setUltima(false);
    }
    // Agrega la carta escogida al arreglo de la mesa y luego ordena la mesa
    mesa.push_back(escogida);
    std::sort(mesa.begin(), mesa.end());
  } else {
    // Si está vacia solo incluye la carta
    mesa.push_back(escogida);
  }
  // Saca de la mano la carta escogida
  sacarMano(escogida);
}

// Roba una carta de la mesa
void Jugador::chupar(Carta40 &deMano, std::vector<Carta40> &mesa) {
  // Variable booleana que revisa si se cumple o nó la accion dada
  bool seCumple = false;

  for (int i = 0; i < mesa.size(); i++) {
    // Sí encuentra una de igual valor
    if (deMano.getValor() == mesa[i].getValor()) {
      // se determina que se cumple la acción
      seCumple = true;

      // pasa la carta de la mano al cartón
      carton.push_back(deMano);
      // saca la carta asignada de la mano
      sacarMano(deMano);
      // copia la carta de la mesa al cartón
      carton.push_back(mesa[i]);
      // la saca de la mesa
      sacarMesa(mesa[i], mesa);
      // se sale del lazo
      break;
    }
  }
  // Si la acción no se cumple lanza la carta a la mesa
  if (!seCumple) {
    jugarCarta(deMano, mesa);
  }
  // Si la mesa no está vacia...
  if (!mesa.empty()) {
    // Se asegura de que todas las cartas de la mesa no sean las últimas en
    // lanzarse
    for (int i = 0; i < mesa.size(); i++) {
      mesa[i].setUltima(false);
    }
    // Ordena la mesa
    std::sort(mesa.begin(), mesa.end());
  }
  // revisa si se limpió
  limpia(mesa);
}

// Realiza la acción de caída
void Jugador::caida(Carta40 &deMano, std::vector<Carta40> &mesa) {
  // boolean que determina si la acción se cumple o nó
  bool seCumple = false;
  for (int i = 0; i < mesa.size(); i++) {
    // se busca la carta de igual equivalencia y que sea la última en lanzarse
    if (deMano.getValor() == mesa[i].getValor() && mesa[i].getUltima()) {
      // Se determina que la acción se cumple
      seCumple = true;
      // Pasa las cartas de la mano y la mesa al cartón
      carton.push_back(deMano);
      sacarMano(deMano);
      mesa[i].setUltima(false);

      carton.push_back(mesa[i]);
      sacarMesa(mesa[i], mesa);
      // da dos puntos al jugador
      setPuntaje(2);

      std::cout << "se hizo caida\n";
      break;
    }
  }

  // Si no se cumple se trata de robar una carta de la mesa
  std::cout << std::endl;
  if (!seCumple) {
    chupar(deMano, mesa);
  }
  // Revisa si se limpió la mesa
  limpia(mesa);
}
// Revisa si se hace limpia
void Jugador::limpia(std::vector<Carta40> &mesa) {
  // Si la meza está vacía se dan dos puntos al jugador
  if (mesa.empty()) {
    std::cout << "Se hizo limpia\n";
    setPuntaje(2);
  }
}
// Determina si el jugador tiene cartas en la mano o nó
bool Jugador::sinMano() {
  if (mano.empty())
    return true;
  else
    return false;
}

// Realiza una escalera
void Jugador::escalera(Carta40 &deMano, std::vector<Carta40> &mesa) {

  bool existe = false;
  // arreglo de cartas que almacena temporalmente la escalera
  std::vector<Carta40> monton;
  // variable interna para el índice de la última carta
  int delta;
  for (int i = 0; i < mesa.size() - 1; i++) {

    // busca una carta del mismo valor
    if (deMano.getValor() == mesa[i].getValor()) {

      // Revisa si es caída
      if (mesa[i].getUltima()) {
        setPuntaje(2);
        mesa[i].setUltima(false);
      }

      // saca la carta de la mano al cartón
      carton.push_back(deMano);
      sacarMano(deMano);
      // itera el alcance de la suma
      for (int j = i + 1; j < mesa.size(); j++) {
        // va pasando las cartas que siguen en secuencia al montón
        if (mesa[i].getValor() == mesa[j].getValor() - 1) {
          // la condición se cumple
          existe = true;
          monton.push_back(mesa[i]);
          i++;
        } else {
          break;
        }

        delta = j - 1;
      }
    }
  }
  // Si se cumple la condición pasa la última carta al cartón y al resto de la
  // escalera
  if (existe) {
    carton.push_back(mesa[delta + 1]);
    sacarMesa(mesa[delta + 1], mesa);
    carton.insert(carton.end(), monton.begin(), monton.end());
    // saca las cartas del arreglo mesa
    for (int i = 0; i < monton.size(); i++) {
      mesa.erase(remove(mesa.begin(), mesa.end(), monton[i]));
    }
  }
  // Si no se cumple la condición trata de chupar una carta
  if (!existe) {
    chupar(deMano, mesa);
  }
  // Ordena la mesa si no está vacía
  if (!mesa.empty())
    std::sort(mesa.begin(), mesa.end());
  // revisa si se hizo limpia
  limpia(mesa);
}
// Suma de cartas
void Jugador::suma(Carta40 &sumar, std::vector<Carta40> &mesa_) {
  bool seCumple = false;
  int suma = 1;
  // lazo anidado para buscar las cartas a sumarse
  for (int i = 0; i < mesa_.size() - 1; i++) {
    for (int j = i + 1; j < mesa_.size(); j++) {
      // Almacena el valor de la suma de dos cartas en la mesa
      suma = mesa_[i].getValor() + mesa_[j].getValor();
      // Revisa que la suma sea menor 7 (valor de J) y  coincida con el valor de
      // la carta lanzada
      if (suma + 1 < 7 && sumar.getValor() == suma + 1) {
        // Se cumple la condición y traslada la carta de la mano al cartón
        seCumple = true;

        carton.push_back(sumar);
        sacarMano(sumar);
        // Traslada las cartas a sumarse al cartón
        carton.push_back(mesa_[i]);
        sacarMesa(mesa_[i], mesa_);
        carton.push_back(mesa_[j - 1]);
        sacarMesa(mesa_[j - 1], mesa_);

        break;
      }
      // Se asegura que todas las cartas en la mesa no sean las últimas lanzadas
      mesa_[i].setUltima(false);
    }
  }
  // Si no se cumple trata de chupar una carta
  if (!seCumple) {
    chupar(sumar, mesa_);
  }
  // revisa si se hizo limpia
  limpia(mesa_);
}
// Mezcla las cartas del mazo
void Jugador::barajar(std::vector<Carta40> &mazo) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(mazo.begin(), mazo.end(), g);
}
// Parte el mazo
void Jugador::partir(
    std::vector<Carta40>
        &mazo) { // iterador que guarda la posición del elemento en la mitad
  std::size_t mitad = mazo.size() / 2;
  // se crea un arreglo que guarda los elementos de la primera mitad
  std::vector<Carta40> parte(mazo.begin(), mazo.begin() + mitad);
  // se borran los elementos de la primera mitad del mazo
  mazo.erase(mazo.begin(), mazo.begin() + mitad);
  // se inserta la otra mitad
  mazo.insert(mazo.end(), parte.begin(), parte.end());
}
// Reparte cartas a los jugadores
void Jugador::repartir(Jugador *sujeto, std::vector<Carta40> &mazo) {
  // arreglo que almacena 5 cartas
  std::vector<Carta40> manoTemp;
  for (int i = 0; i < 5; i++) {
    manoTemp.push_back(mazo.back());
    mazo.pop_back();
  }
  // se pasan las cartas al arreglo mano del jugador
  sujeto->setMano(manoTemp);
}
// Copia un arreglo de cartas a la mano del jugador
void Jugador::setMano(std::vector<Carta40> &mano_) { mano = mano_; }
// Devuelve un elemento de la mano basado en el índice
Carta40 &Jugador::getMano(int val) { return mano[val]; }
// Suma puntos al jugador
void Jugador::setPuntaje(int puntos) { puntaje += puntos; }
// Dibuja las cartas de la mano del jugador
void Jugador::imprimirMano() {
  for (int i = 0; i < mano.size(); i++) {
    mano[i].dibujarCarta();
  }
}
int Jugador::getPuntaje() { return puntaje; }

void Jugador::imprimirCarton() {
  for (int i = 0; i < carton.size(); i++) {
    carton[i].dibujarCarta();
  }

  std::cout << std::endl
            << "El jugador " << getNombre()
            << " tiene un puntaje de: " << getPuntaje() << std::endl;
}

void Jugador::guapo() {
  int contador = 1;

  for (int i = 0; i < 3; i++) {
    Carta40 temp = mano[i];

    for (int j = i + 1; j - 1 < mano.size(); j++) {

      if (temp.getValor() == mano[j].getValor()) {
        contador++;
      }
      if (contador == 3) {
        setPuntaje(2);

        std::cout << std::endl
                  << "2 por guapo para: " << getNombre() << std::endl;
        break;
      }
    }
    contador = 1;
  }
}

void Jugador::calcularCarton() {
  int extras = 0;

  std::cout << std::endl
            << getNombre() << " tiene " << carton.size() << " cartas\n";
  if (carton.size() >= 19 && getPuntaje() < 38) {
    extras = 6;

    int tempCalc = (int)(carton.size()) - 19;
    if (tempCalc % 2 == 1)
      tempCalc++;

    extras += tempCalc;
  }
  std::cout << " se suman " << extras << " puntos\n";
  setPuntaje(extras);
}
void Jugador::setGanar(bool status) { ganar = status; }

bool Jugador::getGanar() { return ganar; }

void Jugador::setNombre(std::string nombre_) { nombre = nombre_; }

std::string Jugador::getNombre() { return nombre; }

void Jugador::sacarMano(Carta40 &seleccionada) {

  mano.erase(std::remove(mano.begin(), mano.end(), seleccionada), mano.end());
}
void Jugador::sacarMesa(Carta40 &seleccionada, std::vector<Carta40> &mesa_) {
  mesa_.erase(std::remove(mesa_.begin(), mesa_.end(), seleccionada),
              mesa_.end());
}
int Jugador::cantCarta() { return (int)(mano.size()); }

void Jugador::devolverCarton(std::vector<Carta40> &mazo) {
  mazo.insert(mazo.end(), carton.begin(), carton.end());
  carton.clear();
}
