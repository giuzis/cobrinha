#include "cobrinha.hpp"
#include <string>

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
    al_draw_filled_rounded_rectangle((x-1)*DIVISAO, (y-1)*DIVISAO, x*DIVISAO, y*DIVISAO, 5, 5, al_map_rgb(0,0,0));
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

Maca::Maca()
{
	numero_macas = 1;
	maca = al_load_bitmap("maca.png");

	if(!maca)
	{
		cout << "N�o carregou ma��. " << endl;
	}
}

int Maca::getX()
{
	return (x);
}

int Maca::getY()
{
	return (y);
}

void Maca::novaMaca(Cobrinha* cobrinha)
{
	cout << "nova maca" << endl;
	bool igual = false;

	while(!igual)
	{
		x = rand() % 33 + 4;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getX() == x)
			{
				igual = false;
			}
		}
	}
	igual = false;
	while(!igual)
	{
		y = rand() % 19 + 6;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getY() == y)
			{
				igual = false;
			}
		}
	}
}

void Maca::novaMaca(Cobrinha* cobrinha, Veneno* veneno, int n_veneno)
{
	cout << "nova maca" << endl;
	bool igual = false;

	while(!igual)
	{
		x = rand() % 33 + 4;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getX() == x)
			{
				igual = false;
			}
		}
		for(int i = 0; i < n_veneno; i++)
		{
			if(veneno[i].getX() == x)
			{
				igual = false;
			}
		}
	}
	igual = false;
	while(!igual)
	{
		y = rand() % 19 + 6;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getY() == y)
			{
				igual = false;
			}
		}
		for(int i = 0; i < n_veneno; i++)
		{
			if(veneno[i].getY() == y)
			{
				igual = false;
			}
		}

	}
}

void Maca::imprime()
{
	al_draw_bitmap(maca, (x-1)*DIVISAO, (y-1)*DIVISAO, 0);
}

Maca::~Maca()
{
	al_destroy_bitmap(maca);
}

Veneno::Veneno()
{
	bit_veneno = al_load_bitmap("veneno.png");

	if(!bit_veneno)
	{
		cout << "N�o carregou veneno. " << endl;
	}
}

int Veneno::getX()
{
	return (x);
}

int Veneno::getY()
{
	return (y);
}

void Veneno::novoVeneno(Cobrinha* cobrinha, Maca* maca)
{
	cout << "novo veneno" << endl;
	bool igual = false;

	while(!igual)
	{
		x = rand() % 33 + 4;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getX() == x)
			{
				igual = false;
			}
		}
		if(maca->getX() == x)
            igual = false;
	}
	igual = false;
	while(!igual)
	{
		y = rand() % 19 + 6;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getY() == y)
			{
				igual = false;
			}
		}
		if(maca->getY() == y)
            igual = false;
	}

	al_draw_bitmap(bit_veneno, (x-1)*DIVISAO, (y-1)*DIVISAO, 0);
}

void Veneno::novoVeneno(Cobrinha* cobrinha, Maca* maca, Veneno* veneno, int n_veneno)
{
	cout << "nova venano" << endl;
	bool igual = false;

	while(!igual)
	{
		x = rand() % 33 + 4;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getX() == x)
			{
				igual = false;
			}
		}
		if(maca->getX() == x)
            igual = false;
        for(int i = 0; i < n_veneno; i++)
		{
			cout << veneno[i].getX() << endl;
			if(veneno[i].getX() == x)
			{
				igual = false;
			}
		}
		cout << "fica aqui eternamente" << endl;
	}

	igual = false;
	while(!igual)
	{
		y = rand() % 19 + 6;
		igual = true;
		for(int i = 0; i < cobrinha->tamanho; i++)
		{
			if(cobrinha->segmentos[i]->getY() == y)
			{
				igual = false;
			}
		}
		if(maca->getY() == y)
            igual = false;

        for(int i = 0; i < n_veneno; i++)
		{
			if(veneno[i].getY() == y)
			{
				igual = false;
			}
		}
	}

	al_draw_bitmap(bit_veneno, (x-1)*DIVISAO, (y-1)*DIVISAO, 0);
}

bool Veneno::operator+(Cobrinha *cobrinha)
{
    if(cobrinha->getCabecaX() == x && cobrinha->getCabecaY() == y)
        return true;
}

Veneno::~Veneno()
{
	al_destroy_bitmap(bit_veneno);
}

Cobrinha::Cobrinha()
{
	aumenta = false;
    x = rand() % 20 + 8;
	y = rand() % 19 + 6;
    tamanho = 3;
    segmentos = new Segmento*[tamanho_maximo];
    for(int i = 0; i < tamanho; i++)
    {
        segmentos[i] = new Segmento(x-i, y);
    }
}

void Cobrinha::movimenta()
{
    int x;
    int y;

    x = segmentos[tamanho-1]->getX();
    y = segmentos[tamanho-1]->getY();
    for(int i = tamanho-1; i > 0; i--)
    {
        segmentos[i]->setX(segmentos[i-1]->getX());
        segmentos[i]->setY(segmentos[i-1]->getY());
    }

	al_draw_filled_rectangle((x-1)*DIVISAO, (y-1)*DIVISAO, x*DIVISAO, y*DIVISAO, al_map_rgb(120, 139, 70)); // apaga rastro
}

void Cobrinha::moveParaDireita()
{
    segmentos[0]->incrementaX();
}

void Cobrinha::moveParaEsquerda()
{
    segmentos[0]->decrementaX();
}

void Cobrinha::moveParaCima()
{
    segmentos[0]->decrementaY();
}

void Cobrinha::moveParaBaixo()
{
    segmentos[0]->incrementaY();
}

void Cobrinha::imprime()
{
    for(int i = 0; i < tamanho; i++)
    {
        segmentos[i]->imprime();
    }
}

int Cobrinha::getCabecaX()
{
	return(segmentos[0]->getX());
}

int Cobrinha::getCabecaY()
{
	return(segmentos[0]->getY());
}

void Cobrinha::aumentaTamanho()
{
	if(tamanho < tamanho_maximo)
	{
		aumenta = true;
		x = segmentos[tamanho-1]->getX();
    	y = segmentos[tamanho-1]->getY();
    	segmentos[tamanho] = new Segmento(x, y);
    	tamanho++;
	}
}

bool Cobrinha::verificaColisao()
{
    for(int i = tamanho-1; i > 0; i--)
    {
        if(getCabecaX() == segmentos[i]->getX() && getCabecaY() == segmentos[i]->getY())
        {
            return true;
        }
    }

    return false;
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
}

void Fundo::menu(ALLEGRO_FONT* font)
{
	al_draw_filled_rectangle(0.0, 0.0, SCREEN_W, SCREEN_H, al_map_rgb(120, 139, 70));

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 2, 539, ALLEGRO_ALIGN_CENTER, "PRESSIONE 'Q' PARA COMECAR");

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 2, 250, ALLEGRO_ALIGN_CENTER, "JODO DA COBRINHA");

    al_flip_display();
}

void Fundo::imprime(ALLEGRO_FONT *font)
{
    macamordida = al_load_bitmap("maca_mordida.png");
    if(!macamordida)
	{
		cout << "N�o carregou ma�amordida. " << endl;
	}
    cout << "Imprime fundo " << endl;
    int i = 0;

    al_draw_filled_rectangle(0.0, 0.0, SCREEN_W, SCREEN_H, al_map_rgb(120, 139, 70));

    for(i = PAREDE_TOPO-1; i < PAREDE_CHAO+1; i++)
        al_draw_filled_rounded_rectangle((PAREDE_ESQUERDA-1)*DIVISAO, i*DIVISAO, PAREDE_ESQUERDA*DIVISAO, (i+1)*DIVISAO, 5, 5, al_map_rgb(0,0,0));

    for(i = PAREDE_ESQUERDA-1; i < PAREDE_DIREITA+1; i++)
        al_draw_filled_rounded_rectangle(i*DIVISAO, (PAREDE_TOPO-1)*DIVISAO, (i+1)*DIVISAO, PAREDE_TOPO*DIVISAO, 5, 5, al_map_rgb(0,0,0));

    for(i = PAREDE_TOPO-1; i < PAREDE_CHAO+1; i++)
        al_draw_filled_rounded_rectangle(PAREDE_DIREITA*DIVISAO, i*DIVISAO, (PAREDE_DIREITA+1)*DIVISAO, (i+1)*DIVISAO, 5, 5, al_map_rgb(0,0,0));

    for(i = PAREDE_ESQUERDA-1; i < PAREDE_DIREITA+1; i++)
        al_draw_filled_rounded_rectangle(i*DIVISAO, PAREDE_CHAO*DIVISAO, (i+1)*DIVISAO, (PAREDE_CHAO+1)*DIVISAO, 5, 5, al_map_rgb(0,0,0));

    al_draw_bitmap(macamordida, 570, 533, 0);

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 1.2, 539, ALLEGRO_ALIGN_RIGHT, "00");

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
    *font = al_load_ttf_font("8-Bit-Madness.ttf", 50,0 );

    //N�O CONSEGUE CARREGAR FONTE, DESCOBRIR POR QUE
    if (!(*font))
    {
        cout << "Could not load '8-Bit Madness.ttf'.\n";
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

void Timer::para()
{
    al_stop_timer(timer);
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
{}

void Comandos::confereComandosCobrinha(Cobrinha *cobrinha)
{
	cobrinha->movimenta();
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

bool Eventos::confereMenu()
{
	while(1)
	{
		if(!al_is_event_queue_empty(event_queue))
    	{
    	    al_wait_for_event(event_queue, &event);
	
	    	    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
	    	    {
	    	    	if(event.keyboard.keycode == ALLEGRO_KEY_Q)
	    	            return false;
	    	    }
	    	    else
	    	    {
	    	        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
	    	            return true;
	    	    }
    	}
    }

}


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
            	if(direcao[KEY_LEFT] || direcao[KEY_RIGHT])
            	{
                	teclas[KEY_UP] = true;
                	teclas[KEY_DOWN] = false;
                	teclas[KEY_LEFT] = false;
                	teclas[KEY_RIGHT] = false;
                }
                break;

            case ALLEGRO_KEY_DOWN:
            	if(direcao[KEY_LEFT] || direcao[KEY_RIGHT])
            	{
                	teclas[KEY_UP] = false;
                	teclas[KEY_DOWN] = true;
                	teclas[KEY_LEFT] = false;
                	teclas[KEY_RIGHT] = false;
                }
                break;

            case ALLEGRO_KEY_LEFT:
               	if(direcao[KEY_UP] || direcao[KEY_DOWN])
            	{
   					teclas[KEY_UP] = false;
   					teclas[KEY_DOWN] = false;
   					teclas[KEY_LEFT] = true;
   					teclas[KEY_RIGHT] = false;
   				}
                break;

            case ALLEGRO_KEY_RIGHT:
            	if(direcao[KEY_UP] || direcao[KEY_DOWN])
            	{
               		teclas[KEY_UP] = false;
               		teclas[KEY_DOWN] = false;
               		teclas[KEY_LEFT] = false;
               		teclas[KEY_RIGHT] = true;
               	}
                break;
            }
        }
    }
    return false;
}

Eventos::~Eventos()
{
    al_destroy_event_queue(event_queue);
}

Colisoes::Colisoes()
{
	//this->cobrinha = cobrinha;
}

bool Colisoes::confereColisoesMaca(Maca* maca, Cobrinha* cobrinha, Veneno* veneno, int n_veneno)
{
	if((cobrinha->getCabecaX() == maca->getX()) && (cobrinha->getCabecaY() == maca->getY()))
	{
		cobrinha->aumentaTamanho();
		maca->novaMaca(cobrinha, veneno, n_veneno);
		maca->imprime();
		return true;
	}
}

bool Colisoes::confereColisoesParede(Cobrinha* cobrinha)
{
    if(cobrinha->getCabecaY() == PAREDE_CHAO || cobrinha->getCabecaY() == PAREDE_TOPO || cobrinha->getCabecaX() == PAREDE_DIREITA || cobrinha->getCabecaX() == PAREDE_ESQUERDA)
    {
        return true;
    }
    return false;
}

bool Colisoes::confereColisoesCorpo(Cobrinha* cobrinha)
{
    if(cobrinha->verificaColisao())
    {
        return true;
    }
    return false;
}

GameOver::GameOver()
{
    event_queue = al_create_event_queue();
    if(!event_queue) {
        cout << "failed to create event_queue!\n";
    }
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void GameOver::imprime(ALLEGRO_FONT *font, int pontuacao)
{
	std::stringstream _pontos;
	_pontos << pontuacao;
	string temp_str = _pontos.str();
	char* pontos = (char*) temp_str.c_str();

    al_draw_filled_rectangle(0.0, 0.0, SCREEN_W, SCREEN_H, al_map_rgb(120, 139, 70));

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 1.2, 539, ALLEGRO_ALIGN_CENTER, "FIM DE JOGO");

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 2, 239, ALLEGRO_ALIGN_CENTER, "PONTUACAO: ");

    al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 2, 300, ALLEGRO_ALIGN_CENTER, pontos);

    al_flip_display();
}

Pontuacao::Pontuacao()
{
    pontos = 0;    
}

void Pontuacao::imprime(ALLEGRO_FONT *font)
{
    std::stringstream _pontos;
	_pontos << pontos;
	string temp_str = _pontos.str();
	char* pontuacao = (char*) temp_str.c_str();

	if(pontos < 10)
    {
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 1.24, 539, ALLEGRO_ALIGN_RIGHT, "0");
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 1.2, 539, ALLEGRO_ALIGN_RIGHT, pontuacao);
    }
    else
        al_draw_text(font, al_map_rgb(0, 0, 0), SCREEN_W / 1.2, 539, ALLEGRO_ALIGN_RIGHT, pontuacao);

}

void Pontuacao::setPontos()
{
    pontos++;
}

int Pontuacao::getPontos()
{
    return pontos;
}

Pontuacao::~Pontuacao()
{ }
