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

const int PAREDE_ESQUERDA = 3;
const int PAREDE_TOPO = 5;
const int PAREDE_DIREITA = 37;
const int PAREDE_CHAO = 25;	

const int DIVISAO = 20;

class Segmento;
class Eventos;
class Cobrinha;
class Maca;
class Fundo;
class Comandos;
class Inicializa;
class Timer;
class Display;
class Colisoes;

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
	int numero_macas;
	int x;
	int y;
public:
	Maca();
	void novaMaca(Cobrinha* cobrinha);
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

//Dependência com cobrinha e comandos
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
	bool aumenta;
	Segmento **segmentos;
	void movimenta();
	void moveParaDireita();
	void moveParaEsquerda();
	void moveParaCima();
	void moveParaBaixo();
  	void imprime();
  	void aumentaTamanho();
public:
	Cobrinha();
	int getCabecaX();
	int getCabecaY();
	~Cobrinha();
	friend bool Eventos::confereEvento(int velocidade, Cobrinha* cobrinha, Comandos* comandos);;
	friend void Comandos::confereComandosCobrinha(Cobrinha *cobrinha);
	friend Colisoes;
	friend Maca;
};

class Fundo
{
public:
	Fundo();
  	void imprime();
};

//Agregação com cobrinha
//dependencia com maça
class Colisoes
{
	//Cobrinha* cobrinha;
public:
	Colisoes(Cobrinha* cobrinha);
	//void novaMaca(Maca* maca);
	int confereColisoesMaca(Maca* maca, Cobrinha* cobrinha);
	void confereColisoesVeneno();
	void confereColisoesParede();
};

#endif // COBRINHA2_H_INCLUDED
