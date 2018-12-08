 #include<stdio.h>
 
 	typedef struct{
 		char nome[20], nacionalidade[10];
		int idade, camisa;
		float salario, altura, peso; 		
 		
	 }jogadores;
	 
	 
 /// ARQUIVO /////////////
 FILE*arquivo;
 ///////// FIM ARQ.
 
 ////////// ESTRUTURA /////////
 jogadores jogador, jogador_nulo;
 ////////////// FIM ESTR. //////////
 
 /////////////// CABEÇALHO /////////////////////
 void cabecalho(){
 	system("color e0");
	system ("cls");
 	printf("\nTabajara Esporte Clube\n\n");
 }/////////////////////////////// FIM CABEÇALHO //////////////

 
 /////////// CRIANDO O ARQ. ///////////////////////
 void criando_arq_jogadores(){
 		arquivo = fopen("arquivo.bin", "r+b");
 		
 		if(arquivo == NULL)
 		{
 			arquivo = fopen ("arquivo.bin", "w+b");
		 }
 } /////////////////// FIM CRIANDO ARQ. /////////////////////////////////////
 
 
 ///////////////////////////// INSERIANDO JOGADORES ///////////////////////////
 inserindo_jogador(){
 	int sair, i;
 	do{
 		cabecalho();
 		printf("\n");
 		printf("cadastro de jogadores");
 		printf("\n");
 		printf("Digite o nome do jogador:");
 		fflush(stdin);
 		gets(jogador.nome);
 		printf("\n");
 		printf("Digite o numero da camisa:");
 		scanf("%d", &jogador.camisa );
 		printf("\n");
 		printf("Digite a idade jogador:");
 		scanf("%d", &jogador.idade );
 		printf("\n");
 		printf("Digite o peso do jogador:");
 		scanf("%f", &jogador.peso );
 		printf("\n");
 		printf("Digite a altura do jogador:");
 		scanf("%f", &jogador.altura );
 		printf("\n");
 		printf("Digite a nacionalidade do jogador:");
 		fflush(stdin);
 		gets(jogador.nacionalidade);
 		printf("\n");
 		printf("Digite o salario do jogador:");
 		scanf("%f", &jogador.salario );
 		
 		fseek(arquivo, 0, SEEK_END);
 		fwrite(&jogador, sizeof(jogadores), 1, arquivo);
 		printf("Jogador cadastrado com sucesso!\n");
 		printf("\n");
 		printf("Deseja cadastrar outro cliente? 1-sim / 2- nao:");
 		scanf("%d", &sair);
 		printf("\n");
 		
	 }while(sair == 1);
 	
 	
 }/////////// FIM CADASTRANDO ////////////////////////////////////////
 
 
 //////////////////////// METODO PRINCIPAL ///////////////////////////
  main(){
 	int opcao;
 	criando_arq_jogadores();
 	
 	
 	do{
 		cabecalho();
 		printf("Escolha a opcao\n");
 		printf("\n");
 		printf("1-Cadastrar Jogador\n");
 		printf("\n");
 		printf("2-Consultar Jogador\n");
 		printf("\n");
 		printf("3-Listar Jogadores\n");
 		printf("\n");
 		printf("4-Remover Jogador\n");
 		printf("\n");
 		printf("0-Sair\n");
 		printf("\n");
 		printf("Digite um numero:");
 		scanf("%d", &opcao);
 	
 		
 	switch(opcao){
 		case 1:inserindo_jogador(); break;
 		case 2:consultar_jogador(); break;
 		case 3:listar_jogadores(); break;
 		case 4:remover_jogador(); break;
 		case 0:fclose(arquivo); break;
 		default: printf("Opcao invalida!"); break;	
	 }	
	 }while(opcao != 0);
 	
 }////////////////////////// FIM DO MET. PRINC. /////////////////////
 
 
 //////////// FUNC. PORCURAR ///////////////////////
procura_jogador(int camisa){
	int p;
	p= 0;
	
	rewind(arquivo);
	fread(&jogador, sizeof(jogadores), 1, arquivo );
	while (feof(arquivo) == 0){
		if(jogador.camisa==camisa){
			return p;
		}else{
			
			fread(&jogador, sizeof(jogadores), 1, arquivo);
			p++;
		}
	}return -1;	
}/////////////// FIM DA FUNC. PROCURAR //////////////

//////////////////// FUNC. MOSTAR //////////////////
mostra_jogador(int pos){
	fseek(arquivo, pos*sizeof(jogadores), SEEK_SET);
	
	fread(&jogador, sizeof(jogadores), 1, arquivo);
	
	printf("Nome:%s\nCamisa:%d\n%Idade:%d\n",jogador.nome, jogador.camisa, jogador.idade);
	printf("Peso:%f\nAltura:%f\nNacionalidade:%s\nSalario:%f", 
	jogador.peso, jogador.altura, jogador.nacionalidade, jogador.salario);
} /////////////////////// FIM DA FUNC. MOSTRAR ///////////

/////////////////////// FUNC. CONSULTAR ///////////////// 
consultar_jogador(){
	int sair, cami, posicao_jogador;
	do{
		cabecalho();
		printf("\n");
		printf("Consultar Jogador\n");
		printf("\n");
		printf("Digite o numero da camisa do Jogador:");
		scanf("%d", &cami);
		printf("\n");
		
		posicao_jogador = procura_jogador(cami);
		if(posicao_jogador== -1)
		printf("Jogador nao encontrado\n");
		else 
		mostra_jogador(posicao_jogador);
		printf("\n");
		printf("Deseja fazer outra consulta? 1-Sim/ 2-nao:");
		scanf("%d", &sair);
		
		
	}while(sair==1);
	
}////////////////////////////////// FIM DA FUNC. CONSULTAR ////////////////////////

////////////////////// FUNC. LISTAR /////////////////////
listar_jogadores(){
	cabecalho();
	printf("listagem de jogadores\n\n");
	rewind(arquivo);
	fread(&jogador, sizeof(jogadores), 1, arquivo);
	printf("\n________________________________________________________________________________\n");
	printf("  NU.CAMISA   NOME             IDADE   NACIONALIDADE");
 	printf("\n________________________________________________________________________________");
 	while(feof(arquivo)==0){
 		if(jogador.camisa != 0)
 		printf("\n%9d     %-10s %9d      %-0s\n", jogador.camisa, jogador.nome, jogador.idade, jogador.nacionalidade);
 		
 		fread(&jogador, sizeof(jogadores), 1, arquivo);
	 }
	printf("\n");
	printf("Tecle enter para voltar ao menu...");
	getche();
}////////////////// FIM DA FUNC. LISTAR //////////////

remover_jogador(){
	int camisa, confirm, resp, posicao;
	jogador_nulo.camisa =0;
	do{
	cabecalho();
	printf("Remover jogadres\n\n");
	printf("Numero da camisa:");
	scanf("%d", &camisa);
	posicao = procura_jogador(camisa);
	if(posicao == -1)
	printf("\nJogador nao encontrado!\n");
	else{
		mostra_jogador(posicao);
		printf("\nDeseja remover o jogador?1-sim/2-nao:");
		scanf("%d", &confirm);
		if(confirm==1){
			
			fseek(arquivo, posicao*sizeof(jogadores), SEEK_SET);
			fwrite(&jogador_nulo, sizeof(jogadores), 1, arquivo);
			printf("\nJogador removido com sucesso!\n");
			
		}else
		printf("Remocao cancelada!\n");
			
	}
	printf("Deseja remover outro? 1-sim/2-nao:");
	scanf("%d", &resp);
	
	}while(resp==1);
	
}
 
