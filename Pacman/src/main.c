/**
  ******************************************************************************************************************
  * @file    main.c 
  * @author  PCo     IUT Informatique La Rochelle
  * @version v1.1
  * @date    6 mai 2019
  * @modification	rien pour le moment
  * @brief   template pour piloter l'afficheur LCD des cartes MCBSTM32EXL
  ******************************************************************************************************************/

#include "stm32f10x.h"                  /* STM32F10x.h definitions            */
#include "GLCD_Config.h"
#include "boule.h"
#include "ext_globales.h"
#include "globales.h"
#include "main.h"
#include "stdlib.h"
#include "stdio.h"

/* Variables nécéssaires au fonctionnement du jeu (Score & positions xy principalement)*/
int x=X_MIN;
int y=Y_MIN;
int bouche=0;
int x_nourr[5];
int y_nourr[5];
int x_map=30;
int y_map=30;
char deplacement;
int score=0;
int scoreF=0;
char Cscore[10];
char Fscore[10];
int miam=0;
/* Coordonnées de tous les fantomes*/
int x_f1 = 100;
int y_f1 = 100;
int x_f2 = 150;
int y_f2 = 150;
int x_f3 = 30;
int y_f3 = 30;
int x_f4 = 90;
int y_f4 = 90;


#define APPUYE 0x0000

void Enable_GPIO(void)
{
	RCC->APB2ENR |= (1<<5);
	RCC->APB2ENR |= (1<<8);
}

void Init_GPIO(void)
{
	GPIOD->CRL = 0x00004000;
	GPIOG->CRH = 0x04400000;
}

/*Méthode servant à faire déplacer la nourriture de façon aléatoire, appel de cette méthode lorsqu'il est mangé*/
void DeplacementFantome(){
	int i = 0;
	for(i = 0;i < 5;++i){
		x_nourr[i] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
		y_nourr[i] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
	}
}
/*Méthodes servant à faire déplacer tous les fantômes vers le fruit*/
void DeplacementFantome2(){
	if(x_f1 == x_nourr[0])
		{
			if(y_f1 < y_nourr[0])
				y_f1++;
			else
				y_f1--;
		}
		else
		{
			if(x_f1 < x_nourr[0])
				x_f1++;
			else
				x_f1--;
		}
	GLCD_DrawBitmap(x_f1,y_f1,10, 10,(const unsigned char *)Pinky);
}
void DeplacementFantome3(){
	if(x_f2 == x_nourr[0])
		{
			if(y_f2 < y_nourr[0])
				y_f2++;
			else
				y_f2--;
		}
		else
		{
			if(x_f2 < x_nourr[0])
				x_f2++;
			else
				x_f2--;
		}
	GLCD_DrawBitmap(x_f2,y_f2,10, 10,(const unsigned char *)Blinky);
}

void DeplacementFantome4(){
	if(x_f3 == x_nourr[0])
		{
			if(y_f3 < y_nourr[0])
				y_f3++;
			else
				y_f3--;
		}
		else
		{
			if(x_f3 < x_nourr[0])
				x_f3++;
			else
				x_f3--;
		}
	GLCD_DrawBitmap(x_f3,y_f3,10, 10,(const unsigned char *)Clyde);
}

void DeplacementFantome5(){
	if(x_f4 == x_nourr[0])
		{
			if(y_f4 < y_nourr[0])
				y_f4++;
			else
				y_f4--;
		}
		else
		{
			if(x_f4 < x_nourr[0])
				x_f4++;
			else
				x_f4--;
		}
	GLCD_DrawBitmap(x_f4,y_f4,10, 10,(const unsigned char *)Inky);
}

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) 
{
	
	  GLCD_Initialize();                          
  	GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);

/* Clear graphical LCD display*/
/* MENU du jeu*/
	GLCD_ClearScreen();               
	GLCD_SetForegroundColor(GLCD_COLOR_YELLOW);
	GLCD_SetFont(&GLCD_Font_16x24);
	lAbscisse=117;
	GLCD_DrawChar(lAbscisse,95,'P');
	lAbscisse=lAbscisse+16;
	GLCD_DrawChar(lAbscisse,95,'A');
	lAbscisse=lAbscisse+16;
	GLCD_DrawChar(lAbscisse,95,'C');
	lAbscisse=lAbscisse+18;
	GLCD_DrawChar(lAbscisse,95,'M');
	lAbscisse=lAbscisse+18;
	GLCD_DrawChar(lAbscisse,95,'A');
	lAbscisse=lAbscisse+16;
	GLCD_DrawChar(lAbscisse,95,'N');
	lAbscisse=lAbscisse+16;
	GLCD_SetFont(&GLCD_Font_6x8);
	GLCD_DrawString(100,150,"Press BP_USER to launch");

	
 /* Contours de la carte*/
	lAbscisse=110;
	GLCD_DrawHLine(102,85,130);
	GLCD_DrawVLine(102,85,45);
	GLCD_DrawVLine(232,85,45);
	GLCD_DrawHLine(102,130,130);

	while(GPIOG->IDR & (1 << 8))
	{
	}
		GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);

	/* Initialize graphical LCD display   */
		GLCD_Initialize();                          
		GLCD_SetBackgroundColor(GLCD_COLOR_BLACK);
		GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
		DeplacementFantome();
	/* Clear graphical LCD display        */
	
	GLCD_FrameBufferAccess(true); 	
	// faire avant appel à GLCD_DrawPixel et GLCD_ReadPixel pour supprimer
	// les limitations d'accès à la SRAM (uniquement nécessaire sur les anciennes
	// cartes sinon les fonctions GLCD_DrawPixel et GLCD_ReadPixel ne 
	// fonctionnent pas
	
	
	RCC->APB2ENR |= (1<<11);
	TIM1->PSC=11;
	TIM1->ARR=60000;
	TIM1->CR1 |= 0x0001;
	
	RCC->APB1ENR |= (1<<0);
	TIM2->PSC = 239;
	TIM2->ARR = 60000;
	TIM2->CR1|=0x0001;
	
	GLCD_ClearScreen();
	GLCD_SetFont(&GLCD_Font_6x8);

/* Lignes de la carte, du titre du jeu & du score (allié et ennemi) */
	GLCD_DrawChar(10,0,'P');
	GLCD_DrawChar(20,0,'A');
	GLCD_DrawChar(30,0,'C');
  GLCD_DrawChar(40,0,'M');
	GLCD_DrawChar(50,0,'A');
	GLCD_DrawChar(60,0,'N');

	GLCD_DrawChar(120,0,'S');
	GLCD_DrawChar(130,0,'c');
	GLCD_DrawChar(140,0,'o');
	GLCD_DrawChar(150,0,'r');
	GLCD_DrawChar(160,0,'e');
	GLCD_DrawChar(170,0,':');
	sprintf(Cscore,"%d",score);
	GLCD_DrawString(190,0,Cscore);
	
	GLCD_DrawChar(210,0,'S');
	GLCD_DrawChar(220,0,'c');
	GLCD_DrawChar(230,0,'o');
	GLCD_DrawChar(240,0,'r');
	GLCD_DrawChar(250,0,'e');
	GLCD_DrawChar(260,0,'F');
	GLCD_DrawChar(270,0,':');
	sprintf(Fscore,"%d",scoreF);
	GLCD_DrawString(280,0,Fscore);
	
	/* Autres contours de la carte*/
	GLCD_DrawHLine(0,10,319);
	GLCD_DrawHLine(0,1005,319);
	GLCD_DrawVLine(0,10,995);
	GLCD_DrawVLine(319,10,995);
	GLCD_SetForegroundColor(0x1234);
	GLCD_DrawPixel(50,150);
	
	
	/* Apparition de la cerise au début du jeu*/
	GLCD_DrawBitmap(x_nourr[0],y_nourr[0],10, 10,(const unsigned char *)bmpNourriture);

	
	
	while (1){
		
		if(TIM1->SR & 0x0001){//tim1
			
			TIM1->SR &= ~(1<<0);
			/* Déplacements du PACMAN si celui-ci n'atteins pas les bords*/
			if((JR==APPUYE ||deplacement=='D') && x!=X_MAX)
				x=x+1;
			if((JL==APPUYE ||deplacement=='G') && x!=X_MIN)
				x=x-1;
			if((JU==APPUYE||deplacement=='H') && y!=Y_MIN)
				y=y-1;
			if((JD==APPUYE||deplacement=='B') && y!=Y_MAX)
				y=y+1;
			DeplacementFantome2();
			/* Méthode utilisée lorsque le pacman "mange" la nourriture (c-à-d même coordonnées), Apparition d'un nouveau fruit random et implémentation du score */
			if ( ((x+10>=x_nourr[0] && x+10<=x_nourr[0]+8) && (y+10>=y_nourr[0] && y+10<=y_nourr[0]+6)) 
				|| ((x<=x_nourr[0]+6 && x>=x_nourr[0]) && (y<=y_nourr[0]+6 && y>=y_nourr[0])) ) {
							score++;
							sprintf(Cscore,"%d",score);
							GLCD_DrawString(190,0,Cscore);
							GLCD_DrawBitmap(x_nourr[0],y_nourr[0],10, 10,(const unsigned char *)null);
							x_nourr[0] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
							y_nourr[0] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
							GLCD_DrawBitmap(x_nourr[0],y_nourr[0],10, 10,(const unsigned char *)bmpNourriture);			
				}
				/* Méthode utilisée lorsque le fantôme "mange" la nourriture (c-à-d même coordonnées), Apparition d'un nouveau fruit random et implémentation du score*/
				if ( ((x_f1+10>=x_nourr[0] && x_f1+10<=x_nourr[0]+8) && (y_f1+10>=y_nourr[0] && y_f1+10<=y_nourr[0]+6)) 
				|| ((x_f1<=x_nourr[0]+6 && x_f1>=x_nourr[0]) && (y_f1<=y_nourr[0]+6 && y_f1>=y_nourr[0])) ) {
							scoreF++;
							sprintf(Fscore,"%d",scoreF);
							GLCD_DrawString(280,0,Fscore);
							GLCD_DrawBitmap(x_nourr[0],y_nourr[0],10, 10,(const unsigned char *)null);
							x_nourr[0] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
							y_nourr[0] = rand()%(Y_MAX - Y_MIN) + Y_MIN;
							GLCD_DrawBitmap(x_nourr[0],y_nourr[0],10, 10,(const unsigned char *)bmpNourriture);
				}
				/*Fais apparaître les fantomes après un certain score allié*/
				if (score > 0){
					DeplacementFantome3();
				}	
				if (score > 2){
					DeplacementFantome4();
				}	
				if (score > 3){
					DeplacementFantome5();
				}	
				/* Fin du jeu à partir d'un certain score (Victoire ou Game Over)*/
				while(score>4 || scoreF>9)
					{
						GLCD_ClearScreen();
				if (score > 4){
					GLCD_DrawString(80,100,"T'as gagne ! Relance le jeu");
					GLCD_DrawString(80,110,"Le score des fantômes est :");
					GLCD_DrawString(80,120,Fscore);
					}
				if (scoreF > 9){
					GLCD_DrawString(80,100,"T'as perdu, fallait etre meilleur...");
					GLCD_DrawString(80,110,"Ton score est :");
					GLCD_DrawString(80,120,Cscore);
					}
				}
				/* Animations du pacman selon sa direction*/
			if(deplacement =='H')
				{
					if(bouche==0)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)HBDO);
			if(bouche==1)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)HBDM);
			if(bouche==2)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BF);
			if(bouche==3)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)HBDM);
				}
				else if (deplacement=='B'){
			if(bouche==0)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BBDO);
			if(bouche==1)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BBDM);
			if(bouche==2)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BF);
			if(bouche==3)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BBDM);
			}
				else if (deplacement=='G'){
			if(bouche==0)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)GBDO);
			if(bouche==1)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)GBDM);
			if(bouche==2)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BF);
			if(bouche==3)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)GBDM);
			}
				else if(deplacement=='D'){
			if(bouche==0)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BDO);
			if(bouche==1)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BDM);
			if(bouche==2)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BF);
			if(bouche==3)
				GLCD_DrawBitmap(x,y,10, 10,(const unsigned char *)BDM);
			}
		}//tim1
		
		
		
		
		if(TIM2->SR & 0x0001){ //if tim2, Timer du changement d'animation du PacMan
			
			TIM2->SR &= ~(1<<0);			
			
			bouche++;
			if(bouche==4)
				bouche=0;
			
		}//end if tim2
		
		
		/* Détermine la direction du pacman pour choisir la bonne animation*/
		if(JR==APPUYE)
		{
			deplacement='D';
		}
		if(JL==APPUYE)
		{
			deplacement='G';
		}
		if(JU==APPUYE)
		{
			deplacement='H';
		}
		if(JD==APPUYE)
		{
			deplacement='B';
		}
		
		/* Evite au PacMan de dépasser les limites de la carte*/
		if(x==X_MAX||x==X_MIN||y==Y_MIN||y==Y_MAX)
		{}
		
	}//end while

}
