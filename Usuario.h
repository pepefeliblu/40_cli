#ifndef USUARIO_H
#define USUARIO_H
#include <string>
#include "Jugador.h"
#include "Carta40.h"
#include <vector>
//Clase que define el comportamiento de un usuario
class Usuario : public Jugador
{
	public:
	//Crea al ususario tomando su nombre
	Usuario(std::string &);
	//Toma la acción y la carta a jugar 
	void jugar(Carta40 &,std::vector<Carta40>&, std::string &);
	//Revisa que la carta exista en mano
	bool checkExist(Carta40 &);	
};

#endif
