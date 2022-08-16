/*
 * Tela.cpp
 *
 *  Created on: 8 de ago. de 2022
 *      Author: Eduardo
 */

#include "Tela.h"
#include "cstring"

namespace dudu {

Tela::Tela(): m_window(NULL), m_renderizador(NULL), m_textura(NULL), m_buffer(NULL), m_buffer2(NULL) // não posso esquecer dos 2 pontos
{

}

bool Tela::inicia()
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	m_window = SDL_CreateWindow("Explosão de Partículas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if(m_window == NULL)
	{
		SDL_Quit();
		return false;
	}

	// bloco de criação e verificação de renderizador e textura
	m_renderizador = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC );// traduzindo os parênteses : o primeiro usa a janela criada, o segundo o indexador, e o terceiro são as flags possiveis - https://wiki.libsdl.org/SDL_RendererFlags
	m_textura = SDL_CreateTexture(m_renderizador, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderizador == NULL)
	{
	//	cout << "não foi possivel criar o renderizador" << endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_textura == NULL)
	{
	//	cout << "não foi possivel criar a textura" << endl;
		SDL_DestroyRenderer(m_renderizador);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer  = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

	//programa o buffer pra ficar com o alpha de 100% (255) e o tamanho da tela multiplicado pelo tamanho do Uint32
	memset(m_buffer, 0,SCREEN_WIDTH * SCREEN_HEIGHT* sizeof(Uint32));
	memset(m_buffer2, 0,SCREEN_WIDTH * SCREEN_HEIGHT* sizeof(Uint32));
	// memset(buffer, 0xFF,SCREEN_WIDTH * SCREEN_HEIGHT* sizeof(Uint32)); // pode ser assim também..

	return true;
}
bool Tela::processaEvento() // existe somente para validar se continua rodando ou não.
{
	SDL_Event evento;
	while(SDL_PollEvent(&evento))
			{
				if(evento.type == SDL_QUIT)
				{
					return false;
				}
			}
	return true;
}

void Tela::Limpeza()  // crio que ficará inútil , aí eu desativo
{
	memset(m_buffer, 0,SCREEN_WIDTH * SCREEN_HEIGHT* sizeof(Uint32));
	memset(m_buffer2, 0,SCREEN_WIDTH * SCREEN_HEIGHT* sizeof(Uint32));
}


void Tela::setaPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) // essa função pega o pixel da vez e atribui a cor , usando um método de movimento de bit de informação
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}


	Uint32 color = 0; // tem que começar zerado, eu tava começando em vermelho

	color += red; // acrescenta a informação nova
	color <<= 8; // operador de bitshifting , desloca a informação toda 8 bytes para o lado
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xff;
	m_buffer[(y * SCREEN_WIDTH) + x] = color;


}

void Tela::atualiza() // bloco responsável por atualizar, limpar, carregar a nova cópia de conteúdo e exibir o frame.
{
		SDL_UpdateTexture(m_textura, NULL, m_buffer,SCREEN_WIDTH* sizeof(Uint32));//o ultimo parâmetro é o pitch, que é uma coluna de pixels
		SDL_RenderClear(m_renderizador);
		SDL_RenderCopy(m_renderizador, m_textura, NULL,NULL);
		SDL_RenderPresent(m_renderizador);
}

void Tela::BoxBorra()
{
	Uint32 *temp = m_buffer;
	m_buffer = m_buffer2;
	m_buffer2 = temp;

	for(int y=0; y < SCREEN_HEIGHT; y++)
	{
		for(int x=0; x<SCREEN_WIDTH; x++)
		{

			int RedTotal=0;
			int BlueTotal=0;
			int GreenTotal=0;

			for (int linha=-1; linha <=1; linha++)
				{
				 for(int col =-1; col <=1; col++)
				 	 {
					 int Xatual = x + col;
					 int Yatual = y + linha;

					 if (Xatual >= 0 && Xatual < SCREEN_WIDTH && Yatual >= 0 && Yatual < SCREEN_HEIGHT)
					 	 {
						 Uint32 cor = m_buffer2[Yatual*SCREEN_WIDTH + Xatual];

						 Uint8 red = cor >>  24; // sim eu movi 24 bits numa variavel de 32, pq o vaolume de dados movido é de 8 que somado a 24 dá 32...
						 Uint8 green = cor >>  16;
						 Uint8 blue = cor >>  8;

						 RedTotal   += red;
						 GreenTotal += green;
						 BlueTotal  += blue;

					 	 }
				 	 }
				}

			Uint8 red = RedTotal/9;
			Uint8 green =GreenTotal/9;
			Uint8 blue = BlueTotal/9;

			Tela::setaPixel(x, y, red, green, blue);
		}
	}

}

void Tela::fecha() //bloco de encerramento do programa, nescessário para destruir a todos no final do programa
{
		delete [] m_buffer;
		delete [] m_buffer2;
		SDL_DestroyRenderer(m_renderizador);
		SDL_DestroyTexture(m_textura);
		SDL_DestroyWindow(m_window);
		SDL_Quit();

}

Tela::~Tela() {
	// TODO Auto-generated destructor stub
}

} /* namespace dudu */

