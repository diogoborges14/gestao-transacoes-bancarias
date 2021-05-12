//Função: gerenciar transações financeira
//Data início: 11/05/2021
#include <stdio.h>
#include <locale.h> // Localização, caracteres
#include <string.h> // Trabalhar com strings
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1
#define databaseFile "database.data"

// Define estrutura para endereços tipo _ADDRESS
typedef struct endereco{
    char state[20];
    char city[20];
    char bairro[20];
    char street[40];
    unsigned short int number;
    unsigned int zipcode;
}_ADDRESS;

// Define estrutura para pressoas do tipo _PERSON
typedef struct pessoa{
    unsigned short int id;
    char name[40];
    long int cpf_cnpj;
    unsigned int phoneNumber;
    _ADDRESS address;
}_PERSON;

// Função para adicionar nova pessoa no banco de dados
int addNewClient(_PERSON pessoa){
    int codigoErro;
    FILE *pessoas_db = fopen(databaseFile, "rb+"); // Abre arquivo no modo "rb+" (leitura e escrita em binário)

    // Verifica se o arquivo existe
    if(pessoas_db == NULL){ // Caso não exista, tentar criar abrin no modo "wb" (escrita em binário)
        pessoas_db = fopen(databaseFile, "wb");
        
        // Guarda os dados do ponteiro em arquivo binário.
        //   (ponteiro para variáve, tamanho, n items, arquivo)
        codigoErro = fwrite(&pessoa, sizeof(pessoa), 1, pessoas_db);
        fclose(pessoas_db);
    }else{ // Caso exista
        fseek(pessoas_db, 0, SEEK_END); // Move o cursor para o final do arquivo

        // Guarda os dados do ponteiro em arquivo binário.
        //   (ponteiro para variáve, tamanho, n items, arquivo)
        codigoErro = fwrite(&pessoa, sizeof(pessoa), 1, pessoas_db);
        fclose(pessoas_db);
    }
    if(codigoErro == 1){
        printf("Arquivo adicionado com sucesso\n");
    }else{
        printf("Cheguei no outro lugar com erro\n");
    } 
    return EXIT_SUCCESS;
}

void listClients(){
    printf("Listar clientes\n");
}

int main(){
   	setlocale(LC_ALL,"Portuguese");
    int codigoErro;
    _PERSON pessoa;
	char option;

    printf(
        "=============== Bem vindo! ================= \n"
        "C – Gerenciar Clientes \n"
        "T – Gerenciar Contas \n"
        "S – Sair \n"
        "Digite um comando para prosseguir: "
    );
    // Lê a opção digitada
    scanf(" %c", &option);

    // Escolhe para qual parte do programa ir
    switch(option){
        case 'C':
        case 'c':
            printf(
                "\033[H\033[2J\033[3J" // This scape sequence clean the screan
                "============ Gerenciar Clientes ============ \n"
                "C – Cadastrar um cliente \n"
                "L – Listar todos os clientes cadastrados \n"
                "B – Buscar cliente já cadastrado \n"
                "A – Atualizar um cliente cadastrado \n"
                "E – Excluir um cliente cadastrado \n"
                "S – Sair \n"
                "Digite um comando para prosseguir: "
            );
            // Lê a opção digitada
            scanf(" %c", &option);

            // Escolhe para qual parte do programa ir
            switch(option){
                case 'C':
                case 'c':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "C – Cadastrar um cliente \n\n"
                        "Digite os dados do cliente. \n"
                        "Nome: "
                    );
                    // scanf(" %s", pessoa.name);
                    printf("CPF/CNPJ: ");
                    // scanf("%d", &pessoa.cpf_cnpj);
                    printf("Telefone: ");
                    // scanf("%d", &pessoa.phoneNumber);
                    printf(
                        "Digite o endereço.\n"
                        "Estado: "
                    );
                    // scanf(" %s", pessoa.address.state);
                    printf("Cidade: ");
                    // scanf(" %s", pessoa.address.city);
                    printf("Bairro: ");
                    // scanf(" %s", pessoa.address.bairro);
                    printf("Rua: ");
                    // scanf(" %s", pessoa.address.street);
                    printf("Número: ");
                    // scanf("%d", &pessoa.address.number);
                    printf("CEP: ");
                    // scanf("%d", &pessoa.address.zipcode);

                    // Test
                    strcpy(pessoa.name, "Fulano");
                    pessoa.cpf_cnpj = 2345312345;
                    pessoa.phoneNumber = 63747364;
                    strcpy(pessoa.address.state, "DF");
                    strcpy(pessoa.address.city, "Brasília");
                    strcpy(pessoa.address.bairro, "AsaNorte");
                    strcpy(pessoa.address.street, "Longe");
                    pessoa.address.number = 333;
                    pessoa.address.zipcode = 445345345;
                    // Fim test

                    // Cadastrar o cliene "pessoa" e armazena possíveis erros em "codigoErro"
                    codigoErro = addNewClient(pessoa);

                    // Verifica se ocorreram erros
                    if(codigoErro == EXIT_SUCCESS){
                            //"\033[H\033[2J\033[3J"
                        printf(
                            "Cliente cadastrado com sucesso. \n"
                        );
                    }else{
                            //"\033[H\033[2J\033[3J"
                        printf(
                            "Ocorreu um erro ao cadastrar o cliente. \n"
                            "Tente novamente. \n"
                        );
                    }
                    break;
                case 'L':
                case 'l':
                    printf(
                        "L – Listar todos os clientes cadastrados \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    listClients();
                    break;
                case 'B':
                case 'b':
                    printf(
                        "B – Buscar cliente já cadastrado \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'A':
                case 'a':
                    printf(
                        "A – Atualizar um cliente cadastrado \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'E':
                case 'e':
                    printf(
                        "E – Excluir um cliente cadastrado \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Saindo... \n"
                    );
                    // Encerra o programa
                    return EXIT_SUCCESS;
                default:
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Comando não encontrado. Tente novamente. \n"
                    );
            }
            break;
        case 'T':
        case 't':
            printf(
                "\033[H\033[2J\033[3J"
                "============ Gerenciar Contas ============== \n"
                "R – Listagem de todas as contas cadastradas. \n"
                "C – Cadastrar uma conta para um cliente. \n"
                "L – Listar todas as contas de um cliente. \n"
                "W – Realizar um saque em uma conta. \n"
                "D – Realizar um depósito em uma conta. \n"
                "T – Realizar transferência entre contas. \n"
                "E – Exibir extrato de uma conta. \n"
                "S – Sair \n"
                "Digite um comando para prosseguir: "
            );
            // Lê a opção digitada
            scanf(" %c", &option);

            // Escolhe para qual parte do programa ir
            switch(option){
                case 'R':
                case 'r':
                    printf(
                        "R – Listagem de todas as contas cadastradas. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'C':
                case 'c':
                    printf(
                        "C – Cadastrar uma conta para um cliente. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'L':
                case 'l':
                    printf(
                        "L – Listar todas as contas de um cliente. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'W':
                case 'w':
                    printf(
                        "W – Realizar um saque em uma conta. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'D':
                case 'd':
                    printf(
                        "D – Realizar um depósito em uma conta. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'T':
                case 't':
                    printf(
                        "T – Realizar transferência entre contas. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'E':
                case 'e':
                    printf(
                        "E – Exibir extrato de uma conta. \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Saindo... \n"
                    );
                    // Encerra o programa
                    return EXIT_SUCCESS;
                default:
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Comando não encontrado. Tente novamente. \n"
                    );
            }
            break;
        case 'S':
        case 's':
            printf(
                "\033[H\033[2J\033[3J"
                "Saindo... \n"
            );
            // Encerra o programa
            return EXIT_SUCCESS;
        default:
            printf(
                "\033[H\033[2J\033[3J"
                "Comando não encontrado. Tente novamente. \n"
            );
            
    }
    main(); // Retorna ao menú principal
    return EXIT_SUCCESS;
}
