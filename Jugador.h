#ifndef JUGADOR_H
#define JUGADOR_H
#include <vector>
#include "Carta40.h" //Se incluye la clase de las cartas
#include <string>
//Clase que define las funciones básicas de un jugador de cuarenta
class Jugador
{
	protected:
		std::vector<Carta40> carton; //Almacena el cartón del jugador
		bool ganar = false; //variable de la victoria
		int puntaje =0; // El puntaje del jugador
		std::vector<Carta40> mano; //Almacena la mano del jugador
		std::string nombre; //Almacena el nombre del jugador
		
		
	public:
		//El constructor sólo toma el nombre asignado al jugador
		Jugador(std::string);
		//Lanza la carta escogida en la mesa
		void jugarCarta(Carta40&, std::vector<Carta40>&);
		//Realiza la caida
		void caida(Carta40&, std::vector<Carta40>&);
		//Roba una carta de la mesa
		void chupar(Carta40&, std::vector<Carta40>&);
		//Revisa si la mesa se limpió
		void limpia( std::vector<Carta40>&);
		//Hace una escalera de cartas
		void escalera(Carta40&, std::vector<Carta40>&); 
		//Suma las cartas
		void suma(Carta40&, std::vector<Carta40>&);
		//Revisa si tiene ronda 
		void guapo();
		//Parte el mazo
		void partir(std::vector<Carta40>&);
		//Baraja el mazo
		void barajar(std::vector<Carta40>&);
		//Reparte cartas al jugador asignado
		void repartir(Jugador*, std::vector<Carta40>&);
		//Asigna las cartas al arreglo de la mano del jugador
		void setMano(std::vector<Carta40>&);
		//Devuelve una carta basado en el índice del arreglo mano
		Carta40 &getMano(int );
		//revisa si el jugador ya no tiene cartas en la mano
		bool sinMano();
		//Asigna los puntos dados
		void setPuntaje(int);
		//Devuelve los puntos del jugador
		int getPuntaje();
		//Cuenta las cartas del cartón y asigna los puntos respectivos
		void calcularCarton();
		//Asigna la victoria
		void setGanar(bool);
		//Devuelve si el jugador ha ganado o no
		bool getGanar();
		//Devuelve las cartas del carton al mazo
		void devolverCarton( std::vector<Carta40>&);
		//Imprime las cartas del cartón
		void imprimirCarton();
		//Imprime la mano del jugador
		void imprimirMano();
		//Asigna el nombre al jugador
		void setNombre(std::string);
		//Devuelve el nombre del jugador
		std::string getNombre();
		//Saca la carta asignada de la mano
		void sacarMano(Carta40&);
		//Saca la carta de la mesa
		void sacarMesa(Carta40&, std::vector<Carta40>&);
		//Deuvleve la cantidad de cartas que el jugador tiene en la mano
		int cantCarta();
		
};
#endif
