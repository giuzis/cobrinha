//ver tamanho max cobrinha

#include "cobrinha.hpp"

int main()
{
	ALLEGRO_FONT *font = NULL;
    srand((unsigned)time(NULL));

    bool sair = false;
    int velocidade = 4;
    Inicializa inicio;
    Fundo fundo;
    Cobrinha cobrinha;
    Veneno* veneno;
    int n_venenos = 1;
    Eventos evento;
    Comandos comandos;
    GameOver fim;
    Pontuacao pontuacao;
    Colisoes colisoes;
    Maca maca;
    int maca_comida = 0;
    bool morre = false;

    inicio.inicializaFont(&font);

    fundo.menu(font);
    sair = evento.confereMenu();

    if(!sair)
    {
    	fundo.imprime(font);
    	maca.novaMaca(&cobrinha);
    	veneno = new Veneno [100];
    	veneno[0].novoVeneno(&cobrinha, &maca);
    	maca.imprime();
    	al_flip_display();
    }


    while (!sair)
    {
        sair = evento.confereEvento(velocidade, &cobrinha, &comandos);
        if(colisoes.confereColisoesMaca(&maca, &cobrinha, veneno, n_venenos))
        {
            maca_comida++;
            pontuacao.setPontos();
            al_draw_filled_rectangle(615, 539, 800, 600, al_map_rgb(120, 139, 70));
            pontuacao.imprime(font);
        }

        if(maca_comida == 3)  // aumenta a velocidade a cada 5 maçãs
        {
            velocidade--;
            maca_comida = 0;
            veneno[n_venenos].novoVeneno(&cobrinha, &maca, veneno, n_venenos);
            n_venenos++;
        }

        for(int j = 0; j < n_venenos; j++)
        {
            if(!morre)
            {
                morre = veneno[j]+&cobrinha;
            }
        }

        if(!morre)
            morre = colisoes.confereColisoesParede(&cobrinha);

        if(!morre)
            morre = colisoes.confereColisoesCorpo(&cobrinha);

        if(morre)
        {
        	evento.para();
            fim.imprime(font, pontuacao.getPontos());
            while(!evento.confereMenu());
            sair = true;
        }
    }

    delete[] veneno;

	return 0;
}
