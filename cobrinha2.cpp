<<<<<<< HEAD
#include "cobrinha2.h"

//KEY_UP KEY_DOWN KEY_LEFT KEY_RIGHT
bool teclas[4] = {false, false, false, true};

enum TECLAS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

Segmento::Segmento(int x_inicial, int y_inicial)
{
    x = x_inicial;
    y = y_inicial;
}

void Segmento::imprime()
{
    al_draw_filled_rounded_rectangle((x-1)*20, (y-1)*20, x*20, y*20, 5, 5, al_map_rgb(0,0,0));
}

void Segmento::incrementaX()
{
    x++;
}

void Segmento::incrementaY()
{
    y++;
}

void Segmento::decrementaX()
{
    x--;
}

void Segmento::decrementaY()
{
    y--;
}

void Segmento::setX(int novo_x)
{
    x = novo_x;
}

void Segmento::setY(int novo_y)
{
    y = novo_y;
}

int Segmento::getX()
{
    return x;
}

int Segmento::getY()
{
    return y;
}

Segmento::~Segmento()
{
    cout << "segmento destruido" << endl;
}

Maca::Maca(Cobrinha* cobrinha)
{
	bool igual = false;
	maca = al_load_bitmap("maca.png");
	x = rand() % 33 + 4;
	y = rand() % 19 + 6;

	if(!maca)
	{
		cout << "N�o carregou ma��. " << endl;
	}

	while(!igual)
	{
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getX() == x)
				igual = false;
		}
	}
	igual = false;
	while(!igual)
	{
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getY() == y)
				igual = false;
		}
	}
}

int Maca::getX()
{
	return x;
}

int Maca::getY()
{
	return y;
}

void Maca::imprime()
{
	al_draw_bitmap(maca, x*20, y*20, 0);
}

Maca::~Maca()
{
	al_destroy_bitmap(maca);
}

Cobrinha::Cobrinha()
{
    x = rand() % 20 + 8;
	y = rand() % 19 + 6;
    tamanho = 3;
    segmentos = new Segmento*[tamanho_maximo];
    for(int i = 0; i < tamanho; i++)
    {
        segmentos[i] = new Segmento(x-i, y);
    }
    cout << "cobrinha criada" << endl;
}

void Cobrinha::movimenta()
{
    int x = segmentos[tamanho-1]->getX();
    int y = segmentos[tamanho-1]->getY();
    al_draw_filled_rectangle((x-1)*20, (y-1)*20, x*20, y*20, al_map_rgb(120, 139, 70)); // apaga rastro
    for(int i = tamanho-1; i > 0; i--)
    {
        segmentos[i]->setX(segmentos[i-1]->getX());
        segmentos[i]->setY(segmentos[i-1]->getY());
    }
}

void Cobrinha::moveParaDireita()
{
    movimenta();
    segmentos[0]->incrementaX();
}

void Cobrinha::moveParaEsquerda()
{
    movimenta();
    segmentos[0]->decrementaX();
}

void Cobrinha::moveParaCima()
{
    movimenta();
    segmentos[0]->decrementaY();
}

void Cobrinha::moveParaBaixo()
{
    movimenta();
    segmentos[0]->incrementaY();
}

void Cobrinha::imprime()
{
    for(int i = 0; i < tamanho; i++)
    {
        segmentos[i]->imprime();
    }
}

Cobrinha::~Cobrinha()
{
    for(int i = 0; i < tamanho; i++)
    {
        delete segmentos[i];
    }
    delete[] segmentos;
    cout << "cobrinha destruida" << endl;
}

Fundo::Fundo()
{
    cout << "Inicializa fundo " << endl;
    parede[0] = 3;
    parede[1] = 5;
    parede[2] = 37;
    parede[3] = 25;
}

void Fundo::imprime()
{
    cout << "Imprime fundo " << endl;
    int i = 0;

    al_draw_filled_rectangle(0.0, 0.0, 800.0, 600.0, al_map_rgb(120, 139, 70));

    for(i = parede[1]-1; i < parede[3]+1; i++)
        al_draw_filled_rounded_rectangle((parede[0]-1)*20, i*20, parede[0]*20, (i+1)*20, 5, 5, al_map_rgb(0,0,0));

    for(i = parede[0]-1; i < parede[2]+1; i++)
        al_draw_filled_rounded_rectangle(i*20, (parede[1]-1)*20, (i+1)*20, parede[1]*20, 5, 5, al_map_rgb(0,0,0));

    for(i = parede[1]-1; i < parede[3]+1; i++)
        al_draw_filled_rounded_rectangle(parede[2]*20, i*20, (parede[2]+1)*20, (i+1)*20, 5, 5, al_map_rgb(0,0,0));

    for(i = parede[0]-1; i < parede[2]+1; i++)
        al_draw_filled_rounded_rectangle(i*20, parede[3]*20, (i+1)*20, (parede[3]+1)*20, 5, 5, al_map_rgb(0,0,0));

    /* para colocar as parede cont�nuas */
    //al_draw_rectangle(parede[0], parede[1], parede[2], parede[3], al_map_rgb(0,0,0), 6.0);
}

Inicializa::Inicializa()
{
    cout << "Inicializa " << endl;
    if(!al_init())
    {
        cout << "failed to initialize allegro!\n";
    }

    if (!al_install_mouse())
    {
        cout << "Falha ao inicializar o mouse.\n";
    }

    if(!al_install_keyboard()) 
    {
        cout << "failed to initialize the keyboard!\n";
    }
    if(!al_init_primitives_addon())
    {
        cout << "failed to initialize allegro primitives!\n";
    }
    if(!al_init_image_addon())
    {
        cout << "failed to initialize the al_init_image_addon!\n";
    }
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon();// initialize the ttf (True Type Font) addon
}

void Inicializa::inicializaFont(ALLEGRO_FONT **font)
{
    cout << "Inicializa Font" << endl;
    *font = al_load_ttf_font("pirulen.ttf", 12,0 );

    //N�O CONSEGUE CARREGAR FONTE, DESCOBRIR POR QUE
    if (!(*font))
    {
        cout << "Could not load 'pirulen.ttf'.\n";
    }
}

Inicializa::~Inicializa()
{ }

Timer::Timer(float _tempo)
{
    tempo = _tempo;
    cout << "Inicializa timer" << endl;
    timer = al_create_timer(tempo);
    if(!timer) {
        cout << "failed to create timer!\n";
    }
    al_start_timer(timer);
}

Timer::~Timer()
{
    al_destroy_timer(timer);
    cout << "Destruiu timer." << endl;
}

Display::Display()
{
    cout << "Inicializa display" << endl;
    display = al_create_display(SCREEN_W, SCREEN_H);
    al_set_window_title(display, "Meu Jogo");

    if(!display) {
        cout << "failed to create display!\n";
    }

    if (!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        cout << "Falha ao atribuir ponteiro do mouse.\n";
    }
}

Display::~Display()
{
    al_destroy_display(display);
    cout << "Destruiu display." << endl;
}

Comandos::Comandos()
{ }

void Comandos::confereComandosCobrinha(Cobrinha *cobrinha)
{
    if(teclas[KEY_UP])
    {
        cobrinha->moveParaCima();
    }
    if(teclas[KEY_DOWN])
    {
        cobrinha->moveParaBaixo();
    }
    if(teclas[KEY_LEFT])
    {
        cobrinha->moveParaEsquerda();
    }
    if(teclas[KEY_RIGHT])
    {
        cobrinha->moveParaDireita();
    }
}

Comandos::~Comandos()
{ }

int Eventos::direcao[4] = {1, 1, 1, 1};
int Eventos::conta_timer = 0;

Eventos::Eventos() : Timer(0.10), Display()
{
    event_queue = al_create_event_queue();
    if(!event_queue) {
        cout << "failed to create event_queue!\n";
    }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}

//Depend�ncia com cobrinha e comandos
bool Eventos::confereEvento(int velocidade, Cobrinha* cobrinha, Comandos* comandos)
{
    if (!al_is_event_queue_empty(event_queue))
    {
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER)
        {
        	if(conta_timer < velocidade)
        		conta_timer++;
        	else
        	{
            	comandos->confereComandosCobrinha(cobrinha);
            	cobrinha->imprime();
            	al_flip_display();
            	direcao[KEY_UP] = teclas[KEY_UP];
            	direcao[KEY_DOWN] =  teclas[KEY_DOWN];
            	direcao[KEY_LEFT] =  teclas[KEY_LEFT];
            	direcao[KEY_RIGHT] =  teclas[KEY_RIGHT];
            	conta_timer = 0;
            }
        }
        else
        {
            if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                return true;
        }
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch(event.keyboard.keycode)
            {
            case ALLEGRO_KEY_UP:
            	// if(teclas[KEY_DOWN]);
            	// else
            	// {
            		if(direcao[KEY_LEFT] || direcao[KEY_RIGHT])
            		{
                		teclas[KEY_UP] = true;
                		teclas[KEY_DOWN] = false;
                		teclas[KEY_LEFT] = false;
                		teclas[KEY_RIGHT] = false;
                	}
            	// }
                break;

            case ALLEGRO_KEY_DOWN:
            	// if(teclas[KEY_UP]);
            	// else
            	// {
            		if(direcao[KEY_LEFT] || direcao[KEY_RIGHT])
            		{
                		teclas[KEY_UP] = false;
                		teclas[KEY_DOWN] = true;
                		teclas[KEY_LEFT] = false;
                		teclas[KEY_RIGHT] = false;
                	}
                // }
                break;

            case ALLEGRO_KEY_LEFT:
            	// if(teclas[KEY_RIGHT]);
            	// else
            	// {
            		if(direcao[KEY_UP] || direcao[KEY_DOWN])
            		{
   						teclas[KEY_UP] = false;
   						teclas[KEY_DOWN] = false;
   						teclas[KEY_LEFT] = true;
   						teclas[KEY_RIGHT] = false;
   					}
   				// }
                break;

            case ALLEGRO_KEY_RIGHT:
            	// if(teclas[KEY_LEFT]);
            	// else
            	// {
            		if(direcao[KEY_UP] || direcao[KEY_DOWN])
            		{
                		teclas[KEY_UP] = false;
                		teclas[KEY_DOWN] = false;
                		teclas[KEY_LEFT] = false;
                		teclas[KEY_RIGHT] = true;
                	}
                // }
                break;
            }
        }
    }
    return false;
}

Eventos::~Eventos()
{
    al_destroy_event_queue(event_queue);
=======
/*
ANOTAÇÕES

TEM UMA PERGUNTA EM ALGUMA CLASSE
QUAL A DIFERENÇA ENTRE ESFECIFICADOR DE ACESSO E ENCAPSULAMENTO


Colocar maçã mordida com pontuação ao lado
interface imprime - filhas maçã, cobrinha e veneno
colocar uma inicializa em timer e em display (ver se dá para fazer superposição ou sobreposição)


*/

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

const float FPS = 60;

const int SCREEN_W = 800;
const int SCREEN_H = 600;

bool comAudio = true;

//KEY_UP KEY_DOWN KEY_LEFT KEY_RIGHT
bool teclas[4] = {false, false, false, false};

enum TECLAS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

//cada segmento 20x20
class Segmento
{
	int x;
	int y;
public:
	Segmento(int x_inicial, int y_inicial)
	{
		x = x_inicial;
		y = y_inicial;
	}
	void imprime()
	{
		al_draw_filled_rounded_rectangle((x-1)*20, (y-1)*20, x*20, y*20, 5, 5, al_map_rgb(0,0,0));
	}
    void incrementaX()
	{
		x++;
	}
	void incrementaY()
	{
        y++;
	}
	void decrementaX()
	{
		x--;
	}
	void decrementaY()
	{
        y--;
	}
	void setX(int novo_x)
	{
		x = novo_x;
	}
	void setY(int novo_y)
	{
		y = novo_y;
	}
    int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
    ~Segmento()
    {
        cout << "segmento destruido" << endl;
    }
};

//Relação de composição com segmentos
class Cobrinha 
{
	int tamanho, x, y;
	static const int tamanho_maximo = 30;
	Segmento **segmentos;
public:
	Cobrinha()
	{
		x = 18;
		y = 18;
		tamanho = 8;
		segmentos = new Segmento*[tamanho_maximo];
		for(int i = 0; i < tamanho; i++)
        {
            segmentos[i] = new Segmento(x-i, y);
        }
        cout << "cobrinha criada" << endl;
	}
	void moveParaDireita()
	{
		int x = segmentos[tamanho-1]->getX();
		int y = segmentos[tamanho-1]->getY();
		al_draw_filled_rectangle((x-1)*20, (y-1)*20, x*20, y*20, al_map_rgb(120, 139, 70));
        for(int i = tamanho-1; i > 0; i--)
        {
            segmentos[i]->setX(segmentos[i-1]->getX());
        }
        segmentos[0]->incrementaX();

	}
	void moveParaEsquerda()
	{
		int x = segmentos[tamanho-1]->getX();
		int y = segmentos[tamanho-1]->getY();
		al_draw_filled_rectangle((x-1)*20, (y-1)*20, x*20, y*20, al_map_rgb(120, 139, 70));
        for(int i = tamanho-1; i > 0; i--)
        {
            segmentos[i]->setX(segmentos[i-1]->getX());
        }
        segmentos[0]->incrementaX();

	}
	void moveParaCima()
	{
		int x = segmentos[tamanho-1]->getX();
		int y = segmentos[tamanho-1]->getY();
		al_draw_filled_rectangle((x-1)*20, (y-1)*20, x*20, y*20, al_map_rgb(120, 139, 70));
        for(int i = tamanho-1; i > 0; i--)
        {
            segmentos[i]->setX(segmentos[i-1]->getX());
        }
        segmentos[0]->incrementaX();

	}
	void moveParaBaixo()
	{
		int x = segmentos[tamanho-1]->getX();
		int y = segmentos[tamanho-1]->getY();
		al_draw_filled_rectangle((x-1)*20, (y-1)*20, x*20, y*20, al_map_rgb(120, 139, 70));
        for(int i = tamanho-1; i > 0; i--)
        {
            segmentos[i]->setX(segmentos[i-1]->getX());
        }
        segmentos[0]->incrementaX();

	}
  	void imprime()
  	{
        for(int i = 0; i < tamanho; i++)
        {
            segmentos[i]->imprime();
        }
  	}
	~Cobrinha()
	{
        for(int i = 0; i < tamanho; i++)
        {
            delete segmentos[i];
        }
        delete[] segmentos;
        cout << "cobrinha destruida" << endl;
	}
	//friend void Eventos::confereEventos(Cobrinha* cobrinha, Comandos* comandos);
	//friend void Comandos::confereComandosCobrinha(Cobrinha* cobrinha);
};

class Fundo
{
	int parede[4]; //0 - parede esquerda; 1 - parede de cima; 2 - parede direita; 3 - parede de baixo; 
public:
	Fundo()
	{
		cout << "Inicializa fundo " << endl;
		parede[0] = 3;
		parede[1] = 5;
		parede[2] = 37;
		parede[3] = 25;
	}

  	void imprime()
  	{
  		cout << "Imprime fundo " << endl;
  		int i = 0;

  		al_draw_filled_rectangle(0.0, 0.0, 800.0, 600.0, al_map_rgb(120, 139, 70));

		for(i = parede[1]-1; i < parede[3]+1; i++)
			al_draw_filled_rounded_rectangle((parede[0]-1)*20, i*20, parede[0]*20, (i+1)*20, 5, 5, al_map_rgb(0,0,0));
		
		for(i = parede[0]-1; i < parede[2]+1; i++)
			al_draw_filled_rounded_rectangle(i*20, (parede[1]-1)*20, (i+1)*20, parede[1]*20, 5, 5, al_map_rgb(0,0,0));
			
		for(i = parede[1]-1; i < parede[3]+1; i++)
			al_draw_filled_rounded_rectangle(parede[2]*20, i*20, (parede[2]+1)*20, (i+1)*20, 5, 5, al_map_rgb(0,0,0));
		
		for(i = parede[0]-1; i < parede[2]+1; i++)
			al_draw_filled_rounded_rectangle(i*20, parede[3]*20, (i+1)*20, (parede[3]+1)*20, 5, 5, al_map_rgb(0,0,0));

		/* para colocar as parede contínuas */
        //al_draw_rectangle(parede[0], parede[1], parede[2], parede[3], al_map_rgb(0,0,0), 6.0);
  	}
};

class Inicializa
{
public:
	Inicializa()
	{
		cout << "Inicializa " << endl;
   		if(!al_init()) 
   		{
   		   cout << "failed to initialize allegro!\n";
   		}

   		if (!al_install_mouse())
	   	{
	   	    cout << "Falha ao inicializar o mouse.\n";
	   	}

   		if(!al_install_keyboard()) {
   		   cout << "failed to initialize the keyboard!\n";
   		}
   		if(!al_init_primitives_addon()){
   			cout << "failed to initialize allegro primitives!\n";
   		}
	}
	
	void inicializaFont(ALLEGRO_FONT **font)
	{
		cout << "Inicializa Font" << endl;
		*font = al_load_ttf_font("pirulen.ttf", 12,0 );
		al_init_font_addon(); // initialize the font addon
   		al_init_ttf_addon();// initialize the ttf (True Type Font) addon
		
		if(!al_init_image_addon()) 
		{
		   cout << "failed to initialize the al_init_image_addon!\n";
		}
	
		//NÃO CONSEGUE CARREGAR FONTE, DESCOBRIR POR QUE
	   	if (!(*font))
	   	{
	   	   cout << "Could not load 'pirulen.ttf'.\n";
	   	}
	}
   
   	~Inicializa()
   	{}
};


//Tem que ficar criando e destruindo para alterar a velocidade da cobrinha?
class Timer
{
protected:
	ALLEGRO_TIMER *timer = NULL;
	int tempo;

	Timer(int _tempo)
   	{
   		tempo = _tempo;
   		cout << "Inicializa timer" << endl;
   		timer = al_create_timer(tempo);
   		if(!timer) {
	   	   cout << "failed to create timer!\n";
	   	}
	   	al_start_timer(timer);
   	}
   	// void setTimer()
   	// {

   	// }
   	~Timer()
   	{
   		al_destroy_timer(timer);
   		cout << "Destruiu timer." << endl;
   	}
};

class Display
{
protected:
	ALLEGRO_DISPLAY *display = NULL;

	Display()
	{
		cout << "Inicializa display" << endl;
		display = al_create_display(SCREEN_W, SCREEN_H);
		al_set_window_title(display, "Meu Jogo");

		if(!display) {
	   	   cout << "failed to create display!\n";
	   	}

	   	if (!al_set_system_mouse_cursor(display, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
   		{
   		    cout << "Falha ao atribuir ponteiro do mouse.\n";
   		}
	}
	~Display()
	{
		al_destroy_display(display);
   		cout << "Destruiu display." << endl;
	}
};


class Comandos
{
public:
	Comandos(){}
	void confereComandosCobrinha(Cobrinha *cobrinha)
	{
		if(teclas[KEY_UP])
		{
			cobrinha->moveParaCima();
		}
		if(teclas[KEY_DOWN])
		{
			cobrinha->moveParaBaixo();
		}
		if(teclas[KEY_LEFT])
		{
			cobrinha->moveParaEsquerda();
		}
		if(teclas[KEY_RIGHT])
		{
			cobrinha->moveParaDireita();
		}
	}
	~Comandos(){}
	//friend void Eventos::confereEventos(Cobrinha* cobrinha, Comandos* comandos);
};

//Herança múltipla
class Eventos: public Timer, public Display
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT event;
public:
	Eventos() : Timer(1.0), Display()
	{
		event_queue = al_create_event_queue();
   		if(!event_queue) {
   		   cout << "failed to create event_queue!\n";
   		}
   		al_register_event_source(event_queue, al_get_display_event_source(display));
    	al_register_event_source(event_queue, al_get_timer_event_source(timer));
    }

	//Dependência com cobrinha e comandos
	bool confereEvento(Cobrinha *cobrinha, Comandos* comandos)
	{
		if (!al_is_event_queue_empty(event_queue))
        {
            al_wait_for_event(event_queue, &event);
 
            if (event.type == ALLEGRO_EVENT_TIMER)
            {
            	comandos->confereComandosCobrinha(cobrinha);
                cobrinha->imprime();
                al_flip_display();
            }
            else 
           	{
           		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
           		    return false;  
           	}

           	if(event.type == ALLEGRO_EVENT_KEY_DOWN)
      		{
      		    switch(event.keyboard.keycode) 
      		    {
            	case ALLEGRO_KEY_UP:
            		teclas[KEY_UP] = true;
            		teclas[KEY_DOWN] = false;
            		teclas[KEY_LEFT] = false;
            		teclas[KEY_RIGHT] = false;
            	    break;
	
	            case ALLEGRO_KEY_DOWN:
	            	teclas[KEY_UP] = false;
            		teclas[KEY_DOWN] = true;
            		teclas[KEY_LEFT] = false;
            		teclas[KEY_RIGHT] = false;
	            	break;
	
	            case ALLEGRO_KEY_LEFT:
	               	teclas[KEY_UP] = false;
            		teclas[KEY_DOWN] = false;
            		teclas[KEY_LEFT] = true;
            		teclas[KEY_RIGHT] = false;
	               	break;
	
	            case ALLEGRO_KEY_RIGHT:
	            	teclas[KEY_UP] = false;
            		teclas[KEY_DOWN] = false;
            		teclas[KEY_LEFT] = false;
            		teclas[KEY_RIGHT] = true;
            	   	break;      		
            	}
            }
      	}
      	return true;
	}
	~Eventos()
	{
		al_destroy_event_queue(event_queue);
	}
};

int main()
{
	ALLEGRO_FONT *font = NULL;
    srand((unsigned)time(NULL));


    bool sair = false;
    Inicializa inicio;
    Fundo fundo;
    Cobrinha cobrinha;
    Eventos evento;
    Comandos comandos;

    inicio.inicializaFont(&font);

    fundo.imprime();
    cobrinha.imprime();
    al_flip_display();


    while (!sair)
    {
        sair = evento.confereEvento(&cobrinha, &comandos);
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
>>>>>>> c231c26369ed72ff12211a0f0d078cb98bbaa374
}
