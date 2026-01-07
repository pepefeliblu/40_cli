#include "Usuario.h"
#include <iostream>
//Crea el objeto llamando al constructor de la clase base
Usuario::Usuario(std::string &nombre):Jugador(nombre)
{
	
}



bool Usuario::checkExist(Carta40 &posible)
{
	//Itera buscando que la carta escogida exista en mano	
	for(int i = 0; i < mano.size(); i++)
	{
	 	
		if(posible == mano[i])
		{
			return true;
		}	
	}

	return false;
}

void Usuario::jugar(Carta40 &mano, std::vector<Carta40> &mesa, std::string &comando)
{
	//Compara el comando definido por el usuario y ejecuta la acción respectiva
	std::cout << "El Comando fue " << comando << std::endl <<std::endl;	
	if(comando == "caida")
	{
		caida(mano, mesa);
		
	}
	else if(comando == "sumar")
	{
		
		suma(mano, mesa);
	}
	else if(comando =="escalera")
	{
		escalera(mano, mesa);
	}
	else if(comando == "robar")
	{
		chupar(mano, mesa);
	}
	else if(comando == "lanzar")
	{
		jugarCarta(mano, mesa);
	}
	else
	{
		//Si el comando no existe pide que lo vuelva a escribir y la función se llama de manera recursiva
		std::cout << "El comando que escribiste '" << comando << "' no existe, por favor escribelo nuevamente" << std::endl;
		std::cin >> comando;
		jugar(mano, mesa, comando);
	}
}


