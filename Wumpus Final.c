#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
int main(){
	//     OURO REPRESENTADO POR O=3
	//	   WUMPUS REPRESENTADO POR W=4
	//	   AGENTE REPRESENTADO POR A=2
	// 	   POÇOS REPRESENTADO POR P=5
	//     BRISA REPRESENTADA POR B=6
	//     FEDOR REPRESENTADO POR F=7
	//     BRILHO REPRESENTADO POR F=8
	//     BRISA E FEDOR REPRESENTADO POR BF=9
	//     BRISA E BRILHO REPRESENTADO POR BB=10
	//     FEDOR E BRILHO REPRESENTADO POR FB=11
	//     BRISA, BRILHO E FEDOR REPRESENTADO POR BBF=12

	int n, i, j, lo, co, lw, cw,W=4, O=3, A=2, P=5, DF,t;
	int B=6, BH=8, F=7, BB=10, BF=9, FB=11, BBF=12, flecha=1, ouro=0, C=0;
	printf("\t========    BEM VINDO AO MUNDO WUMPUS   ========\n\n");
	printf("\tEquipe: Jonas e Velcides\n\n");
	printf("\tINFORME O TAMANHO DA MATRIZ: DE 4 A 10:");
	scanf("%i", &n);
	printf("\n");
	//CRIANDO AS MATRIZES
	int MAMB[n][n];
	int MSEN[n][n];
	for(i=0; i < n; i++){
	for(j=0; j < n; j++){
		MAMB[i][j]=0;               //  PREENCHENDO AS MATRIZES DE ZEROS
		MSEN[i][j]=0;
	}
	}
	int LA=0, CA=0;
    srand(time(NULL) );
	MAMB[LA][CA]=A;
	//COLOCANDO O OURO NA MATRIZ AMBIENTE
	do{		lo= rand() %n;
			co= rand() %n;
			}while(lo==0&&co==0);               //  PARA EVITAR QUE O OURO FIQUE NA (0,0
    MAMB[lo][co]=O;
	//COLOCANDO O WUMPUS NA MATRIZ AMBIENTE
	do{		lw= rand() %n;
			cw= rand() %n;
	}while(lw==0&&cw==0 || lw==lo&&cw==co);	//	PARA EVITAR QUE O WUMPUS FIQUE NA (0,0) E NA MESMA CASA DO OURO
	MAMB[lw][cw]=W;
	// COORDENADAS DOS POÇOS
	int QP;
	QP= n - 1;      					  	//  QUANTIDADE DE POÇOS SERÁ O TAMANHO DA MATRIZ - 1
	int a, b;
	for(i=0; i < QP; i++)
	{	do{
		a= rand() %n;                       //  SORTEANDO AS COORDENADAS DOS  POÇOS
		b= rand() %n;
		}while(MAMB[a][b]!=0);				//  SÓ COLOCARÁ POÇOS QUANDO A CASA FOR IGUAL A 0 - VAZIA
        MAMB[a][b]=5; }

	// =================================  CRIANDO BRISA   =================================
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (MAMB[i][j] == 5){                        		//  SE TIVER POCO
                if(i==0){                                       //  ==== SE PRIMEIRA LINHA ====
                    MSEN[i+1][j] = 6;                  			//  SENTE BRISA ACIMA
                    MSEN[i][j-1] = 6;                  			//  SENTE BRISA A ESQUERDA
                    if (j!=n-1) MSEN[i][j+1] = 6;    }			//  SE NAO TIVER NA ULTIMA COLUNA SENTE BRIA A DIREITA
                else if(i==n-1){                              	//  ==== SE TIVER NA ULTIMA LINHA ====
                    MSEN[i-1][j] = 6;                  			//  SENTE BRISA ABAIXO
                    if (j==0) MSEN[i][j+1] = 6;        			//  SE TIVER NA PRIMEIRA COLUNA SENTE BRISA A DIREITA
                    else if(j==n-1) MSEN[i][j-1] = 6;			//  SE TIVER NA ULTIMA COLUNA SENTE BRISA A ESQUERDA
                    else{                                       //  SE TIVER NA COLUNA DO MEIO
                        MSEN[i][j+1] = 6;              			//  SENTE BRISA A DIREITA
                        MSEN[i][j-1] = 6; }}             			//  SENTE BRISA A ESQUERDA
                else{                                           //  ==== SE TIVER NA LINHA DO MEIO ====
                    MSEN[i+1][j] = 6;                  			//  SENTE BRISA ACIMA
                    MSEN[i-1][j] = 6;                  			//  SENTE BRISA ABAIXO
                    if (j==0) MSEN[i][j+1] = 6;       			//  SE TIVER NA PRIMEIRA COLUNA SENTE BRISA A DIREITA
                    else if(j==n-1) MSEN[i][j-1] = 6;			//  SE TIVER NA ULTIMA COLUNA SENTE BRISA A ESQUERDA
                    else{                                       //  SE TIVER NA COLUNA DO MEIO
                        MSEN[i][j+1] = 6;              			//  SENTE BRISA A DIREITA
                        MSEN[i][j-1] = 6;              			//  SENTE BRISA A ESQUERDA
                    }
                }
            }
        }
    }

	// =================================  CRIANDO FEDOR   =================================
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (MAMB[i][j] == 4){                        			//  SE ESTIVER POCO
				if(i==0){                                       	//  ==== SE ESTIVER NA PRIMEIRA LINHA ====
                    if(MSEN[i+1][j]==6)MSEN[i+1][j] = 9;            //  SE SENTE BRISA ACIMA, PASSARÁ A SENTIR BRISA E FEDOR
                    else MSEN[i+1][j] = 7;							//  SE NÃO SENTE NADA ACIMA, PASSARÁ A SENTIR FEDOR
					if(MSEN[i][j-1]==6)MSEN[i][j-1] = 9;			//  SE SENTE BRISA A ESQUERDA, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i][j-1] = 7;                 			//  SE NÃO SENTE NADA A ESQUERDA, PASSARÁ A SENTIR FEDOR
                    if (j!=n-1){									//  SE ELE NÃO ESTIVER NA ÚLTIMA COLUNA...
                    if(MSEN[i][j+1]==6)MSEN[i][j+1] = 9;			//  SE SENTE BRISA A DIREITA, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i][j+1] = 7;    						//  SE NAO SENTE NADA A DIREITA, PASSARÁ A SENTIR FEDOR
                }
				}
                else if(i==n-1){                              		//  ==== SE ESTIVER NA ULTIMA LINHA ====
                    	if(MSEN[i-1][j]==6)MSEN[i-1][j] = 9;		//  SE JÁ SENTE BRISA ABAIXO, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i-1][j] = 7;                  	//  SE NÃO SENTE NADA ABAIXO, PASSARÁ A SENTIR FEDOR
                    	if (j==0){									//  SE TIVER NA PRIMEIRA COLUNA
						if(MSEN[i][j+1]==6) MSEN[i][j+1] = 9;		//  SE SENTE BRISA A DIREITA, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i][j+1] = 7;}       				//  SE NÃO SENTE NADA A DIREITA, PASSARÁ A SENTIR FEDOR
                    	else if(j==n-1){							//  SE ESTIVER NA ULTIMA COLUNA
						if(MSEN[i][j-1]==6)MSEN[i][j-1] = 9;		//  SE SENTE BRISA A ESQUERDA, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i][j-1] = 7;}						//  SE NÃO SENTE NADA A ESQUERDA, PASSARÁ A SENTIR FEDOR
                    else{											//  SE TIVER NA COLUNA DO MEIO
						if(MSEN[i][j+1]==6)MSEN[i][j+1] = 9;        //  SE SENTE BRISA A DIREITA, PASSARÁ A SENTIR BRISA E FEDOR
                        else MSEN[i][j+1] = 7;              		//  SE NÃO SENTE NADA A DIREITA, PASSARÁ A SENTIR FEDOR
                        if(MSEN[i][j-1]==6)MSEN[i][j-1] = 9;		//  SE SENTE BRISA A ESQUERDA, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i][j-1] = 7;             		    //  SE NÃO SENTE NADA A ESQUERDA, PASSARÁ A SENTIR FEDOR
                    }
                }
                else{                                           	//  ==== SE ESTIVER NA LINHA DO MEIO ====
                    if(MSEN[i+1][j]==6)MSEN[i+1][j] = 9;			//  SE SENTE BRISA ACIMA, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i+1][j] = 7;                  		//  SE NÃO SENTE NADA ACIMA, PASSARÁ A SENTIR FEDOR
                    if(MSEN[i-1][j]==6)MSEN[i-1][j] = 9; 			//  SE SENTE BRISA ABAIXO, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i-1][j] = 7;                  		//  SE NÃO SENTE NADA ABAIXO, PASSARÁ A SENTIR FEDOR
                    if (j==0) {										//  SE ESTIVER NA PRIMEIRA COLUNA
					if(MSEN[i][j+1]==6)MSEN[i][j+1] = 9;			//  SE SENTE BRISA A DIREITA, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i][j+1] = 7;}        					//  SE NÃO SENTE NADA A DIREITA, PASSARÁ A SENTIR FEDOR
                    else if(j==n-1) { 								//  SE ESTIVER NA ULTIMA COLUNA SENTE BRISA A ESQUERDA
					if(MSEN[i][j-1]==6)MSEN[i][j-1] = 9;			//  SE SENTE BRISA A ESQUERDA, PASSARÁ A SENTIR BRISA E FEDOR
					else MSEN[i][j-1] = 7;}							//  SE NÃO SENTE NADA A ESQUERDA, PASSARÁ A SENTIR FEDOR
                    else{                                       	//  SE ESTIVER NA COLUNA DO MEIO
                        if(MSEN[i][j+1]==6)MSEN[i][j+1] = 9;		//  SE SENTE BRISA A DIREITA, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i][j+1] = 7;              		//  SE NÃO SENTE NADA A DIREITA, PASSARÁ A SENTIR FEDOR
                        if(MSEN[i][j-1]==6)MSEN[i][j-1] = 9;		//  SE SENTE BRISA A ESQUERDA, PASSARÁ A SENTIR BRISA E FEDOR
						else MSEN[i][j-1] = 7;            			//  SE NÃO SENTE NADA A ESQUERDA, PASSARÁ A SENTIR FEDOR
                    }
                }
            }
        }
    }

    	// =================================  CRIANDO BRILHO   =================================
    for (i=0; i<n; i++){
        for (j=0; j<n; j++){
            if (MAMB[i][j] == 3){                        	//  SE TIVER POCO
                if(MSEN[i][j]==6)MSEN[i][j]=10;			 	//  CASO JÁ TENHA BRISA, PASSARÁ A TER BRISA E BRILHO
                else if(MSEN[i][j]==7)MSEN[i][j]=11;		//  CASO JÁ TENHA FEDOR, PASSARÁ A TER FEDOR E BRILHO
                else if(MSEN[i][j]==9)MSEN[i][j]=12;		//  CASO JÁ TENHA BRISA E FEDOR, PASSARÁ A TER BRISA, FEDOR E BRILHO
                else MSEN[i][j]=8;							//  CASO NÃO TENHA NADA, PASSARÁ A APENAS O BRILHO
    		}
    	}
	}

	// IMPRIMINDO A MATRIZ SENSAÇÕES
	printf("\t   MATRIZ SENSACOES    \n\n");
	for(i=n-1; i >= 0; i--){printf("\t   ");
	for(j=0; j < n; j++){
		if(MSEN[i][j]==12)printf("BBF ");
		else if(MSEN[i][j]==11)printf("FBH ");
		else if(MSEN[i][j]==10)printf("BB  ");
		else if(MSEN[i][j]==9)printf("BF  ");
		else if(MSEN[i][j]==8)printf("BH  ");
		else if(MSEN[i][j]==7)printf("F   ");
		else if(MSEN[i][j]==6)printf("BR  ");
		else printf("-   ");}
        printf("\n");}
	printf("\n\n\n");


    // =========================== CRIANDO MOVIMENTAÇÃO DO AGENTE ========================================
	                                    //  POSIÇÃO QUE O AGENTE INICIA
	int LAA, CAA, DM, z=0;

               while(ouro==0){
                    //    IMPRIMINDO A MATRIZ AMBIENTE
    for(i= n -1; i>= 0; i--){printf("\t   ");
	for(j=0; j < n; j++){
		if(MAMB[i][j]==3)
		{	printf("O ");}
		else if(MAMB[i][j]==4)
		{   printf("W ");}
		else if(MAMB[i][j]==2)
		{   printf("A ");}
		else if(MAMB[i][j]==5)
		{	printf("P ");}
		else printf("- ");
	}printf("\n");}
printf("\n\n");
		if(MSEN[LA][CA]==12){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRISA, BRILHO E FEDOR\n\n", LA,CA);}
		else if(MSEN[LA][CA]==11){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRILHO E FEDOR\n\n", LA, CA);}
		else if(MSEN[LA][CA]==10){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRISA E BRILHO\n\n", LA, CA);}
		else if(MSEN[LA][CA]==9){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRISA E FEDOR\n\n", LA, CA);}
		else if(MSEN[LA][CA]==8){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRILHO\n\n", LA, CA);}
		else if(MSEN[LA][CA]==7){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: FEDOR\n\n", LA, CA);}
		else if(MSEN[LA][CA]==6){printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: BRISA\n\n", LA,CA);}
		else {printf("\tPOSICAO DO AGENTE: [%d,%d]\n\tSENTINDO: NADA\n\n", LA, CA);}




                   if(LA==0&&CA==0){
                //=========================================  CASA CANTO DE BAIXO[0,0]  ===================================================//
                        if(MSEN[LA][CA]==9){
                            if(flecha==1){
                                DF= rand()%2;
                                    if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\t MATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\t ERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\t MATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\t ERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%2;
                                if(DM==1){
                                LAA=LA;
                                CAA=CA;
                                if(MAMB[LA+1][CA]==5){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO POCO\n\n"); break;}
                                else if(MAMB[LA+1][CA]==4){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                else if(MAMB[LA+1][CA]==0){
                                   LA++;
                                   MAMB[LA][CA]=2;
                                   MAMB[LAA][CAA]=0;}
                                }
                                if(DM==0){
                                LAA=LA;
                                CAA=CA;
                                if(MAMB[LA][CA+1]==5){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO POCO\n\n");break;}
                                else if(MAMB[LA][CA+1]==4){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                else if(MAMB[LA][CA+1]==0){
                                   CA++;
                                   MAMB[LA][CA]=2;
                                   MAMB[LAA][CAA]=0;}
                                }}}
                        else if(MSEN[LA][CA]==7){
                            if(flecha==1){
                                DF= rand()%2;
                                    if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\t ERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\t ERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%2;
                                if(DM==1){
                                LAA=LA;
                                CAA=CA;
                                if(MAMB[LA+1][CA]==4){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                else if(MAMB[LA+1][CA]==0){
                                    LA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}
                                if(DM==0){
                                LAA=LA;
                                CAA=CA;
                                if(MAMB[LA][CA+1]==4){
                                   MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                else if(MAMB[LA][CA+1]==0){
                                    CA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}}

                        else if(MSEN[LA][CA]==6){
                                DM= rand()%2;
                                    if(DM==1){
                                        if(MAMB[LA+1][CA]==5){ MAMB[LA][CA]=0;  printf("\n\n\tAGENTE MORREU NO POCO\n\n");break;}
                                        else{
                                            LAA=LA;
                                            CAA=CA;
                                            LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){
                                            if(MAMB[LA][CA+1]==5){ MAMB[LA][CA]=0;  printf("\n\n\tAGENTE MORREU NO POCO\n\n");break;}
                                            else{
                                                LAA=LA;
                                                CAA=CA;
                                                CA++;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){
                                DF= rand()%2;
                                    if(DF==1){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}
                                    else if(DF==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
           //=========================================  CASA CANTO DE BAIXO A DIREITA ===================================================//
                   else if(LA==0&&CA==n-1) {                                            // SE ESTIVER NA PRIMEIRA LINHA E NA ULTIMA COLUNA
                            if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%2;
                                                if(DF==1){
                                                    if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1;  printf("\n\n\tERROU A FLECHA\n\n"); }}}
                                            else {
                                                DM= rand()%2;
                                                if(DM==1){           //  SE DER 1 MOVER ACIMA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA+1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==0){
                                                        LA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA][CA-1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==0){
                                                        CA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2; MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%2;
                                    if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                else {
                                    DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER ACIMA
                                    LAA=LA; CAA=CA;
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER ACIMA
                                    LAA=LA; CAA=CA;
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                                    DM= rand()%2;
                                        if(DM==1){           //  SE DER 1 MOVER ACIMA
                                            LAA=LA; CAA=CA;
                                            if(MAMB[LA+1][CA]==5){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                            else if(MAMB[LA+1][CA]==0){
                                                LA++;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}
                                        else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                            LAA=LA; CAA=CA;
                                                if(MAMB[LA][CA-1]==5){
                                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                else if(MAMB[LA][CA-1]==0){
                                                    CA--;
                                                    MAMB[LA][CA]=2;
                                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==8){                  //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%2;
                                if(DM==1){           //  SE DER 1 MOVER ACIMA
                                    LAA=LA; CAA=CA; LA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}
                                else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                    LAA=LA; CAA=CA; CA--;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%2;
                                if(DF==1){
                                    if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1;printf("\n\n\tERROU A FLECHA\n\n");}}
                                else if(DF==0){
                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else { DM= rand()%2;
                            if(DM==1){                             //  CASO O SORTEIO ALEATORIO DO MOVIMENTO SEJA IGUAL A 1 MOVER ACIMA
                                LAA=LA; CAA=CA;
                                if(MAMB[LA+1][CA]==4){
                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                else if(MAMB[LA+1][CA]==0){
                                    LA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}
                                    if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%2;
                            if(DM==1){                             //  CASO O SORTEIO ALEATORIO DO MOVIMENTO SEJA IGUAL A 1 MOVER ACIMA
                                LAA=LA; CAA=CA;
                                if(MAMB[LA+1][CA]==5){
                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA+1][CA]==0){
                                    LA= LA + 1;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}
                                    if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%2;
                            if(DM==1){                             //  CASO O SORTEIO ALEATORIO DO MOVIMENTO SEJA IGUAL A 1 MOVER ACIMA
                                LAA=LA; CAA=CA; LA++;
                                MAMB[LA][CA]=2;
                                MAMB[LAA][CAA]=0;}
                            else if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                    LAA=LA; CAA=CA; CA--;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}
           //=========================================  CASAS LATERAIS DE BAIXO  ========================================================//
                   else if(LA==0&&(CA!=0&&CA!=n-1)){                                    // SE ESTIVER NA PRIMEIRA LINHA E NA ULTIMA COLUNA
                            if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1;             printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%3;
                                                if(DF==2){
                                                    if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==1){
                                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                            else {
                                                DM= rand()%3;
                                                if(DM==2){           //  SE DER 2 MOVER ACIMA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA+1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==0){
                                                        LA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                               else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA][CA-1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==0){
                                                        CA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA;CAA=CA;
                                                    if(MAMB[LA][CA+1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==0){
                                                        CA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1;  printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2; MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER ACIMA
                                    if(MAMB[LA+1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA+1][CA]==0){
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%3;
                                    if(DM==2){                  //  SE DER 2 MOVER ACIMA
                                    if(MAMB[LA+1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA+1][CA]==0){
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){             //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {  DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER ACIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2; MSEN[LA][CA]=0;     }
                            else {  DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER ACIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                             else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER ACIMA
                                    if(MAMB[LA+1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA+1][CA]==0){
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                DM= rand()%3;
                                if(DM==2){                  //  SE DER 2 MOVER ACIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){             //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER ACIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
           //=========================================  CASA CANTO SUPERIOR DA ESQUERDA =================================================//
                   else if(LA==n-1&&CA==0){                                             // SE ESTIVER NA PRIMEIRA COLUNA
                        if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%2;
                                if(DF==1){
                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                else if(DF==0){
                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%2;
                                if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==4){
                                        LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA][CA+1]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                    else if(MAMB[LA][CA+1]==4){
                                        CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%2;
                                    if(DF==1){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                else {
                                    DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                    LAA=LA; CAA=CA;
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                                    DM= rand()%2;
                                        if(DM==1){                 //  SE DER 1 MOVER PARA BAIXO
                                            LAA=LA;
                                            CAA=CA;
                                            if(MAMB[LA-1][CA]==5){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                            else if(MAMB[LA-1][CA]==0){
                                                LA--;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}
                                        else if(DM==0){            //  SE DER 0 MOVER A DIREITA
                                            LAA=LA;
                                                CAA=CA;
                                                if(MAMB[LA][CA+1]==5){
                                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                else if(MAMB[LA][CA+1]==0){
                                                    CA++;
                                                    MAMB[LA][CA]=2;
                                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%2;
                                if(DM==1){                           //  SE DER 1 MOVER PARA BAIXO
                                    LAA=LA; CAA=CA; LA--;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}
                                else if(DM==0){                      //  SE DER 0 MOVER A DIREITA
                                    LAA=LA; CAA=CA; CA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%2;
                                if(DF==1){
                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                else if(DF==0){
                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else{
                                DM= rand()%2;
                                if(DM==1){                             //  SE DER 1, DEVE MOVER-SE PARA BAIXO
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                if(DM==0){                     //  SE DER 0 MOVER A DIREITA
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA][CA+1]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA][CA+1]==0){
                                        CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%2;
                            if(DM==1){
                                LAA=LA;                            //  SE DER 1, DEVE MOVER-SE PARA BAIXO
                                CAA=CA;
                                if(MAMB[LA-1][CA]==5){
                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA-1][CA]==0){
                                    LA--;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}
                            if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                LAA=LA;
                                CAA=CA;
                                if(MAMB[LA][CA+1]==5){
                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA][CA+1]==0){
                                    CA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE NÃO ESTIVER SENTINDO NADA
                            DM= rand()%2;
                            if(DM==1){                             //  SE DER 1 DEVE MOVER-SE ABAIXO
                                LAA=LA; CAA=CA; LA--;
                                MAMB[LA][CA]=2;
                                MAMB[LAA][CAA]=0;}
                            else if(DM==0){                        //  SE DER 0 MOVER A ESQUERDA
                                    LAA=LA; CAA=CA; CA++;
                                    MAMB[LA][CA]=2;
                                    MAMB[LAA][CAA]=0;}}}
           //=========================================  CASA CANTO SUPERIOR DA DIREITA ==================================================//
                   else if(LA==n-1&&CA==n-1){                                           // SE ESTIVER NA ÚLTIMA COLUNA
                        if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                            if(ouro==0){                           // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%2;
                                if(DF==1){
                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                else if(DF==0){
                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%2;
                                if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                    LAA=LA;
                                    CAA=CA;
                                    if(MAMB[LA][CA-1]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                    else if(MAMB[LA][CA-1]==0){
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%2;
                                    if(DF==1){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                else {
                                    DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA;
                                        CAA=CA;
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%2;
                                    if(DM==1){           //  SE DER 1 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");
                                            MAMB[LAA][CAA]=0;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){          //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");
                                            MAMB[LAA][CAA]=0;}
                                        else if(MAMB[LA][CA-1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                                    DM= rand()%2;
                                        if(DM==1){                 //  SE DER 1 MOVER PARA BAIXO
                                            LAA=LA;
                                            CAA=CA;
                                            if(MAMB[LA-1][CA]==5){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");
                                                MAMB[LAA][CAA]=0;}
                                            else if(MAMB[LA-1][CA]==4){
                                                LA--;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}
                                        else if(DM==0){            //  SE DER 0 MOVER A ESQUERDA
                                            LAA=LA;
                                                CAA=CA;
                                                if(MAMB[LA][CA-1]==5){
                                                    MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                else if(MAMB[LA][CA-1]==0){
                                                    CA--;
                                                    MAMB[LA][CA]=2;
                                                    MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                                    if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                        ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                        MAMB[LA][CA]=2;
                                        MSEN[LA][CA]=0;     }
                                    else  { DM= rand()%2;
                                        if(DM==1){                           //  SE DER 1 MOVER PARA BAIXO
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}
                                        else if(DM==0){                      //  SE DER 0 MOVER A ESQUERDA
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                                    if(flecha==1){
                                        DF= rand()%2;
                                        if(DF==1){
                                            if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                            else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                        else if(DF==0){
                                            if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                            else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                    else{
                                        DM= rand()%2;
                                        if(DM==1){                     //  SE DER 1, DEVE MOVER-SE PARA BAIXO
                                        LAA=LA;
                                        CAA=CA;
                                            if(MAMB[LA-1][CA]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                            else if(MAMB[LA-1][CA]==0){
                                                LA--;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}
                                        if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                            LAA=LA;
                                            CAA=CA;
                                            if(MAMB[LA][CA-1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                            else if(MAMB[LA][CA-1]==0){
                                                CA--;
                                                MAMB[LA][CA]=2;
                                                MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                    DM= rand()%2;
                                    if(DM==1){
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){                     //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA;
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE NÃO ESTIVER SENTINDO NADA
                                    DM= rand()%2;
                                    if(DM==1){                             //  SE DER 1 DEVE MOVER-SE ABAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){                        //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}




                    }
           //=========================================  CASAS LATERAIS SUPERIORES  ======================================================//
                   else if(LA==n-1&&(CA!=0&&CA!=n-1)){                                  // SE ESTIVER NA PRIMEIRA LINHA E NA ULTIMA COLUNA
                            if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%3;
                                                if(DF==2){
                                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==1){
                                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                            else {
                                                DM= rand()%3;
                                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA-1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==0){
                                                        LA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                               else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA][CA-1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==0){
                                                        CA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA;
                                                    CAA=CA;
                                                    if(MAMB[LA][CA+1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==0){
                                                        CA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%3;
                                    if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){             //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    if(DM==0){                 //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {  DM= rand()%3;
                                    if(DM==2){              //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else {  DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 0 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                             else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                DM= rand()%3;
                                if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){             //  SE DER 1 MOVER A ESQUERDA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER A ESQUERDA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
           //=========================================  CASAS LATERAIS DA ESQUERDA  =====================================================//
                   else if(LA!=0&&LA!=n-1&&CA==0){                                      // SE ESTIVER NA ULTIMA COLUNA
                                    if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%3;
                                                if(DF==2){
                                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==1){
                                                    if(MAMB[LA+1][CA]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                            else {
                                                DM= rand()%3;
                                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA-1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==0){
                                                        LA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                               else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA+1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==0){
                                                        LA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA][CA+1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==0){
                                                        CA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%3;
                                    if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){                 //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");} }}
                            else {  DM= rand()%3;
                                    if(DM==2){              //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else {  DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 0 MOVER PARA CIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                             else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                DM= rand()%3;
                                if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
           //=========================================  CASAS LATERAIS DA DIREITA  ======================================================//
                   else if((LA!=0&&CA!=n-1)&&CA==n-1){                                  // SE ESTIVER NA ULTIMA COLUNA
                            if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%3;
                                                if(DF==2){
                                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==1){
                                                    if(MAMB[LA+1][CA]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                            else {
                                                DM= rand()%3;
                                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA-1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==0){
                                                        LA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                               else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA+1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==0){
                                                        LA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA; CAA=CA;
                                                    if(MAMB[LA][CA-1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==0){
                                                        CA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%3;
                                    if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){                 //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {  DM= rand()%3;
                                    if(DM==2){              //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;  printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else {  DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 0 MOVER PARA CIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%3;
                                    if(DF==2){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                             else {
                                DM= rand()%3;
                                if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                DM= rand()%3;
                                if(DM==2){                  //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%3;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        LAA=LA; CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA; CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
           //=========================================  CASAS CENTRAIS  ===========M======================================================//
                   else if((LA!=0&&LA!=n-1)&&(CA!=0&&CA!=n-1)){                         // SE ESTIVER NAS CASAS CENTRAIS

                            if(MSEN[LA][CA]==12){                      //  SE ESTIVER SENTINDO BRISA, BRILHO E FEDOR
                                            if(ouro==0){               // CASO NÃO TENHA PEGO O OURO AINDA
                                            ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                            MAMB[LA][CA]=2;
                                            MSEN[LA][CA]=0;     }
                                            else if(flecha==1){
                                                DF= rand()%4;
                                                if(DF==3){
                                                    if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==2){
                                                    if(MAMB[LA+1][CA]==4){MAMB[LA][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==1){
                                                    if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                                else if(DF==0){
                                                    if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                                    else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                                            else {
                                                DM= rand()%4;
                                                if(DM==3){           //  SE DER 2 MOVER PARA BAIXO
                                                    LAA=LA;
                                                    CAA=CA;
                                                    if(MAMB[LA-1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA-1][CA]==0){
                                                        LA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                               else if(DM==2){          //  SE DER 1 MOVER PARA CIMA
                                                    LAA=LA;
                                                    CAA=CA;
                                                    if(MAMB[LA+1][CA]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA+1][CA]==0){
                                                        LA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA;
                                                    CAA=CA;
                                                    if(MAMB[LA][CA-1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA-1]==0){
                                                        CA--;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}
                                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                                    LAA=LA;
                                                    CAA=CA;
                                                    if(MAMB[LA][CA+1]==5){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==4){
                                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                                    else if(MAMB[LA][CA+1]==0){
                                                        CA++;
                                                        MAMB[LA][CA]=2;
                                                        MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==11){                  //  SE ESTIVER SENTINDO BRILHO E FEDOR
                            if(ouro==0){                            // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else if(flecha==1){
                                DF= rand()%4;
                                    if(DF==3){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");} }
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {
                                DM= rand()%4;
                                if(DM==3){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==2){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                         else if(MSEN[LA][CA]==10){                  //  SE ESTIVER SENTINDO BRISA E BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else  { DM= rand()%4;
                                    if(DM==3){                  //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==5){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                    else if(DM==2){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){                 //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){                 //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==9){                  //  SE ESTIVER SENTINDO BRISA E FEDOR
                            if(flecha==1){
                                DF= rand()%4;
                                    if(DF==3){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                            else {  DM= rand()%4;
                                    if(DM==3){              //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA-1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==2){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POÇO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==4){
                                                MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==8){                    //  SE ESTIVER SENTINDO BRILHO
                            if(ouro==0){                             // CASO NÃO TENHA PEGO O OURO AINDA
                                ouro= ouro + 1; printf("\n\n============ PEGOU O OURO ==================\n\n");
                                MAMB[LA][CA]=2;
                                MSEN[LA][CA]=0;     }
                            else {  DM= rand()%4;
                                    if(DM==3){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA;
                                        CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==2){          //  SE DER 0 MOVER PARA CIMA
                                        LAA=LA;
                                        CAA=CA; LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA;
                                        CAA=CA; CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA;
                                        CAA=CA; CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==7){                  //  SE ESTIVER SENTINDO FEDOR
                            if(flecha==1){
                                DF= rand()%4;
                                    if(DF==3){
                                        if(MAMB[LA-1][CA]==4){MAMB[LA-1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==2){
                                        if(MAMB[LA+1][CA]==4){MAMB[LA+1][CA]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}
                                    else if(DF==1){
                                        if(MAMB[LA][CA-1]==4){MAMB[LA][CA-1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");} }
                                    else if(DF==0){
                                        if(MAMB[LA][CA+1]==4){MAMB[LA][CA+1]=0;flecha=flecha - 1; printf("\n\n\tMATOU O WUMPUS\n\n");}
                                        else {flecha= flecha - 1; printf("\n\n\tERROU A FLECHA\n\n");}}}
                             else {
                                DM= rand()%4;
                                if(DM==3){           //  SE DER 2 MOVER PARA BAIXO
                                    if(MAMB[LA-1][CA]==4){
                                        MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                    else if(MAMB[LA-1][CA]==0){
                                        LAA=LA; CAA=CA; LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}
                                else if(DM==2){          //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==4){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE MORREU NO WUMPUS\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}}
                        else if(MSEN[LA][CA]==6){                  //  SE ESTIVER SENTINDO BRISA
                                DM= rand()%4;
                                if(DM==3){                  //  SE DER 2 MOVER PARA BAIXO
                                        if(MAMB[LA-1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                else if(MAMB[LA-1][CA]==0){
                                            LAA=LA; CAA=CA; LA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==2){             //  SE DER 1 MOVER PARA CIMA
                                        if(MAMB[LA+1][CA]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA+1][CA]==0){
                                            LAA=LA; CAA=CA; LA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==1){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA-1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA-1]==0){
                                            LAA=LA; CAA=CA; CA--;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}
                                else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        if(MAMB[LA][CA+1]==5){
                                            MAMB[LA][CA]=0;   printf("\n\n\tAGENTE CAIU NO POCO\n\n");break;}
                                        else if(MAMB[LA][CA+1]==0){
                                            LAA=LA; CAA=CA; CA++;
                                            MAMB[LA][CA]=2;
                                            MAMB[LAA][CAA]=0;}}}
                        else if(MSEN[LA][CA]==0){                  //  SE ESTIVER SENTINDO BRISA
                            DM= rand()%4;
                                    if(DM==2){           //  SE DER 2 MOVER PARA BAIXO
                                        LAA=LA;
                                        CAA=CA;
                                        LA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==1){          //  SE DER 1 MOVER PARA CIMA
                                        LAA=LA;
                                        CAA=CA;
                                        LA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==3){          //  SE DER 3 MOVER A DIREITA
                                        LAA=LA;
                                        CAA=CA;
                                        CA--;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}
                                    else if(DM==0){          //  SE DER 0 MOVER A DIREITA
                                        LAA=LA;
                                        CAA=CA;
                                        CA++;
                                        MAMB[LA][CA]=2;
                                        MAMB[LAA][CAA]=0;}}}

printf("\n\n");
        }
    // =================================================================================================================================
	      // IMPRIMINDO A MATRIZ AMBIENTE FINAL
	      for(i= n -1; i>= 0; i--){printf("\t   ");
	for(j=0; j < n; j++){
		if(MAMB[i][j]==3)
		{	printf("O ");}
		else if(MAMB[i][j]==4)
		{   printf("W ");}
		else if(MAMB[i][j]==2)
		{   printf("A ");}
		else if(MAMB[i][j]==5)
		{	printf("P ");}
		else printf("- ");
	}printf("\n");}
printf("\n\n\n");



	if(ouro==1){
            {printf("========================= PARABENS VOCE VENCEU!!================================");}}
    else{printf("==================   VOCE PERDEU!   ============================\n\n");}

    return 0;


}
