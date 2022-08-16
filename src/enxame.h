/*
 * enxame.h
 *
 *  Created on: 12 de ago. de 2022
 *      Author: Eduardo
 */

#ifndef ENXAME_H_
#define ENXAME_H_

#include "particulas.h"

namespace dudu {

class enxame {
private:
	particulas * m_pParticulasmaneiras;
	int ultimavez;


public: // variáveis , constantes e estáticas
const static int NPARTICULAS =5000;

public:
	enxame();
	virtual ~enxame();
	void enxameatualizado(int tempopassado);

	const particulas * const getParticulas() {return m_pParticulasmaneiras; };
};

} /* namespace dudu */

#endif /* ENXAME_H_ */
