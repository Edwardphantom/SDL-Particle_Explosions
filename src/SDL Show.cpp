//============================================================================
// Name        : SDL.cpp
// Author      : Eduardo Fernandes Larrubia
// Version     :
// Copyright   : Sem copyright neste momento
// Description : Hello World in C++, Ansi-style
// link importante : https://stackoverflow.com/questions/32342285/undefined-reference-to-winmain16-c-sdl-2/32343111#32343111
// nota do eduardo : Deixar as bibliotecas junto do binário no debug faz o terminal abrir corretamente.
//============================================================================

#define SDL_MAIN_HANDLED // FOOOKKKK -> without this my software simply quebra e pára de funcionar

#include "Tela.h"
#include "enxame.h"
#include <SDL.h>
#include <math.h>
#include <time.h>
#include <cstring> // sem isso o memset não funciona ! preciso disso pro memset funcionar
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace dudu;

int main() {

	srand(time(NULL));

	Tela telinha;
	if(telinha.inicia() == false)
	{
		cout << "erro inicializando o SDL" << endl;
	}


	enxame zerg1;

	while(true)
	{
				int passado = SDL_GetTicks(); // explicação da mágica : obtemos o inteiro a partir do "tick" registrado no SDL, com isso temos um valor aleatorio

			//	telinha.Limpeza();

				zerg1.enxameatualizado(passado);

				unsigned char red   = (unsigned char)((1 + sin(passado * 0.0001)) * 128); // fizemos o valor variar entre 0.001 e 0.003 para ter alguma variação nas cores
				unsigned char green = (unsigned char)((1 + sin(passado * 0.0002)) * 128); // deste valor nós multiplicamos por 0.001 e  obtemos o Seno (sin) , multiplicamos novamente por 1 e depois tudo por 128
				unsigned char blue  = (unsigned char)((1 + cos(passado * 0.0003)) * 128); // aqui usamos o coseno para dar um ponto de partida mais colorido
				// e então obtemos um range de valor trabalhável para nosso programa, no caso aqui entre 255.484 e 0.00123284. legal né ?
				// mudamos tb de 0.001 para 0.0001 para que fique *muito* mais lenta e suave. só que eu não gostei e deixei como estava antes

				// a linha de código usava um double, passando a usar um simples int nós obtemos o valor arredondado entre 0 e 255 que é o que queremos !
				// double blue = (1 + sin(passado * 0.001)) * 128 ;

				// a linha de codigo abaixo usava um inteiro pra limitar entre 0 e 255 , porém se usarmos esse valor pra um  char sem sinal de positivo/negativo
				// nós obtemos uma transição mais suave e solida dando um efeito bem melhor
				// int blue = (1 + sin(passado * 0.001)) * 128 ;

		const particulas * const pParticulas = zerg1.getParticulas();

		for (int i=0; i < enxame::NPARTICULAS; i++ )
		{
			particulas particulas1 = pParticulas[i];

			int x = (particulas1.m_x + 1) * Tela::SCREEN_WIDTH/2;					// não é má ideia transformar isso numa constante pra evitar recalcular tudo toda santa vez.
			int y = particulas1.m_y * Tela::SCREEN_WIDTH/2 + Tela::SCREEN_HEIGHT/2;

			telinha.setaPixel(x,y,red,green,blue);
		}

		telinha.BoxBorra();

		telinha.atualiza();

		if(telinha.processaEvento() ==false)
		{
			break;
		}

	}

telinha.fecha();
	return 0;
}
