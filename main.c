//Função: gerenciar transações financeira
//Data início: 11/05/2021
#include <stdio.h>
#include <locale.h> // Localização, caracteres
#include <string.h> // Trabalhar com strings
#include "./lib/listaDeDados.h"
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

/*
#define databaseFile "database.data"
// Função para adicionar nova pessoa no banco de dados
int addNewClient(_PERSON pessoa){
    short int quantidadeClientesCadastrados;
    short int codigoErro=0;
    FILE *pessoas_db = fopen(databaseFile, "rb+"); // Abre arquivo no modo leitura e escrita em binário

    // Verifica se o arquivo existe
    if(pessoas_db == NULL){// Caso não exista
        // Abrir arquivo no modo escrita em binário
        pessoas_db = fopen(databaseFile, "wb");
        
        // Adiciona identificador a peossoa
        pessoa.id = 0;
        quantidadeClientesCadastrados = 1;

        // Guarda os dados da pessoa e quantidade em arquivo binário.
        //   (ponteiro para variáve, tamanho, n items, arquivo)
        codigoErro += fwrite(&quantidadeClientesCadastrados, sizeof(quantidadeClientesCadastrados), 1, pessoas_db);
        codigoErro += fwrite(&pessoa, sizeof(pessoa), 1, pessoas_db);
        fclose(pessoas_db);
    }else{// Caso exista
        // Lê quantos clientes estão cadastrados, incrementa a quatidade de clientes
        fread(&quantidadeClientesCadastrados, sizeof(quantidadeClientesCadastrados), 1, pessoas_db);
        printf("Foram encontrados %d clientes.\n", quantidadeClientesCadastrados);
        quantidadeClientesCadastrados += 1;

        // Guarda os dados do ponteiro em arquivo binário.
        //   (ponteiro para variáve, tamanho, n items, arquivo)
        codigoErro += fwrite(&quantidadeClientesCadastrados, sizeof(quantidadeClientesCadastrados), 1, pessoas_db);
        codigoErro += fwrite(&pessoa, sizeof(pessoa), 1, pessoas_db);
        fclose(pessoas_db);
    }
    if(codigoErro == 2){
        printf("Arquivo adicionado com sucesso\n");
    }else{
        printf("Cheguei no outro lugar com erro\n");
    } 
    return EXIT_SUCCESS;
}

void listClients(){
    _PERSON pessoa[3];
    FILE *pessoas_db = fopen(databaseFile, "rb"); // Abre arquivo no modo leitura de bináiro
    short int quantidadeClientesCadastrados=0;
    short int codigoErro=0;

    // Ler arquivo binário e carregar na memório
    // (onde guardar, tamanho, vezes, arquivo de origem)
    codigoErro += fread(&quantidadeClientesCadastrados, sizeof(quantidadeClientesCadastrados), 1, pessoas_db);
    printf("Quantidade de pessoas encontradas: %d\n", quantidadeClientesCadastrados);
    codigoErro += fread(&pessoa, sizeof(pessoa), 3, pessoas_db);
    fclose(pessoas_db);
    

    printf("Listaando clientes encontrados...\n");
    if(codigoErro > 0){
        printf("Leitura realizada com sucesso\n");
        for (int i = 0; i < 3; i++){
            printf(
                "Informações encontradas pessoa[%d].\n"
                "Id: %d\n"
                "Nome: %s\n"
                "CPF/CNPJ: %ld\n"
                "Telefone: %d\n"
                "Estado: %s\n"
                "Cidade: %s\n"
                "Bairro: %s\n"
                "Rua: %s\n"
                "Número: %d\n"
                "CEP: %d\n",
                i,
                pessoa[i].id,
                pessoa[i].name,
                pessoa[i].cpf_cnpj,
                pessoa[i].phoneNumber,
                pessoa[i].address.state,
                pessoa[i].address.city,
                pessoa[i].address.bairro,
                pessoa[i].address.street,
                pessoa[i].address.number,
                pessoa[i].address.zipcode
            );
        }
    }else{
        printf("Erro de leitura\n"); // Exibe erro
    }
}
*/

_PERSON_LIST *clientes;
_PERSON pessoa;
unsigned long codigoParaConsultar;
int execTimes = 0;
short int codigoErro;
char option;
int i;

int main(){
   	setlocale(LC_ALL,"Portuguese");

    // Cria a lista de clientes somente 1 vez
    if(execTimes == 0){
        // Cria lista de pessoas com nome 'clientes'
        clientes = newPesonList();
        execTimes++;
    }

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
                "V - Voltar ao menu anterior \n"
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
                        "Id: "
                    );
                    // scanf("%hd", pessoa.id);
                    printf("Nome: ");
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

                    // Entradas para teste.
                    // Foram suprimidos os scanf para teste
                    pessoa.id = 336;
                    strcpy(pessoa.name, "Fulano");
                    pessoa.cpf_cnpj = 1345312345;
                    pessoa.phoneNumber = 63747364;
                    strcpy(pessoa.address.state, "DF");
                    strcpy(pessoa.address.city, "Brasília");
                    strcpy(pessoa.address.bairro, "AsaNorte");
                    strcpy(pessoa.address.street, "Longe");
                    pessoa.address.number = 333;
                    pessoa.address.zipcode = 445345345;
                    // Fim teste

                    // Cadastrar o cliene "pessoa" e armazena possíveis erros em "codigoErro"
                    // codigoErro = addNewClient(pessoa);
                    codigoErro = addPerson(clientes, pessoa);

                    // Verifica se ocorreram erros
                    if(codigoErro == 1){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente cadastrado com sucesso. \n"
                        );
                    }else if(codigoErro == -1){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente já cadastrado. \n"
                        );
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Ocorreu um erro ao cadastrar o cliente. \n"
                            "Tente novamente. \n"
                        );
                    }
                    break;
                case 'L':
                case 'l':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "L – Listar todos os clientes cadastrados \n\n"
                        "Foram encontrados: %d cliente(s). \n",
                        clientes->quantity
                    );
                    
                    // Verifica se existem clientes cadastados
                    if(isEmpityPersonList(clientes)){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Nenhum cliente cadastrado.\n"
                        );
                        break; // Sai do case
                    }

                    // Lista todos os cliente cadastrados
                    for(i = 0; i < clientes->quantity; i++){
                        printf(
                            "-----------------------------------\n"
                            "Id: %d\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %ld\n"
                            "Telefone: %d\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %d\n"
                            "CEP: %d\n",
                            clientes->dados[i].id,
                            clientes->dados[i].name,
                            clientes->dados[i].cpf_cnpj,
                            clientes->dados[i].phoneNumber,
                            clientes->dados[i].address.state,
                            clientes->dados[i].address.city,
                            clientes->dados[i].address.bairro,
                            clientes->dados[i].address.street,
                            clientes->dados[i].address.number,
                            clientes->dados[i].address.zipcode
                        );
                    }

                    // Aguarda apertar enter para continar
                    printf("\nPressione 'q' para continuar...\n");
                    while((getchar() == '\n'));

                    printf("\033[H\033[2J\033[3J");
                    break;
                case 'B':
                case 'b':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "B – Buscar cliente já cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Obtém a pessoa consultada e armazena no buffer pessoa
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoa);

                    if(codigoErro){
                        // Mostrando pessoa encontrada
                        printf(
                            "-----------------------------------\n"
                            "Id: %d\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %ld\n"
                            "Telefone: %d\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %d\n"
                            "CEP: %d\n",
                            pessoa.id,
                            pessoa.name,
                            pessoa.cpf_cnpj,
                            pessoa.phoneNumber,
                            pessoa.address.state,
                            pessoa.address.city,
                            pessoa.address.bairro,
                            pessoa.address.street,
                            pessoa.address.number,
                            pessoa.address.zipcode
                        );
                        // Aguarda apertar enter para continar
                        printf("\nPressione 'q' para continuar...\n");
                        while((getchar() == '\n'));
                        printf("\033[H\033[2J\033[3J");
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Não foi possível encontrar a pessoa. \n"
                        );
                    }
                    break;
                case 'A':
                case 'a':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "A – Atualizar um cliente cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Obtem o Index do cliente
                    i = getPersonIndex(clientes, codigoParaConsultar);
                    
                    // Verifica se o cliente existe
                    if(i >= 0){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente encontrado: \n"
                            "-----------------------------------\n"
                            "Id: %d\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %ld\n"
                            "Telefone: %d\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %d\n"
                            "CEP: %d\n"
                            "-----------------------------------\n",
                            clientes->dados[i].id,
                            clientes->dados[i].name,
                            clientes->dados[i].cpf_cnpj,
                            clientes->dados[i].phoneNumber,
                            clientes->dados[i].address.state,
                            clientes->dados[i].address.city,
                            clientes->dados[i].address.bairro,
                            clientes->dados[i].address.street,
                            clientes->dados[i].address.number,
                            clientes->dados[i].address.zipcode
                        );
                        printf(
                            "Digite os novos dados do cliente.\n"
                            "Nome: "
                        );
                        // Limpa buffer stdin
                        while(getchar() != '\n');
                        fgets(pessoa.name, MAX_NAME, stdin);
                        // Limpa buffer stdin
                        while(getchar() != '\n');
                        printf("CPF/CNPJ: ");
                        scanf("%ld", &pessoa.cpf_cnpj);
                        printf("Telefone: ");
                        scanf("%d", &pessoa.phoneNumber);
                        printf(
                            "Digite o endereço.\n"
                            "Estado: "
                        );
                        scanf(" %s", pessoa.address.state);
                        printf("Cidade: ");
                        scanf(" %s", pessoa.address.city);
                        printf("Bairro: ");
                        scanf(" %s", pessoa.address.bairro);
                        printf("Rua: ");
                        scanf(" %s", pessoa.address.street);
                        printf("Número: ");
                        scanf("%hu", &pessoa.address.number);
                        printf("CEP: ");
                        scanf("%d", &pessoa.address.zipcode);

                        // Atualiza dados do cliente
                        codigoErro = updatePerson(clientes, i, pessoa); // (lista, index, cliente)

                        if(codigoErro){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Dados atualizados com sucesso.\n"
                            );
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Não foi possível atualizar os dados. \n"
                            );
                        }
                    }else if(i == -1){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Não foi possível procurar o cliente. \n"
                            "Isso pode ser ocasionado por erro no banco de bacos. \n"
                            "Código erro: %d\n",
                            i
                        );
                    }else if(i == -2){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'E':
                case 'e':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "E – Excluir um cliente cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Tenta obter o cliente
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoa);

                    // Verifica se a cliente foi encontrado
                    if(codigoErro){
                        // Mostrando pessoa encontrada
                        printf(
                            "-----------------------------------\n"
                            "Id: %d\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %ld\n"
                            "Telefone: %d\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %d\n"
                            "CEP: %d\n",
                            pessoa.id,
                            pessoa.name,
                            pessoa.cpf_cnpj,
                            pessoa.phoneNumber,
                            pessoa.address.state,
                            pessoa.address.city,
                            pessoa.address.bairro,
                            pessoa.address.street,
                            pessoa.address.number,
                            pessoa.address.zipcode
                        );
                        // Aguarda confirmação para continar
                        printf("\nTem certeza que deseja exluir o cliente? (s/n)\n");
                        scanf(" %c", &option);
                        
                        // Verifica a resposta
                        if(option == 's'){
                            // Excluí o cliente
                            codigoErro = removePerson(clientes, codigoParaConsultar);
                        
                            // Verifi se ocorreu erro
                            if(codigoErro){
                                printf(
                                    "\033[H\033[2J\033[3J"
                                    "Cliente excuído com sucesso. \n"
                                );
                            }else{
                                printf(
                                    "\033[H\033[2J\033[3J"
                                    "Ocorreu um erro ao excuir o cliente. Cod.: %hd\n",
                                    codigoErro
                                );
                            }
                        }else{
                            printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente não foi excuído. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'V':
                case 'v':
                    printf("\033[H\033[2J\033[3J");
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Saindo... \n"
                    );

                    // Libera da memória e salva em arquivo
                    closePersonList(clientes);

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
                "V - Voltar ao menu anterior \n"
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
                case 'V':
                case 'v':
                    printf("\033[H\033[2J\033[3J");
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J"
                        "Saindo... \n"
                    );

                    // Libera da memória e salva em arquivo
                    closePersonList(clientes);

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
            
            // Libera da memória e salva em arquivo
            closePersonList(clientes);

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
