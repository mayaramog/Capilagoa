/**********************************************
*                                             *
* Aluna: Mayara Marques de Oliveira Gonçalves *
* Trabalho Prático                            *
* Disciplina: Algortimos e Programação II     *
* Professores: Ivone, Mauro e Ronaldo         *
*                                             *
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/***************

 1 -> Descrição:

 1.1 -> Dados dos produtos: Uma struct para armazenar as informações necessárias de cada produto, como proposto por Seu Canínde.

***************/
struct cel{
    int cod; /* Código: Inteiro, maior que zero, código do produto. Possui valor único. */
    char desc[50]; /* Descrição: Texto, descrição do produto. A descrição não possui espaços (“ ”) e muito menos acentos. */
    int qtd; /* Quantidade em estoque: Inteiro, maior ou igual a zero. */
    float precov; /* Preço de Venda: Real, maior ou igual a zero. */
    struct cel *prox;
};
typedef struct cel celulad;



/***************

 1.2 -> Operações: O sistema de controle do minimercado deve funcionar como um interpretador de comandos.

    1.2.1 -> INSERÇÃO: Cadastra um produto.
    inserir <codigo> <nome> <quantidade> <valor>

***************/
void inserir(celulad **lst, int codi, char *desci, int qtdi, float precovi, int *ver){ /* Ponteiro de ponteiros para a lista pois passará por referência para não perder os produtos inseridos. */
    celulad *p, *q, *nova; /* Ponteiros auxiliares que percorrem a lista (*p, *q) e ponteiro que armazena o novo produto a ser inserido (*nova). */
    p = NULL; /* Inicialização do ponteiro p, auxiliar de q. */
    q = *lst; /* Inicialização do ponteiro q.*/

    *ver = 0; /* 0 para falso, 1 para verdadeiro. Será falso até que se prove verdadeiro. Criei essa váriavel para facilitar na importação, dependendo do valor gerado, imprimirá uma mensagem diferente na tela quando um produto for inserido diretamente no terminal, já quando um número n de produtos forem importados, tal mensagem não será transmitida na tela. */

    nova = (celulad *) malloc(sizeof(celulad)); /* Alocação de memória no início, caso ocorra falhas a função não executará nenhum comando em vão. */
    if(nova != NULL){

        while(q != NULL && q->cod < codi){ /* Laço que percorre a lista até o final ou até encontrar um código com o valor mais alto que o a ser inserido. O motivo de conter um "&&" e não um "||" no laço é devido ao fato de que, o laço deve percorrer a lsita enquanto as DUAS condições forem verdadeiras, caso uma seja falsa o laço deve ser encerrado. */
            p = q;
            q = q->prox;
        }

        nova->cod = codi;
        strcpy(nova->desc, desci);
        nova->qtd = qtdi;
        nova->precov = precovi;
        nova->prox = q;

        if(*lst == NULL){ /* Inserção no começo da lista vazia. */
            *lst = nova; /* Como a lista está vazia, não há codigos iguais e não há problemas para o ponteiro "original" em apontar diretamente para a nova célula. */
            *ver = 1; /* Sucesso. */
        }
        else{
            if(q == NULL){ /* Inserção no final da lista. */
                p->prox = nova; /* Ponteiro auxiliar p que aponta para a célula anterior de q, já que q == NULL, não há codigos iguais e p->prox aponta para a célula nova. */
                *ver = 1; /* Sucesso. */
            }
            else{
                if(q->cod != codi){
                    if(p == NULL) /* Inserção no começo da lista cheia. Ocorre no caso da primeira célula possuir um código maior que o ao ser inserido. */
                        *lst = nova;
                    else /* Inserção no meio da lista. */
                        p->prox = nova;
                    *ver = 1; /* Sucesso. */
                }     
            }
        }
    }
    else
        printf("Erro ao alocar memória.\n"); /* Falha na alocação de memória. */  
}



/***************

    1.2.2 -> EXCLUSÃO: exclui um produto através do seu código.
    excluir <codigo>

***************/
void excluir(celulad **lst, int codi){ /* Ponteiro de ponteiros para a lista pois passará por referência para excluir definitivamente o produto da lista.*/
    celulad *p, *q; /* Os ponteiros p e q seguem o mesmo esquema da função acima, percorrem a lista e auxiliam a remoção sem modificar e perder itens. */
    p = NULL;
    q = *lst; 

    while(q != NULL && q->cod != codi){ /* Procura o produto com o código semelhante (ao que foi digitado) na lista. */
        p = q;
        q = q->prox;
    }

    if(q != NULL){ /* Se o ponteiro não chegou ao final da lista. */
        if(p != NULL) /* Se a lista não estiver vazia. */
            p->prox = q->prox;        
        else
            *lst = q->prox;
        free(q); /* Remove o produto da lista encadeada. */
        printf("Produto %d excluído com sucesso!\n", codi); /* Sucesso. */
    }
    else
        printf("Produto %d não cadastrado!\n", codi); /* Falha. */
}



void excluirLista(celulad **lst){ /* Exclusão de listas utilizadas para liberar memória. */
    celulad *p;
    p = *lst;
    while(p != NULL){
        free(p);
        p = p->prox;
    }
}



/***************

    1.2.3 -> ATUALIZAÇÃO: Recebe um parâmetro (p): para -q atualiza a quantidade e para -v o preço de vendas, o código e o novo valor.
    atualizar < p > <codigo> <novo valor>

***************/
void atualizar(celulad **lst, char *px, int codi, float vlr){ /* Ponteiro de ponteiros para a lista pois algum valor do produto será atualizado definitivamente, não apenas na função. */
    celulad *q; /* Apenas um ponteiro auxiliar é necessário. */

    q = *lst; /* Inicialização do ponteiro auxiliar. */
    while(q != NULL && q->cod != codi) /* Percorre a lista até encontrar o código. */
        q = q->prox;

    if(q != NULL && q->cod == codi){ /* q será nulo caso a lista esteja vazia ou no final, em ambos os casos, o código não existirá. */         
        if(strcmp(px, "-q") == 0) /* Condição para alterar o valor da quantidade. */
            q->qtd = vlr;
        if(strcmp(px, "-v") == 0) /* Condição para alterar o valor do preço de venda. */
            q->precov = vlr;
        printf("Produto %d atualizado!\n", codi); /* Sucesso. */
    }
    else
        printf("Produto %d não cadastrado.\n", codi); /* Falha. */
}



/***************

    1.2.4 -> CONSULTA: Procura uma cadeia ou subcadeia dentre os produtos existentes.
    consultar <sequencia de caracteres>

***************/
void consultar(celulad *lst, char *seqc){ /* A lista não precisa ser alterada nesse comando, então é passada apenas como ponteiro. É necessário ler a sequência de caracteres nessa função. */
    celulad *p; /* Ponteiro auxiliar para percorrer a lista. */
    char *q; /* Ponteiro auxiliar para identificar a subcadeia do produto. */
    int cont; /* Contador para identificar se nenhum produto foi encontrado. */
    
    p = lst;
    
    cont = 0; /* Inicialização. */
    while(p != NULL){
        q = strstr(p->desc, seqc); /* Comparação da descrição com a sequência de caracteres inserida pelo usuário. */
        if(q != NULL){ /* Caso tenha sido encontrada uma subcadeia. */
            printf("%d - %s - %d - %.2f\n", p->cod, p->desc, p->qtd, p->precov); /* Sucesso. */
            cont++;
        }
        p = p->prox;
    }
    if(cont == 0)
        printf("Nenhum produto encontrado!\n"); /* Falha. */
}



/***************

    1.2.5 -> RELATÓRIO: Imprime na tela e salva em "Relatorio.txt" os dados de todos os produtos carregados até o momento, em ordem alfabética pelo nome e agrupados pela letra inicial.
    <letra inicial>
     <codigo> - <nome> - <qtd em estoque> - <valor>
    ...

***************/
void relatorio(celulad *lst){ /* A lista não será alterada, então passa apenas como um ponteiro. */
    celulad *p, *q, *r, *nova, *lstrelat; /* Ponteiro p que percorre a lista principal. Ponteiros q e r para percorrer a nova lista que será criada (para ordenar em ordem alfabética).*/
    char letra[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'X', 'W', 'Y', 'Z'}; /* Alfabeto para a impressão. */
    int i;

    FILE *relat; /* Criação de um ponteiro para ser possível armazenar as informações em um arquivo "Relatorio.txt". */

    lstrelat = NULL; /* Inicialização da nova lista em ordem alfabética de produtos. */

    p = lst;
    while(p != NULL){ /* ponteiro p percorre a lista até o final. */

        q = NULL;
        r = lstrelat;

        while(r != NULL && strcmp(r->desc,p->desc) <= 0){ /* Condição para identificar alguma descrição que seja menor ou igual na questão alfabética. */
            q = r;
            r = r->prox;
        }

        nova = (celulad *) malloc(sizeof(celulad));
        if(nova != NULL){
            nova->cod = p->cod;
            strcpy(nova->desc, p->desc);
            nova->qtd = p->qtd;
            nova->precov = p->precov;
            nova->prox = r;
            
            if(q == NULL) /* Inserção no começo da lista vazia. */
                lstrelat = nova;
            else
                q->prox = nova;
        }
        else
            printf("Erro ao alocar memória.\n"); /* Falha na alocação de memória. */
        p = p->prox;
    }

    relat = fopen("Relatorio.txt", "w"); /* Criação ou abertura do arquivo para salvar as informações da função. */
    if(relat != NULL){
        p = lstrelat;
        for(i = 0; i < 26; i++){ /* Percorre o alfabeto para imprimir os produtos agrupados pela letra inicial. */
            if(p != NULL && letra[i] == p->desc[0]){ /* Compara o alfabeto com as letras iniciais das descrições dos produtos. */
                fprintf(relat, "%c\n", letra[i]); /* Impressão no arquivo. */
                printf("%c\n", letra[i]); /* Impressão na tela. */

                while(p != NULL && letra[i] == p->desc[0]){ /* Os produtos de descrições com a inicial igual a atual do alfabeto serão mostrados em sequência. */
                    fprintf(relat, " %d - %s - %d - %.2f\n", p->cod, p->desc, p->qtd, p->precov); /* Impressão no arquivo. */
                    printf(" %d - %s - %d - %.2f\n", p->cod, p->desc, p->qtd, p->precov); /* Impressão na tela. */
                    p = p->prox;
                }
            } 
        }
    }
    else
        printf("Erro ao salvar produtos em ordem alfabética no arquivo Relatorio.txt.");
    fclose(relat); /* Fecha o arquivo. */

    excluirLista(&lstrelat); /* Exclusão da lista para a liberar memória. */
}



/***************

    1.2.6 -> IMPORTAÇÃO: Importa os produtos salvos em um arquivo. O arquivo possui a quantidade de produtos presentes, em seguida código;descrição;quantidade;preço de venda.
    importar <nome do arquivo>

***************/
void importar(celulad **lst, char *arq, int cod, char *desc, int qtd, float precov, int *qtdp, int *ver, int *cont){ /* Para a importação, como a função será utilizada tanto no começo para importar Produtos.dat e quando for solicitada, decidi passar como parâmetro a lsita, nome do arquivo a ser importado, as informações do registro (para serem lidos na função e inseridos na lista principal) a variavel "ver" que analisa se o produto foi inserido, e a váriavel "cont" que possui a quantidade de produtos contidos dentro do arquivo que foi importado. */
    int i, arquant, veri; /* i = variável auxiliar. arqtd = Quantidade de produtos do arquivo importado. */

    FILE *arqop; /* Ponteiros para a importação do arquivo inserido. */

    *cont = 0; /* Quantidade de produtos que o arquivo possui, para a impressão na tela. */
    *ver = 0; /* Condição para importar na lista, até então nada foi importado. Falha. */

    arqop = fopen(arq, "rb+"); /* Abertura do arquivo, arquivos .dat e .txt podem ser importados. */
    if(arqop != NULL){
        i = 0; /* Váriavel auxiliar para importar a quantidade correta de produtos do arquivo. */
        fscanf(arqop, "%d", &arquant); /* Leitura dentro do arquivo. */
        while(i < arquant){      
            fscanf(arqop, "%d;%[^;];%d;%f", &cod, desc, &qtd, &precov); /* Leitura dentro do arquivo. */
            inserir(lst, cod, desc, qtd, precov, &veri); /* Chama a função inserir para a inserção ordenada por código, facilitando a ordenação. */
            i++;
            if(veri == 1)
                (*cont)++; /* A cada inserção, adiciona 1. A lógica da variável é identificar se o arquivo já foi importado (caso não serão importados 0 produtos), ou se há algum semelhante dentro de outro arquivo, dessa forma, esse produto não será inserido e contado. */
        }
        *ver = 1; /* Caso ocorra tudo bem com a abertura do arquivo, ele será importado. */
        *qtdp = *qtdp + *cont; /* A quantidade de produtos importados será somado com a quantidade de produtos atual no sistema. */
        fclose(arqop); /* Fechamento do arquivo. */
    }          
}



/***************

    1.2.7 -> REGISTRO DE VENDA: É passado um conjunto de códigos, encerrando em 0. O produto só pode ser vendido caso esteja cadastrado ou caso sua quantidade de estoque seja maior que 0.
    vender
    <codigo>
    0 - Encerramento -
    ---------
    Total soma dos valores

***************/
void vender(celulad *lst, int codi, float *vtotal){ /* A disposição da lista não será alterada, então será passada como ponteiro. O código de identificação é necessário. A soma total será um parametro de referência pois é necessário para a impressão na função "main". */
    celulad *p; /* Ponteiro auxiliar. */
    
    p = lst;
    while(p != NULL && p->cod != codi){
        p = p->prox;
    }

    if(p == NULL) /* Caso chegue ao final, nenhum produto foi encontrado. */
        printf("%d - produto não cadastrado\n", codi); /* Falha. */
    else
        if(p->qtd > 0){ /* Caso o produto esteja em estoque, poderá ser vendido. */
            printf("%d - %s - %.2f",p->cod, p->desc, p->precov); /* Sucesso. */
            *vtotal = *vtotal + p->precov; /* A cada produto vendido, é adicionado ao valor total dos produtos vendidos. */
            p->qtd = p->qtd - 1; /* A quantidade de produtos vendidos será alterada, como um ponteiro auxiliar p é possível a alteração. */
        }
        else
            printf("%d - produto em falta no estoque\n", codi); /* Falha. */
}



/***************

    1.2.8 -> HELP: Essa função mostra na tela um breve texto justificando a estrutura escolhida para o código.

***************/
void help(){

    printf("  O código gira entorno de uma lista principal que contém todos os produtos cadastrados ou importados no sistema. A priori, a escolha da estrutura ser uma lista ");
    printf("encadeada é a facilidade na inserção e remoção de elementos, pois como utiliza a alocação dinâmica de memória, não é necessário que seja estipulado um tamanho fixo de ");
    printf("memória para alocar os elementos novos, como ocorre com os vetores, por exemplo. Com a lista encadeada pode ser armazenado n elementos sem antes informar o sistema a quantidade total de inserções ou remoções.\n");

    printf("  Agora a escolha do tipo da lista principal, que é uma lista simplesmente encadeada sem cabeça. O primeiro critério de escolha foi analisar as operações, ");
    printf("não seria necessário a utilização de uma lista duplamente encadeada, pois a criação de funções a parte da função principal (main) com a utilização de ponteiros auxiliares ");
    printf("já consegue realizar as operações necessárias fornecidas no trabalho (inserção, remoção, importação, criação de listas novas para uma ordenação diferenciada, ");
    printf("salvar em arquivos) sem a existência de um ponteiro extra que aponta para o nó anterior da lista, que também utilizaria muito mais memória.\n");

    printf("  A escolha de uma lista sem cabeça é a facilidade de realizar operações, pois não é preciso levar em consideração que existe um nó vazio inicial toda vez que uma operação for ");
    printf("realizada em cima da lista. Caso a inserção ou remoção acontecesse só no começo, eu acharia viável essa estrutura, mas como pode ocorrer em qualquer parte da lista, ");
    printf("acho mais fácil manusear uma lista simplesmente encadeada e sem cabeça para essas operações.\n");

    printf("  Para as operações “Relatório” e “Sair”, pensei na criação de funções que possuem listas temporárias para ordenar por ordem alfabética e de quantidade, como é descrito nas operações, facilitando assim para a impressão na tela do sistema e ao salvar nos arquivos necessários.\n");
}



/***************

    1.2.9 -> SAIR: Encerra o programa e lista em ordem não decrescente os produtos com o estoque abaixo de 15 unidades, mostra na tela e salva em um arquivo Comprar.txt. Após isso, os produtos registrados e importados no sistema serão salvos/atualizados no arquivo Produtos.dat mantendo o formato do arquivo.

***************/
void sairCompra(celulad *lst){ /* A lista não será alterada então, será passada como ponteiro.*/
    celulad *p, *q, *r, *nova, *lstcompra; /* Ponteiro q auxiliar para a lista principal, ponteiros q r para a nova lista que será criada para armazenar os produtos com baixo estoque. */

    FILE *compra; /* *compra = ponteiro para ser possível armazenar os produtos com baixo estoque no arquivo Comprar.txt. */
    
    lstcompra = NULL;
    p = lst; /* Ponteiro que percorre a lista principal com todos os produtos apra encontrar os produtos que serão salvos no arquivo Comprar.txt, ou seja, com a quantidade < 15. */

    

    while(p != NULL){ /* ponteiro p percorre a lista até o final. */
        if(p != NULL && p->qtd < 15){ /* Percorre a lista principal de produtos a procura dos produtos com o estoque menor que 15. */

            q = NULL;
            r = lstcompra;

            while(r != NULL && p->qtd >= r->qtd){ /* Com o ponteiro p apontando para o produto da lista com o estoque baixo, o laço procura o lugar a ser inserido esse produto na nova lista. */
                q = r;
                r = r->prox;
            }

            nova = (celulad *) malloc(sizeof(celulad));
            if(nova != NULL){
                nova->cod = p->cod;
                strcpy(nova->desc, p->desc);
                nova->qtd = p->qtd;
                nova->precov = p->precov;
                nova->prox = r;
            
                if(q == NULL) /* Inserção no começo da lista vazia. */
                    lstcompra = nova;
                else
                    q->prox = nova;
             }
             else
                printf("Erro ao alocar memória.\n"); /* Falha na alocação de memória. */
        }
        p = p->prox;
    }

    compra = fopen("Comprar.txt", "w"); /* Abertura do arquivo. */
    if(compra != NULL){
        p = lstcompra;
        while(p != NULL){
            fprintf(compra, "%d - %s - %d\n", p->cod, p->desc, p->qtd); /* Impressão no arquivo. */
            printf("%d - %s - %d\n", p->cod, p->desc, p->qtd); /* Impressão na tela. */
            p = p->prox;
        }
    }
    else
        printf("Erro ao salvar produtos com estoque <15 no arquivo Comprar.txt.");
    fclose(compra); /* Fechamento do arquivo. */
    
    excluirLista(&lstcompra); /* Exclusão da lista para a liberar memória. */
}



void imprime(celulad *lst){ /* Impressão dos produtos (armazenados em Produtos.dat) na inicialização do sistema. */
    celulad *p;
    p = lst;
    while(p != NULL){
        printf("%d;%s;%d;%.2f\n", p->cod, p->desc, p->qtd, p->precov);
        p = p->prox;
    }   
}



void imprimearq(celulad *lst, int qtdp, FILE **arq){ /* Impressão em Produtos.dat na finalização do sistema. É passada a lista, quantidade e o arquivo é passado com ponteiro de ponteiros pois ele já foi criado ou já existe na inicialização do sistema. */
    celulad *p;
    p = lst;
    fwrite(&qtdp, sizeof(int), 1, *arq);
    while(p != NULL){
        fwrite(p, sizeof(celulad), 1, *arq);
        p = p->prox;
    }   
}



/***************

    Função "main" para a realização das operações.

***************/
int main(void){

    celulad *listaprod, read; /* Lista para alocar os produtos inseridos ou importados. */
    char comando[10], descr[50], p[3], seqchar[50], learq[30]; /* seqchar = caracteres a serem consultados no comando "consultar". learq = leitura do arquivo a ser importado. */
    int codigo, quant, quantpdt, verif, conta, i; /* quantpdt = quantidade de produtos inseridos/importados ou excluídos (total). verif = verifica se o produto foi inserido ou não, ou se já foi importado, e devolve um valor para definir qual mensagem será mostrada ao usuário. conta = quantidade de produtos contira no arquivo importado. */
    float preco, valoratt, precot; /* valoratt = valor de venda ou quantidade atualizado no comando "atualizar". precot = preço total dos produtos vendidos para o comando "vender". */

    FILE *prodat; /* prodat = ponteiro para abertura do arquivo produtos.dat na inicialização do sistema. */   

    quantpdt = 0; /* Haverá 0 produtos até o cadastro ou importação de produtos. */
    conta = 0; /* 0 produtos importados, além de Produtos.dat, na inicialização. */

    listaprod = NULL; /* Inicialização da lista. */

    verif = 0; /* Inicialização da variável, até então nenhum produto foi importado além do arquivo Produtos.dat. */
    prodat = fopen("Produtos.dat", "ab+"); /* Abertura ou criação do arquivo Produtos.dat na inicialização do sistema. */
    if(prodat != NULL){
        fread(&quantpdt, sizeof(int), 1, prodat);
        i = 0;
        while(i < quantpdt){
            fread(&read, sizeof(celulad), 1, prodat);
            inserir(&listaprod, read.cod, read.desc, read.qtd, read.precov, &verif);
            i++;
        }
        if(quantpdt != 0)
            imprime(listaprod); /* Mostra na tela os produtos do arquivo principal Produtos.dat. */
    }
    else
        printf("Erro ao importar arquivo Produtos.dat para a inicialização do sistema.");

    fclose(prodat); /* Fechamento do arquivo. */

    verif = 0; /* Inicialização da variável, até então nenhum produto foi importado além do arquivo Produtos.dat. */
    do{

        scanf("%s", comando); /* Lê o comando inserido pelo usuário. */

        if(strcmp(comando, "inserir") == 0){ /* Condição para inserir novos produtos na lista -> 1.2.1. */
            scanf("%d %s %d %f", &codigo, descr, &quant, &preco);
            inserir(&listaprod, codigo, descr, quant, preco, &verif); /* A função recebe: lista, código, descrição, quantidade, preço e a variável que verifica se o produto pode ser inserido*/
            quantpdt++; /* Contador para a quantidade de produtos cadastrados, para inserir a quantidade no início do arquivo a ser guardado. */

            if(verif == 1) /* Se o produto for inserido na lista. */
                printf("Produto %d inserido com sucesso!\n", codigo); /* Sucesso. */
            else /* Caso não puder ser inserido na lista. */
                printf("Erro ao inserir o produto %d.\n", codigo); /* Falha. */          
        }

        if(strcmp(comando, "excluir") == 0){ /* Condição para excluir produtos da lista -> 1.2.2. */
            scanf("%d", &codigo);
            excluir(&listaprod, codigo); /* A função recebe: lista e o código do produto a ser excluído. */
            quantpdt--; /* Caso o produto seja excluído, a quantidade de produtos também diminuirá. */
        }

        if(strcmp(comando, "atualizar") == 0){ /* Condição para atualizar valores dos produtos -> 1.2.3. */
            scanf("%s %d %f", p, &codigo, &valoratt);
            atualizar(&listaprod, p, codigo, valoratt); /* A funão recebe: lista, variável p que será "-v" ou "-q", codigo do produto, novo valor a ser atualizado. */
        }

        if(strcmp(comando, "consultar") == 0){ /* Condição para consultar a cadeia ou ubcadeia do(s) produto(s) -> 1.2.4.*/
            scanf("%s", seqchar);
            consultar(listaprod, seqchar); /* A função recebe: lista, sequencia de caracteres a ser consultada. */
        }

        if(strcmp(comando, "relatorio") == 0){ /* Condição para imprimir em ordem alfabética e guardar no arquivo Relatorio.txt-> 1.2.5. */
            relatorio(listaprod); /* A função recebe a lista principal. */
        }

        if(strcmp(comando, "importar") == 0){ /* Condição para importar produtos de um arquivo -> 1.2.6. */
            scanf("%s", learq); 
            importar(&listaprod, learq, codigo, descr, quant, preco, &quantpdt, &verif, &conta); /* A função recebe: lista, nome do arquivo a ser importado, os itens do registro para ser possível a inserção ordenada por código na lista sem a criação de um ponteiro auxiliar dentro da função, a quantidade atual de produtos no sistema. */

            if(verif == 1) /* Se o produto for importado para a lista. */
                printf("%d produtos importados!\n", conta); /* Sucesso. */
            else /* Em caso de falha de importação */
                printf("Erro ao importar do arquivo %s\n", learq);  /* Falha. */
        }

        if(strcmp(comando, "vender") == 0){ /* Condição para analisar quais produtos podem ser vendidos ou não -> 1.2.7. */     
            precot = 0; /* Preço total dos produtos antes de serem vendidos. */  
            do{
                scanf("%d", &codigo);
                if(codigo != 0) /* Condição para a mensagem de "produto não cadastrado" não aparecer na tela. */
                    vender(listaprod, codigo, &precot);
            }while(codigo != 0);
            printf("---------\nTotal %.2f\n", precot); /* Preço total dos produtos vendidos. */
        }

        if(strcmp(comando, "help") == 0){ /* Condição para mostrar na tela um texto justificando a escolha das estruturas para o programa -> 1.2.8. */
            help();
        }

        if(strcmp(comando, "sair") == 0){ /* Condição para a finalização do sistema e armazenamento dos produtos em Produtos.dat e dos produtos com o estoque < 15 em Comprar.txt -> 1.2.9. */
            prodat = fopen("Produtos.dat", "wb+"); /* wb+ para salvar por cima do arqivo aberto, dessa forma as alterações de algum produto já existente antes da abertura do sistema serão atualizadas. */
            if(prodat != NULL)
                imprimearq(listaprod, quantpdt, &prodat); /* Salvar no arquivo Produtos.dat. */
            else
                printf("Erro ao salvar produtos no arquivo Produtos.dat.");
            fclose(prodat);

            sairCompra(listaprod); /* Função que identifica, salva e imprime os produtos com baixo estoque (<15). */
        
            excluirLista(&listaprod); /* Exclusão da lista principal para liberar memória. */
        }

    }while (strcmp(comando, "sair") != 0);  

    return 0;
}
