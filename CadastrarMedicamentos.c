#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//estrutura de medicamentos
struct medicamentos{
    int codigo;
    char nome[20],laboratorio[20];
    float preco;
   
};

//funcao de insercao de produtos
void inserir(struct medicamentos *medicamentos[20],int *quantidade){
    int i;
    
    //atribuicao de valores a estrutura
    printf("\nDigite o nome do produto:");scanf("%s",medicamentos[*quantidade]->nome);
    printf("\nDigite o laboratorio do produto:");scanf("%s",medicamentos[*quantidade]->laboratorio);
    printf("\nDigite o preco do produto:");scanf("%f",&medicamentos[*quantidade]->preco);
    
    //atribuicao de codigo
    int validacao=0;
    do{
        //solicita o codigo do produto
        printf("\nDigite o codigo do produto:");scanf("%i",&medicamentos[*quantidade]->codigo);
        
        //sai do laco caso seja o primeiro medicamento
        if(*quantidade==0){
            validacao=1;
        }else{
            
            //codigo valido para encerrar o while
            validacao=1;
            
            //laco que percorre toda estrutura procurando codigo repetido
            for(i=0;i<=*quantidade-1;i++){
                if(medicamentos[*quantidade]->codigo==medicamentos[i]->codigo){
                    //zera a validacao para repetir o while
                    validacao=0;
                    //encerra o loop para poupar tempo
                    break;
                }
            }
        }
    }while(validacao!=1);
    
    //icrementando em 1 a quantidade de medicamentos
    *quantidade=*quantidade+1;
    
}

//printar o medicamento
void printar(struct medicamentos *medicamentos){
    
    printf("\nNome do produto %s",medicamentos->nome);
    printf("\nLaboratorio do produto %s",medicamentos->laboratorio);
    printf("\nPreco do produto R$%.2f",medicamentos->preco);
    printf("\nCodigo do produto %i",medicamentos->codigo);
    
    
}

//buscar medicamento pelo nome
void buscar(struct medicamentos *medicamentos[20],int *quantidade){
    
    char nome[20];
    int i;
    //recebe o nome para pesquisa
    printf("\nDigite o nome do medigamento para busca:");scanf("%s",nome);
    int validacao=0,local;
    
    
    //laco para percorrer todo vetor
    for(i=0;i<*quantidade;i++){
        
        //verifica o nome do medicamento
        if(strcmp(nome,medicamentos[i]->nome)==0){
            //guarda o local em que o medicamento esta no vetor
            local=i;
            //atualiza a validacao
            validacao=1;
            //encerra o laco
            break;
        }
    }
    
    //firificacao se o medicamento foi encontrado
    if(validacao==1){
        //printa nome se foi encontrado
        printar(medicamentos[local]);
    }else{
        //mensagem de nao encontrado
        printf("\nO medicamento nao foi encontrado");
    }
}

void ordenar(struct medicamentos *medicamentos[20]){
    
    //criacao de variaveis
    int local,verificacao=0;
    int *menor=NULL,i;
    
    //vetor com todos os dados de medicamento
    struct medicamentos temporario[20];
    //atribuicao de dados do vetor ponteiro para o temporario
    for(i=0;i<20;i++){
        temporario[i]=*medicamentos[i];
    }
    
    
    //laco para printar medicamentos em ordem
    do{
        //validacao igual a 1 para fechar o programa
        verificacao=1;
        //percorre todos elementos do vetor
        for(i=0;i<20;i++){
            //verifica codigo de medicamento
            if(temporario[i].codigo!=-999){
                //verifica se menor esta vazio ou e menor que o ponteiro
                if(menor==NULL || temporario[i].codigo<*menor){
                    //menor recebe valor do ponteiro
                    menor=&temporario[i].codigo;
                    //local recebe o indice do vetor
                    local=i;
                    //verificacao e zerada
                    verificacao=0;
                }
            }
        }
        //caso verificacao nao zerada
        if(verificacao!=1){
            //printa o no do vetor
            printar(&temporario[local]);
            //coloca valor invalido em codigo
            temporario[local].codigo=-999;
            //zera menor
            menor=NULL;
        }
        printf("\n");
    
    //encerra o laco caso saia do for sem achar valor valido para codigo   
    }while(verificacao!=1);    
}

//funcao principal
void main()
{
    //quantidade de medicamentos cadastrados
    int quantidade=0,i;
    
    //vetor de estrutura que contem n campos
    struct medicamentos medicamentos[20],*ponteiro[20];
    
    //atribui ponteiro de cada casa do vetor ao vetor ponteiro e zera medicamentos
    for(i=0;i<20;i++){
        ponteiro[i]=&medicamentos[i];
        medicamentos[i].preco=0;
        medicamentos[i].codigo=-999;
    }
    
    //programa rodando em loop
    int opcao=0;
    do{
        
        //menu interativo
        printf("\n");
        printf("\n(1) Insarir novo medicamento");
        printf("\n(2) Ver ultimo medicamento");
        printf("\n(3) Ver todos os medicamentos");
        printf("\n(4) Pesquisar medicamentos");
        printf("\n(5) Exibir medicamentos em ordem");
        printf("\n(6) Sair");
        printf("\nDigite a opcao desejada:");scanf("%i",&opcao);
        
        //verifica se tem produtos medicamentos ou espaco para cadastrar
        if((opcao==1 && quantidade<20) ||(opcao>=2 && quantidade>=1)){
            
            //escolha de caso
            switch(opcao){
            
                //insere um novo medicamento
                case 1:
                    inserir(ponteiro,&quantidade);
                    break;
                
                //exibe o ultimo medicamento
                case 2:
                    printar(&medicamentos[quantidade-1]);
                    break;
                
                //exibe todos os medicamentos
                case 3:
                    for(i=0;i<quantidade;i++){
                        printar(&medicamentos[i]);
                        printf("\n");
                    }
                    break;
                
                //busca de medicamento pelo nome
                case 4:
                    buscar(ponteiro,&quantidade);
                    break;
                
                //exibe medicamentos em ordem crescente    
                case 5:
                    ordenar(ponteiro);
                    break;
            }
            
            
        //mensagens para opcao invalida    
        }else{
            if(quantidade==20){
                //quando atinge o limite de cadastro
                printf("\nLimite de cadastros atingido\n");
            }else{
                //quando nao tem medicamentos cadastrados
                printf("\nSem medicamentos cadastrados");
            }
            
        }
        
        
    //condicao de encerramento do programa    
    }while(opcao!=6);
   
}
