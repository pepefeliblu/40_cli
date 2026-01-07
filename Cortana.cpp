#include "Cortana.h"
#include <iostream>
//El constructor llama al constructor  de la clase base
Cortana::Cortana(std::string &name_): Jugador(name_)
{
	
}
//Revisa si la carta existe en la mano 
bool Cortana::checkExist(Carta40 &posible)
{
	for(int i = 0; i < mano.size(); i++)
	{
		if(posible == mano[i])
		{
			return true;
		}
		else 
			return false;
	}
}
//Revisa si se puede hacer una caída
bool Cortana::checkCaida(Carta40 &deMano, std::vector<Carta40>& mesa)
{
	for(int i = 0; i < mesa.size(); i++)
	{
		//Si los valores de la carta en mano y mesa coinciden; y fué la ultima en jugarse
		if(deMano.getValor() == mesa[i].getValor() && mesa[i].getUltima())
		{
			
			return true;
		}
	}
	
	return false;
}

bool Cortana::checkSuma(Carta40 &sumar, std::vector<Carta40> &mesa_)
{
	int suma = 1;
	//Lazo anidado que compara dos cartas en mesa
	for(int i = 0; i < mesa_.size()-1; i++)
	{
		for(int j= i+1; j < mesa_.size(); j++)
		{
			//Suma dos cartas en mesa
			suma = mesa_[i].getValor() + mesa_[j].getValor();
			//Si la suma es menor a 7 (Valor que representa a la J) y coincide con la carta lanzada hay suma
			if(suma+1 < 7 && sumar.getValor() == suma+1)
			{
				return true;
			}
		}
	}
	return false;
}
//Revisa si realiza una escalera
bool Cortana::checkEscalera(Carta40 &deMano, std::vector<Carta40> &mesa)
{
	int delta ;
	for(int i=0; i< mesa.size(); i++)
	{
		//Si los valores de la carta en mano y en mesa coinciden
		if(deMano.getValor() ==mesa[i].getValor())
		{
			
			delta = i;
			//Si se puede hacer una escalera de mínimo dos cartas hay escalera
			if(mesa[delta].getValor() ==mesa[1+delta].getValor()-1)
			{
				return true;
			}
					
		}
	}
	
	return false;
}
//Juega la carta
void Cortana::jugar(Carta40 &mano, std::vector<Carta40> &mesa)
{
	//variable que determina si una acción es viable
	bool exito = false;
	for(int i = 0; i < mesa.size(); i++)
	{
		//Si la carta en mano y en mesa coinciden en valor
		if(mano.getValor() == mesa[i].getValor())
		{
			//Una acción es viable
			exito = true;
			if(checkEscalera(mano, mesa))
			{
				//Se realiza escalera
				std::cout << getNombre() << " hace una escalera con "; 
				mano.dibujarCarta();
				std::cout << std::endl<<std::endl;
				escalera(mano,mesa);
				break;
			}
			else if(checkSuma(mano, mesa))
			{
				//Se realiza suma
				std::cout << getNombre() << " hace una suma con "; 
				mano.dibujarCarta();
				std::cout << std::endl<<std::endl;
				suma(mano, mesa);
				break;
			}
			else if(checkCaida(mano, mesa))
			{
				//Se realiza caída
				std::cout << getNombre() << " hace una caída con "; 
				mano.dibujarCarta();
				std::cout << std::endl<<std::endl;
				caida(mano, mesa);
				break;
			}
			else
			{
				//Roba la carta de la mesa
				std::cout << getNombre() << " chupa una carta con "; 
				mano.dibujarCarta();
				std::cout << std::endl <<std::endl;
				chupar(mano, mesa);
				break;
			}
		}
	}
	//Si ninguna acción es viable lanza la carta
	if(!exito)
	{
		std::cout << getNombre() << " lanza la carta "; 
				mano.dibujarCarta();
				std::cout << std::endl <<std::endl;
		jugarCarta(mano, mesa);
	}
}
//Escoge una carta alzar basado en el tamaño de la mano
Carta40 &Cortana::randPicker()
{
	int random = rand()%mano.size();
	
	return mano[random];
}
