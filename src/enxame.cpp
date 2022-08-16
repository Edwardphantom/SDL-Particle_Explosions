/*
 * enxame.cpp
 *
 *  Created on: 12 de ago. de 2022
 *      Author: Eduardo
 */

#include "enxame.h"

namespace dudu {

enxame::enxame(): ultimavez(0) // ridículo, ele só faz pegar e criar um novo objeto, com as 5000 posições disponíveis no vetor.
{
	m_pParticulasmaneiras = new particulas[NPARTICULAS];
}

enxame::~enxame()
{
	delete [] m_pParticulasmaneiras;
}

void enxame::enxameatualizado(int tempopassado)
{
		int intervalo = tempopassado - ultimavez;        // criando o intervalo que irá homogenizar a valocidade.

		for (int i=0; i < enxame::NPARTICULAS; i++ )
			{
				m_pParticulasmaneiras[i].recoloca(intervalo);
			}
		ultimavez = tempopassado;
}

} /* namespace dudu */
