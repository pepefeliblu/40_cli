// CMP-320 Programación para ciencias e ingeniería 2
// Profesor: Aldo Cassola
// Juan José Rueda
// 00131765
// CUARENTA
/*
    Este programa simula un cuarenta basadas en las siguientes reglas
   tradicionales: -No hay 38 que no juega -Se puede hacer caída y limpia por 4
   puntos -Después de 38 no vale el cartón -Solo se puede hacer suma con dos
   cartas
*/
#include "Carta40.h"
#include "Cortana.h"
#include "Jugador.h"
#include "Usuario.h"
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <istream>
#include <vector>


using namespace std;

// Imprime las cartas dentro del arreglo Mazo
void imprimirMazo(vector<Carta40> &);
// Imprime las cartas jugadas
void imprimirMesa(vector<Carta40> &);
// Se ejecuta si el usuario reparte
void userComienzo();
// Se ejecuta si la computadora reparte
void pCComienzo();
// Revisa si alguno de los dos jugadores ha llegado a 40 puntos
void revisarVictoria(Jugador *, Jugador *);
// Función que lanzar un número aleatorio y lo compara con el input del usuario
bool decider(int);
// Da un nombre a la computadora
string nameGen();

// Arreglo que guarda todas las cartas
vector<Carta40> mazo(40);
// Arreglo que guarda las cartas jugadas
vector<Carta40> mesa;
// Puntero al jugador humano
Usuario *user;
// Puntero al jugador automático
Cortana *pc;

int main() {
  // Se define la semilla para la función rand()
  srand(time(0));
  // Imprima caracteres con acentos y ñ
  setlocale(LC_ALL, "Spanish_Ecuador.1252");
  // Se llena el mazo con las cartas
  for (int i = 1; i <= 4; i++) {

    static int centinela = 0;
    for (int j = 0; j < 10; j++) {
      mazo[centinela] = Carta40(j, i);
      centinela++;
    }
  }

  cout << setw(30) << "***********CUARENTA***********" << endl;
  cout << "¡Bienvenido! para iniciar una nueva partida por favor escribe tu "
          "nombre y presiona enter"
       << endl
       << endl;
  // Se define la identidad del jugador humano y se crea el objeto
  string nombre;
  cin >> nombre;

  user = new Usuario(nombre);
  // Se genera el jugador automático con un nombre aleatorio
  string maquina = nameGen();
  pc = new Cortana(maquina);
  cout << endl
       << endl
       << "INSTRUCCIONES" << endl
       << user->getNombre()
       << " para realizar acciones escribe\n\n\n 'partir' -> para partir el "
          "mazo\n 'caida' -> para realizar caída\n 'sumar' -> para sumar dos "
          "cartas\n 'escalera' -> para hacer una escalera ascendente de "
          "cartas\n 'robar' -> para robar una carta de la mesa \n 'lanzar' -> "
          "para botar una carta \n  seguido por la carta.\n"
       << "Por ejemplo, si quieres robar una carta de la mesa usando el As de "
          "corazones  escribe 'robar AC '\n\n"
       << endl;
  cout << endl
       << endl
       << user->getNombre() << " tu oponente será " << pc->getNombre() << endl;

  cout << endl
       << "Para decidir quien reparte adivina el valor dentro de un rango del "
          "1 al 4"
       << endl;
  // Se decide quien comienza
  int val;

  cin >> val;

  // Si el usuario adivina él comienza y se alternan hasta que alguien gane
  if (decider(val)) {

    while (!pc->getGanar() && !user->getGanar()) {
      // Se imprime el mazo para demostrar que está completo
      imprimirMazo(mazo);
      // Reparte el usuario
      userComienzo();
      imprimirMazo(mazo);
      // Reparte la computadora
      pCComienzo();
    }
  } else {
    while (!pc->getGanar() && !user->getGanar()) {
      imprimirMazo(mazo);
      pCComienzo();
      imprimirMazo(mazo);
      userComienzo();
    }
  }
}
// Toma un arreglo de Cartas e imprime cada una en pantalla
void imprimirMazo(vector<Carta40> &mazo_) {
  for (int i = 0; i < mazo_.size(); i++) {
    if (i % 10 == 0 && i != 0)
      cout << endl;
    mazo_[i].dibujarCarta();
  }
  cout << endl << endl;
}
// Imprime las cartas jugadas con un margen izquierdo y de 5 por fila
void imprimirMesa(vector<Carta40> &mesa_) {

  for (int i = 0; i < mesa_.size(); i++) {
    if (i % 6 == 0 && i != 0)
      cout << setw(10) << endl;
    mesa_[i].dibujarCarta();
  }

  cout << endl;
}
// Lanza un número aleatorio entre 0-9 y asigna un nombre dependiendo del valor
string nameGen() {
  int azar = rand() % 10;

  string nombre;
  switch (azar) {
  case 0:
    nombre = "Carlos";
    break;
  case 1:
    nombre = "Julia";
    break;
  case 2:
    nombre = "Marcus";
    break;
  case 3:
    nombre = "Silvia";
    break;
  case 4:
    nombre = "Erik";
    break;
  case 5:
    nombre = "Sofía";
    break;
  case 6:
    nombre = "Martín";
    break;
  case 7:
    nombre = "Alejandra";
    break;
  case 8:
    nombre = "Esteban";
    break;
  case 9:
    nombre = "Massiel";
    break;
  }

  return nombre;
}
// toma un número entre 1-4 y lo compara con uno dado por el usuario, si
// coincide él reparte
bool decider(int val_) {
  int random = rand() % 4 + 1;

  if (val_ == random) {
    cout << "Adivinaste el valor!\n ";
    return true;
  } else {
    cout << "El valor era " << random << endl;
    return false;
  }
}

// Si el usuario comienza
void userComienzo() {
  // Mientras nadie haya ganado
  if (!user->getGanar() && !pc->getGanar()) {
    cout << endl
         << "Tu repartes, barajas el mazo de cartas y pides a "
         << pc->getNombre() << " que parta" << endl;
    user->barajar(mazo);
    pc->partir(mazo);

    cout << endl << "Repartes 5 cartas a " << pc->getNombre() << endl;
    // Reparte 5 cartas para el oponente
    user->repartir(pc, mazo);
    // revisa si tiene ronda
    pc->guapo();
    cout << endl << "Tomas 5 cartas " << endl;
    // se da 5 cartas
    user->repartir(user, mazo);
    // revisa si tiene ronda
    user->guapo();
    // muestra la mano del jugador
    cout << user->getNombre() << ": ";
    user->imprimirMano();
    cout << endl << pc->getNombre() << " comienza" << endl;

    // se juega toda una ronda
    for (int i = 0; i < 20; i++) {
      // escoge una carta aleatoria
      Carta40 gen;
      gen = pc->randPicker();
      // juega esa carta aleatoria
      pc->jugar(gen, mesa);
      // revisa si alguien ganó
      revisarVictoria(user, pc);
      // se imprime la mesa y los puntajes
      cout << endl
           << "****************************************************************"
              "************************\n";
      cout << endl << "MESA --->  ";
      imprimirMesa(mesa);
      cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
           << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
      cout << endl;
      cout << endl
           << "****************************************************************"
              "************************\n";

      cout << user->getNombre() << ": ";
      user->imprimirMano();
      cout << endl;

      // se toma la acción y la carta del usuario
      string accion;
      char carta[2];

      cin >> accion;
      cin >> carta[0] >> carta[1];
      carta[0] = static_cast<char>(toupper(carta[0]));
      carta[1] = static_cast<char>(toupper(carta[1]));
      // revisa si esa carta existe en la mano
      Carta40 temp(carta);

      if (user->checkExist(temp)) {
        // juega la carta con la acción respectiva
        user->jugar(temp, mesa, accion);
        // revisa si alguien ganó
        revisarVictoria(user, pc);
        // se imprime la mesa con los puntajes
        cout << endl
             << "**************************************************************"
                "**************************\n";

        cout << endl << "MESA --->  ";
        imprimirMesa(mesa);
        cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
             << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
        cout << endl;
        cout << endl
             << "**************************************************************"
                "**************************\n";
      } else {
        // si la carta no existe en la mano
        while (!user->checkExist(temp)) {
          // toma valores nuevos para la carta
          cout << endl
               << "No tienes la carta que ingresaste, escribe nuevamente la "
                  "carta"
               << endl;
          cin >> carta[0] >> carta[1];
          carta[0] = static_cast<char>(toupper(carta[0]));
          carta[1] = static_cast<char>(toupper(carta[1]));
          temp = Carta40(carta);
        }
        // juega la carta corregida
        user->jugar(temp, mesa, accion);
        // revisa si alguien ganó
        revisarVictoria(user, pc);
      }

      // si la máquina se queda sin cartas y el mazo no está vacio
      if (pc->sinMano() && !mazo.empty()) {
        // se reparten cartas para la máquina y se revisa si hay ronda
        user->repartir(pc, mazo);
        pc->guapo();
      }
      // si el ususario se queda sin cartas y el mazo no está vacio
      if (user->sinMano() && !mazo.empty()) {
        // reparte cartas para el usuario y revisa si tiene ronda
        user->repartir(user, mazo);
        user->guapo();
      }
    }
  }
  // si se acaban las catas del mazo cuenta los cartones y asigna los puntos
  // respectivos
  if (mazo.empty()) {
    cout << endl << "Se cuentan los cartones\n";
    // calcula el cartón de la máquina
    pc->calcularCarton();
    // calcula el carton del usuario
    user->calcularCarton();
    // Imprime el puntaje del usuario y la máquina
    cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
         << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
    cout << endl;
    // devuelve los cartones al mazo de cartas original
    pc->devolverCarton(mazo);
    user->devolverCarton(mazo);
    // devuelve las cartas restantes de la mesa y luego limpia la mesa
    mazo.insert(mazo.end(), mesa.begin(), mesa.end());
    mesa.clear();
    // revisa si alguien ganó
    revisarVictoria(user, pc);
  }
}
// Si el usuario comienza
void pCComienzo() {
  // revisa si alguien ganó
  revisarVictoria(user, pc);
  if ((!user->getGanar() && !pc->getGanar())) {
    // la máquina baraja
    cout << endl
         << pc->getNombre()
         << " reparte, baraja el mazo de cartas y te pide que partas" << endl;
    pc->barajar(mazo);
    // hace que el usuario parta
    string partir;

    cin >> partir;
    // si no parte correctamente se penaliza dandole al oponente 10 puntos
    if (partir == "partir") {
      user->partir(mazo);
    } else {
      cout << endl
           << "No partiste, son 10 puntos para " << pc->getNombre() << endl;
      pc->setPuntaje(10);
    }

    // La máquina reparte 5 cartas al usuario y revisa si tiene cartón
    cout << endl << pc->getNombre() << " te reparte 5 cartas " << endl;

    pc->repartir(user, mazo);
    user->guapo();
    // La máquina toma 5 cartas y revisa si tiene cartón
    cout << endl << pc->getNombre() << " toma 5 cartas " << endl;
    pc->repartir(pc, mazo);
    pc->guapo();

    cout << endl << "Tu comienzas" << endl;

    // Se imprime la mano del usuario y se toma su acción y la carta a lanzar
    for (int i = 0; i < 20; i++) {
      cout << user->getNombre() << ": ";
      user->imprimirMano();
      cout << endl;
      string accion;
      char carta[2];

      cin >> accion;
      cin >> carta[0] >> carta[1];
      carta[0] = static_cast<char>(toupper(carta[0]));
      carta[1] = static_cast<char>(toupper(carta[1]));

      Carta40 temp(carta);
      // Si la carta existe la juega
      if (user->checkExist(temp)) {
        user->jugar(temp, mesa, accion);
        revisarVictoria(user, pc);

        // Imprime la mesa con los puntajes correspondientes
        cout << endl
             << "**************************************************************"
                "**************************\n";

        cout << endl << "MESA --->  ";
        imprimirMesa(mesa);
        cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
             << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
        cout << endl;
        cout << endl
             << "**************************************************************"
                "**************************\n";
      } else {
        // si no existe la carta pide que la ingrese nuevamente
        while (!user->checkExist(temp)) {

          cout << endl
               << "No tienes la carta que ingresaste, escribe nuevamente la "
                  "carta"
               << endl;
          cin >> carta[0] >> carta[1];
          carta[0] = static_cast<char>(toupper(carta[0]));
          carta[1] = static_cast<char>(toupper(carta[1]));
          temp = Carta40(carta);
        }
        // juega la carta y revisa si alguien ganó
        user->jugar(temp, mesa, accion);
        revisarVictoria(user, pc);
      }
      // La máquina escoge una carta al azar y la juega
      Carta40 gen;
      gen = pc->randPicker();

      pc->jugar(gen, mesa);
      // Revisa si alguien ganó e imprime la mesa
      revisarVictoria(user, pc);
      cout << endl
           << "****************************************************************"
              "************************\n";
      cout << endl << "MESA --->  ";
      imprimirMesa(mesa);
      cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
           << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
      cout << endl;
      cout << endl
           << "****************************************************************"
              "************************\n";
      cout << endl;

      // Si no tiene más cartas el usuario y el mazo no está vacio se reparten
      // más cartas, se revisa si tiene ronda
      if (user->sinMano() && !mazo.empty()) {
        pc->repartir(user, mazo);
        user->guapo();
      }
      // Si no tiene más cartas la máquina...
      if (pc->sinMano() && !mazo.empty()) {
        pc->repartir(pc, mazo);
        pc->guapo();
      }
    }
  }

  // Si se acaban las cartas del mazo se cuentan los cartones y se imprimen los
  // puntos asignados
  if (mazo.empty()) {
    cout << endl << "Se cuentan los cartones\n";
    pc->calcularCarton();
    user->calcularCarton();
    cout << setw(10) << user->getNombre() << ": " << user->getPuntaje()
         << setw(10) << pc->getNombre() << ": " << pc->getPuntaje() << endl;
    cout << endl;
    pc->devolverCarton(mazo);
    user->devolverCarton(mazo);
    // devuelve las cartas de la mesa al mazo y la limpia
    mazo.insert(mazo.end(), mesa.begin(), mesa.end());
    mesa.clear();
    // se revisa si alguien ganó
    revisarVictoria(user, pc);
  }
}
// Revisa si alguno de los jugadores tiene 40 o más puntos y le asigna la
// victoria
void revisarVictoria(Jugador *A, Jugador *B) {
  // Si el usuario gana...
  if (A->getPuntaje() >= 40) {
    A->setGanar(true);
    cout << endl
         << "¡Felicitaciones " << A->getNombre() << "! haz derrotado a "
         << B->getNombre() << endl;
  }
  // Si la máquina gana...
  else if (B->getPuntaje() >= 40) {

    B->setGanar(true);
    cout << endl
         << B->getNombre() << " te ha derrotado mejor suerte la proxima"
         << endl;
  }
  // Si alguno de los dos ganó se termina el programa
  if (A->getGanar() == true || B->getGanar() == true) {
    cout << "Presiona cualquier tecla para salir\n";
    exit(0);
  }
}
