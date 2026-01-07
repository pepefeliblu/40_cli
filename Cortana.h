#ifndef CORTANA_H
#define CORTANA_H
#include "Carta40.h"
#include "Jugador.h"
#include <algorithm>
#include <string>
#include <vector>

// Clase que define el comportamiento de un jugador automatizado
class Cortana : public Jugador {
public:
  // Constructor que crea el objeto tomando el nombre
  Cortana(std::string &);
  // Función que determina la jugada de la máquina
  void jugar(Carta40 &, std::vector<Carta40> &);
  // Revisa que la carta exista en mano
  bool checkExist(Carta40 &);
  // Revisa si es posible una caída
  bool checkCaida(Carta40 &, std::vector<Carta40> &);
  // Revisa si se puede sumar
  bool checkSuma(Carta40 &, std::vector<Carta40> &);
  // Revisa si se puede hacer una escalera
  bool checkEscalera(Carta40 &, std::vector<Carta40> &);
  // Escoge una carta de manera aleatoria
  Carta40 &randPicker();
};

#endif
