#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ROW 25
#define COL 35
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// 									ESCOLA SUPERIOR TECNOLOGIA E GEST�O

//											TPSI - PROGRAMA��O

//									   	  TRABALHO REALIZADO POR: 
//								DIOGO SILVA (19525) E LEONOR CALDEIRA (23404)

//											DATA: 06/01/2023

//										  ANO LETIVO 2022/2023

//FUN��ES CRIADAS:
void inicia_tabuleiro(int tabuleiro[ROW][COL]);
void exibe_tabuleiro(int tabuleiro[ROW][COL]);
void inserir_celula(int tabuleiro[ROW][COL]);
void inserir_N_celula(int tabuleiro[ROW][COL]);
void apagar_celula(int tabuleiro[ROW][COL]);
void apagar_N_celula(int tabuleiro[ROW][COL]);
void reinicia(int tabuleiro[ROW][COL]);
void contagem_vizinhos(int tabuleiro[ROW][COL]);
void debug(int tabuleiro[ROW][COL]);
void avancar_geracao(int tabuleiro[ROW][COL]);
void delay(int milliseconds);
void avancar_N_geracoes(int tabuleiro[ROW][COL]);
void calculos_estatisticas(int tabuleiro[ROW][COL]);
void estatisticas(int tabuleiro[ROW][COL]);
void velocidade_padrao(int tabuleiro[ROW][COL]);
void velocidade(int tabuleiro[ROW][COL]);
void exibicao_tabuleiro_config(int tabuleiro[ROW][COL]);
void exibicao_estatisticas_config(int tabuleiro[ROW][COL]);
void menuConfiguracoes(int tabuleiro[ROW][COL]);
void menu(int tabuleiro[ROW][COL]);

//VARI�VEIS GLOBAIS:
int linha, coluna;
int milliseconds = 100;
int geracao=1, vivas=0;
int min_vivas=0, max_vivas=0, geracao_min_vivas=0, geracao_max_vivas=0, viva_mais_velha=0, geracao_viva_mais_velha=0;
int contagem1_20=0, contagem21_40=0, contagem41_60=0, contagem61_80=0, contagem80plus=0;
bool mostra_estatistica = false;
bool mostra_tabuleiro = false;
//------------------------------------------------------------------------------------------------
//MAIN - fun��o principal para iniciar
int main(int argc, char *argv[]) {
	
	int tabuleiro[ROW][COL];
	
	inicia_tabuleiro(tabuleiro);
	menu(tabuleiro);

	
	return 0;
}

//------------------------------------------------------------------------------------------------
//INICIAR O TABULEIRO - Fun��o para iniciar tabuleiro a 0's (Diogo e Leonor)
void inicia_tabuleiro(int tabuleiro[ROW][COL]){

	
	
	for(linha=0; linha<ROW; linha++){
		for(coluna=0; coluna<COL; coluna++){
			tabuleiro[linha][coluna]=0; 	//Preenche toda a matriz com 0's (Sem celulas/celulas mortas);	 
		}
	}
	
}


//------------------------------------------------------------------------------------------------
//EXIBIR O TABULEIRO - Fun��o que faz mostrar o tabuleiro do jogo
void exibe_tabuleiro(int tabuleiro[ROW][COL]){
	
	int count=0;
	
	printf(" Geracao: %d", geracao);
	
	for(linha = 0; linha < ROW; linha++){
		printf("\n");
		for(coluna = 0; coluna < COL; coluna++){
			
			if(tabuleiro[linha][coluna] == 0){
				printf(" . ");	
			}
			else{
				printf(" %c ", 254);
			//	printf(" %d ", tabuleiro[linha][coluna]); //descomentar este print e comentar o print acima para debug
			}
		}
	}
	
	
	printf("\n\n\n");
	
}

//------------------------------------------------------------------------------------------------
//INSERIR UMA C�LULA - Fun��o para inserir uma celula
void inserir_celula(int tabuleiro[ROW][COL]){              //  (Diogo)
    
   
	//do-while -> verficar se a coordenada ja tem uma celula if(!=0)
	do{
		
		do{
			linha=0;
			fflush(stdin);
			printf("\nInsira o numero da linha que deseja inserir a celula (1-25): ");
	    	scanf("%d", &linha);
	    	
	    	if(linha > ROW || linha <= 0 || linha=='a' || linha=='z' || linha=='A' || linha=='Z'){
	        	printf("\nCaracter errado!\n");
	    	}
	    	
		}while(linha > ROW || linha <= 0 || linha=='a' || linha=='z' || linha=='A' || linha=='Z');
	    
	 	
		do{
			coluna=0;
			fflush(stdin);
		    printf("\nInsira o numero da coluna que deseja inserir a celula (1-35): ");
		    scanf("%d", &coluna);
		
		    if(coluna > COL || coluna <= 0 || coluna=='a' || coluna=='z' || coluna=='A' || coluna=='Z'){
		        printf("\nCaracter errado!\n");
	    	}
			
		}while(coluna > COL || coluna <= 0 || coluna=='a' || coluna=='z' || coluna=='A' || coluna=='Z');
		
	}while(tabuleiro[linha-1][coluna-1]!=0);
		
	
	
    
    tabuleiro[linha-1][coluna-1] = 1;

}

//------------------------------------------------------------------------------------------------
//INSERIR 'N' C�LULAS - Fun��o para inserir v�rias celulas
void inserir_N_celula(int tabuleiro[ROW][COL]){  //  (Diogo)

    char resposta;

    inserir_celula(tabuleiro);

    do{
        fflush(stdin);
        printf("\nDeseja continuar a inserir? (S / N): ");
        scanf("%c", &resposta);

		printf("\n");
		
        if(resposta == 's' || resposta == 'S'){
            inserir_celula(tabuleiro);
        }
        else if(resposta == 'n' || resposta == 'N'){
        	exibe_tabuleiro(tabuleiro);
        	menu(tabuleiro);
        }
        else{
        	printf("\nCaracter errado!\n");
		}

    }while(resposta=='S' || resposta=='s' || resposta!='n' || resposta!='N');


}

//------------------------------------------------------------------------------------------------
//APAGAR UMA C�LULA - fun��o para apagar uma c�lula
void apagar_celula(int tabuleiro[ROW][COL]) {         //  (Leonor)

	
	do{
		
		do {
			linha = 0;
			
			fflush(stdin);
			printf("\nInsira o numero da linha que deseja apagar a celula (1-25): ");
			scanf("%d", &linha);
			
			if(linha > ROW || linha <= 0 || linha == 'a' || linha == 'z' || linha == 'A' || linha == 'Z'){
				
				printf("\nCaracter errado!\n");
			}
			
		}while(linha > ROW || linha <= 0 || linha == 'a' || linha == 'z' || linha == 'A' || linha == 'Z');	
	
		do {	
			coluna = 0;
			
			fflush(stdin);		
			printf("\nInsira o numero da coluna que deseja apagar a celula (1-35): ");
			scanf("%d", &coluna);
				
			if (coluna > COL || coluna <= 0 || coluna == 'a' || coluna == 'z' || coluna == 'A' || coluna == 'Z'){
				
				printf("\nCaracter errado!\n");
			}
				
		}while(coluna > COL || coluna <= 0 || coluna == 'a' || coluna == 'z' || coluna == 'A' || coluna == 'Z');
		
		if (tabuleiro [linha - 1][coluna - 1] == 1){
			
			tabuleiro[linha - 1][coluna - 1] = 0;	
		}
		
	}while(tabuleiro[linha][coluna] != 0);	
}


//------------------------------------------------------------------------------------------------
//APAGAR 'N' C�LULAS - fun��o para apagar v�rias c�lulas
void apagar_N_celula(int tabuleiro[ROW][COL]) { //  (Leonor)

	char resposta;

	apagar_celula(tabuleiro);
	
	do{
		
        fflush(stdin);
        printf("\nDeseja continuar a apagar? (S / N): ");
        scanf("%c", &resposta);
        
        printf("\n");

        if(resposta == 'S' || resposta == 's'){
        	
            apagar_celula(tabuleiro);
        }
        else if(resposta == 'N' || resposta == 'n'){
        	
            exibe_tabuleiro(tabuleiro);
            
            menu(tabuleiro);
        }
        else{
        	printf("\nCaracter errado!\n");
		}

    }while(resposta == 'S' || resposta == 's' || resposta != 'n' || resposta != 'N');


}
//------------------------------------------------------------------------------------------------
//REINICIAR - fun��o para reiniciar o jogo
void reinicia(int tabuleiro[ROW][COL]) { //  (Leonor)
	
	char resposta;
	
	do{
		
        fflush(stdin);
        printf("\nTem a certeza que quer reiniciar o tabuleiro? (S / N): ");
        scanf("%c", &resposta);
        
        printf("\n");

        if(resposta == 'S' || resposta == 's'){
        	fflush(stdin);
    		system("cls");
			inicia_tabuleiro(tabuleiro);
			geracao = 0;
			vivas = 0;
			max_vivas = 0;
			geracao_max_vivas = 0;
			min_vivas = 0;
			geracao_min_vivas = 0;
			viva_mais_velha = 0;
			geracao_viva_mais_velha = 1; //Valor default=1 
            exibe_tabuleiro(tabuleiro);
            break;
        }
        else if(resposta == 'N' || resposta == 'n') {
        	
            exibe_tabuleiro(tabuleiro);
            break;
        }
        else{
        	
        	printf("\nCaracter errado!\n");
		}

    }while(resposta == 'S' || resposta == 's' || resposta != 'n' || resposta != 'N');


}


//------------------------------------------------------------------------------------------------
//DEBUG - Fun��o Debug para uma r�pida resolu��o de problemas
void debug(int tabuleiro[ROW][COL]){

//Glider
tabuleiro[14][9] = 1;
tabuleiro[15][9] = 1;
tabuleiro[16][9] = 1;
tabuleiro[16][8] = 1;
tabuleiro[15][7] = 1;


tabuleiro[5][5] = 1;
tabuleiro[5][6] = 1;
tabuleiro[6][5] = 1;
tabuleiro[6][6] = 1;
tabuleiro[6][7] = 1;

tabuleiro[20][30] = 1;
tabuleiro[21][30] = 1;
tabuleiro[22][30] = 1;

tabuleiro[10][5] = 1;
tabuleiro[11][5] = 1;
tabuleiro[11][6] = 1;
tabuleiro[11][7] = 1;
tabuleiro[10][8] = 1;
tabuleiro[11][8] = 1;

geracao=1;

system("cls");

}


//------------------------------------------------------------------------------------------------
//AVAN�A UMA GERA��O - Fun��o para realizar o avan�o de uma gera��o
void avancar_geracao(int tabuleiro[ROW][COL]){ 	//(Diogo)
	
	int tabuleiroProximaGeracao[ROW][COL];
	int vizinhas;
	
	inicia_tabuleiro(tabuleiroProximaGeracao);
	//PASSO 1
			//Verificar a vizinhan�a (8 posi��es) da c�lula que est� a ser iterada deste momento no ciclo for
			//Sempre que for encontrada uma vizinha viva o contador de vizinhas deve incrementar
			//(Fazer primeiro tabuleiro normal e depois de estar a funcionar optimizar para esferica) -> if's
	
	for(int linha = 0; linha < ROW; linha++){       //(Leonor)
		for(int coluna = 0; coluna < COL; coluna++){
			vizinhas = 0;
			
			if (linha != 0 && linha != ROW-1 && coluna != 0 && coluna != COL-1) {
				
    			if(tabuleiro[linha][coluna-1] > 0){ //esq
    				vizinhas++;
    			}
    			if(tabuleiro[linha+1][coluna-1] > 0){ // esq; baixo
    				vizinhas++;
    			}
    			if(tabuleiro[linha+1][coluna] > 0){ // baixo
    				vizinhas++;
    			}
    			if(tabuleiro[linha+1][coluna+1] > 0){ // dir; baixo
    				vizinhas++;
    			}
    			if(tabuleiro[linha][coluna+1] > 0){ // dir
    				vizinhas++;
    			}
    			if(tabuleiro[linha-1][coluna+1] > 0){ // cima; dir
    				vizinhas++;
    			}
    			if(tabuleiro[linha-1][coluna] > 0){ // cima
    				vizinhas++;
    			}
    			if(tabuleiro[linha-1][coluna-1] > 0){ // cima; esq
    				vizinhas++;
    			}   
			} else {
			    if (linha == 0) {
			        if (coluna == 0) {
			        	
//			            1 0 0 0 0 esq; cima
//            		    0 0 0 0 0
//            			0 0 0 0 0
//            			0 0 0 0 0 

            			if(tabuleiro[linha][COL-1] > 0){ //esq
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][COL-1] > 0){ // esq; baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][coluna] > 0){ // baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][coluna+1] > 0){ // dir; baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha][coluna+1] > 0){ // dir
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][coluna+1] > 0){ // cima; dir
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][coluna] > 0){ // cima
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][COL-1] > 0){ // cima; esq
            				vizinhas++;
            			}
			        } else if (coluna == COL-1) {
			        	
//			            0 0 0 0 1 dir:linha=0; coluna = 0
//            			0 0 0 0 0 
//            			0 0 0 0 0
//            			0 0 0 0 0 cima:linha=ROW-1; coluna = COL-1
            			
            			if(tabuleiro[linha][coluna-1] > 0){ //esq
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][coluna-1] > 0){ // esq; baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][coluna] > 0){ // baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha+1][0] > 0){ // dir; baixo
            				vizinhas++;
            			}
            			if(tabuleiro[linha][0] > 0){ // dir
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][0] > 0){ // cima; dir
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][coluna] > 0){ // cima
            				vizinhas++;
            			}
            			if(tabuleiro[ROW-1][coluna-1] > 0){ // cima; esq
            				vizinhas++;
            			} 
			        } else {
			        	
//			            0 1 0 0 0 cima: linha = ROW-1; coluna=coluna
//            			0 0 0 0 0 cima,esq
//            			0 0 0 0 0 cima, dir
//            			0 0 0 0 0
						if(tabuleiro[linha][coluna-1] > 0){ //esq
    					vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna] > 0){ // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna+1] > 0){ // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][coluna+1] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[ROW-1][coluna+1] > 0){ // cima; dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[ROW-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[ROW-1][coluna-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}   
			        }
			    } else if (linha == ROW-1) {
			        if (coluna == 0) {
			        	
//			            0 0 0 0 0
//            			0 0 0 0 0 esq; baixo
//            			0 0 0 0 0
//            			1 0 0 0 0

						if(tabuleiro[linha][COL-1] > 0){ //esq
    					    vizinhas++;
		    			}
		    			if(tabuleiro[0][COL-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna] > 0){  // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna+1] > 0){ // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][coluna+1] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna+1] > 0){ // cima; dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][COL-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}   
						
			        } else if (coluna == COL-1) {
			        	
//			            0 0 0 0 0
//            			0 0 0 0 0
//            			0 0 0 0 0 dir;baixo
//            			0 0 0 0 1

						if(tabuleiro[linha][coluna-1] > 0){ //esq
    						vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna] > 0){ // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][0] > 0){ // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][0] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][0] > 0){ // cima; dir
		    				vizinhas++;
		    			} 
		    			if(tabuleiro[linha-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}
			        } else {
			        	
//			            0 0 0 0 0
//            			0 0 0 0 0
//            			0 0 0 0 0
//            			0 1 0 0 0 baixo

						if(tabuleiro[linha][coluna-1] > 0){ //esq
    						vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna] > 0){ // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[0][coluna+1] > 0){  // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][coluna+1] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna+1] > 0){ // cima; dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}   
			        }
			    } else {
			        if (coluna == 0) {
			        	
//			            0 0 0 0 0
//            			0 0 0 0 0
//            			1 0 0 0 0 esq
//            			0 0 0 0 0

            			if(tabuleiro[linha][COL-1] > 0){ //esq
    						vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][COL-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna] > 0){ // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna+1] > 0){ // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][coluna+1] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna+1] > 0){ // cima; dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][COL-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}   
			        } else if (coluna == COL-1) {
			        	
//			            0 0 0 0 0
//            			0 0 0 0 0 dir
//            			0 0 0 0 1
//            			0 0 0 0 0
					
						if(tabuleiro[linha][coluna-1] > 0){ //esq
    						vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna-1] > 0){ // esq; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][coluna] > 0){ // baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha+1][0] > 0){ // dir; baixo
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha][0] > 0){ // dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][0] > 0){ // cima; dir
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna] > 0){ // cima
		    				vizinhas++;
		    			}
		    			if(tabuleiro[linha-1][coluna-1] > 0){ // cima; esq
		    				vizinhas++;
		    			}
			        }
			    } 
			}
			
			//printf("%3d", vizinhas); //DEBUG
			
			//PASSO 2
			//Aplicar as regras da genetica de Conway, com base no numero de vizinhas que foi calculado no passo 1
			//A nova gera��o deve ser criada no tabuleiro da proxima gera��o ->  if-else if
			if(tabuleiro[linha][coluna]>=1 && vizinhas == 2 || vizinhas == 3){ //sobreviver
				tabuleiroProximaGeracao[linha][coluna] = tabuleiro[linha][coluna] + 1;
				//printf("%d", tabuleiroProximaGeracao[linha][coluna]);
			}
			else if(vizinhas >=4 || vizinhas ==1 || vizinhas == 0){ // morte
				tabuleiroProximaGeracao[linha][coluna]=0;
			}
			else if(tabuleiro[linha-1][coluna]==0 && vizinhas == 3){ // nascimento -> linha-1 porque � uma casa vazia
				tabuleiroProximaGeracao[linha][coluna]=1;
			}
			
		}
	} 
	
	
	//PASSO 3 (Leonor)
	//Substituir os valores do tabuleiro pelos do tabuleiro da proxima gera��o -> dois 'for' para percorrer as posicoes
	for(int linha = 0; linha < ROW; linha++) {
		
		for(int coluna = 0; coluna < COL; coluna++) {
			
		tabuleiro[linha][coluna] = tabuleiroProximaGeracao[linha][coluna];
			
		}	
	}
	
	
	//PASSO 4
	//Incrementar uma vari�vel global que conta as gera��es
	geracao++;
	
	
	calculos_estatisticas(tabuleiro); //Ir� apanhar os dados necess�rios para os c�lculos -> colocar a exibi��o das estatisticas onde e quando o utilizador quiser
	
	if(mostra_tabuleiro){
		exibe_tabuleiro(tabuleiro); //Aqui atualiza gera��o a gera��o
	}
	
	if (mostra_estatistica) { //mostra ao longo das gera�oes se a variavel for true

		estatisticas(tabuleiro);
	}
	
	
	
}

//------------------------------------------------------------------------------------------------
//DELAY - Fun��o para atrasar a atualiza��o do tabuleiro entre as gera��es
void delay(int milliseconds){
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while((now-then) < pause){
        now = clock();
    }
        
}

//------------------------------------------------------------------------------------------------
//AVAN�AR 'N' GERA��ES - Fun��o para realizar o avan�o de v�rias gera��es
void avancar_N_geracoes(int tabuleiro[ROW][COL]){  //Diogo
	
	int ngeracao;
	bool number = false;
	
	do{
		fflush(stdin);
		printf("\n Digite quantas geracoes pretende avancar: ");
		scanf("%d", &ngeracao);
		printf("\n");
		
		if(ngeracao<0 || ngeracao == 'a' || ngeracao == 'z' || ngeracao == 'A' || ngeracao == 'Z'){
			number=false;
		}
		else{
			number=true;
		}
		
        if(ngeracao){
        	
            for(int i=1; i<=ngeracao; i++){
				system("cls");
				avancar_geracao(tabuleiro);
				delay(milliseconds);
			}
        }
        else{
        	system("cls");
        	printf("\n Caracter errado!\n");
		}

    }while(!ngeracao);
		
	if(!mostra_tabuleiro){
		exibe_tabuleiro(tabuleiro); //Aqui aparece no fim de todas as gera��es
	}	
		
	if (!mostra_estatistica) {  //Mostra as estat�sticas no fim
	 
		estatisticas(tabuleiro);			
	}
		
	
}
//------------------------------------------------------------------------------------------------
//C�LCULOS DAS ESTATISTICAS - Fun��o para realizar os c�lculos necess�rios para as estatisticas do jogo
void calculos_estatisticas(int tabuleiro[ROW][COL]){
	
	vivas=0;
	contagem1_20=0, contagem21_40=0, contagem41_60=0, contagem61_80=0, contagem80plus=0;
	
	int vivas_20plus=0, vivas_minor21_40plus=0, vivas_minor41_60plus=0, vivas_minor61_80plus=0, vivas_minor80=0;
	int viva_mais_velha_atual = 0;
	
	
	
	for(int linha = 0; linha < ROW; linha++){       
		for(int coluna = 0; coluna < COL; coluna++){
													
			if(tabuleiro[linha][coluna] >= 1){
				
				vivas++;						//n�mero de c�lulas vivas na presente gera��o (Leonor)
			}	
			if(tabuleiro[linha][coluna] > viva_mais_velha){       
				
				viva_mais_velha = tabuleiro[linha][coluna];				//o valor da idade da c�lula mais velha que tenha sido encontrada (Leonor)
			}	
			
			if(tabuleiro[linha][coluna] > viva_mais_velha_atual) {
				
				viva_mais_velha_atual = tabuleiro[linha][coluna];
			}
			
			if(tabuleiro[linha][coluna]>=1 && tabuleiro[linha][coluna]<=20){ //Contar as c�lulas de cada intervalo (Diogo)
				contagem1_20++;
			}
			if(tabuleiro[linha][coluna]>=21 && tabuleiro[linha][coluna]<=40){
				contagem21_40++;
			}
			if(tabuleiro[linha][coluna]>=41 && tabuleiro[linha][coluna]<=60){
				contagem41_60++;
			}
			if(tabuleiro[linha][coluna]>=61 && tabuleiro[linha][coluna]<=80){
				contagem61_80++;
			}
			if(tabuleiro[linha][coluna]>80){
				contagem80plus++;
			}
		}
	}
	
	
	if(min_vivas==0 || max_vivas==0){			//confirmar se ele faz apenas uma vez, n�mero minimo de c�lulas vivas � igual ao n�mero m�ximo de c�lulas vivas (Diogo)
		min_vivas=max_vivas=vivas;
	}
	else{
		if(vivas>max_vivas && geracao>geracao_max_vivas){   			//n�mero m�ximo de c�lulas vivas e a gera��o onde ocorreu (Diogo)
			max_vivas=vivas;
			geracao_max_vivas=geracao;
			
		}
		if(vivas<min_vivas && geracao>geracao_min_vivas){
			min_vivas=vivas;
			geracao_min_vivas=geracao;						//n�mero minimo de c�lulas vivas e a gera��o onde ocorreu (Diogo)
			
		}
	}
	 
	if(viva_mais_velha_atual == viva_mais_velha) {  //o valor da idade da c�lula mais velha que tenha sido encontrada (Leonor)
    	
		if(geracao - viva_mais_velha > geracao_viva_mais_velha){
			
	        geracao_viva_mais_velha = geracao - viva_mais_velha;
	    }	
	}
	
	
	//C�lculos para os intervalos do histograma (Diogo)
	contagem1_20 = vivas - contagem21_40 - contagem41_60 - contagem61_80 - contagem80plus;
	contagem21_40 = vivas - contagem1_20 - contagem41_60 - contagem61_80 - contagem80plus;
	contagem41_60 = vivas - contagem1_20 - contagem21_40 - contagem61_80 - contagem80plus;
	contagem61_80 = vivas -	contagem1_20 - contagem21_40 - contagem41_60 - contagem80plus;
	contagem80plus = vivas - contagem1_20 - contagem21_40 - contagem41_60 - contagem61_80;
	
	
}
//------------------------------------------------------------------------------------------------
//ESTATISTICAS - Fun��o que mostra as estatisticas
void estatisticas(int tabuleiro[ROW][COL]){
	
	
	calculos_estatisticas(tabuleiro);
	
	printf("\n\n  Estatisticas\n\n");

	printf("\n  Nr de celulas vivas: %d\n", vivas);
		
	printf("\n  Historico de nr de celulas vivas maximas: %d			Geracao onde ocorreu: %d\n", max_vivas, geracao_max_vivas);
	
	printf("\n  Historico de nr de celulas vivas minimas: %d			Geracao onde ocorreu: %d\n", min_vivas, geracao_min_vivas);
	
	printf("\n  Idade da celula mais velha do jogo: %dg			Geracao onde nasceu: %d\n", viva_mais_velha, geracao_viva_mais_velha);
	
	
	//Histograma da idade das c�lulas
	
	printf("\n  Histograma: \n");
	
	printf("  Idade [1-20]: %d\n", contagem1_20); 
	printf("  Idade [21-40]: %d\n", contagem21_40);
	printf("  Idade [41-60]: %d\n", contagem41_60);
	printf("  Idade [61-80]: %d\n", contagem61_80);
	printf("  Idade [+80]: %d\n", contagem80plus);
	
}

//------------------------------------------------------------------------------------------------
//VELOCIDADE PADR�O(Menu Configura��es) - fun��o para mostrar ao utilizador a velocidade do delay na atualiza��o do tabuleiro que se encontra em utiliza��o
void velocidade_padrao(int tabuleiro[ROW][COL]){
	
	system("cls");
	
	printf("\nA velocidade de simulacao encontra-se em %d milisegundos.\n", milliseconds);
		
	delay(milliseconds);
	

}

//------------------------------------------------------------------------------------------------
//VELOCIDADE(Op��o n�1 - Menu de configura��es) - Fun��o para o utilizador escolher a velocidade de delay na atualiza��o do tabuleiro
void velocidade(int tabuleiro[ROW][COL]){
	
	char resposta;	
	
	do {
		
		fflush(stdin);
		velocidade_padrao(tabuleiro);
		
		printf("\nDeseja alterar a velocidade? (S / N): ");
    	scanf("%c", &resposta);

        if (resposta == 'S' || resposta == 's') {
        	
        	printf("\nInsira a velocidade de simulacao, em milisegundos, que deseja: ");
        	scanf("%d", &milliseconds);
        	
        	delay(milliseconds);
			
			printf("\nA velocidade de simulacao encontra-se em %d milisegundos.", milliseconds);
			printf("\n");
		}		
        
        else if (resposta == 'N' || resposta == 'n') {
        	
        	break;
        }
        else{
        	
        	printf("\nCaracter errado!\n");
		}
	
    } while(resposta == 'S' || resposta == 's' || resposta != 'n' || resposta != 'N');

	
}

//------------------------------------------------------------------------------------------------
//EXIBI��O DO TABULEIRO(Op��o n�2 - Menu de configura��es) - Fun��o para a op��o n�2 do menu de configura��es que d� ao utilizador a hipotese de mudar a exibi��o do tabuleiro
void exibicao_tabuleiro_config(int tabuleiro[ROW][COL]){
	
	char resposta;

	do {
		
		fflush(stdin);
		
		printf("\nDeseja exibir o tabuleiro durante o avancar de geracoes? (S / N): ");
    	scanf("%c", &resposta);

        if (resposta == 'S' || resposta == 's') {
        
        	mostra_tabuleiro = true;
//        	printf("\n******%d******\n", mostra_estatistica); //DEBUG

        	break;
		}		
        
        else if (resposta == 'N' || resposta == 'n') {
        	
        	mostra_tabuleiro = false;
//        	printf("\n******%d******\n", mostra_estatistica); //DEBUG

        	break;
        }
        else{
        	printf("\nCaracter errado!\n");
		}
	
    } while(resposta=='S' || resposta=='s' || resposta!='n' || resposta!='N');
	
}

//------------------------------------------------------------------------------------------------
//EXIBI��O DAS ESTATISTICAS(Op��o n�3 - Menu de configura��es) - Fun��o para a op��o n�3 do menu de configura��es que d� ao utilizador a hipotese de mudar a exibi��o das estatisticas
void exibicao_estatisticas_config(int tabuleiro[ROW][COL]){
	
	char resposta;

	do {
		
		fflush(stdin);
		
		printf("\nDeseja exibir as estatisticas durante o avancar de geracoes? (S / N): ");
    	scanf("%c", &resposta);

        if (resposta == 'S' || resposta == 's') {
        
        	mostra_estatistica = true;
        //	printf("\n******%d******\n", mostra_estatistica); //DEBUG

        	break;
		}		
        
        else if (resposta == 'N' || resposta == 'n') {
        	
        	mostra_estatistica = false;
        //	printf("\n******%d******\n", mostra_estatistica); //DEBUG

        	break;
        }
        else{
        	
        	printf("\nCaracter errado!\n");
		}
	
    } while(resposta == 'S' || resposta == 's' || resposta != 'n' || resposta != 'N');
	
}

//------------------------------------------------------------------------------------------------
//MENU CONFIGURA��ES - Fun��o que mostra o menu de configura��es e as suas op��es
void menuConfiguracoes(int tabuleiro[ROW][COL]){
	
	int opcao;
	
	do{
		printf("\n ************************************************************************** \n");
		printf(" **************************************************************************\n");
		printf(" **                          Menu Configuracoes                          **\n");
		printf(" **************************************************************************\n");
		printf(" **                                                                      **\n");
		printf(" **                                                                      **\n");
		printf(" **    [1] - Velocidade de simulacao       				 **\n");
		printf(" **                                                                      **\n");
		printf(" **    [2] - Exibicao do tabuleiro entre o avan�ar das geracoes          **\n");
		printf(" **                                                                      **\n");
		printf(" **    [3] - Exibicao das estatisticas entre o avan�ar das geracoes.     **\n");
		printf(" **                                                                      **\n");
		printf(" **                                                                      **\n");
		printf(" **    [0] - Voltar ao Menu Principal                                    **\n");
		printf(" **                                                                      **\n");
		printf(" **************************************************************************\n");
		printf(" **************************************************************************\n");
		
		printf(" Digite a opcao: ");
		scanf("%d", &opcao);
		
		if(opcao!=0 && opcao>=4 || opcao=='a' || opcao=='z' || opcao=='A' || opcao=='Z'){
			do{
				system("cls");
				printf("\nCaracter errado!\n");
				fflush(stdin);
				menuConfiguracoes(tabuleiro);
				system("pause");
			}while(opcao!=0 && opcao>=4 || opcao=='a' || opcao=='z' || opcao=='A' || opcao=='Z');
		}
		switch(opcao){
			case 0:
				system("cls");
				menu(tabuleiro);
				system("pause");
				break;
			case 1:
				system("cls");
				velocidade(tabuleiro);
				system("pause");
				break;
			case 2:
				system("cls");
				exibicao_tabuleiro_config(tabuleiro);
				system("pause");
				break;
			case 3:
				system("cls");
				exibicao_estatisticas_config(tabuleiro);
				system("pause");
				break;
		}		
		
		
	}while(opcao!=0);
}

//------------------------------------------------------------------------------------------------
//MENU PRINCIPAL - Fun��o que mostra o menu principal e as suas op��es

void menu(int tabuleiro[ROW][COL]) {			// Abre o menu Principal (Diogo)
	
	int opcao;
	
	do{
		printf("\n ****************************************************************************** \n");
		printf(" ******************************************************************************\n");
		printf(" **                            Menu Principal                                **\n");
		printf(" ******************************************************************************\n");
		printf(" **                                   |                                      **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [1] - Inserir uma celula       |     [6] - Avancar uma geracao        **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [2] - Apagar uma celula        |     [7] - Avancar 'n' geracoes       **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [3] - Inserir varias celulas   |     [8] - Estatisticas               **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [4] - Apagar varias celulas    |     [9] - Configuracoes              **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [5] - Reiniciar o tabuleiro    |     [10] - Regras do jogo            **\n");
		printf(" **                                   |                                      **\n");
		printf(" **                                   |                                      **\n");
		printf(" **    [0] - Sair                     |     [11] - Debug                     **\n");
		printf(" **                                   |                                      **\n");
		printf(" ******************************************************************************\n");
		printf(" ******************************************************************************\n");
		
		printf(" Digite a opcao: ");
		scanf("%d", &opcao);
		
		
		if(opcao!=0 && opcao>=12 || opcao=='a' || opcao=='z' || opcao=='A' || opcao=='Z'){
			do{
				system("cls");
				printf("\nCaracter errado!\n");
				fflush(stdin);
				menu(tabuleiro);
			}while(opcao!=0 && opcao>=12 || opcao=='a' || opcao=='z' || opcao=='A' || opcao=='Z');
		}
		else if(opcao>=0 || opcao<=11){
			system("cls");
		}
		
		
		switch(opcao){
			case 0:
				printf("\n\n  GAME OVER\n\n");
				exit(1);
			case 1:
				system("cls");
				inserir_celula(tabuleiro);
				exibe_tabuleiro(tabuleiro);
				system("pause");
				break;
			case 2:
				system("cls");
				apagar_celula(tabuleiro);
				exibe_tabuleiro(tabuleiro);
				system("pause");
				break;
			case 3:
				system("cls");
				inserir_N_celula(tabuleiro);
				exibe_tabuleiro(tabuleiro);
				system("pause");
				break;
			case 4:
				system("cls");
				apagar_N_celula(tabuleiro);
				exibe_tabuleiro(tabuleiro);
				system("pause");
				break;
			case 5:
				reinicia(tabuleiro);
				system("pause");
				break;
			case 6:
				system("cls");
				avancar_geracao(tabuleiro);
				system("pause");
				break;
			case 7:
				system("cls");
				avancar_N_geracoes(tabuleiro);
				system("pause");
				break;
			case 8:
				system("cls");
				estatisticas(tabuleiro);
				system("pause");
				break;
			case 9:
				system("cls");
				//printf("Escolhi a opcao 9\n");
				menuConfiguracoes(tabuleiro);
				system("pause");
				break;
			case 10:
				system("cls");
				printf("\n\n 1 - Sobrevivencia: Uma celula rodeada por 2 ou 3 celulas vizinhas sobrevive e passara a geracao seguinte.\n");
				printf("\n 2 - Morte: Uma celula com 4 ou mais vizinhas morre devido a excesso de populacao. Uma celula com 1 ou nenhuma vizinhas morre por solidao. As celulas mortas s�o removidas do tabuleiro, ficando a celula vazia na geracao seguinte.\n");
				printf("\n 3 - Nascimento: Numa casa vazia rodeada por exactamente 3 celulas vizinhas, nascera uma celula na proxima geracao.\n");
				system("pause");
				break;
			case 11:
				system("cls");
				debug(tabuleiro);
				exibe_tabuleiro(tabuleiro);
				system("pause");
				break;
		}
		
	}while(opcao!=0);
}

//------------------------------------------------------------------------------------------------

