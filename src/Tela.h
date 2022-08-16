/*
 * Tela.h
 *
 *  Created on: 8 de ago. de 2022
 *      Author: Eduardo
 */

#ifndef TELA_H_
#define TELA_H_
#include "SDL.h"

namespace dudu {

class Tela {

//constantes estáticas
public:
	const static int SCREEN_WIDTH =800;
	const static int SCREEN_HEIGHT = 600;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderizador;
	SDL_Texture *m_textura;
	Uint32 *m_buffer;
	Uint32 *m_buffer2;

//métodos públicos
public:
	Tela();
	virtual ~Tela();
	bool inicia();
	bool processaEvento();
	void atualiza();
	void setaPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void fecha();
	void Limpeza();
	void BoxBorra();

};

} /* namespace dudu */

#endif /* TELA_H_ */
