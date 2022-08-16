/*
 * particulas.h
 *
 *  Created on: 12 de ago. de 2022
 *      Author: Eduardo
 */

#ifndef PARTICULAS_H_
#define PARTICULAS_H_
#include <stdlib.h>

namespace dudu {

struct particulas {

	double m_x ;
	double m_y;

private:
	double m_velocidade;
	double m_praondevai;

	double m_velox = 0.001 * (((2.0 * rand())/RAND_MAX) -1);
	double m_veloy = 0.001 * (((2.0 * rand())/RAND_MAX) -1);

private:
	void start();

public:
	particulas();
	virtual ~particulas();
	void recoloca(int intervalo);
};

} /* namespace dudu */

#endif /* PARTICULAS_H_ */
