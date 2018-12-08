#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
///////// ESTRUTUTA DO CLIENTE //
	typedef struct{
	char nome_cliente[10], endereco[10];
	int cpf, telefone;
	
}clientes;////// FIM ESTRUTURA CLIENTE //////

////// CRIANDO ARQUIVO DO CLIENTE ////
FILE*arquivocliente;
clientes cliente;
//////// FIM ARQUIVO/////

//// ESTRUTURA DO FILME ///
 typedef struct{
 	char nome_filme[10], categoria[10];
 	int codigo_filme;
 	
 }filmes; ///// FIM ESTRUTURA ///
 
 ///// ARQUIVO DO FILME ////
FILE*arquivofilme;
filmes filme;
//// FIM ARQUIVO DO FILME ////////

void cabecalho(){
	system("color e0");
	system ("cls");
	printf("Locadora Eanova\n\n");
}
//// CRIANDO ARQUIVO DO CLIENTE //
 void criando_arq_cliente(){
 	arquivocliente= fopen("arquivocliente.bin", "r+b");
 	
 	if (arquivocliente == NULL){
 	arquivocliente = fopen ("arquivocliente.bin","w+b");	

	 }
 } //////// FIM DA FUN ARQ. DO CLIENTE ///////
 
 //// CRIANDO ARQUVIO DO FILME  //////
 void criando_arq_filme(){
 	arquivofilme= fopen("arquivofilme.bin", "r+b");
 	
 	if (arquivofilme == NULL){
 	arquivofilme = fopen ("arquivofilme.bin","w+b");	

	 }
 }///////// FIM FUNC. ARQ DO FILME ////
 
 
 /////////  PRINCIAPL //////////////////
 main(){
 int op;
 criando_arq_cliente();
 criando_arq_filme();
 
 do{
 	cabecalho();
 	printf("Escolha uma opcao\n");
 	printf("\n");
 	printf("1-Cadastrar cliente\n");
 	printf("\n");
 	printf("2-Consultar cliente\n");
 	printf("\n");
 	
 	printf("3-Cadastrar filme\n");
 	printf("\n");
 	printf("4-Consultar filme\n");
 	printf("\n");
 	
 	///////// testeando 
 	printf("5-Listar clientes\n");
 	printf("\n");
 	printf("6-Listar filmes\n");
 	printf("\n");
 	
 	
 	printf("0-Sair\n");
 	printf("\n");
 	printf("Informe a opcao:");
 	scanf("%d", &op);
 	
switch (op){
	case 1:cadastrar_cliente(); break;
	case 2:consultar_cliente(); break;
	case 3:cadastrar_filme(); break;
	case 4:consultar_filme(); break;
	case 5:listagem_cliente(); break;
	case 6:listagem_filmes(); break;
	case 0: fclose(arquivocliente) && fclose(arquivofilme); break;
	default: printf("Opcao invalida"); break;
} 	
 	
 }while (op!=0);	
 	
 }//////////// FIM PRINCIPAL //////////////
 
///////// INICIO FUNCAO CADASTRO DE CLIENTE////////
 cadastrar_cliente(){
 	int sair;
 	int i;
 	
do{
 	cabecalho();
	 printf("\n");
	 
	 printf("Cadastro de clientes\n");
	 printf("\n");
	 
	 //cpf
	 printf("Digite o CPF do cliente:");
	 scanf("%d", &cliente.cpf);
	 printf("\n");
	
	 //Nome
	 printf("Nome do cliente:");
	 fflush(stdin);
	 gets(cliente.nome_cliente);
	 printf("\n");
	 
	 //telefone
	 printf("Digite o telefone do cliente:");
	 scanf("%d", & cliente.telefone);
	 printf("\n");
	 
	 //endereco
	 printf("Digite o endereco do cliente:");
	 fflush(stdin);
	 gets(cliente.endereco);
	 
	 
	 fseek(arquivocliente, 0, SEEK_END);
	 
	 fwrite(&cliente, sizeof(clientes),1, arquivocliente);
	 
	 printf("Cliente cadastrado com sucesso:\n\n");
	 printf("\n");
	 printf("Deseja cadastrar outro cliente? 1-sim / 2-nao:");
	 scanf("%i", &sair);
	 
}while(sair==1 );


 	
}////////// FIM DA FUNCAO CADASTRO CLIENTE //////////////

///////////// FUNCAO PROCURAR CLIENTE ////////////////////
procura_cliente(int pcod){
 int p;
 p=0;
 
 rewind (arquivocliente);
 fread(&cliente, sizeof(clientes),1, arquivocliente);
 while (feof(arquivocliente)==0){
 	if(cliente.cpf==pcod){
 		return p;
	 }else{
	 	fread(&cliente, sizeof(clientes), 1, arquivocliente);
	 	p++;
	 } 
 }	
	return -1;
}    //////// FIM DA FUNCAO PROCURA CLIENTE //////////// 

  /////// FUNC. MOSTRA CLIENTE ////////
  mostre_cliente(int pos){
  	fseek(arquivocliente, pos*sizeof(clientes),SEEK_SET);
  	fread(&cliente, sizeof(clientes),1, arquivocliente);
  	printf("\n");
  	printf("CPF:%i\nNome:%s\nTelefone:%d\nEndereco:%s\n",cliente.cpf,cliente.nome_cliente,cliente.telefone,cliente.endereco);
  	
  }  ///////// FIM FUNC. MOSTRA CLIENTE /////////
  
//////////// CONSULTA CLIENTE /////////////
  consultar_cliente(){
  	int sair, cpf, posicao_cliente;
do{
	cabecalho();
	printf("\n");
	printf("Consultar cliente\n");
	printf("\n");
	printf("CPF do cliente:");
	scanf("%d", &cpf);
	printf("\n");
posicao_cliente=procura_cliente(cpf);
if(posicao_cliente== -1)
 printf("CPF nao encontrado:\n\n");
 else
 mostre_cliente(posicao_cliente);
 printf("\n");
 printf("Deseja fazer outra consulta? 1-sim / 2- nao");
   scanf("%d", &sair);
}while (sair==1);
  	
  }///////////// FIM DA FUNC. CONSULTA CLIENTE ////////////////
  
  
  ////////////// LISTAGEM DE CLIENTES ///////////
 listagem_cliente()
 {
 	cabecalho();
 	printf("Listagem clientes\n\n");
 	
 	
 	rewind(arquivocliente);
 	fread(&cliente, sizeof(clientes), 1, arquivocliente);
 	printf("\n________________________________________________________________________________\n");
 	printf("  CPF       NOME                  TELEFONE   EENDERECO");
 	printf("\n________________________________________________________________________________");
 	while(feof(arquivocliente)==0){
 		
 		if (cliente.cpf != 0)
 		printf("\n%9d   %-20s %9d   %-0s", cliente.cpf, cliente.nome_cliente, cliente.telefone, cliente.endereco);
 		
 		fread(&cliente, sizeof(clientes), 1, arquivocliente);
 		
	 }
	 printf("\n\n");
	 printf("Tecle enter para voltar ao menu...");
	 getche();
 		
  } //////// FIM DA LISTAGEM DE CLIENTES//////////////////
  
///////////////// FUNC. REMOVER CLIENTES //////////////

/*
remover_cliente(){
	int cpf, conf, resp, posicao;
	cliente.cpf = 0;
	
	do{
		cabecalho();
		printf("Remover cliente\n");
		printf("Digite o CPF do cliente:");
		scanf("%d", &cpf);
		posicao = procura_cliente(cpf);
		
		if(posicao == -1)
			printf("\nCliente nao encontrado!");
			else
			mostre_cliente(posicao);
			
			printf("\nDeseja remover o aluno?(1-sim/2-nao)");
			scanf("%d", &conf);
			
			if(conf = 1){
				fseek(arquivocliente, posicao*sizeof(clientes), SEEK_SET);
				fwrite()
			}
		
	}
	
	
}*/


  
  
///////////////////////////------ FILMES----//////////////////////

////////////// FUNC. CADASTRO FILME ////////
cadastrar_filme(){
	int sair;
	do{
		cabecalho();
		printf("\n");

	printf("Cadastro de filmes\n");
	printf("\n");
//codigo
	printf("Codigo do filme:");
	scanf("%d",&filme.codigo_filme);
	printf("\n");
//nome
	printf("Nome do filme:");
	fflush(stdin);
	gets(filme.nome_filme);
	printf("\n");
//categoria
	printf("Categoria do filme:");
	fflush(stdin);
	gets(filme.categoria);
	printf("\n");


	fseek(arquivofilme,0,SEEK_END);

	fwrite(&filme, sizeof(filmes),1, arquivofilme);
	printf("filme cadastrado com sucesso:\n\n");
	printf("\n");
	printf("deseja cadastrar outro filme? 1-sim / 2-nao:");
	scanf("%i",&sair);
	
}while (sair==1);	
}///////// FIM DA FUNC. CADASTRO FILME //////////

//////////////// FUNC. PROCURA FILME /////////////
	procura_filme(int pcod){
	int p;
	p=0;
	rewind(arquivofilme);
	fread(&filme, sizeof(filmes),1, arquivofilme);
	while(feof(arquivofilme)==0){
	if(filme.codigo_filme==pcod){
	return p;
	
}else{
  fread(&filme, sizeof(filmes),1, arquivofilme);
  p++;	
	
}	
	
}			    
 return -1;
} //////////// FIM DA FUNC. PROCURA FILME ///////////


////////// FUNC. MOSTRAR FILME /////////////
	mostre_filme(int pos){
	fseek(arquivofilme ,pos*sizeof(filmes),SEEK_SET);
	fread(&filme, sizeof(filmes),1, arquivofilme);
	printf("\n");
	printf("Codigo:%i\nNome:%s\nCategoria:%s\n",filme.codigo_filme, filme.nome_filme, filme.categoria);
	
}/////////// FIM  DA FUNC. MOSTRAR CÓDIGO /////////////

//////////// FUNC. CONSULTAR FILME ////////////////////////
consultar_filme(){
int sair, codigo, posicao_filme;

do{
	cabecalho();
	printf("\n");
	printf("consultar filme\n");
	printf("\n");
	printf("codigo do filme:");
	scanf("%d",&codigo);
	printf("\n");
	posicao_filme=procura_filme(codigo);
	if(posicao_filme == -1)
	printf("codigo nao encontrado!\n\n");
	else
	mostre_filme(posicao_filme);
	printf("\n");
	printf("deseja fazer outra consulta? 1-sim / 2-nao:");
	scanf("%d", &sair);
	
	}while (sair==1);	
	
}////////////// FIM DA FUNC. CONSULAR FILME ////////

////////////// LISTAGEM DE FILMES ///////////
  listagem_filmes()
 {
 	cabecalho();
 	printf("Lista de filmes \n\n");
 	
 	
 	rewind(arquivofilme);
 	fread(&filme, sizeof(filmes), 1, arquivofilme);
 	printf("\n__________________________________________________________________\n");
 	printf("      CODIGO     NOME                  CATEGORIA");
 	printf("\n__________________________________________________________________");
 	while(feof(arquivofilme)==0){
 		
 		if (filme.codigo_filme != 0)
 		printf("\n%9d        %-20s  %-20s", filme.codigo_filme, filme.nome_filme, filme.categoria);
 		
 		fread(&filme, sizeof(filmes), 1, arquivofilme);
 		
	 }
	 printf("\n\n");
	 printf("tecle enter para voltar ao menu...");
	 getche();
 		
  } //////// FIM DA LISTAGEM DE FILMES//////////////////

