#ifndef USUARIO_H
#define USUARIO_H
#include "Carta40.h"
#include "Jugador.h"
#include <string>
#include <vector>


// Clase que define el comportamiento de un usuario
class Usuario : public Jugador {
public:
  // Crea al usuario tomando su nombre
  explicit Usuario(std::string &);
  // Toma la acción y la carta a jugar
  void jugar(Carta40 &, std::vector<Carta40> &, std::string &);
  // Revisa que la carta exista en mano
  bool checkExist(Carta40 &);
};

#endif
