#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdio>
#include <windows.h>      //usada para reproduzir sons de fundo
#include <mmsystem.h>    //usada para reproduzir sons de fundo
#include <math.h>



#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

//============= Texturas e obj ===================
#define STB_IMAGE_IMPLEMENTATION//usada para carregar textura das imagens
#include "stb_image.h" //usada para carregar textura das imagens
//#include "glm.h"//usada para carregar os objetos(obj) do jogo
//================================================
#include "glm.h"

using namespace std;
#define BLOCOS 1
#define BALAS 10
#define VIDAS 20
#define PI 3.14159265


GLuint elephant;
float elephantrot;
char ch = '1';

float QuantVida = VIDAS;

int w = 800, h = 600;

float cx = -1, cy = 8, cz = 25.5 , Ry = 0 , Raux = -90;
float PBcx = 8, PBcy = 8, PBcz = 20.5 , PBRy = 0 , PBRaux = -90;

bool VidaPersonagemA = true, VidaPersonagemB = true;

float inimigoX = 2, inimigoY = 8, inimigoZ = 19.5;
//bala

float  zoom = -30;

float blocoX = -2.30, blocoY = 8.0, blocoZ = 15;
float velX = 0;
float velZ = -1.0;

float velXB = 0;
float velZB = -1.0;

//porsche

GLMmodel * pmodel = NULL;
GLMmodel * tank2 = NULL;


float luzX = 0.7f, luzY = 0.75f, luzZ = 8.5f;
GLfloat light0_position[] = {luzX, luzY, luzZ, 1.0f};

//----




struct Bala
{
	float x;
	float z;
	float y;
	float velX;
	float velZ;
	bool ativa;
};

struct Vida
{
	float x;
	float z;
	float y;
	bool ativa;
};


Bala balas[BALAS];
Vida vidas[VIDAS];
void DesenharVida();

void iniciaBalas();
void iniciarVida();






void criaCubo(float x)
{
	// Desenhas as linhas das "bordas" do cubo
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);	// frontal
	glVertex3f(x, x, x);
	glVertex3f(-x, x, x);
	glVertex3f(-x, -x, x);
	glVertex3f(x, -x, x);
	glEnd();
	glBegin(GL_LINE_LOOP);	//  posterior
	glVertex3f(x, x, -x);
	glVertex3f(x, -x, -x);
	glVertex3f(-x, -x, -x);
	glVertex3f(-x, x, -x);
	glEnd();
	glBegin(GL_LINES);	//  laterais
	glVertex3f(-x, x, -x);
	glVertex3f(-x, x, x);
	glVertex3f(-x, -x, -x);
	glVertex3f(-x, -x, x);
	glVertex3f(x, x, -x);
	glVertex3f(x, x, x);
	glVertex3f(x, -x, -x);
	glVertex3f(x, -x, x);
	glEnd();

	// Desenha as faces do cubo preenchidas
	// Face frontal
	glBegin(GL_QUADS);


	glNormal3f(0.0, 0.0, 1.0);	// Normal da face
	glColor3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, x, x);

	glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, x, x);

	glColor3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, x);


	glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, -x, x);



	// Face posterior
	glNormal3f(0.0, 0.0, -1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	// glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, x, -x);

	glColor3f(1.0f, 0.0f, 1.0f);
	// glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, -x, -x);

	glColor3f(0.0f, 0.0f, 1.0f);
	//  glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, -x);

	glColor3f(0.0f, 1.0f, 1.0f);
//	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, -x);

	// Face lateral esquerda
	glNormal3f(-1.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, x);



	glColor3f(0.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, x, -x);



	glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, -x, -x);



	glColor3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, x);



	// Face lateral direita
	glNormal3f(1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(x, x, x);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, -x, x);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(x, -x, -x);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(x, x, -x);


	// Face superior
	glNormal3f(0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, x, -x);



	glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, x);



	glColor3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, x, x);



	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, x, -x);



	//Iluminação
	glNormal3f(0.0, -1.0, 0.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-x, -x, -x);
	glTexCoord2f(0, 1); //atribui coordenada de textura ao objeto
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(x, -x, -x);
	glTexCoord2f(0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, -x, x);
	glTexCoord2f(1, 0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -x, x);
	glTexCoord2f(1, 1);

	glEnd();
}

//A - inimigo
//B - personagem ou outro elemento
bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt)
{

	if(Ay + Aalt < By) return false;
	else if(Ay > By + Balt) return false; //bater embaixo
	else if(Ax + Acomp < Bx) return false;
	else if(Ax > Bx + Bcomp) return false;

	return true;
}





void update(int value)
{



	for(int i = 0; i < BALAS / 2; i++) // A ataca B
	{

		if(balas[i].ativa)
		{

			if(colisao(balas[i].x, balas[i].z, 0.7, 0.7, PBcx, PBcz, 1.1, 0.9) == true)
			{


				balas[i].ativa = false; //dsativa a bala


				printf("colidiu em B\n");
				//	velX = -velX; //bateu no bloco, volta

				for(int j = 0 ; j < VIDAS / 2; j++)
				{
					if(vidas[j].ativa)
					{
						vidas[j].ativa = false;
						if(j != (VIDAS/2) - 1)
						{
							PlaySound("impact2.wav", NULL, SND_ASYNC | SND_FILENAME | SND_SYNC);
						}
						else
						{
							PlaySound("explosion.wav", NULL, SND_ASYNC | SND_FILENAME | SND_SYNC);
						}


						j = VIDAS / 2;
					}
					if(j == (VIDAS / 2) - 2)
					{

						printf("B PERDEU");
						VidaPersonagemB = false;


					}
				}

				i = BALAS / 2;
			}
		}

	}

	for(int i = BALAS / 2; i < BALAS; i++) // B ataca A
	{

		if(balas[i].ativa)
		{

			if(colisao(balas[i].x, balas[i].z, 0.7, 0.7, cx, cz, 1.1, 0.9) == true)
			{


				balas[i].ativa = false;


				printf("colidiu em A\n");
				//	velX = -velX; //bateu no bloco, volta

				for(int j = VIDAS / 2; j < VIDAS; j++)
				{
					if(vidas[j].ativa)
					{
						vidas[j].ativa = false;
						j = VIDAS;
						if(j != VIDAS - 1)
						{
							PlaySound("impact2.wav", NULL, SND_ASYNC | SND_FILENAME | SND_SYNC);
						}
						else
						{
							PlaySound("explosion.wav", NULL, SND_ASYNC | SND_FILENAME | SND_SYNC);
						}

					}
					if(j == (VIDAS - 2))
					{
						printf("A PERDEU");
						VidaPersonagemA = false;
					
					}

				}



				//if(QuantVida <= 0)
				//	blocos[0].vivo = false;


				//blocos[n].vivo = false;
				//break
				i = BALAS / 2;
			}
		}

	}




	
	velZ = cos(Raux * PI / 180);
	velX = -sin(Raux * PI / 180) ;

	velZB = cos(PBRaux * PI / 180);
	velXB = -sin(PBRaux * PI / 180) ;


	for(int i = 0; i < BALAS; i++)
	{
		balas[i].z += balas[i].velX ;
		balas[i].x += balas[i].velZ;
	}




	for(int n = 0; n < BALAS; n++)//limita as balas pela arena
	{
		if(balas[n].z <= 15 || balas[n].x > 13 || balas[n].x <= -3 || balas[n].z >= 31.5)  //tocar em cima
		{
			//velZ = -velZ;

			if( balas[n].ativa)
			{

				balas[n].ativa = false;

				break;

			}


		}
	}








	glutPostRedisplay();
	glutTimerFunc(200, update, 0);
}



void tank34(char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}

	glPointSize(2.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POLYGON);
		while(!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			/*
			normal color texture vertice
			*/
			//	if(read == 4 && ch == 'vn') //normal
			//	{
			//		glNormal3f (x, y, z);
			//	}
			if(read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}

		}
		glEnd();
	}




	glPopMatrix();
	glEndList();
	fclose(fp);
}

void tank34_B(char *fname)
{
	FILE *fp;
	int read;
	GLfloat x, y, z;
	char ch;
	elephant = glGenLists(1);
	fp = fopen(fname, "r");
	if (!fp)
	{
		printf("can't open file %s\n", fname);
		exit(1);
	}

	glPointSize(2.0);
	glNewList(elephant, GL_COMPILE);
	{
		glPushMatrix();
		glBegin(GL_POLYGON);
		while(!(feof(fp)))
		{
			read = fscanf(fp, "%c %f %f %f", &ch, &x, &y, &z);
			/*
			normal color texture vertice
			*/
			//	if(read == 4 && ch == 'vn') //normal
			//	{
			//		glNormal3f (x, y, z);
			//	}
			if(read == 4 && ch == 'v')
			{
				glVertex3f(x, y, z);
			}

		}
		glEnd();
	}




	glPopMatrix();
	glEndList();
	fclose(fp);
}

void drawCar()
{
	glPushMatrix();
	glTranslatef(cx, cy, cz); //0,-40.00,-105

	glScalef(0.004, 0.004, 0.004);
	glRotatef(Ry, 0, 1.0, 0);
	glColor3f(0.7, 0.1, 0);


	glCallList(elephant);


}

void drawCar_B()
{
	glPushMatrix();
	glTranslatef(PBcx, PBcy, PBcz); //0,-40.00,-105

	glScalef(0.005, 0.005, 0.005);
	glRotatef(PBRy, 0, 1.0, 0);
	glColor3f(0.1, 0.4, 0.8);


	glCallList(elephant);


}







void drawGrid()
{
	int i;
	int quant = 56;
	for(i = 0; i < quant; i++)
	{
		glPushMatrix();
		if(i < quant/2)
		{
			glTranslatef(0, 0, i);
		}

		if(i >= quant/2)
		{
			glTranslatef(i - quant/2, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}

		glBegin(GL_LINES);
		glColor3f(0.01, 0.51, 0.21);
		glLineWidth(1);
		glVertex3f(0, -0.1, 0);
		glVertex3f((quant/2) - 1, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}



void DesenhaBalas()
{


	// blocos[9].ativa = false;

	int w, h;
	GLuint texture2;
	unsigned char *uc2 = stbi_load("l.jpeg", &w, &h, NULL, 0);
	glGenTextures(1, &texture2); //gera nomes identificadores de texturas
	glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual

	// Cria a textura lateral de cada bloco
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
				 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D); //Ativando textura


	for(int i = 0; i < BALAS; i++)
	{
		if(balas[i].ativa) 	//se o bloco NÃO foi tocado -> desenha
		{


			// fim textura
			glPushMatrix();
			//glEnable(GL_LIGHTING);
			//glEnable(GL_LIGHT0);
			glColor3f(0, 0, 1);
			glTranslatef(balas[i].x, 8, balas[i].z);
			criaCubo(0.1);
			//glutSolidCube(0.9);
			glDisable(GL_LIGHTING);
			glPopMatrix();


		}
	}

	glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos
}

void DesenharVida()
{


	// blocos[9].vivo = false;

	int w, h;
	GLuint texture2;
	unsigned char *uc2 = stbi_load("t.jpeg", &w, &h, NULL, 0);
	glGenTextures(1, &texture2); //gera nomes identificadores de texturas
	glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual

	// Cria a textura lateral de cada bloco
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
				 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D); //Ativando textura

	for(int i = 0; i < QuantVida; i++)
	{

		if(vidas[i].ativa == true) 	//se o bloco NÃO foi tocado -> desenha
		{


			// fim textura
			glPushMatrix();
			//glEnable(GL_LIGHTING);
			//glEnable(GL_LIGHT0);
			glColor3f(0, 0, 1);
			glTranslatef(vidas[i].x, 9, vidas[i].z);
			criaCubo(0.1);
			//glutSolidCube(0.9);
			glDisable(GL_LIGHTING);
			glPopMatrix();
		}
	}

	glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glTranslatef(-13, 0, -45);
	glRotatef(40, 1, 1, 0);



	drawGrid();

	if(VidaPersonagemA)
		drawCar();


	if(VidaPersonagemB)
		drawCar_B();






	DesenharVida();

	DesenhaBalas();



	glutSwapBuffers();
}

void init()
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(65.0, 1.0f, 0.1f, 1000.0);


	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_COLOR_MATERIAL);



	glEnable(GL_CULL_FACE);                // Habilita Backface-Culling
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION , 1.0f);




	//-------

}



void keyboard(unsigned char key, int x, int y)
{

	// Frente / para tras
	// Não move pra frente
	if(key == 'w')
	{
		if(cz <= 15)
		{
			cz = 15;
		}
		else
		{
			cz -= 0.2;

		}

	} //frente

	if(key == 's')
	{
		if(cz + 0.5 >= 31.5)
		{
			cz = 31.5;
		}
		else
		{
			cz += 0.2;
		}
	} //forward / back
	//Fim do frente tras

	//left / right
	if(key == 'a')
	{
		if(cx - 1 <= -3)  //Lado esq. inferior
		{
			cx = -2.3;
		}
		else
		{
			cx -= 0.2;
		}
	}
	if(key == 'd')  //Lado dir. inferior
	{
		if(cx + 0.5 >= 13)
		{
			cx = cx;
		}
		else
		{
			cx += 0.2;
		}
		//==== FIM left / right
	}

	if( key == 'f')
	{


		for(int i = 0; i < BALAS / 2; i++) // 0 -> 4
		{
			if( balas[i].ativa == false)
			{
				balas[i].x = cx;
				balas[i].y = cy;
				balas[i].z = cz;
				balas[i].velX  = velX;
				balas[i].velZ  = velZ;
				balas[i].ativa = true;
				break;

			}

		}
	}
	if(key == 'q') // sentido anti-horário
	{
		Ry = (Ry + 5) ;
		Raux += 5;

	}

	if(key == 'e') // sentido horário
	{
		Ry = (Ry - 5) ;
		Raux -= 5;
	}

	//***********************

	if(key == 'i')
	{
		if(PBcz <= 15)
		{
			PBcz = 15;
		}
		else
		{
			PBcz -= 0.2;
		}

	} //frente

	if(key == 'k')
	{
		if(PBcz + 0.5 >= 31.5)
		{
			PBcz = 31.5;
		}
		else
		{
			PBcz += 0.2;
		}
	} 
	if(key == 'j')
	{
		if(PBcx - 1 <= -3)  //Lado esq. inferior
		{
			PBcx = -2.3;
		}
		else
		{
			PBcx -= 0.2;
		}
	}
	if(key == 'l')  //Lado dir. inferior
	{
		if(PBcx + 0.5 >= 13)
		{
			PBcx = cx;
		}
		else
		{
			PBcx += 0.2;
		}
		//==== FIM left / right
	}

	if( key == '/')
	{


		for(int i = 5; i < BALAS; i++) //5 -> 9
		{
			if( balas[i].ativa == false)
			{
				balas[i].x = PBcx;
				balas[i].y = PBcy;
				balas[i].z = PBcz;
				balas[i].velX  = velXB;
				balas[i].velZ  = velZB;
				balas[i].ativa = true;
				break;

			}
		}
	}
	if(key == 'u') // sentido anti-horário
	{
		PBRy = (PBRy + 5) ;
		PBRaux += 5;

	}

	if(key == 'o') // sentido horário
	{
		PBRy = (PBRy - 5) ;
		PBRaux -= 5;
	}






	glutPostRedisplay();
}



void iniciaBalas()
{
	//cria blocos
//	float x = -2.3, z = 15.5;
	for(int n = 0;  n < BALAS; n++)
	{

		/*if(x > 8.5)
		{
			x = -2.3;
			z += 2;
		}*/

		balas[n].x = cx;
		balas[n].z = cz;
		balas[n].y = 8;
		balas[n].ativa = false;
		//	x += 1.3;
	}
}

void iniciarVida ()
{

	//cria blocos
	float x = cx - 1.5 , z = cz + 8;//+3
	for(int n = 0;  n < QuantVida / 2; n++)
	{



		vidas[n].x = x;
		vidas[n].z = z;
		vidas[n].y = 8; //ficar acima do personagem
		vidas[n].ativa = true;

		x += 0.2;
	}
	x += 1;
	for(int n = QuantVida / 2;  n < QuantVida; n++) //P2
	{



		vidas[n].x = x;
		vidas[n].z = z;
		vidas[n].y = 8; //ficar acima do personagem
		vidas[n].ativa = true;

		x += 0.2;
	}
}




int main(int argc, char** argv)
{

	iniciarVida ();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("");
	glutDisplayFunc(display);
	
	glutKeyboardFunc(keyboard);
	init();
	tank34("T-34.obj");
	tank34_B("T-34.obj");
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}
