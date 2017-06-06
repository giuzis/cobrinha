#include "cobrinha2.h"

int main()
{
	ALLEGRO_FONT *font = NULL;
    srand((unsigned)time(NULL));


    bool sair = false;
    int velocidade = 5;
    ALLEGRO_BITMAP* maca;
    Inicializa inicio;
    Fundo fundo;
    Cobrinha cobrinha;
    Eventos evento;
    Comandos comandos;
    Maca maca1(&cobrinha), maca2(&cobrinha);

    inicio.inicializaFont(&font);

    fundo.imprime();
    maca1.imprime();
    maca2.imprime();
    al_flip_display();


    while (!sair)
    {
        sair = evento.confereEvento(velocidade, &cobrinha, &comandos);
    }

    //TESTES INICIAS DA MOVIMENTAÇÃO
    // cobrinha.imprime();
    // al_flip_display();
    // al_rest(0.5);
    // cobrinha.moveParaDireita();
    // cobrinha.imprime();
    // al_flip_display();
    // al_rest(0.5);
    // cobrinha.moveParaDireita();
    // cobrinha.imprime();
    // al_flip_display();
    // al_rest(0.5);
    // cobrinha.moveParaDireita();
    // cobrinha.imprime();
    // al_flip_display();
    // al_rest(0.5);
    // cobrinha.moveParaDireita();
    // cobrinha.imprime();
    // al_flip_display();
    // al_rest(0.5);

    // TESTANDO SEGMENTO
    // Segmento segmento(10,6);
    // segmento.imprime();

    // TESTANDO ROUNDED RECTANGLE
    //al_draw_filled_rounded_rectangle(100, 100, 120, 120, 5, 5, al_map_rgb(0,0,0));

	// criaBitmap bitmap;
 //    Cobrinha cobrinha;

 //    //Iniciamos o Allegro
 //    if(!al_init()) {
 //        cout << "failed to initialize allegro!\n";
 //        return -1;
 //    }

 //    // Inicializa o add-on para utilização de imagens
 //    al_init_image_addon();


 //    display = al_create_display(SCREEN_W, SCREEN_H);
 //    if(!display) {
 //        cout << "failed to create display!\n";
 //        return -1;
 //    }

 //    if(bitmap.imagemDeFundo() == -1)
 //      return -1;

 //    bitmap.imprimeFundo();

 //    cobrinha.imprimeCobrinha();

 //    al_set_target_bitmap(al_get_backbuffer(display));


 //    while(1)
 //    {
 //        al_rest(0.15);
 //        bitmap.imprimeFundo();
 //        cobrinha.mover();
 //        al_flip_display();
 //    }



	al_destroy_font(font);
   	cout << "Destruiu font." << endl;

	return 0;
}
