/*
    Biblioteca para trabalhar com lista sequêncial e tratar dados
    permitindo criação, remoção, adição e consulta

    (c) 2021 Diogo B. Silva
*/
#include <stdlib.h> // Necessário para gerenciamento de memória dinâmico (malloc, free)
#include <stdio.h> // Necessário para manipular arquivos (fopen, fclose, fwrite, fread)
#include <string.h> // Necessário para manipular strings (strcmp)
#include <ctype.h> // Necessário para trocar caracteres maísculos e minúsculos(toupper)
#include <math.h> // Necessário para arredondar valor (round)
#include <time.h> // Necessário para obter a data e hora atual
#include "listaDeDados.h"

/* **************** Library settings *************** */
#define personDB "clients.data" // Arquivo que armazena informações sobre clientes
#define accountDB "accounts.data" // Arquivo que armazena informações sobre contas bancárias
#define statmentDB "statment.data" // Arquivo que armazena informações sobre extrato
#define ID_MAX_NUMBER 65536

/* ************* PERSON LIST FUNCTIONS ************* */

// Função que cria a lista de clientes e carrega clientes salvos em arquivo
_PERSON_LIST* newPesonList(){
    FILE *arquivoComClientes = fopen(personDB, "rb"); // Abre arquivo no modo leitura em binário
    short int codigoErro=0;
    _PERSON_LIST *list; // Cria ponteiro para uma lista

    // Aloca espaço para uma lista de clientes do tipo (_PERSON_LIST*)
    list = (_PERSON_LIST*) malloc(sizeof(_PERSON_LIST));

    // Se deu certo
    if(list != NULL){
        list->quantity = 0; // Atribuí 0 para quantidade da lista
    }

    // Verifica se existe um arquivo com clientes.
    if(arquivoComClientes != NULL){
        // Lê os dados dos clientes do arquivo
        //          (ponteiro para variável, tamanho, n items, arquivo)
        codigoErro = fread(list, sizeof(_PERSON_LIST), 1, arquivoComClientes);
        fclose(arquivoComClientes);

        // Verifica se ocorreu erro ao ler o arquivo
        if(codigoErro == 1){
            printf("Clientes carregados com sucesso. \n");
        }else{
            printf("Erro ao carregar clientes. Cod.: %d\n", codigoErro);
        }
    }

    // Retorna a lista criada
    return list;
}

// Função que grava clientes em arquivo e limpa a lista da memória
int closePersonList(_PERSON_LIST* list){
    FILE *arquivoComClientes = fopen(personDB, "wb"); // Abre arquivo no modo escrita em binário
    short int codigoErro=0;

    // Guarda os dados dos clientes no arquivo
    //           (ponteiro para variável, tamanho, n items, arquivo)
    codigoErro = fwrite(list, sizeof(_PERSON_LIST), 1, arquivoComClientes);
    fclose(arquivoComClientes);

    // Verifica se ocorreu erro ou se a lista é nula
    if(codigoErro != 1 || list == NULL){
        return 0; // Retorna 0 (falso), indicando que não foi possível gravar o arquivo
    }

    // Libera a lista da memória
    free(list);

    return 1; // Retorna 1 (verdadeiro), indicando sucesso ao gravar lista e liberar lista da memória
}

// Verifica o tamanho da lista
int lengthPersonList(_PERSON_LIST* list){
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

    // Verifica se CPF/CNPJ ou Id já está cadastrado. Valores positivos indicam que foi encontrado
    if((getPersonIndex(list, person.cpf_cnpj) >= 0) || (getPersonIndex(list, person.id) >= 0)){
        return -1; // Retorna erro -1, indicando que o CPF/CNPJ ou Id já está cadastrada
    }

    // Insere no final da lista
    list->peopleData[list->quantity] = person;
    list->quantity++;

    // Oraganiza a lista em ordem alfabética
    if(list->quantity > 1){
        personListToAlphabeticalOrder(list);
    }

    return 1; // Retorna 1 (verdadeiro), indicando sucesso na adição
}

// Remove da lista de qualquer posição passando código(id ou CPF/CNPJ)
int removePerson(_PERSON_LIST* list, unsigned long code){
    int i=0;

    // Obtém o índice onde a pessoa está alocada
    int personIndex = getPersonIndex(list, code);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(personIndex >= 0){
        // Move os itens para esquerda ← sobrescevendo o primeiro item
        for (i = personIndex; i < list->quantity; i++){
            /*                 próximo elemento inserido
            se torna o elemento anterior               */
            list->peopleData[i] = list->peopleData[i+1];
        }
        
        // Apaga a última pessoa adicionado indicando que a última posição está vaga
        list->quantity--;
        return 1; // Retorna 1 (verdadeiro), indicando que foi excluído com sucesso
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a pessoa
    }
}

// Obtém o Index na lista passando código(id ou CPF/CNPJ)
int getPersonIndex(_PERSON_LIST* list, unsigned long code){
    int personIndex = 0;

    // Faz verificações para saber se será possível encontrar pessoa
    // → Se: lista é nulo ou a lista está vazia ou o código é negativo ou maior que um CNPJ
    if(
        (list == NULL) ||
        (isEmpityPersonList(list)) ||
        (code < 0) ||
        (code > 99999999999999)
    ){
        return -1; // Retorna erro -1, indicando que não foi possível encontrar a pessoa
    }

    // Verifica se o código é um ID ou CPF/CNPJ
    if(code < ID_MAX_NUMBER){ // Se menor que ID_MAX_NUMBER → id
        // Percorre os índices procurando pelo ID
        while((code != list->peopleData[personIndex].id) && (personIndex < list->quantity)){
            personIndex++;
        }
    }else{ // Senão → CPF/CNPJ
        // Percorre os índices procurando pelo CPF/CNPJ
        while ((code != list->peopleData[personIndex].cpf_cnpj) && (personIndex < list->quantity)){
            personIndex++;
        }
    }

    // Verifica se o valor foi encontrado
    if(personIndex == list->quantity){ // Se chegar na posição vazia, indica que procurou em todas as posições e nõo encontrou
        return -2; // Retorna erro -2, indicando que não foi possível encontrar a pessoa
    }else{
        // Retorna a posição da pessoa na lista
        return personIndex;
    }
}

// Consultar na lista passando código(id ou CPF/CNPJ)
int getPerson(_PERSON_LIST* list, unsigned long code, _PERSON *person){
    // Obtém o índice onde a pessoa está alocada
    int personIndex = getPersonIndex(list, code);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(personIndex >= 0){
        // Armazena a pessoa encontrada no ponteiro recebido na função
        *person = list->peopleData[personIndex];
        return 1; // Retorna 1 (verdadeiro)
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a pessoa
    }
}

// Consultar na lista passando nome
int getPersonByName(_PERSON_LIST* list, char name[MAX_NAME], _PERSON *person){
    int personIndex=0;
    int commonChar=0; // quantidade de caracteres em comúm
    int commonCharRecord=0; // maior recorde de caracteres em comúm
    int i, k;

    // Percorre todas as pessoas da lista verificando se os nomes são iguais 
    while((strcmp(name, list->peopleData[personIndex].name) != 0) && (personIndex < list->quantity)){
        personIndex++;
    }

    /* Verifica se o nome foi encontrado. 
       Se "personIndex" chegou em "list->quantity", indica que procurou em todas as posições e nõo encontrou.
    */
    if(personIndex == list->quantity){
        /* Tenta achar o nome que temanha maior quantidade de caracteres em comúm */
        
        // Percorre todas as pessoas da lista
        for (k = 0; k < list->quantity; k++){
            // Percorre todos os caracteres do nome da pessoa na lista ou name recebido na função. O que chegar primeiro
            for(i=0; (i < MAX_NAME && i < strlen(name)); i++){
                // Verifica se os caracteres são iguais (usando a versão em minúsuclo dos caracteres)
                if(tolower(list->peopleData[k].name[i]) == tolower(name[i])){
                    commonChar += 1;
                }
            }

            /* Verifica se nome da pessoa em peopleData[k].name tem
               mais caracteres em comúm que o nome da pessoa anterior.
               Ou se for a primeira excução, a pessoa que tem a maior correpondência se torna peopleData[0]*/
            if(commonChar > commonCharRecord || k == 0){
                personIndex = k;
                commonCharRecord = commonChar;
            }
            // Reseta a quantidade de caracteres em comúm
            commonChar = 0;
        }

        // Armazena a pessoa encontrada no ponteiro recebido na função
        *person = list->peopleData[personIndex];
        return -1; // Retorna -1, indicando nome não encontrado. Porém, existe uma possível correpondência
    }else{
        // Siginifica que encontrou a pessoa.
        // Armazena a pessoa encontrada no ponteiro recebido na função
        *person = list->peopleData[personIndex];
        return 1; // Retorna 1 (verdadeiro)
    }
}

// Atualiza informações passando código(id ou CPF/CNPJ)
int updatePerson(_PERSON_LIST* list, unsigned long code, _PERSON person){
    int personIndex = 0;

    // Obtém o índice onde a pessoa está alocada
    personIndex = getPersonIndex(list, code);

    // Verifica se a lista é válido e se o índice encontrado é válido
    if(list == NULL || personIndex < 0){
        return 0; // Retorna 0 (falso), indicando que não foi possível atualizar as informações
    }

    // Atualiza as informações recebidas
    list->peopleData[personIndex] = person;

    // Reorganiza a lista em ordem alfabética
    if(list->quantity > 1){
        personListToAlphabeticalOrder(list);
    }

    return 1; // Retorna 1 (verdadeiro), indicando que foi atualizado com sucesso
}

// Organiza a lista em ordem alfabética
void personListToAlphabeticalOrder(_PERSON_LIST* list){
    _PERSON temporaryPerson;
    int k=0;
    int i=0;

    // Percorre a lista de pessoas várias vezes
    for(k=0; (k < list->quantity * list->quantity); k++){
        /* Coloca a primeira letra do nome da pessoa em maiúscula
           → 1ª letra do nome recebe sua versão maiúscula */
        list->peopleData[i].name[0] = toupper(list->peopleData[i].name[0]);
        list->peopleData[i+1].name[0] = toupper(list->peopleData[i+1].name[0]);

        /* Compara o valor entre dois nomes
           → se (valor > 0) → não está em ordem alfabética 
           → se (valor < 0) → está em ordem crescente/alfabética
           → se (valor == 0) as duas palavras tem o mesmo valor */
        if(strcmp(list->peopleData[i].name, list->peopleData[i+1].name) > 0){
            // Troca posição de pessoa[i] por pessoa[i+1] e vice-versa, usando variável auxiliar temporaryPerson
            temporaryPerson = list->peopleData[i];
            list->peopleData[i] = list->peopleData[i+1];
            list->peopleData[i+1] = temporaryPerson;
        }
            
        // Passa para a próximo pessoa
        i++;

        // Se chegar na última posição, volta do início
        if(i == list->quantity-1){
            i = 0;
        }
    }
}

/* ************* ACCOUNT LIST FUNCTIONS ************ */

// Função que cria a lista de contas bancárias e carrega contas salvos em arquivo
_ACCOUNT_LIST* newAccountList(){
    FILE *arquivoComClientes = fopen(accountDB, "rb"); // Abre arquivo no modo leitura em binário
    short int codigoErro=0;
    _ACCOUNT_LIST *list; // Cria ponteiro para uma lista

    // Aloca espaço para uma lista de contas bancárias do tipo (_ACCOUNT_LIST*)
    list = (_ACCOUNT_LIST*) malloc(sizeof(_ACCOUNT_LIST));

    // Se deu certo
    if(list != NULL){
        list->quantity = 0; // Atribuí 0 para quantidade da lista
    }

    // Verifica se existe um arquivo com clientes.
    if(arquivoComClientes != NULL){
        // Lê os dados dos clientes do arquivo
        //          (ponteiro para variável, tamanho, n items, arquivo)
        codigoErro = fread(list, sizeof(_ACCOUNT_LIST), 1, arquivoComClientes);
        fclose(arquivoComClientes);

        // Verifica se ocorreu erro ao ler o arquivo
        if(codigoErro == 1){
            printf("Contas bancárias carregadas com sucesso. \n");
        }else{
            printf("Erro ao carregar contas bancárias. Cod.: %d\n", codigoErro);
        }
    }

    // Retorna a lista criada
    return list;
}

// Função que grava contas bancárias em arquivo e limpa a lista da memória
int closeAccountList(_ACCOUNT_LIST* list){
    FILE *arquivoComContasBancarias = fopen(accountDB, "wb"); // Abre arquivo no modo escrita em binário
    short int codigoErro=0;

    // Guarda os dados das contas bancárias no arquivo
    //           (ponteiro para variável, tamanho, n items, arquivo)
    codigoErro = fwrite(list, sizeof(_ACCOUNT_LIST), 1, arquivoComContasBancarias);
    fclose(arquivoComContasBancarias);

    // Verifica se ocorreu erro ou se a lista é nula
    if(codigoErro != 1 || list == NULL){
        return 0; // Retorna 0 (falso), indicando que não foi possível gravar o arquivo
    }

    // Libera a lista da memória
    free(list);

    return 1; // Retorna 1 (verdadeiro), indicando sucesso ao gravar lista e liberar lista da memória
}

// Verifica o tamanho da lista
int lengthAccountList(_ACCOUNT_LIST* list){
    // Verifica se a lista existe
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        return list->quantity; // Retorna tamanho da lista
    }
}

// Verifica se a lista está cheia
int isFullAccountList(_ACCOUNT_LIST* list){
    // Verifica se a lista existe
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        // Se a quantidade de itens é o máximo permitido
        return (list->quantity == MAX_ACCOUNT); // Retorna 1 para verdadeiro ou 0 para falso
    }
}

// Verifica se a lista está vazia
int isEmpityAccountList(_ACCOUNT_LIST* list){
    // Verifica se a lista existe
    if(list == NULL){
        return -1; // Se a lista é nula, retorna erro -1
    }else{
        // Se a quantidade de itens é zero
        return (list->quantity == 0); // Retorna 1 para verdadeiro ou 0 para falso
    }
}

// Insere na lista
int addAccount(_ACCOUNT_LIST* list, _ACCOUNT account){
    // Verifica se a lista existe e se está cheia
    if((list == NULL) || isFullAccountList(list)){
        return 0; // Retorna 0 (falso), indicando que não foi possível adicionar na lista
    }

    // Verifica se o número da conta e agência já estão cadastrados. Valores positivos indicam que foi encontrado
    if(getAccountIndex(list, account.agencyNumber, account.accountNumber) >= 0){
        return -1; // Retorna erro -1, indicando que a conta e agência já estão cadastradas
    }

    // Atribuí saldo 0 para conta
    account.balance = 0;
    // Insere no final da lista
    list->accountsData[list->quantity] = account;
    list->quantity++;

    return 1; // Retorna 1 (verdadeiro), indicando sucesso na adição
}

// Remove da lista de qualquer posição passando número agência e conta
int removeAccount(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber){
    int i, accountIndex=0;

    // Obtém o índice onde a conta está alocada
    accountIndex = getAccountIndex(list, agencyNumber, accountNumber);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(accountIndex >= 0){
        // Move os itens para esquerda ← sobrescevendo o primeiro item
        for (i = accountIndex; i < list->quantity; i++){
            /*                 próximo elemento inserido
            se torna o elemento anterior               */
            list->accountsData[i] = list->accountsData[i+1];
        }

        // Apaga a última conta adicionado indicando que a última posição está vaga
        list->quantity--;
        return 1; // Retorna 1 (verdadeiro), indicando que foi excluído com sucesso
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a conta
    }
}

// Remove todas as contas associadas a um CPF/CNPJ. (é acionado quando um cliente é excuído)
void removeAllAccountsOf(_ACCOUNT_LIST* list, unsigned long cpf_cnpj){
    int accountIndex = 0;

    // Enquanto encontrar alguma conta
    while(getAccountIndexByCode(list, cpf_cnpj) >= 0){

        // Move os itens para esquerda ← sobrescevendo
        for(accountIndex = getAccountIndexByCode(list, cpf_cnpj); accountIndex < list->quantity; accountIndex++){
            /*                   próximo elemento inserido
            se torna o elemento anterior                 */
            list->accountsData[accountIndex] = list->accountsData[accountIndex+1];
        }

        // Apaga a última conta adicionado indicando que a última posição está vaga
        list->quantity--;
    }
}

// Obtém o Index onde a primeira conta que contém o CPF/CNPJ está alocada
int getAccountIndexByCode(_ACCOUNT_LIST* list, unsigned long cpf_cnpj){
    int accountIndex = 0;

    // Faz verificações para saber se será possível encontrar conta
    // → Se: lista é nulo ou a lista está vazia ou o CPF/CNPJ < ID ou maior que um CNPJ
    if(
        (list == NULL) ||
        (isEmpityAccountList(list)) ||
        (cpf_cnpj < ID_MAX_NUMBER) ||
        (cpf_cnpj > 99999999999999)
    ){
        return -1; // Retorna erro -1, indicando que não foi possível encontrar a conta com este id ou CPF/CNPJ
    }

    // Percorre os índices procurando pelo CPF/CNPJ
    while ((cpf_cnpj != list->accountsData[accountIndex].cpf_cnpj) && (accountIndex < list->quantity)){
        accountIndex++;
    }

    // Verifica se o valor foi encontrado
    if(accountIndex == list->quantity){ // Se chegar na posição vazia, indica que procurou em todas as posições e nõo encontrou
        return -2; // Retorna erro -2, indicando que não foi possível encontrar a conta
    }else{
        // Retorna a posição da conta na lista
        return accountIndex;
    }
}

// Obtém o Index na lista passando número da agência e conta
int getAccountIndex(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber){
    int accountIndex = 0;

    // Faz verificações para saber se será possível encontrar conta
    // → Se: lista é nulo ou a lista está vazia ou a agencia ou conta são números negativos
    if(
        (list == NULL) ||
        (isEmpityAccountList(list)) ||
        (agencyNumber < 0) ||
        (accountNumber < 0)
    ){
        return -1; // Retorna erro -1, indicando que não foi possível encontrar a conta com agência
    }

    /* Percorre os índices procurando pelo núero da agência e conta.
       → Enquanto agência ou conta não forem encontradas, continue incrementando
       → Enquanto accountIndex não chegou no final da lista continue incrementando
    */
    while(
        (
            agencyNumber != list->accountsData[accountIndex].agencyNumber ||
            accountNumber != list->accountsData[accountIndex].accountNumber
        ) &&
        accountIndex < list->quantity
    ){
        accountIndex++;
    }

    // Verifica se o valor foi encontrado
    if(accountIndex == list->quantity){ // Se chegar na posição vazia, indica que procurou em todas as posições e nõo encontrou
        return -2; // Retorna erro -2, indicando que não foi possível encontrar a conta e agnencia
    }else{
        // Retorna a posição da conta e agência
        return accountIndex;
    }
}

// Consultar na lista passando código(id ou CPF/CNPJ)
int getAccount(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber, _ACCOUNT *account){
    // Obtém o índice onde a conta está alocada
    int accountIndex = getAccountIndex(list, agencyNumber, accountNumber);

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(accountIndex >= 0){
        // Armazena a conta encontrada no ponteiro recebido na função
        *account = list->accountsData[accountIndex];
        return 1; // Retorna 1 (verdadeiro)
    }else{
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar a conta
    }
}

// Otem a quantidade de contas bancárias associadas a um CPF/CNPJ
int getAmountOfAccounts(_ACCOUNT_LIST* list, unsigned long cpf_cnpj){
    int accountsQuantity = 0;

    // Verifica se a lista existe
    if(list == NULL){
        return 0; // Retorna 0 (falso), indicando que não foi possível encontrar contas
    }

    // Percorre toda a lista de contas bancárias
    for(int accountIndex = 0; accountIndex < MAX_ACCOUNT; accountIndex++){
        // Se encontrar alguma conta, contablizar
        if(list->accountsData[accountIndex].cpf_cnpj == cpf_cnpj){
            accountsQuantity++;
        }
    }

    return accountsQuantity;
}

// Obtém todos as contas associadas a um CPF/CNPJ e imprime
void getAllAccountsOf(_ACCOUNT_LIST* list, unsigned long cpf_cnpj){
    int accountIndex;
    int accountsQuantity = getAmountOfAccounts(list, cpf_cnpj);
    int i=0;
    int tmpBalance;
    int *balancesMask = (int *)malloc(sizeof(int) * accountsQuantity); // Aloca vetor dinâmico para os saldos

    // Verifica se a lista existe
    if(list == NULL){
        return; // Retorna, indicando que não foi possível encontrar contas
    }

    // Percorre toda a lista de contas bancárias
    for(accountIndex = 0; accountIndex < list->quantity; accountIndex++){
        // Se achar uma conta do cliente, copiar saldo
        if(list->accountsData[accountIndex].cpf_cnpj == cpf_cnpj){
            balancesMask[i] = list->accountsData[accountIndex].balance;
            i++;
        }
    }

    i = 0;
    if(accountsQuantity > 1){ // Só vai ordenar se tiver 2 ou mais elementos
        // Ordena lista de saldo
        while(balancesMask[i] < balancesMask[i+1]){
            tmpBalance = balancesMask[i];
            balancesMask[i] = balancesMask[i+1];
            balancesMask[i+1] = tmpBalance;

            i++;
            // Se chegar no final da lista, volta do início
            if(i >= accountsQuantity - 1){
                i = 0;
            }
        }
    }

    i = 0; // Representa index do saldo
    accountIndex = 0;
    /* 
        Percorre toda a lista de contas bancárias várias vezes,
        a primeira lista 'balancesMask' está em ordem descrescente de saldo
        ele servirá como uma 'másca' para decidir quanto um saldo deve ser impresso
    */
    while(i < accountsQuantity){
        // Se achar a conta de um cliente cujo saldo seja igual ao da máscara 'balancesMask', mostrá-la
        if(
            list->accountsData[accountIndex].cpf_cnpj == cpf_cnpj &&
            list->accountsData[accountIndex].balance == balancesMask[i]
        ){
            printf(
                "-----------------------------------\n"
                "Agência: %u\n"
                "Conta: %u\n"
                "Saldo: R$%.2f\n",
                list->accountsData[accountIndex].agencyNumber,
                list->accountsData[accountIndex].accountNumber,
                (list->accountsData[accountIndex].balance / 100.0)
            );
            i++; // Incrementa índice de 'balancesMask'
        }
        accountIndex++;
        // Se chegar no final da lista de contas, voltar do início
        if(accountIndex >= list->quantity){
            accountIndex = 0;
        }
    }

    free(balancesMask); // Libera o array da memória
}

// Lista todas as contas salvas em ordem alfabética e descrecente de saldo
void getAllAccounts(_ACCOUNT_LIST* accountsList, _PERSON_LIST *personList){
    typedef struct contas{
        unsigned short personId; // Id do cliente
        unsigned long cpf_cnpj; // CPF/CNPJ do cliente
        char name[MAX_NAME]; // Nome do cliente
    }_ACCOUNTS2;
    _ACCOUNTS2 accountsToShow[accountsList->quantity];
    _ACCOUNTS2 tmpAccount;
    char lastName[MAX_NAME];
    int i, k;

    // Copia todas as contas para uma array do tipo 'accounts2'
    for(i=0; i < accountsList->quantity; i++){
        accountsToShow[i].cpf_cnpj = accountsList->accountsData[i].cpf_cnpj;
        accountsToShow[i].personId = accountsList->accountsData[i].personId;
        strcpy( // Copia o nome do cliente
            accountsToShow[i].name,
            personList->peopleData[
                getPersonIndex(personList, accountsList->accountsData[i].cpf_cnpj) // Obtem o índice do cliente enviando a lista de clientes e CPF/CNPJ
            ].name
        );
    }

    if(accountsList->quantity > 1){
        // Oraganiza em ordem alfabética
        k=0;
        i=0;
        // Percorre a lista de clientes várias vezes
        for(k=0; (k < accountsList->quantity * accountsList->quantity); k++){
            /* Coloca a primeira letra do nome da pessoa em maiúscula
            → 1ª letra do nome recebe sua versão maiúscula */
            accountsToShow[i].name[0] = toupper(accountsToShow[i].name[0]);
            accountsToShow[i+1].name[0] = toupper(accountsToShow[i+1].name[0]);

            /* Compara o valor entre dois nomes
            → se (valor > 0) → não está em ordem alfabética 
            → se (valor < 0) → está em ordem crescente/alfabética
            → se (valor == 0) as duas palavras tem o mesmo valor */
            if(strcmp(accountsToShow[i].name, accountsToShow[i+1].name) > 0){
                // Troca posição de conta[i] por conta[i+1] e vice-versa, usando variável auxiliar
                tmpAccount = accountsToShow[i];
                accountsToShow[i] = accountsToShow[i+1];
                accountsToShow[i+1] = tmpAccount;
            }
                
            // Passa para a próximo conta
            i++;

            // Se chegar na última posição, volta do início
            if(i >= accountsList->quantity-1){
                i = 0;
            }
        }
    }

    // Mostrando todas as contas bancárias
    for(i=0; i < accountsList->quantity; i++){
        // Verifica se cliente já foi mostrado anteriomente
        if(strcmp(accountsToShow[i].name, lastName) != 0){
            printf(
                "\n\033[1;31m$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\033[0m\n"
                "Nome: %s\n"
                "Id: %hu\n"
                "CPF/CNPJ: %lu\n",
                accountsToShow[i].name,
                accountsToShow[i].personId,
                accountsToShow[i].cpf_cnpj
            );
            getAllAccountsOf(accountsList, accountsToShow[i].cpf_cnpj);
        }
        strcpy( // Guarda o nome do último cliente exibido
            lastName,
            accountsToShow[i].name
        );
    }
}

/* ************ STATMENT LIST FUNCTIONS ************ */

// Depósito bancária passando número da agência, conta, descrição, valor monetário
int bankDeposit(_ACCOUNT_LIST* list,  unsigned int agencyNumber, unsigned int accountNumber, char *description, float cash){
    unsigned int cashOnInteger;
    int accountIndex = getAccountIndex(list, agencyNumber, accountNumber);
    char descriptionFormated[MAX_STATMENT_CHAR];

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(accountIndex < 0){
        return 0; // Retorna 0 (falso), indicando que não foi possível realizar o depósito
    }

    // Transforma o valor em inteiro, arredondando com 2 casas decimais
    cashOnInteger = round(cash * 100);

    // Adiciona o valor à conta
    list->accountsData[accountIndex].balance += cashOnInteger;
    
    // Obtem a hora atual
    struct tm *dateAndTime;
    time_t seconds; // variável do tipo time_t para armazenar o tempo em segundos
    time(&seconds);// obtendo o tempo em segundos
    dateAndTime = localtime(&seconds);// para converter de segundos para o tempo local utilizamos a função localtime

    // Adiciona detalhes na descrição
    sprintf(
        descriptionFormated,
        "R$%.2f - %s - CREDITO — %02d/%02d/%02d às %02d:%02d:%02d\n",
        (cashOnInteger / 100.0),
        description,
        dateAndTime->tm_mday,
        dateAndTime->tm_mon+1,
        dateAndTime->tm_year+1900,
        dateAndTime->tm_hour,
        dateAndTime->tm_min,
        dateAndTime->tm_sec
    );

    // Libera espaço na primeira posição do Extrato
    bankStatmentFreeFirstPosition(list, agencyNumber, accountNumber);

    // Adicona a descrição da transação na posição 0
    strcpy(
        list->accountsData[accountIndex].statmentData.statment[0],
        descriptionFormated
    );
    list->accountsData[accountIndex].statmentData.quantity++; // Incrementa

    return 1; // Retorna 1 (verdadeiro), indicando sucesso no depósito
}

// Saque passando número da agência, conta, valor monetário
int bankDraft(_ACCOUNT_LIST* list,  unsigned int agencyNumber, unsigned int accountNumber, char *description, float cash){
    unsigned int cashOnInteger;
    int accountIndex = getAccountIndex(list, agencyNumber, accountNumber);
    char descriptionFormated[MAX_STATMENT_CHAR];

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(accountIndex < 0){
        return 0; // Retorna 0 (falso), indicando que não foi possível realizar o saque
    }

    // Transforma o valor em inteiro, arredondando com 2 casas decimais
    cashOnInteger = round(cash * 100);

    // Verifica se existe saldo suficiente para o saque
    if(list->accountsData[accountIndex].balance < cashOnInteger){
        return -1; // Retorna erro -1, indicando que não há saldo suficiente
    }

    // Faz o saque
    list->accountsData[accountIndex].balance -= cashOnInteger;

    // Obtem a hora atual
    struct tm *dateAndTime;
    time_t seconds; // variável do tipo time_t para armazenar o tempo em segundos
    time(&seconds);// obtendo o tempo em segundos
    dateAndTime = localtime(&seconds);// para converter de segundos para o tempo local utilizamos a função localtime

    // Adiciona detalhes na descrição
    sprintf(
        descriptionFormated,
        "R$-%.2f - %s - DÉBITO — %02d/%02d/%02d às %02d:%02d:%02d\n",
        (cashOnInteger / 100.0),
        description,
        dateAndTime->tm_mday,
        dateAndTime->tm_mon+1,
        dateAndTime->tm_year+1900,
        dateAndTime->tm_hour,
        dateAndTime->tm_min,
        dateAndTime->tm_sec
    );

    // Libera espaço na primeira posição do Extrato
    bankStatmentFreeFirstPosition(list, agencyNumber, accountNumber);
    
    // Adicona a descrição da transação na posição 0
    strcpy(
        list->accountsData[accountIndex].statmentData.statment[0],
        descriptionFormated
    );
    list->accountsData[accountIndex].statmentData.quantity++; // Incrementa

    return 1; // Retorna 1 (verdadeiro), indicando sucesso ao sacar o dinheiro
}

// Transrência passando número da agência e conta de origem, agência e conta de destino e valor da transferência
int bankTransfer(_ACCOUNT_LIST* list, unsigned int sourceAgencyNumber, unsigned int sourceAccountNumber, unsigned int destinationAgencyNumber, unsigned int destinationAccountNumber, float cash){
    unsigned int cashOnInteger;
    int sourceAccountIndex = getAccountIndex(list, sourceAgencyNumber, sourceAccountNumber);
    int destinationAccountIndex = getAccountIndex(list, destinationAgencyNumber, destinationAccountNumber);
    char descriptionFormated[MAX_STATMENT_CHAR];

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(sourceAccountIndex < 0 || destinationAccountIndex < 0 || cash < 0){
        return 0; // Retorna 0 (falso), indicando que não foi possível realizar a transferência
    }

    // Transforma o valor em inteiro, arredondando com 2 casas decimais
    cashOnInteger = round(cash * 100);
    
    // Verifica se tem saldo suficiente na conta de origem
    if(list->accountsData[sourceAccountIndex].balance < cashOnInteger){
        return -1; // Retorna erro -1, indicando que o saldo é insuficiente
    }

    // Faz o saque da conta de origem
    list->accountsData[sourceAccountIndex].balance -= cashOnInteger;

    // Adiciona o valor à conta de destino
    list->accountsData[destinationAccountIndex].balance += cashOnInteger;

    // Obtem a hora atual
    struct tm *dateAndTime;
    time_t seconds; // variável do tipo time_t para armazenar o tempo em segundos
    time(&seconds);// obtendo o tempo em segundos
    dateAndTime = localtime(&seconds);// para converter de segundos para o tempo local utilizamos a função localtime

    // Adiciona detalhes na descrição de origiem e copia para extrato
    sprintf(
        descriptionFormated,
        "R$-%.2f - Tranferência para conta: %u-%u — %02d/%02d/%02d às %02d:%02d:%02d\n",
        (cashOnInteger / 100.0),
        destinationAccountNumber,
        destinationAccountNumber,
        dateAndTime->tm_mday,
        dateAndTime->tm_mon+1,
        dateAndTime->tm_year+1900,
        dateAndTime->tm_hour,
        dateAndTime->tm_min,
        dateAndTime->tm_sec
    );
    // Libera espaço na primeira posição do Extrato
    bankStatmentFreeFirstPosition(list, sourceAgencyNumber, sourceAccountNumber);
    strcpy(
        list->accountsData[sourceAccountIndex].statmentData.statment[0],
        descriptionFormated
    );
    list->accountsData[sourceAccountIndex].statmentData.quantity++; // Incrementa

    // Adiciona detalhes na descrição de destino e copia para extrato
    sprintf(
        descriptionFormated,
        "R$%.2f - Tranferência de conta: %u-%u — %02d/%02d/%02d às %02d:%02d:%02d\n",
        (cashOnInteger / 100.0),
        sourceAgencyNumber,
        sourceAccountNumber,
        dateAndTime->tm_mday,
        dateAndTime->tm_mon+1,
        dateAndTime->tm_year+1900,
        dateAndTime->tm_hour,
        dateAndTime->tm_min,
        dateAndTime->tm_sec
    );
    // Libera espaço na primeira posição do Extrato
    bankStatmentFreeFirstPosition(list, destinationAgencyNumber, destinationAccountNumber);
    strcpy(
        list->accountsData[destinationAccountIndex].statmentData.statment[0],
        descriptionFormated
    );
    list->accountsData[destinationAccountIndex].statmentData.quantity++; // Incrementa

    return 1; // Retorna 1 (verdadeiro), indicando a transferência foi realizada com sucesso.
}

// Mostra o extrato passando número da agência, conta, dias para mostrar
int bankStatment(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber, int daysToShow){
    int accountIndex = getAccountIndex(list, agencyNumber, accountNumber);
    int dayReaded;
    int lastDayReaded=99;
    int daysCounted=0;
    int i = 0;

    // Verifica se o valor é válido. Valores negativos indicam erro
    if(accountIndex < 0 || daysToShow <= 0){
        return 0; // Retorna 0 (falso), indicando que não foi possível mostrar o extrato
    }

    // Verifica se o extrato está vazio
    if(list->accountsData[accountIndex].statmentData.quantity == 0){
        return -1; // Retorna erro -1, indicando que o extrato está vazio
    }

    // Percorre todo o extrato
    for(i = 0; i < list->accountsData[accountIndex].statmentData.quantity; i++){
        /* Scanf to search the day number. I'm using a special character
            —	em dash	        020024	8212	0x2014	&mdash;     */
        sscanf(
            list->accountsData[accountIndex].statmentData.statment[i],
            "%*[^—]—%d/%*d/%*d às %*d:%*d:%*d",
            &dayReaded
        );

        // Conta quantos dias diferente estão sendo mostrado 
        if(daysCounted <= daysToShow && dayReaded != lastDayReaded){
            daysCounted++;
        }

        // Mostra o extrato 
        printf("%s\n", list->accountsData[accountIndex].statmentData.statment[i]);
        
        // Verifica se já tiver atingido a quantidade de dias suficiente
        if(daysCounted == daysToShow){
            break; // Encerra o loop
        }

        // Guarda o último dia lido
        lastDayReaded = dayReaded;
    }

    return 1; // Retorna 1 (verdadeiro), indicando sucesso
}

// Libera espaço na primeira posição da lista de extrato
void bankStatmentFreeFirstPosition(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber){
    int accountIndex = getAccountIndex(list, agencyNumber, accountNumber);

    // Libera espaço na primeira posição do Extrato
    for(int i = list->accountsData[accountIndex].statmentData.quantity - 1; i >= 0; i--){
        strcpy(
            list->accountsData[accountIndex].statmentData.statment[i+1], // próxima posição na lista[i+1]
            list->accountsData[accountIndex].statmentData.statment[i]  // recebe o elemento atual [i]
        );
    }
}
