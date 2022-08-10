#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<locale.h>
#define MAX_CARROS 100

typedef struct abacatinho
{
	char fabricante[100];
	char modelo[100];
	int ano;
	int consumo;
	int ativo;
}Carro;


typedef struct azulao
{
	char fabricante[100];
	char modelo[100];
	int ano;
	int consumo;
	int ativo;
}Amarelao;

Amarelao carros[MAX_CARROS];


void menu();
void cadastrar();
void remover();
void economico();
void maiorconsumo();
void maisnovo();
void listar();

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL,"portuguese");
    
    	Carro goiaba;
	int j=0;

    	FILE *dados;
	
	dados = fopen("dados.bin","rb");
	
	while(fread(&goiaba,sizeof(Carro),1,dados))
	{
			carros[j].consumo=goiaba.consumo;
			carros[j].ano=goiaba.ano;
			strcpy(carros[j].fabricante,goiaba.fabricante);
			strcpy(carros[j].modelo,goiaba.modelo);
			carros[j].ativo=goiaba.ativo;
			j++;
			
	}
	
	fclose(dados);

    
    
    menu();
    return 0;
}

void menu()
{

int opcao;

	do
	{
	
		printf("\n|-----------CADASTRO DE CARROS------------|");
		printf("\n|                                         |");
		printf("\n|             MENU PRINCIPAL              |");
		printf("\n|    1-Cadastrar veiculo                  |");
		printf("\n|    2-listar veiculos                    |");
		printf("\n|    3-remover veiculo do sistema         |");
		printf("\n|    4-carro mais economico               |");
		printf("\n|    5-veículo com maior consumo          |");
		printf("\n|    6-veículo(s) mais novo(s)            |");
		printf("\n|                                         |");
		printf("\n|    0-sair do programa                   |\n");
		scanf("%d", &opcao);


	switch(opcao)
		{
			case 1:
				cadastrar();
			break;
			case 2:
				listar();
			break;
			case 0:
				printf("\nencerrando o programa...\n");
				return;
			break;
			case 3:
				remover();
			break;
			case 4:
				economico();
			break;
			case 5:
				maiorconsumo();
			break;
			case 6:
				maisnovo();
			break;
			
			default:
				menu();
				system("clear");
				printf("\n essa opção não existe\n");
				printf("\n digite novamente uma opção válida no menu\n");
			break;
		}	


	}while(opcao!=0);
}


void cadastrar()
{
	
	Carro goiaba;
	int opcao=0;
	
	int j=0;
	
	
	
	system("clear");
	
	
		
	FILE *dados;
	
		
	dados = fopen("dados.bin","a+b");
	
	
	printf("\nInsira o nome da fabricante do possante:\n");
	getchar();	
	fgets(goiaba.fabricante,sizeof(goiaba.fabricante),stdin);
	
	printf("\ninsira o modelo do carro:\n");
	
	fgets(goiaba.modelo,sizeof(goiaba.modelo),stdin);
	
	printf("\ninsira o consumo desse carro por litro\n");
	scanf("%d",&goiaba.consumo);
	
	printf("\nInsira o ano de fabricação\n");
	scanf("%d",&goiaba.ano);
	
	goiaba.ativo=1;
	
	fwrite(&goiaba,sizeof(Carro),1,dados);
	
	
	fclose(dados);
	
	
	dados = fopen("dados.bin","r+b");
	
	while(fread(&goiaba,sizeof(Carro),1,dados))
	{
			carros[j].consumo=goiaba.consumo;
			carros[j].ano=goiaba.ano;
			strcpy(carros[j].fabricante,goiaba.fabricante);
			strcpy(carros[j].modelo,goiaba.modelo);
			carros[j].ativo=goiaba.ativo;
			j++;
			
	}
	
	fclose(dados);
	
	printf("\n O número de carros gravados é: %d, use esse valor para gravar as informações no arquivo caso você remova algum veículo",j);
	

		
}

void listar()
{
	char fabricante[20];
	
	system("clear");
	
	printf("\nInsira o nome da fabricante para ser procurado\n");
	getchar();
	fgets(fabricante,sizeof(fabricante),stdin);
	
	
	for(int i=0;i<MAX_CARROS;i++)
	{
		if(strstr(carros[i].fabricante,fabricante)!=NULL  && carros[i].ativo==1)//ta cumprindo sua função 
		{
			printf("\nfabricante:%s\n",carros[i].fabricante);
			printf("modelo :%s\n",carros[i].modelo);
			printf("ano de fabricação:%d\n",carros[i].ano);
			printf("\nconsumo:%d km/l\n",carros[i].consumo);
			printf("\n--------------\n");
		}
	}
}
void remover()
{
	char modelo[20];

	printf("Insira o nome do carro que você deseja excluir\n");
	getchar();
	fflush(stdin);
	gets(modelo);
	
	for(int i=0;i<MAX_CARROS;i++)
	{
		if(strstr(carros[i].modelo,modelo)!=NULL)
		{
			carros[i].ativo=0;
		}
	}
	
	Carro goiaba;
	int numero;
	
	printf("Digite o número de carros cadastrados no sistema\n");
	scanf("%d",&numero);
	
	FILE *dados;
	
	dados = fopen("dados.bin","w+b");
	for(int i=0;i<numero;i++)
	{
	strcpy(goiaba.fabricante,carros[i].fabricante);
	strcpy(goiaba.modelo,carros[i].modelo);
	goiaba.consumo=carros[i].consumo;
	goiaba.ano=carros[i].ano;
	goiaba.ativo=carros[i].ativo;
	fwrite(&goiaba,sizeof(Carro),1,dados);
	}
	fclose(dados);

}

void economico()
{

	int  consumo=0;
	
	system("clear");

	for(int i=0;i<MAX_CARROS;i++)
	{
		if(carros[i].ativo>0){//alterar para consumo
		for(int j=i+1;j<MAX_CARROS;j++)
		{
			if(carros[i].consumo>carros[j].consumo && carros[j].consumo>0 && carros[i].consumo>0)
			{
				consumo=carros[i].consumo;
			}
			if(carros[i].consumo<carros[j].consumo && carros[j].consumo>0 && carros[i].consumo>0)
			{
				consumo=carros[j].consumo;
			}
		}
		}
	}
	
	printf("\no(s) carro(s) mais economico(s) é(são):\n");

	for(int i=0;i<MAX_CARROS;i++)
	{
		if(carros[i].ativo>0){
		if(carros[i].consumo==consumo)
		{
			printf("modelo \n%s",carros[i].modelo);
			printf("\n cujo consumo é:\n%d",consumo);
			printf("\n----------------\n");
		}
		}
	}

}


void maiorconsumo()
{

	int  consumo=0;
	
	system("clear");

	for(int i=0;i<MAX_CARROS;i++)
	{
		
		for(int j=i+1;j<MAX_CARROS;j++)
		{
			if(carros[i].ativo>0 && carros[j].ativo>0){
			if(carros[i].consumo>carros[j].consumo && carros[j].consumo>0 && carros[i].consumo>0)
			{
				consumo=carros[j].consumo;
			}
			if(carros[i].consumo<carros[j].consumo && carros[j].consumo>0 && carros[i].consumo>0)
			{
				consumo=carros[i].consumo;
			}
			}
		}
	}
	
	printf("\no(s) carro(s) menos economico(s) é(são):\n");

	for(int i=0;i<MAX_CARROS;i++)
	{
		if(carros[i].ativo>0){
		if(carros[i].consumo==consumo)
		{
			printf("modelo \n%s",carros[i].modelo);
			printf("\n cujo consumo é:\n%d",consumo);
			printf("\n----------------\n");
		}
		}
	}


}

void maisnovo()
{

	int ano=0;

	system("clear");
	
	
	for(int i=0;i<MAX_CARROS;i++)
	{
		for(int j=i+1;j<MAX_CARROS;j++)
		{
		if(carros[i].ativo>0 && carros[j].ativo>0){
			if(carros[i].ano<carros[j].ano && carros[j].ano>0 && carros[i].ano>0)
			{
				ano=carros[j].ano;
			}
		}
		}
	}
	
	printf("\no(s) carro(s) mais novo(s) é(são):\n");

	for(int i=0;i<MAX_CARROS;i++)
	{
		if(carros[i].ativo>0){
		if(carros[i].ano==ano)
		{
			printf("modelo \n%s",carros[i].modelo);
			printf("\n cujo ano de fabricação é:\n%d",ano);
			printf("\n----------------\n");
		}
		}
	}



}

void salvar()
{

	

}


