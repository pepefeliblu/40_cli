#include "Carta40.h"
#include <cctype>
#include <iostream>
#include <stdexcept>
// Crea una carta sin definición alguna
Carta40::Carta40() {}

Carta40::Carta40(int valor, int palo) {
  // Asigna el palo, valor y la representación de la carta
  Carta40::setCarta(valor, palo);

  ultima = false;
}
Carta40::Carta40(char code[2]) {
  // Se copia la representación
  carta[1] = toupper(code[0]);
  carta[2] = toupper(code[1]);
  // Se establece el palo y el valor
  setCarta(code);

  ultima = false;
}

Carta40::~Carta40() {}
// Compara los valores de la carta para evaluar si es mayor
bool Carta40::operator<(const Carta40 &siguiente) const {

  return (getValor() < siguiente.getValor());
}
// Compara los valores del palo y el valor para evaluar si dos cartas son
// iguales
bool Carta40::operator==(const Carta40 &espejo) const {
  if (valor == espejo.valor && palo == espejo.palo) {
    return true;
  } else
    return false;
}

void Carta40::setCarta(int valor_, int palo_) {
  // Revisa que el palo esté en rango
  if (palo_ > 0 && palo_ <= 4) {
    // Asigna el valor del palo y luego su representación gráfica
    palo = palo_;
    switch (palo) {
    case 1:
      carta[2] = 'C';
      break;
    case 2:
      carta[2] = 'P';
      break;
    case 3:
      carta[2] = 'T';
      break;
    case 4:
      carta[2] = 'D';
      break;
    }
    // Revisa que los valores estén en rango
    if (valor_ >= 0 && valor_ < 10) {
      // Asigna el valor y luego su representación
      valor = valor_;

      switch (valor) {
      case 0:
        carta[1] = 'A';
        break;
      case 1:
        carta[1] = '2';
        break;
      case 2:
        carta[1] = '3';
        break;
      case 3:
        carta[1] = '4';
        break;
      case 4:
        carta[1] = '5';
        break;
      case 5:
        carta[1] = '6';
        break;
      case 6:
        carta[1] = '7';
        break;
      case 7:
        carta[1] = 'J';
        break;
      case 8:
        carta[1] = 'Q';
        break;
      case 9:
        carta[1] = 'K';
        break;
      }

    } else {
      throw std::out_of_range("El valor de la carta está fuera de rango\n");
    }
  } else {
    throw std::out_of_range("Los valores de palo están fuera de rango\n");
  }
}
// Asigna el valor y el palo basado en los caracteres que representan a la carta
void Carta40::setCarta(char imagen[]) {
  switch (imagen[0]) {
  case 'A':
    valor = 0;
    break;
  case '2':
    valor = 1;
    break;
  case '3':
    valor = 2;
    break;
  case '4':
    valor = 3;
    break;
  case '5':
    valor = 4;
    break;
  case '6':
    valor = 5;
    break;
  case '7':
    valor = 6;
    break;
  case 'J':
    valor = 7;
    break;
  case 'Q':
    valor = 8;
    break;
  case 'K':
    valor = 9;
    break;
  }
  switch (imagen[1]) {
  case 'C':
    palo = 1;
    break;
  case 'P':
    palo = 2;
    break;
  case 'T':
    palo = 3;
    break;
  case 'D':
    palo = 4;
    break;
  }
}
// Cambia el estado de si fue la última en jugarse
void Carta40::setUltima(bool isUltima) { ultima = isUltima; }
// Devuelve el estado si fue la última en jugarse
bool Carta40::getUltima() { return ultima; }
// Devuelve un puntero al arreglo carta
char *Carta40::getCarta() { return carta; }
// Devuelve el valor de la carta
int Carta40::getValor() const { return valor; }
// Devuelve el palo de la carta
int Carta40::getPalo() const { return palo; }
// Dibuja la carta
void Carta40::dibujarCarta() {
  std::cout << ' ';
  for (int i = 0; i < 4; i++) {
    std::cout << carta[i];
  }

  std::cout << ' ';
}
