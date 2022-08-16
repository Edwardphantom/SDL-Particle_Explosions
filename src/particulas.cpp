/*
 * particulas.cpp
 *
 *  Created on: 12 de ago. de 2022
 *      Author: Eduardo
 *
 *      link de referência : https://cplusplus.com/reference/cstdlib/rand/ << função de geração de valores aleatórios
 */

#include "particulas.h"
#include <math.h>
#include <stdlib.h>

namespace dudu {

particulas::particulas(): m_x(0), m_y(0)
{

	start();

}

void particulas::start()
{
	m_x =0;
	m_y =0;

	m_praondevai = (2 * M_PI * rand())/RAND_MAX;
	m_velocidade = (0.04 * rand())/RAND_MAX;   // velocidade de expansão
	m_velocidade *= m_velocidade; // adicionando o quadrado da velocidade.

}

particulas::~particulas()
{
	// TODO Auto-generated destructor stub
}

void particulas::recoloca(int intervalo)
{

	m_praondevai += intervalo * 0.0004;

double m_velox = m_velocidade * cos(m_praondevai);
double m_veloy = m_velocidade * sin(m_praondevai);

m_x += m_velox * intervalo; // homogenizando a velocidade
m_y += m_veloy * intervalo; // homogenizando a velocidade

if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1)
{
	particulas::start();
}
	if(rand() < RAND_MAX/100)
	{
		particulas::start();
	}
}

} /* namespace dudu */
