// Define a biblioteca
#ifndef LISTADEDADOS_H_
#define LISTADEDADOS_H_

/*
    Biblioteca para trabalhar com lista sequêncial e tratar dados
    permitindo criação, remoção, adição e consulta

    (c) 2021 Diogo B. Silva
*/

/* **************** Library settings *************** */

#define MAX_PERSON 100 // Máximo de clientes
#define MAX_STATMENT 1000 // Máximo de transações bancárias
#define MAX_STATMENT_CHAR 100 // Máximo de caracteres para descrição de transação bancária
#define MAX_ACCOUNT 200 // Máximo de contas bancárias
#define MAX_NAME 50 // Máximo de caracteres para nome de clinte
#define MAX_ADRESS 30 // Máximo de caracteres para campos de endereço

/* ***************** Data format ******************* */

// Define estrutura para endereços tipo _ADDRESS
typedef struct endereco{
    char state[MAX_ADRESS];
    char city[MAX_ADRESS];
    char bairro[MAX_ADRESS];
    char street[MAX_ADRESS];
    unsigned short number;
    unsigned int zipcode;
}_ADDRESS;

// Define estrutura para pessoas do tipo _PERSON
typedef struct pessoa{
    unsigned short id;
    char name[MAX_NAME];
    unsigned long cpf_cnpj;
    unsigned int phoneNumber;
    _ADDRESS address;
}_PERSON;

// Define estrutura para extrato bancário do tipo _STATMENT
typedef struct extrato{
    unsigned int quantity;
    char statment[MAX_STATMENT][MAX_STATMENT_CHAR]; // Linhas, colunas
}_STATMENT;

// Define estrutura para conta do tipo _ACCOUNT
typedef struct conta{
    unsigned short personId; // Id do cliente
    unsigned long cpf_cnpj; // CPF/CNPJ do cliente
    unsigned int agencyNumber; // Número da agência bancária
    unsigned int accountNumber; // Número da conta
    unsigned int balance; // Saldo da conta
    _STATMENT statmentData; // Extrato da conta bancária
}_ACCOUNT;

// Define a estrutura que armazenará as contas bancárias
typedef struct listaContas{
    int quantity;
    _ACCOUNT accountsData[MAX_ACCOUNT]; // Criar vetor accountData do tipo _ACCOUNT
}_ACCOUNT_LIST;

// Define a estrutura que vai armazenar ao clientes
typedef struct listaClientes{
    int quantity;
    _PERSON peopleData[MAX_PERSON]; // Criar vetor peopleData do tipo _PERSON
}_PERSON_LIST;

/* ************* PERSON LIST FUNCTIONS ************* */

// Função que cria a lista de clientes e carrega clientes salvos em arquivo
_PERSON_LIST* newPesonList();

// Função que grava clientes em arquivo e limpa a lista da memória
int closePersonList(_PERSON_LIST* list);

// Verifica o tamanho da lista
int lengthPersonList(_PERSON_LIST* list);

// Verifica se a lista está cheia
int isFullPersonList(_PERSON_LIST* list);

// Verifica se a lista está vazia
int isEmpityPersonList(_PERSON_LIST* list);

// Insere na lista de forma ordenada
int addPerson(_PERSON_LIST* list, _PERSON person);

// Remove da lista de qualquer posição passando código(id ou CPF/CNPJ)
int removePerson(_PERSON_LIST* list, unsigned long code);

// Obtém o Index na lista passando código(id ou CPF/CNPJ)
int getPersonIndex(_PERSON_LIST* list, unsigned long code);

// Consultar na lista passando código(id ou CPF/CNPJ)
int getPerson(_PERSON_LIST* list, unsigned long code, _PERSON *person);

// Consultar na lista passando nome
int getPersonByName(_PERSON_LIST* list, char name[MAX_NAME], _PERSON *person);

// Atualiza informações passando código(id ou CPF/CNPJ)
int updatePerson(_PERSON_LIST* list, unsigned long code, _PERSON person);

// Reorganiza a lista em ordem alfabética
void personListToAlphabeticalOrder(_PERSON_LIST* list);

/* ************* ACCOUNT LIST FUNCTIONS ************ */

// Função que cria a lista de contas bancárias e carrega contas salvos em arquivo
_ACCOUNT_LIST* newAccountList();

// Função que grava contas bancárias em arquivo e limpa a lista da memória
int closeAccountList(_ACCOUNT_LIST* list);

// Verifica o tamanho da lista
int lengthAccountList(_ACCOUNT_LIST* list);

// Verifica se a lista está cheia
int isFullAccountList(_ACCOUNT_LIST* list);

// Verifica se a lista está vazia
int isEmpityAccountList(_ACCOUNT_LIST* list);

// Insere na lista
int addAccount(_ACCOUNT_LIST* list, _ACCOUNT account);

// Remove da lista de qualquer posição passando número agência e conta
int removeAccount(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber);

// Remove todas as contas associadas a um CPF/CNPJ
void removeAllAccountsOf(_ACCOUNT_LIST* list, unsigned long cpf_cnpj);

// Obtém o Index na lista passando número da agência e conta
int getAccountIndex(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber);

// Obtém o Index onde a primeira conta que contém o CPF/CNPJ está alocada
int getAccountIndexByCode(_ACCOUNT_LIST* list, unsigned long cpf_cnpj);

// Consultar na lista passando número da agência e conta
int getAccount(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber, _ACCOUNT *account);

// Otem a quantidade de contas bancárias associadas a um CPF/CNPJ
int getAmountOfAccounts(_ACCOUNT_LIST* list, unsigned long cpf_cnpj);

// Obtém todos as contas associadas a um CPF/CNPJ e imprime
void getAllAccountsOf(_ACCOUNT_LIST* list, unsigned long cpf_cnpj);

// Lista todas as contas salvas em ordem alfabética e descrecente de saldo
void getAllAccounts(_ACCOUNT_LIST* accountsList, _PERSON_LIST *personList);
/* ************ STATMENT LIST FUNCTIONS ************ */

// Depósito bancária passando número da agência, conta, descrição, valor monetário
int bankDeposit(_ACCOUNT_LIST* list,  unsigned int agencyNumber, unsigned int accountNumber, char *description, float cash);

// Saque passando número da agência, conta, descrição, valor monetário
int bankDraft(_ACCOUNT_LIST* list,  unsigned int agencyNumber, unsigned int accountNumber, char *description, float cash);

// Transrência passando número da agência e conta de origem, agência e conta de destino e valor da transferência
int bankTransfer(_ACCOUNT_LIST* list, unsigned int sourceAgencyNumber, unsigned int sourceAccountNumber, unsigned int destinationAgencyNumber, unsigned int destinationAccountNumber, float cash);

// Mostra o extrato passando número da agência, conta, dias para mostrar
int bankStatment(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber, int daysToShow);

// Libera espaço na primeira posição da lista de extrato
void bankStatmentFreeFirstPosition(_ACCOUNT_LIST* list, unsigned int agencyNumber, unsigned int accountNumber);

/* Termina a biblioteca */
#endif
