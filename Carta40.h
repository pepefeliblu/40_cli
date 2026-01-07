#ifndef CARTA40_H
#define CARTA40_H
#include <iostream>
// Clase que define los valores y representación de una carta en cuarenta
class Carta40 {
private:
  // Guarda un arreglo de caracteres para la impresión de la carta en consola
  char carta[4] = {'|', '|', '|', '|'};
  // variable que representa el palo de la carta
  int palo;
  // El valor numérico de la carta
  int valor;
  bool ultima;

public:
  // Constructor sin argumentos
  Carta40();
  // constructor basado en el palo y el valor
  Carta40(int, int);
  // Constructor basado en la representación de la carta
  Carta40(char[2]);

  ~Carta40();
  // Crea la carta basada en el palo y el valor
  void setCarta(int, int);
  // Crea la carta basada en la representación
  void setCarta(char[2]);
  // Devuelve un puntero al arreglo carta
  char *getCarta();
  // Devuelve el valor de la carta
  int getValor() const;
  // Devuelve el palo de la carta
  int getPalo() const;
  // Establece que fue la última carta en lanzarse
  void setUltima(bool);
  // Retorna si fue la última en lanzarse
  bool getUltima();
  // Compara lógicamente dos cartas
  bool operator<(const Carta40 &) const;
  // Compara si dos cartas son identicas
  bool operator==(const Carta40 &) const;
  // Imprime la carta en consola
  void dibujarCarta();
};

#endif
