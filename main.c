
//Clique em "REGRAS" com o mouse, para selecionar jogadores, utilize os números do teclado

#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include<time.h>//necessário p/ função time()

typedef enum
{
    false = ( 1 == 0 ),
    true = ( ! false )
} bool;

typedef struct Comida 
{
    int comidax;
    int comiday;
    int contador;
    bool come;
}comida;

typedef struct Jogador
{
	int cabeca;
	int jogx[10000];
	int jogy[10000];
	int speedjogx;
	int speedjogy;
	int auxdirecao;
	bool vivo;
}jogador;

jogador Jogador[4];
comida Comida[4];
int vivos = 0;
int vencedor = 0;
int GameFps = 10;
int numJogadores = 0;
int comidas;
float rgb[4][3];

void init(void);
void desenha(void);
void restart(void);
void comerCobra(void);
void comer(void);
void mover(void);
void baterParede(void);
void aparecerComida(void);
void iniciarCabeca(void);
void DesenhaTextoStroke(void *font, char *string);
void Timer(int time);
void ganhador(void);
void teclado(unsigned char key, int x, int y);
static void SpecialKey(int key, int x, int y);
void MouseClick (int button, int state, int x, int y);

bool regras, pause = false;
int i, y, z, x;

int main(int argc, char** argv) 
{
	regras = false;
	rgb[0][0] = 1;
	rgb[0][1] = 0;
	rgb[0][2] = 0;
	rgb[1][0] = 0;
	rgb[1][1] = 1;
	rgb[1][2] = 0;
	rgb[2][0] = 0;
	rgb[2][1] = 0;
	rgb[2][2] = 1;
	rgb[3][0] = 1;
	rgb[3][1] = 0;
	rgb[3][2] = 1;

  srand(time(NULL)); //inicializar o gerador de números aleatórios (rand) com o valor da função time(NULL), 
                     //sendo assim, a cada execução do programa, os números serão diferentes.
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize (800, 600); 
  glutInitWindowPosition (50, 50); 
  glutCreateWindow ("Jogo SNAKE");
  
  init();
	glutDisplayFunc(desenha);
  	glutKeyboardFunc(teclado);
  	glutSpecialFunc(SpecialKey);
  	glutMouseFunc(MouseClick);
  	glutTimerFunc(1000.0/GameFps, Timer, 0);
  glutMainLoop();
}
void init(void)
{
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glOrtho (0, 256, 0, 256, -1 ,1);
}

void desenha()
{
	int a, n;
	if(regras == true)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		y = 280;
		glColor3f(0, 0, 0);
		
		glPushMatrix();
  			glTranslatef(15, 220, 0);	
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1-Jogador");
		glPopMatrix();
		
		glPushMatrix();
  			glTranslatef(15, 160, 0);
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"2-Jogadores");
		glPopMatrix();
		
		glPushMatrix();
  			glTranslatef(15, 100, 0);
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3-Jogadores");
		glPopMatrix();
		
		glPushMatrix();
  			glTranslatef(15, 40, 0);
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4-Jogadores");
		glPopMatrix();
		
		glPushMatrix();
  			glTranslatef(202, 222, 0);
  			glScalef(0.11, 0.11, 0.11);
  			glLineWidth(4);     
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"[ESC]");
		glPopMatrix();
		
		glPushMatrix();
  			glTranslatef(5, 6, 0);
  			glScalef(0.075, 0.075, 0.075);
  			glLineWidth(4);     
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Aperte R para reiniciar e P para pausar o jogo");
		glPopMatrix();
		
		for(i = 0; i < 4; i++)
		{
			y -= 60;
			x = 80;
			n = 0;
			for(z = i+1; z > 0; z--)
			{
				x += 35;
				
				glColor3f(rgb[n][0], rgb[n][1], rgb[n][2]);
				
  				glPushMatrix();
  					glTranslatef(x, y, 0);
  					glScalef(0.1, 0.1, 0.1);
  					glLineWidth(3);
  					if(n == 0)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"a");
  					else if(n == 1)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"<");
  					else if(n == 2)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"4");
  					else if(n == 3)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"j");
				glPopMatrix();
				
				glPushMatrix();
  					glTranslatef(x+10, y, 0);
  					glScalef(0.1, 0.1, 0.1);
  					glLineWidth(3);
  					if(n == 0)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"s");
  					else if(n == 1)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"v");
  					else if(n == 2)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"5");
  					else if(n == 3)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"k");
				glPopMatrix();
				
				glPushMatrix();
  					glTranslatef(x+10, y+11, 0);
  					glScalef(0.1, 0.1, 0.1);
  					glLineWidth(3);
  					if(n == 0)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"w");
  					else if(n == 1)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"^");
  					else if(n == 2)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"8");
  					else if(n == 3)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"i");
				glPopMatrix();
				
				glPushMatrix();
  					glTranslatef(x+20, y, 0);
  					glScalef(0.1, 0.1, 0.1);
  					glLineWidth(3);
  					if(n == 0)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"d");
  					else if(n == 1)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,">");
  					else if(n == 2)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"6");
  					else if(n == 3)
  						DesenhaTextoStroke(GLUT_STROKE_ROMAN,"l");
				glPopMatrix();
				n++;
			}
		}
	}
	else if(numJogadores == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
  		//parede limite
  		glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2i(1, 1);
			glVertex2i(255, 1);
			glVertex2i(255, 250);
			glVertex2i(1, 250);
  		glEnd();
  		
  		glBegin(GL_QUADS);
			glColor3f(0.2f, 0.1f, 0.3f);
			glVertex2i(3, 3);
			glVertex2i(50, 3);
			glVertex2i(50, 30);
			glVertex2i(3, 30);
  		glEnd();
  		
  		glColor3f(0.0f, 0.0f, 0.0f);
  		glPushMatrix();
  			glTranslatef(30, 220, 0);
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);     
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"1-Jogador  2-Jogadores");
		glPopMatrix();
  		
  		glPushMatrix();
  			glTranslatef(30, 110, 0);
  			glScalef(0.12, 0.12, 0.12);
  			glLineWidth(4);     
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"3-Jogadores 4-Jogadores");
  		glPopMatrix();
  		
  		glPushMatrix();
  			glColor3f(1, 1, 1);
  			glTranslatef(5, 10, 0);
  			glScalef(0.11, 0.11, 0.11);
  			glLineWidth(4);     
  			DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Regras");
		glPopMatrix();
		
		for(i = 0; i < 4; i++)
		{
			n = 0;
			if(i < 2) y = 200;
			else y = 95;
			if(i % 2 == 0) x = 45;
			else x = 150;
		
			for(z = i+1; z > 0; z--)
			{
				y -= 15;	
				glColor3f(rgb[n][0], rgb[n][1], rgb[n][2]);
				n++;
				for(a = 0; a < 50; a++)
				{
					glPointSize(10);
  						glBegin(GL_POINTS);
    					glVertex2i(x+a, y);
  					glEnd();
				}

				glPointSize(15);
				//cabeça
  				glBegin(GL_POINTS);
    				glColor3f(0.5f, 0.5f, 0.5f);
    				glVertex2i(x+50, y);
  				glEnd();
			
				glColor3f(0, 0, 0);
			
				glPointSize(4);
  				glBegin(GL_POINTS);
   					glVertex2i(x+50, y-2);
  				glEnd();

  				glPointSize(4);
  				glBegin(GL_POINTS);
   					glVertex2i(x+50, y+2);
  				glEnd();
			}
		}
	}
	else if(vencedor == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
  		glLineWidth(6); 
  		//parede limite
  		glBegin(GL_LINE_LOOP);
			glColor3f(0.0f, 0.0f, 0.0f);
			glVertex2i(1, 1);
			glVertex2i(255, 1);
			glVertex2i(255, 250);
			glVertex2i(1, 250);
  		glEnd();
  
  		glPointSize(4);
  		for(y = 0; y < numJogadores; y++)
  			if(Jogador[y].vivo == true)
  				for(i=0; i< Jogador[y].cabeca-1; i++)
  				{
  					glBegin(GL_POINTS);
  						glColor3f(rgb[y][0], rgb[y][1], rgb[y][2]);
    					glVertex2i(Jogador[y].jogx[i], Jogador[y].jogy[i]);
  					glEnd();
  				}
  		
		glPointSize(7);
		for(i = 0; i < numJogadores; i++)
			if(Jogador[i].vivo == true)
			{
				//cabeça
  				glBegin(GL_POINTS);
    				glColor3f(0.5f, 0.5f, 0.5f);
    				glVertex2i(Jogador[i].jogx[Jogador[i].cabeca-1], Jogador[i].jogy[Jogador[i].cabeca-1]);
  				glEnd();
			}	
		
		glPointSize(3);
		for(i = 0; i < numJogadores; i++)
			if(Jogador[i].vivo == true)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				if(Jogador[i].auxdirecao == 0 || Jogador[i].auxdirecao == 1 || Jogador[i].auxdirecao == 2)
  				{
  					glBegin(GL_POINTS);
   						glVertex2i(Jogador[i].jogx[Jogador[i].cabeca-1]-1, Jogador[i].jogy[Jogador[i].cabeca-1]);
  					glEnd();
  		
  					glBegin(GL_POINTS);
   						glVertex2i(Jogador[i].jogx[Jogador[i].cabeca-1]+1, Jogador[i].jogy[Jogador[i].cabeca-1]);
  					glEnd();
					}
					else
					{
  					glBegin(GL_POINTS);
   						glVertex2i(Jogador[i].jogx[Jogador[i].cabeca-1], Jogador[i].jogy[Jogador[i].cabeca-1]-1);
  					glEnd();
  		
  					glBegin(GL_POINTS);
   						glVertex2i(Jogador[i].jogx[Jogador[i].cabeca-1], Jogador[i].jogy[Jogador[i].cabeca-1]+1);
  					glEnd();
				}
			}
  		
  		glPointSize(6);
  		for(i = 0; i < 2; i++)
  			if(Comida[i].come == true && Comida[i].contador > 80)
  			{
  				glBegin(GL_POINTS);
    				glColor3f(0.0f, 0.0f, 0.0f);
    				glVertex2i(Comida[i].comidax, Comida[i].comiday);
  				glEnd();
			}
	}
	else if(vencedor != 0)
  	{
  		char caractere[2];
  		itoa(vencedor, caractere, 10);
  		
  		
  		glColor3f(rgb[vencedor-1][0], rgb[vencedor-1][1], rgb[vencedor-1][2]);
		glPushMatrix();	
  			glTranslatef(75, 200, 0);
  			glScalef(0.2, 0.2, 0.2);
  			glLineWidth(4);
  			if(vencedor == -1)
  				DesenhaTextoStroke(GLUT_STROKE_ROMAN,"Empate");
			else
			{
				DesenhaTextoStroke(GLUT_STROKE_ROMAN, "Jogador");
  				DesenhaTextoStroke(GLUT_STROKE_ROMAN, caractere);	
			}
  		glPopMatrix();
	}
  	glFlush();	
}
void Timer(int time)
{
	if(pause == false)
	{
		mover();
		iniciarCabeca();
		comer();
		aparecerComida();
		comerCobra();
		baterParede();
		ganhador();
		desenha();
	}
	
	glutTimerFunc(1000.0/GameFps, Timer, 0);
}

void ganhador(void)
{
	if(vivos == 1 && vivos != numJogadores)
	{
		for(i = 0; i < numJogadores; i++)
			if(Jogador[i].vivo == true)
				vencedor = i+1;
	}
	else if(vivos == 0)
		vencedor = -1;
}

void iniciarCabeca(void)
{
	for(i = 0; i < numJogadores; i++)
		if(Jogador[i].cabeca < 10)
			Jogador[i].cabeca++;
}
void aparecerComida(void)
{
	for(i = 0; i < 2; i++)
	{
		if(Comida[i].come == true && Comida[i].contador < 80)
			Comida[i].contador++;
		else if(Comida[i].contador == 80)
		{
			Comida[i].contador++;
			Comida[i].comidax = rand() % 254;
			Comida[i].comiday = rand() % 249;
			Comida[i].come = true;
		}	
		else if(Comida[i].come == false)
		{
			Comida[i].contador = 0;
			Comida[i].come = true;
		}
		else if(Comida[i].contador < 300)
			Comida[i].contador++;
		else if(Comida[i].contador >= 300)
		{
			Comida[i].contador = 0;
			Comida[i].come = true;
		}
	}
}
void mover(void)
{
	for(i = 0; i < numJogadores; i++)
		if(Jogador[i].vivo == true)
		{
			Jogador[i].jogx[Jogador[i].cabeca]= Jogador[i].jogx[Jogador[i].cabeca-1] + Jogador[i].speedjogx; 
			Jogador[i].jogy[Jogador[i].cabeca]= Jogador[i].jogy[Jogador[i].cabeca-1] + Jogador[i].speedjogy; 
		}

	for(i = 0; i < numJogadores; i++)
		if(Jogador[i].vivo == true)
			for(y = 0; y < Jogador[i].cabeca; y++)
				if(Jogador[i].cabeca >= 10)
				{
					Jogador[i].jogx[y] = Jogador[i].jogx[y+1];
					Jogador[i].jogy[y] = Jogador[i].jogy[y+1];
				}		
}
void comer(void)
{
	for(i = 0; i < numJogadores; i++)
		for(z = 0; z < 2; z++)
			if(Jogador[i].jogx[Jogador[i].cabeca] == Comida[z].comidax && Jogador[i].jogy[Jogador[i].cabeca] == Comida[z].comiday && Comida[z].come == true)
			{
				for(y = 1; y <= 15; y++)
				{
					Jogador[i].jogx[Jogador[i].cabeca+y] = Jogador[i].jogx[Jogador[i].cabeca-1] + Jogador[i].speedjogx;
					Jogador[i].jogy[Jogador[i].cabeca+y] = Jogador[i].jogy[Jogador[i].cabeca-1] + Jogador[i].speedjogy; 
				}
				Jogador[i].cabeca += 15;
				Comida[z].come = false;
			}
}
void baterParede(void)
{
	if(vencedor == 0)
		for(i = 0; i < numJogadores; i++)
			if(Jogador[i].vivo == true)
				if(Jogador[i].jogx[Jogador[i].cabeca-1] == 1 || Jogador[i].jogx[Jogador[i].cabeca-1] == 255 || Jogador[i].jogy[Jogador[i].cabeca-1] == 1 || Jogador[i].jogy[Jogador[i].cabeca-1] == 250)
					if(vivos >= 1)
					{
						Jogador[i].vivo = false;
						vivos--;
					}
}
void comerCobra(void)
{
	int aux[4];
	for(i = 0; i < 4; i++)
		aux[i] = -1;
	
	for(y = 0; y < numJogadores; y++)
		if(Jogador[y].vivo == true)
			for(z = 0; z < numJogadores; z++)
				if(z != y && Jogador[z].vivo == true)
					for(i = 0; i < Jogador[z].cabeca; i++)
						if(Jogador[y].jogx[Jogador[y].cabeca-1] == Jogador[z].jogx[i] && Jogador[y].jogy[Jogador[y].cabeca-1] == Jogador[z].jogy[i] )
						{
							if(vivos >= 1)
							{
								aux[y] = y;
								vivos--;
							}	
							break;	
						}
	
	for(i = 0; i < 4; i++)
		if(aux[i] != -1)
			Jogador[aux[i]].vivo = false;
}

void Mover(int tecla, int jogador)
{	
	switch(tecla)
	{
		case 1:
			if(Jogador[jogador].auxdirecao != 1 && Jogador[jogador].auxdirecao != 2)
			{
				Jogador[jogador].speedjogx = 0;
				Jogador[jogador].speedjogy = 1;
			}
			break;
		case 2:
			if(Jogador[jogador].auxdirecao != 2 && Jogador[jogador].auxdirecao != 1)
			{
				Jogador[jogador].speedjogx = 0;
				Jogador[jogador].speedjogy = -1;	
			}
			break;
		case 3:
			if(Jogador[jogador].auxdirecao != 3 && Jogador[jogador].auxdirecao != 4)
			{
				Jogador[jogador].speedjogx = -1;
				Jogador[jogador].speedjogy = 0;
			}
			break;
		case 4:
			if(Jogador[jogador].auxdirecao != 3 && Jogador[jogador].auxdirecao != 4)
			{
				Jogador[jogador].speedjogx = 1;
				Jogador[jogador].speedjogy = 0;
			}
			break;
	}
	Jogador[jogador].auxdirecao = tecla;
}
void teclado(unsigned char key, int x, int y)
{
  switch (key) 
  {  
  case 'w':
  	Mover(1, 0);
    break;
  case 's':
  	Mover(2, 0);
    break;
  case 'a':
  	Mover(3, 0);
    break;
  case 'd':
  	Mover(4, 0);
    break;
  case 'i':
  	Mover(1, 3);
    break;
  case 'k':
  	Mover(2, 3);
    break;
  case 'j':
  	Mover(3, 3);
    break;
  case 'l':
  	Mover(4, 3);
    break;
  case '1':
  	if(numJogadores == 0)
  	{
  		numJogadores = 1;
  		restart();
  		vivos = numJogadores;
	}
  	break;
  case '2':
  	if(numJogadores == 0)
  	{
  		numJogadores = 2;
  		restart();
  		vivos = numJogadores;
    }
    break;
  case '3':
  	if(numJogadores == 0)
  	{
  		numJogadores = 3;
  		restart();
  		vivos = numJogadores;
	}
	break;
  case '4':
  	if(numJogadores == 0)
  	{
  		numJogadores = 4;
  		restart();
  		vivos = numJogadores;
    }
    else Mover(3, 2);
    break;
  case '8':
  	Mover(1, 2);
  	break;
  case '5':
  	Mover(2, 2);
  	break;
  case '6':
  	Mover(4, 2);
  	break;
  case 'r':
  	numJogadores = 0;
  	restart();
  	break;
  case 'p':
  	if(pause == false) 
	  pause = true;
  	else 
	  pause = false;
  	break;
  case 27:
  	regras = false;
  	break;
  }    
}
static void SpecialKey(int key, int x, int y)
{
  switch (key) 
  {
  case GLUT_KEY_UP:
  	Mover(1, 1);
    break;
  case GLUT_KEY_DOWN:
  	Mover(2, 1);
    break;
  case GLUT_KEY_LEFT:
  	Mover(3, 1);
    break;
  case GLUT_KEY_RIGHT:
  	Mover(4, 1);
    break;
  }
}
void MouseClick (int button, int state, int x, int y)
{
    switch (button)
    {
        case GLUT_LEFT_BUTTON: 
    		if(x < 155 && x > 9 && y < 590 && y > 530) regras = true;
        break;
    }
}
void DesenhaTextoStroke(void *font, char *string)
{
	while(*string)
	glutStrokeCharacter(GLUT_STROKE_ROMAN,*string++);
}
void restart(void)
{
    vencedor = 0;
  for(i = 0; i < numJogadores; i++)
  {
  	if(i == 0)
  	{
  		Jogador[i].jogx[0] = 5 + (rand() % 122);
    	Jogador[i].jogy[0] = 5 + (rand() % 95);
	}
	else if(i == 1)
	{
		Jogador[i].jogx[0] = 132 + (rand() % 121);
    	Jogador[i].jogy[0] = 5 + (rand() % 95);
	}
	else if(i == 2)
	{
		Jogador[i].jogx[0] = 5 + (rand() % 122);
    	Jogador[i].jogy[0] = 105 + (rand() % 94);
	}
	else if(i == 3)
	{
		Jogador[i].jogx[0] = 132 + (rand() % 121);
    	Jogador[i].jogy[0] = 105 + (rand() % 94);
	}
	
  	Jogador[i].speedjogx = 1 - rand() % 3;
  	if(Jogador[i].speedjogx == 0)
  		while(Jogador[i].speedjogy == 0)
  		{
  			Jogador[i].speedjogy = 1 - rand() % 3;
  			if(Jogador[i].speedjogy == 1)
  				Jogador[i].auxdirecao = 1;
  			else if(Jogador[i].speedjogy == -1)
  				Jogador[i].auxdirecao = 2;
		}
	else
	{
		if(Jogador[i].speedjogx == -1)
  			Jogador[i].auxdirecao = 3;
  		else if(Jogador[i].speedjogx == 1)
  			Jogador[i].auxdirecao = 4;
  		Jogador[i].speedjogy = 0;
	}	
  	Jogador[i].cabeca = 1;
  	
    Comida[i].come = false;
    Jogador[i].vivo = true;
  }
}
