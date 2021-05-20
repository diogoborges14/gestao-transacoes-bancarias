/*
    Biblioteca para trabalhar com lista sequêncial e tratar dados
    permitindo criação, remoção, adição e consulta

    (c) 2121 Diogo B. Silva
*/
#include <stddef.h> // Necessário para definir o tipo NULL
#include "listaDeDados.h"
#include <stdlib.h> // Necessário para manipular arquivos
#define personDB "clients.data" // Arquivo que armazena informações sobre clientes
#define accountDB "accounts.data" // Arquivo que armazena informações sobre contas bancárias
#define statmentDB "statment.data" // Arquivo que armazena informações sobre extrato

/* ************* PERSON LIST FUNCTIONS ************* */

// Função que cria a lista de clientes
_PERSON_LIST* newPesonList(){
    _PERSON_LIST *list; // Cria ponteiro para uma lista

    // Aloca espaço para uma lista de clientes do tipo (_PERSON_LIST*)
    list = (_PERSON_LIST*) malloc(sizeof(_PERSON_LIST));
    // Se deu certo
    if(list != NULL){
        list->quantity = 0; // Atribuí 0 para quantidade da lista
    }

    // Retorna a lista criada
    return list;
}

// Função que limpa a lista da memória
void closePersonList(_PERSON_LIST* list){
    
    free(list);

    // Será implementado 

    // short int codigoErro=0;
    // FILE *pessoas_db = fopen(personDB, "rb+"); // Abre arquivo no modo leitura e escrita em binário

    // // Verifica se o arquivo existe
    // if(pessoas_db == NULL){// Caso não exista
    //     // Abrir arquivo no modo escrita em binário
    //     pessoas_db = fopen(personDB, "wb");

    //     // Guarda os dados da pessoa
    //     //   (ponteiro para variáve, tamanho, n items, arquivo)
    //     codigoErro += fwrite(&list, sizeof(list), 1, pessoas_db);
    //     fclose(pessoas_db);
    // }
    // if(codigoErro == 2){
    //     printf("Arquivo adicionado com sucesso\n");
    // }else{
    //     printf("Cheguei no outro lugar com erro\n");
    // } 
}

// Verifica o tamanho da lista
int lenthPersonList(_PERSON_LIST* list){
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        return list->quantity; // Retorna tamanho da lista
    }
}

// Verifica se a lista está cheia
int isFullPersonList(_PERSON_LIST* list){
    // Verifica se a lista existe
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        // Se a quantidade de itens é o máximo permitido
        return (list->quantity == MAX_PERSON); // Retorna 1 para verdadeiro ou 0 para falso
    }
}

// Verifica se a lista está vazia
int isEmpityPersonList(_PERSON_LIST* list){
    // Verifica se a lista existe
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        // Se a quantidade de itens é zero
        return (list->quantity == 0); // Retorna 1 para verdadeiro ou 0 para falso
    }
}

// Insere na lista de forma ordenada
int addPerson(_PERSON_LIST* list, _PERSON person){
    // Verifica se a lista existe e se está cheia
    if((list == NULL) || isFullPersonList(list)){
        return 0; // Retorna 0 (falso), indicando que não foi possível adicionar na lista
    }

    // Verifica se CPF/CNPJ já está cadastrado. Valores negativos indicam erro
    if(getPersonIndex(list, person.cpf_cnpj) >= 0){
        return -1; // Retorna erro -1, indicando que a pessoa já está cadastrada
    }

    // Faz uma varredura no nome dos clientes para decidir em qual posição colocar

    // Insere no final por enquanto
    list->dados[list->quantity] = person;
    list->quantity++;

    return 1; // Retorna 1 (verdadeiro), indicando sucesso na adição
}

// Remove da lista de qualquer posição passando código(id ou CPF/CNPJ)
int removePerson(_PERSON_LIST* list, int code){

    // Em imprementação ...

    // Obtém o índice onde a pessoa está alocada
    int personIndex = getPersonIndex(list, code);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(personIndex >= 0){
        
        return 1; // Retorna 1 (verdadeiro)
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a pessoa
    }
}

// Obtém o Index na lista passando código(id ou CPF/CNPJ)
int getPersonIndex(_PERSON_LIST* list, unsigned long code){
    int i=0;
    
    // Faz verificações para saber se será possível encontrar pessoa
    // → Se: lista é nulo ou a lista está vazia ou o código é negativo ou maior que um CNPJ
    if(
        (list == NULL) ||
        (list->quantity == 0) ||
        (code < 0) ||
        (code > 99999999999999)
    ){
        return -1; // Retorna erro -1, indicando que não foi possível encontrar a pessoa
    }

    // Verifica se o código é um ID ou CPF/CNPJ
    if(code < 999){ // Se menor que 999 → id
        // Percorre os índices procurando pelo ID
        while((code != list->dados[i].id) && (code <= list->quantity)){
            i++;
        }
    }else{ // Senão → CPF/CNPJ
        // Percorre os índices procurando pelo CPF/CNPJ
        while ((code != list->dados[i].cpf_cnpj) && (code <= list->quantity)){
            i++;
        }
    }

    // Verifica se o valor foi encontrado
    if(i == list->quantity){ // Se chegar na posição vazia, indica que procurou em todas a posições e nõo encontrou
        return -2; // Retorna erro -2, indicando que não foi possível encontrar a pessoa
    }else{
        // Retorna a posição da pessoa na lista
        return i;
    }
}

// Consultar na lista passando código(id ou CPF/CNPJ)
int getPerson(_PERSON_LIST* list, unsigned long code, _PERSON *person){
    // Obtém o índice onde a pessoa está alocada
    int personIndex = getPersonIndex(list, code);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(personIndex >= 0){
        // Armazena a pessoa encontrada no ponteiro recebido na função
        *person = list->dados[personIndex];
        return 1; // Retorna 1 (verdadeiro)
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a pessoa
    }
}

// Atualiza informações de cliente passando Index
int updatePerson(_PERSON_LIST* list, int index, _PERSON person){
    // Verifica se a lista é válido
    if(list == NULL){
        return 0; // Retorna 0 (falso), indicando que não foi possível atualizar as informações
    }

    // Atualiza as informações recebidas
    list->dados[index] = person;

    return 1; // Retorna 1 (verdadeiro), indicando que foi atualizado com sucesso
}

/* ************* ACCOUNT LIST FUNCTIONS ************ */

/* ************ STATMENT LIST FUNCTIONS ************ */
