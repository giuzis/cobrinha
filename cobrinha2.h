#ifndef COBRINHA2_H_INCLUDED
#define COBRINHA2_H_INCLUDED

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

class Segmentos;
class Eventos;
class Cobrinha;
class Maca;
class Fundo;
class Comandos;
class Inicializa;
class Timer;
class Display;

class Segmento
{
	int x;
	int y;
public:
	Segmento(int x_inicial, int y_inicial);
	void imprime();
    void incrementaX();
	void incrementaY();
	void decrementaX();
	void decrementaY();
	void setX(int novo_x);
	void setY(int novo_y);
    int getX();
	int getY();
    ~Segmento();
};

class Maca
{
	ALLEGRO_BITMAP* maca;
	int x;
	int y;
public:
	Maca(Cobrinha* cobrinha);
	int getX();
	int getY();
	void imprime();
	~Maca();
};

class Inicializa
{
public:
	Inicializa();
	void inicializaFont(ALLEGRO_FONT **font);
   	~Inicializa();
};

class Timer
{
protected:
	ALLEGRO_TIMER *timer = NULL;
	float tempo;
	Timer(float _tempo);
   	~Timer();
};

class Display
{
protected:
	ALLEGRO_DISPLAY *display = NULL;
	Display();
	~Display();
};

class Comandos
{
public:
	Comandos();
	void confereComandosCobrinha(Cobrinha *cobrinha);
	~Comandos();
	friend Eventos;
};

class Eventos: public Timer, public Display
{
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_EVENT event;
	static int direcao[4];
	static int conta_timer;
public:
	Eventos();
	bool confereEvento(int velocidade, Cobrinha* cobrinha, Comandos* comandos);
	~Eventos();
};


class Cobrinha
{
	int tamanho, x, y;
	static const int tamanho_maximo = 30;
	Segmento **segmentos;
	void movimenta();
	void moveParaDireita();
	void moveParaEsquerda();
	void moveParaCima();
	void moveParaBaixo();
  	void imprime();
public:
	Cobrinha();
	~Cobrinha();
	friend bool Eventos::confereEvento(int velocidade, Cobrinha* cobrinha, Comandos* comandos);;
	friend void Comandos::confereComandosCobrinha(Cobrinha *cobrinha);
	friend Maca;
};

class Fundo
{
	int parede[4]; //0 - parede esquerda; 1 - parede de cima; 2 - parede direita; 3 - parede de baixo;
public:
	Fundo();
  	void imprime();
};


#endif // COBRINHA2_H_INCLUDED
