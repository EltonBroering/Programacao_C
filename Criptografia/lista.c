#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
 
#define TRUE 1
#define FALSE 0
#define PALAVRA "%16[a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"
#define PULAR "%*[^a-zA-ZãÃáÁçéÉóÓúâÂíÍêÊõÕàÀ-]"

/*
 *
 *
 * 
 */

struct Lista *criaLista() {
    struct Lista * lista;

 lista = (struct Lista*) malloc(sizeof (struct Lista));
 
  lista->primeiro = NULL;
  lista->comprimento = 0;
 
    return lista;
}

struct Nodo *  criaNodo (char * palavra) {
    struct Nodo * nodo;

    nodo = (struct Nodo *) malloc (sizeof (struct Nodo));

    if(nodo == NULL) return NULL;

    nodo->palavra=palavra;
    return nodo;
}

int adicionaItem(struct Lista * lista, char * palavra)
{
    struct Nodo *nodo;
    
    if(nodo== NULL) return 0;
    
    nodo=criaNodo(palavra);
    nodo->proximo=lista->primeiro;
    lista->primeiro=nodo;
    
    lista->comprimento++;

    return 1;
}

int    adicionaItemNoFim(struct Lista * lista, char * palavra) {

     struct Nodo *nodo;
     struct Nodo *fim;

	if(lista==NULL) return 0;     
	if(lista->comprimento==0){
         return adicionaItem(lista,palavra);
     }

     nodo=criaNodo(palavra);
     if(nodo==NULL) return 0;

     fim = lista->primeiro;

     for(;fim->proximo!=NULL;fim=fim->proximo);

	  fim->proximo=nodo;           
     lista->comprimento++;
     
     return 1;
}




int buscaPalavra (struct Lista * lista, char *palavra) {

struct Nodo *aux;

for (aux=lista->primeiro; aux!=NULL; aux=aux->proximo){
	if (strcmp(palavra, aux->palavra)==1) return 1;
}
return 0;
}





   // a função malloc aloca dinamicamente uma certa quantidade de bytes.
  // ela retorna um ponteiro para a área de memória alocada, ou NULL
  // se não conseguir realizar a alocação (ex: acabou a memória livre).

void   destroiLista(struct Lista * lista)
{
    // A função free libera uma área de memória que foi alocada anteriormente com malloc
// umNodo é uma variável do tipo "struct Nodo *"
}

void mostraLista(struct Lista *lista){
    struct Nodo *aux;
    int i=0;
        
     for(aux=lista->primeiro; aux != NULL; aux=aux->proximo, i++){
         printf("\n O conteudo do nodo %d: %s \n", i,aux->palavra);
                  
     }
}


// Esta função executa o gpg e testa se ele conseguiu decriptar o arquivo, retornando 
// TRUE caso afirmativo, e FALSE caso contrário.
// Ela usa outras funções específicas do sistema operacional Linux, as quais
// são avançadas para o estágio de conhecimento da turma. Aguardem pela disciplina
// de Sistemas Operacionais na próxima fase para entenderem como ela funciona ...
 
/* Função executa: tenta decriptar um arquivo .gpg
 
Parâmetros de entrada:
chave: a chave de decriptação a ser testada
arquivo: o nome do arquivo encriptado (.gpg)
saida: o nome do arquivo onde será salvo o conteúdo decriptado
 
Valor de retorno da função:
0: se NÃO conseguiu decriptar o arquivo
1: se CONSEGUIU decriptar o arquivo
*/
int executa(char * palavra, char * arquivo, char * pronto) {
  pid_t pid;
  int status;
 
  // cria um novo processo
  pid = fork();
 
  // o bloco dentro do "if" é executado somente pelo processo filho.
  if (pid == 0) {
    // As duas linhas a seguir fazem o redirecionamento de saída padrão deste processo
    // para o arquivo cujo nome está na variável "saida". Elas têm o efeito
    // de escrever "> arquivo_de_saida" após um comando no prompt do shell.
    int fd = open(pronto, O_CREAT | O_WRONLY, 0600);
    dup2(fd, 1);
 
    // Executa o gpg. A função execlp não retorna se conseguir executá-lo.
    execlp("gpg", "gpg", "-d", "--passphrase", palavra, arquivo, NULL);
 
    // Se a linha a seguir for executada, é porque falhou a execução do gpg. Assim,
    // mostra-se uma mensagem de erro na tela e termina-se o programa.
    perror("ao executar o gpg !");
    _exit(errno);
  }
 
  // As próximas linhas são executadas somente pelo processo pai.
  // Espera o gpg terminar, e em seguida testa seu status de terminação.
  // Se ele terminou com sucesso, então significa que conseguiu decriptar o arquivo.
  waitpid(pid, &status, 0);
  if (WIFEXITED(status)) {
    if (WEXITSTATUS(status) == 0) return TRUE;
  }
  return FALSE;
}

