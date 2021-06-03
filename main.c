//Função: gerenciar transações financeira
//Data início: 11/05/2021
#include <stdio.h>
#include <locale.h> // Localização, caracteres
#include <string.h> // Necessário para manipular strings (strcpy)
#include <math.h> // Necessário para valores monetários (round)
#include "./lib/listaDeDados.h" // Biblioteca que gerencia os dados
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <stdlib.h>
#endif

// Limpa o aqruivo stdin
void clearStdinBuffer(){
    while(getchar() != '\n');
}
void clearScreen(){
    printf("\033[H\033[2J\033[3J"); // Limpa a tela
}

// Var declaration section
_PERSON_LIST *clientes; // Listas onde todos os clientes estão guardados
_PERSON pessoaTemporaria;
char nomeTemporario[MAX_ADRESS];
_ACCOUNT_LIST *contasBancaria; // Lista onde todas as contas estão guardadas
_ACCOUNT contaTemporaria;
unsigned int numeroAgencia;
unsigned int numeroAgenciaDestino;
unsigned int numeroConta;
unsigned int numeroContaDestino;
int accountIndex;
float valorMonetario;
char descricao[MAX_STATMENT_CHAR - 45];
unsigned long codigoParaConsultar;
unsigned int vezesExecutado = 0;
short int codigoErro;
char opcaoEscolhida;
int personIndex=0;

int main(){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
        setlocale(LC_ALL, NULL);
   	#else
        setlocale(LC_ALL,"Portuguese");
    #endif

    // Verifica quantas vezes a função main() foi executada
    if(vezesExecutado == 0){
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
            system("chcp 65001"); // Ativa UTF-8 encoding
            printf("\033[H\033[2J\033[3J");
        #endif
        // Cria/carrega na memória lista de pessoas com nome 'clientes'
        clientes = newPesonList();
        contasBancaria = newAccountList();
        printf("\n");
    }
    vezesExecutado++;

    printf(
        "\033[5;32m============== Menú principal ============== \033[0m\n"
        "C – Gerenciar Clientes \n"
        "T – Gerenciar Contas \n"
        "S – Sair \n"
        "Digite um comando para prosseguir: "
    );
    // Lê a opção digitada
    scanf(" %c", &opcaoEscolhida);

    // Escolhe para qual parte do programa ir
    switch(opcaoEscolhida){
        case 'C':
        case 'c':
            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela – This scape sequence clean the screan
                "\033[5;32m============ Gerenciar Clientes ============ \033[0m\n"
                "C – Cadastrar um cliente \n"
                "L – Listar todos os clientes cadastrados \n"
                "B – Buscar cliente cadastrado \n"
                "A – Atualizar um cliente cadastrado \n"
                "E – Excluir um cliente cadastrado \n"
                "V - Voltar ao menu anterior \n"
                "S – Sair \n"
                "Digite um comando para prosseguir: "
            );
            // Lê a opção digitada
            scanf(" %c", &opcaoEscolhida);

            // Escolhe para qual parte do programa ir
            switch(opcaoEscolhida){
                case 'C':
                case 'c':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "C – Cadastrar um cliente \n\n"
                        "Digite os dados do cliente. \n"
                    );
                    while(1){
                        printf("Id: ");
                        scanf("%hu", &pessoaTemporaria.id);
                        clearStdinBuffer();

                        // Verifica se o ID é um número válido
                        if(pessoaTemporaria.id <= 0 || pessoaTemporaria.id >= 65535){
                            printf("Id inválido.\n");
                        }else{
                            break; // Encerra o loop
                        }
                    }
                    printf("Nome: ");
                    scanf(" %[^\n]", pessoaTemporaria.name);
                    clearStdinBuffer();
                    while(1){
                        printf("CPF/CNPJ: ");
                        scanf("%lu", &pessoaTemporaria.cpf_cnpj);
                        clearStdinBuffer();

                        // Verifica se o CPF/CNPJ é válido
                        if(pessoaTemporaria.cpf_cnpj <= 65536 || pessoaTemporaria.cpf_cnpj > 99999999999999){
                            printf("CPF/CNPJ inválido. \n");
                        }else{
                            break; // Encerra o loop
                        }
                    }
                    printf("Telefone: ");
                    scanf("%u", &pessoaTemporaria.phoneNumber);
                    clearStdinBuffer();
                    printf(
                        "Digite o endereço.\n"
                        "Estado: "
                    );
                    scanf(" %[^\n]", pessoaTemporaria.address.state);
                    clearStdinBuffer();
                    printf("Cidade: ");
                    scanf(" %[^\n]", pessoaTemporaria.address.city);
                    clearStdinBuffer();
                    printf("Bairro: ");
                    scanf(" %[^\n]", pessoaTemporaria.address.bairro);
                    clearStdinBuffer();
                    printf("Rua: ");
                    scanf(" %[^\n]", pessoaTemporaria.address.street);
                    clearStdinBuffer();
                    printf("Número: ");
                    scanf("%hu", &pessoaTemporaria.address.number);
                    clearStdinBuffer();
                    printf("CEP: ");
                    scanf("%u", &pessoaTemporaria.address.zipcode);
                    clearStdinBuffer();

                    // Cadastra o cliene "pessoaTemporaria" e armazena possíveis erros em "codigoErro"
                    codigoErro = addPerson(clientes, pessoaTemporaria); // (lista, cliente)

                    // Verifica se ocorreram erros
                    if(codigoErro == 1){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente cadastrado com sucesso. \n"
                        );
                    }else if(codigoErro == -1){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente já cadastrado. \n"
                        );
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Ocorreu um erro ao cadastrar o cliente. \n"
                            "Tente novamente. \n"
                        );
                    }
                    break;
                case 'L':
                case 'l':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "L – Listar todos os clientes cadastrados \n\n"
                    );

                    // Verifica se existem clientes cadastados
                    if(isEmpityPersonList(clientes)){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Nenhum cliente cadastrado.\n"
                        );
                        break; // Sai de "case 'l'"
                    }

                    printf("Foram encontrados: %d cliente(s). \n", lengthPersonList(clientes));
                    // Lista todos os cliente cadastrados
                    for(personIndex = 0; personIndex < clientes->quantity; personIndex++){
                        printf(
                            "-----------------------------------\n"
                            "Id: %hu\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %lu\n",
                            //"Telefone: %u\n"
                            //"Estado: %s\n"
                            //"Cidade: %s\n"
                            //"Bairro: %s\n"
                            //"Rua: %s\n"
                            //"Número: %hu\n"
                            //"CEP: %u\n",
                            clientes->peopleData[personIndex].id,
                            clientes->peopleData[personIndex].name,
                            clientes->peopleData[personIndex].cpf_cnpj
                            //clientes->peopleData[personIndex].phoneNumber,
                            //clientes->peopleData[personIndex].address.state,
                            //clientes->peopleData[personIndex].address.city,
                            //clientes->peopleData[personIndex].address.bairro,
                            //clientes->peopleData[personIndex].address.street,
                            //clientes->peopleData[personIndex].address.number,
                            //clientes->peopleData[personIndex].address.zipcode
                        );
                    }

                    // Aguarda receber um caractere para continuar execução
                    printf("\nPressione 'q' para continuar...\n");
                    while((getchar() == '\n'));

                    clearScreen(); // Limpa a tela
                    break;
                case 'B':
                case 'b':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "B – Buscar cliente cadastrado \n\n"
                    );

                    // Verifica se existem contas bancárias cadastados
                    if(isEmpityPersonList(clientes)){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Nenhum cliente cadastrado.\n"
                        );
                        break; // Sai de "case 'b'"
                    }

                    printf(
                        "\033[1;31mProcurar por: \n"
                        "N → nome. \n"
                        "C → CPF/CNPJ ou Id. \033[0m\n"
                    );
                    while(1){
                        printf("\033[1;31m(N/C): \033[0m");
                        scanf(" %c", &opcaoEscolhida);
                        clearStdinBuffer();
                        if(
                            (opcaoEscolhida == 'N') ||
                            (opcaoEscolhida == 'n') ||
                            (opcaoEscolhida == 'C') ||
                            (opcaoEscolhida == 'c')
                        ){
                            break; // Encerra o loop
                        }
                    };

                    if ((opcaoEscolhida == 'N')|| (opcaoEscolhida == 'n')){
                        printf("Digite o nome: ");
                        scanf(" %[^\n]", nomeTemporario);
                        clearStdinBuffer();

                        // Obtém o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                        codigoErro = getPersonByName(clientes, nomeTemporario, &pessoaTemporaria); // (lista, nome do cliente, ponteiro para armazenar o cliente)
                    }else{
                        printf("Digite o Id ou CPF/CNPJ: ");
                        scanf("%lu", &codigoParaConsultar);

                        // Obtém o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                        codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)
                    } 

                    if(codigoErro == 1){
                        // Mostrando pessoa encontrada
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Pessoa encontrada: \n"
                            "-----------------------------------\n"
                            "Id: %hu\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %lu\n"
                            "Telefone: %u\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %hu\n"
                            "CEP: %u\n",
                            pessoaTemporaria.id,
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj,
                            pessoaTemporaria.phoneNumber,
                            pessoaTemporaria.address.state,
                            pessoaTemporaria.address.city,
                            pessoaTemporaria.address.bairro,
                            pessoaTemporaria.address.street,
                            pessoaTemporaria.address.number,
                            pessoaTemporaria.address.zipcode
                        );
                        // Aguarda receber um caractere para continuar execução
                        printf("\nPressione 'q' para continuar...\n");
                        while((getchar() == '\n'));
                        clearScreen(); // Limpa a tela
                    }
                    else if(codigoErro == -1){
                        // Mostrando nome com maior quantidade de caracteres em comúm
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Possível correpondência: \n"
                            "-----------------------------------\n"
                            "Id: %hu\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %lu\n"
                            "Telefone: %u\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %hu\n"
                            "CEP: %u\n",
                            pessoaTemporaria.id,
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj,
                            pessoaTemporaria.phoneNumber,
                            pessoaTemporaria.address.state,
                            pessoaTemporaria.address.city,
                            pessoaTemporaria.address.bairro,
                            pessoaTemporaria.address.street,
                            pessoaTemporaria.address.number,
                            pessoaTemporaria.address.zipcode
                        );
                        // Aguarda receber um caractere para continuar execução
                        printf("\nPressione 'q' para continuar...\n");
                        while((getchar() == '\n'));
                        clearScreen(); // Limpa a tela    
                    }
                    else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Não foi possível encontrar a pessoa. \n"
                        );
                    }
                    break;
                case 'A':
                case 'a':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "A – Atualizar um cliente cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Tenta obter o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)
                    
                    // Verifica se o cliente existe
                    if(codigoErro){
                        // Mostra o cliente
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente encontrado: \n"
                            "-----------------------------------\n"
                            "Id: %hu\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %lu\n"
                            "Telefone: %u\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %hu\n"
                            "CEP: %u\n",
                            pessoaTemporaria.id,
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj,
                            pessoaTemporaria.phoneNumber,
                            pessoaTemporaria.address.state,
                            pessoaTemporaria.address.city,
                            pessoaTemporaria.address.bairro,
                            pessoaTemporaria.address.street,
                            pessoaTemporaria.address.number,
                            pessoaTemporaria.address.zipcode
                        );
                        /* CPF/CNPJ e ID não podem ser alterados */
                        printf(
                            "-----------------------------------\n"
                            "Digite os novos dados do cliente.\n"
                        );
                        printf("Nome: ");
                        scanf(" %[^\n]", pessoaTemporaria.name);
                        clearStdinBuffer();
                        printf("Telefone: ");
                        scanf("%u", &pessoaTemporaria.phoneNumber);
                        clearStdinBuffer();
                        printf(
                            "Digite o endereço.\n"
                            "Estado: "
                        );
                        scanf(" %[^\n]", pessoaTemporaria.address.state);
                        clearStdinBuffer();
                        printf("Cidade: ");
                        scanf(" %[^\n]", pessoaTemporaria.address.city);
                        clearStdinBuffer();
                        printf("Bairro: ");
                        scanf(" %[^\n]", pessoaTemporaria.address.bairro);
                        clearStdinBuffer();
                        printf("Rua: ");
                        scanf(" %[^\n]", pessoaTemporaria.address.street);
                        clearStdinBuffer();
                        printf("Número: ");
                        scanf("%hu", &pessoaTemporaria.address.number);
                        clearStdinBuffer();
                        printf("CEP: ");
                        scanf("%u", &pessoaTemporaria.address.zipcode);
                        clearStdinBuffer();

                        // Atualiza dados do cliente e armazena possíveis erros em "codigoErro"
                        codigoErro = updatePerson(clientes, codigoParaConsultar, pessoaTemporaria); // (lista, codigo do cliente, cliente)

                        if(codigoErro){
                            printf(
                                "\033[H\033[2J\033[3J" // Limpa a tela
                                "Dados atualizados com sucesso.\n"
                            );
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J" // Limpa a tela
                                "Não foi possível atualizar os dados. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'E':
                case 'e':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "E – Excluir um cliente cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Tenta obter o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)

                    // Verifica se a cliente foi encontrado
                    if(codigoErro){
                        // Mostrando pessoa encontrada
                        printf(
                            "-----------------------------------\n"
                            "Id: %hu\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %lu\n"
                            "Telefone: %u\n"
                            "Estado: %s\n"
                            "Cidade: %s\n"
                            "Bairro: %s\n"
                            "Rua: %s\n"
                            "Número: %hu\n"
                            "CEP: %u\n",
                            pessoaTemporaria.id,
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj,
                            pessoaTemporaria.phoneNumber,
                            pessoaTemporaria.address.state,
                            pessoaTemporaria.address.city,
                            pessoaTemporaria.address.bairro,
                            pessoaTemporaria.address.street,
                            pessoaTemporaria.address.number,
                            pessoaTemporaria.address.zipcode
                        );
                        // Aguarda confirmação para continar
                        printf("\n\033[1;31mTem certeza que deseja excluir o cliente? (s/n)\033[0m ");
                        scanf(" %c", &opcaoEscolhida);

                        // Verifica a resposta
                        if(opcaoEscolhida == 's'){
                            // Excluí o cliente e armazena possíveis erros em "codigoErro"
                            codigoErro = removePerson(clientes, codigoParaConsultar);
                            // Remove todas as contas associadas a um CPF/CNPJ
                            removeAllAccountsOf(contasBancaria, pessoaTemporaria.cpf_cnpj);

                            // Verifica se ocorreu erro
                            if(codigoErro){
                                printf(
                                    "\033[H\033[2J\033[3J" // Limpa a tela
                                    "Cliente excuído com sucesso. \n"
                                );
                            }else{
                                printf(
                                    "\033[H\033[2J\033[3J" // Limpa a tela
                                    "Ocorreu um erro ao excuir o cliente. Cod.: %hd\n",
                                    codigoErro
                                );
                            }
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J" // Limpa a tela
                                "Cliente não foi excuído. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'V':
                case 'v':
                    // V - Voltar ao menu anterior
                    clearScreen(); // Limpa a tela
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    // S – Sair
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Saindo... \n"
                    );

                    codigoErro = 0;
                    // Libera da memória e salva em arquivo
                    codigoErro += closePersonList(clientes);
                    codigoErro += closeAccountList(contasBancaria);

                    // Verifica se ocorreu erro
                    if(codigoErro == 2){
                        printf("Dados salvos com sucesso. \n");
                    }else{
                        printf("Erro ao salvar os dados. Cod.: %d\n", codigoErro);
                    }
                    
                    // Encerra o programa
                    return EXIT_SUCCESS;
                default:
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Comando não encontrado. Tente novamente. \n"
                    );
            }
            break;
        case 'T':
        case 't':
            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela
                "\033[5;32m============= Gerenciar Contas ============= \033[0m\n"
                "C – Cadastrar uma conta para um cliente. \n"
                "R – Listagem de contas cadastradas. \n"
                "L – Listar contas de um cliente. \n"
                "W – Realizar um saque em uma conta. \n"
                "D – Realizar um depósito em uma conta. \n"
                "T – Realizar transferência entre contas. \n"
                "E – Exibir extrato de uma conta. \n"
                "V - Voltar ao menu anterior \n"
                "S – Sair \n"
                "Digite um comando para prosseguir: "
            );
            // Lê a opção digitada
            scanf(" %c", &opcaoEscolhida);

            // Escolhe para qual parte do programa ir
            switch(opcaoEscolhida){
                case 'C':
                case 'c':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "C – Cadastrar uma conta para um cliente. \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Obtém o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)

                    // Verifica se ocorreu erro ao procutar o cliente na lista
                    if(codigoErro){
                        // Lê os dados da conta
                        printf(
                            "Cliente: %s\n"
                            "CPF/CNPJ: %lu\n\n"
                            "Preencha o formulário. \n",
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj
                        );
                        while(1){
                            printf("Número da agência: ");
                            scanf("%u", &contaTemporaria.agencyNumber);
                            clearStdinBuffer();

                            // Verifica a agência é um número válido
                            if(contaTemporaria.agencyNumber < 0 || contaTemporaria.agencyNumber > 999){
                                printf("Agência inválida.\n");
                            }else{
                                break; // Encerra o loop
                            }
                        }
                        while(1){
                            printf("Número da conta: ");
                            scanf("%u", &contaTemporaria.accountNumber);
                            clearStdinBuffer();

                            // Verifica a conta é um número válido
                            if(contaTemporaria.accountNumber < 999 || contaTemporaria.accountNumber > 4294967295){
                                printf("Conta inválida.\n");
                            }else{
                                break; // Encerra o loop
                            }
                        }
                        // Preenchendo Id, CPF/CNPJ e saldo automaticamente
                        contaTemporaria.personId = pessoaTemporaria.id;
                        contaTemporaria.cpf_cnpj = pessoaTemporaria.cpf_cnpj;
                        contaTemporaria.balance = 0;

                        // Cadastra a conta lida
                        codigoErro = addAccount(contasBancaria, contaTemporaria);
                        if(codigoErro == 1){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Conta cadastrada com sucesso. \n"
                            );
                        }
                        else if(codigoErro == -1){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Conta já cadastrada. \n"
                            );
                        }
                        else{
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Não foi possível cadastrar esta conta. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'R':
                case 'r':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "R – Listagem de contas cadastradas. \n\n"
                    );

                    // Verifica se existem contas bancárias cadastados
                    if(isEmpityAccountList(contasBancaria)){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Nenhuma conta cadastrada.\n"
                        );
                        break; // Sai de "case 'r'"
                    }

                    printf("Foram encontradas: %d conta(s) bancária(s). \n", lengthAccountList(contasBancaria));
                    getAllAccounts(contasBancaria, clientes);

                    // Aguarda receber um caractere para continuar execução
                    printf("\nPressione 'q' para continuar...\n");
                    while((getchar() == '\n'));

                    clearScreen(); // Limpa a tela
                    break;
                case 'L':
                case 'l':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "L – Listar contas de um cliente. \n\n"
                        "Digite o código ou CPF/CNPJ: "
                    );
                    scanf(" %lu", &codigoParaConsultar);

                    // Obtém o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)

                    if(codigoErro == 1){
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Cliente: %s\n"
                            "CPF/CNPJ: %lu\n",
                            pessoaTemporaria.name,
                            pessoaTemporaria.cpf_cnpj
                        );

                        // Obtem quantas contas bancárias estão associadas a um CPF/CNPJ
                        int accountsQuantity = getAmountOfAccounts(contasBancaria, pessoaTemporaria.cpf_cnpj);

                        // Verifica quantas contas foram encontradas
                        if(accountsQuantity > 0){
                            // Mostra a lista de contas do cliente
                            getAllAccountsOf(contasBancaria, pessoaTemporaria.cpf_cnpj);
                            
                            // Aguarda receber um caractere para continuar execução
                            printf("\nPressione 'q' para continuar...\n");
                            while((getchar() == '\n'));
                            clearScreen(); // Limpa a tela
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J" // Limpa a tela
                                "Nenhuma conta encontrada. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente não encontrado. \n"
                        );
                    }
                    break;
                case 'W':
                case 'w':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "W – Realizar um saque em uma conta. \n\n"
                        "Agência: "
                    );
                    scanf( "%u", &numeroAgencia);
                    clearStdinBuffer();
                    printf("Conta: ");
                    scanf( "%u", &numeroConta);
                    clearStdinBuffer();

                    // Tenta encontrar a conta bancária
                    codigoErro = getAccount(contasBancaria, numeroAgencia, numeroConta, &contaTemporaria);

                    // Verifica ocorreu erro
                    if(codigoErro){
                        // Tenta obter dados do cliente enviando Id do cliente
                        getPerson(
                            clientes,
                            contaTemporaria.personId,
                            &pessoaTemporaria
                        );
                        // Dados do cliente
                        printf(
                            "\n"
                            "Cliente: %s\n"
                            "Agência: %u\n"
                            "Conta: %u\n"
                            "Saldo: R$%.2f\n\n"
                            "Valor do saque: ",
                            pessoaTemporaria.name,
                            contaTemporaria.agencyNumber,
                            contaTemporaria.accountNumber,
                            (contaTemporaria.balance / 100.0)
                        );
                        scanf(" %f", &valorMonetario);
                        clearStdinBuffer();

                        // Transforma o valor decimal em inteiro
                        int valorMonetarioInt = round(valorMonetario * 100);

                        // Distribuí o valor entre as notas disponíveis 2, 5, 10, 20, 50, 100 e 200 reais.
                        unsigned int notas200 = valorMonetarioInt / 20000;
                        valorMonetarioInt -= notas200 * 20000;
                        unsigned int notas100 = valorMonetarioInt / 10000;
                        valorMonetarioInt -= notas100 * 10000;
                        unsigned int notas50 = valorMonetarioInt / 5000;
                        valorMonetarioInt -= notas50 * 5000;
                        unsigned int notas20 = valorMonetarioInt / 2000;
                        valorMonetarioInt -= notas20 * 2000;
                        unsigned int notas10 = valorMonetarioInt / 1000;
                        valorMonetarioInt -= notas10 * 1000;
                        unsigned int notas5 = valorMonetarioInt / 500;
                        valorMonetarioInt -= notas5 * 500;
                        unsigned int notas2 = valorMonetarioInt / 200;
                        valorMonetarioInt -= notas2 * 200;
                        unsigned int resto = valorMonetarioInt;

                        // Calcula qual valor poderá ser sacado
                        valorMonetarioInt = (notas200 * 200) + (notas100 * 100) + (notas50 * 50) + (notas20 * 20) + (notas10 * 10) + (notas5 * 5) + (notas2 * 2);
                        
                        printf(
                            "Você pode sacar: R$%u\n"
                            "Dividido em: \n",
                            valorMonetarioInt
                        );
                        if(notas200 > 0) printf("%u notas de R$200 \n", notas200);
                        if(notas100 > 0) printf("%u notas de R$100 \n", notas100);
                        if(notas50 > 0) printf("%u notas de R$50 \n", notas50);
                        if(notas20 > 0) printf("%u notas de R$20 \n", notas20);
                        if(notas10 > 0) printf("%u notas de R$10 \n", notas10);
                        if(notas5 > 0) printf("%u notas de R$5 \n", notas5);
                        if(notas2 > 0) printf("%u notas de R$2 \n", notas2);
                        if(resto > 0) printf("R$%.2f não poderá ser sacado. \n", resto / 100.0);

                        // Pede confirmação
                        printf("\033[1;31mDeseja continuar? (s/n) \033[0m");
                        scanf("%c", &opcaoEscolhida);
                        if(opcaoEscolhida != 's' && opcaoEscolhida != 'S'){
                            clearScreen(); // Limpa a tela
                            break; // Termina o case 'w'
                        }

                        printf("Descrição: ");
                        scanf(" %[^\n]", descricao);
                        clearStdinBuffer();

                        // Tenta fazer o saque
                        codigoErro = bankDraft(contasBancaria, contaTemporaria.agencyNumber, contaTemporaria.accountNumber, descricao, valorMonetarioInt);

                        if(codigoErro == 1){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Saque realizado com sucesso. \n"
                            );
                        }else if(codigoErro == -1){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Saldo insuficiente. \n"
                            );
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Não foi possível realizar o saque. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Conta não encontrada. \n"
                        );
                    }
                    break;
                case 'D':
                case 'd':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "D – Realizar um depósito em uma conta. \n\n"
                        "Agência: "
                    );
                    scanf( "%u", &numeroAgencia);
                    clearStdinBuffer();
                    printf("Conta: ");
                    scanf( "%u", &numeroConta);
                    clearStdinBuffer();

                    // Tenta encontrar a conta bancária
                    codigoErro = getAccount(contasBancaria, numeroAgencia, numeroConta, &contaTemporaria);

                    // Verifica ocorreu erro
                    if(codigoErro){
                        // Tenta obter dados do cliente enviando Id do cliente
                        getPerson(
                            clientes,
                            contaTemporaria.personId,
                            &pessoaTemporaria
                        );
                        // Dados do cliente
                        printf(
                            "\n"
                            "Cliente: %s\n"
                            "Agência: %u\n"
                            "Conta: %u\n\n"
                            "Valor do depósito: ",
                            pessoaTemporaria.name,
                            contaTemporaria.agencyNumber,
                            contaTemporaria.accountNumber
                        );
                        scanf(" %f", &valorMonetario);
                        clearStdinBuffer();
                        printf("Descrição: ");
                        scanf(" %[^\n]", descricao);
                        clearStdinBuffer();

                        // Tenta fazer o depósito
                        codigoErro = bankDeposit(contasBancaria, contaTemporaria.agencyNumber, contaTemporaria.accountNumber, descricao, valorMonetario);
                        if(codigoErro){
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Depósito realizado com sucesso. \n"
                            );
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J"
                                "Não foi possível realizar o deposito. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Conta não encontrada. \n"
                        );
                    }
                    break;
                case 'T':
                case 't':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "T – Realizar transferência entre contas. \n\n"
                        "Agência de origem: "
                    );
                    scanf( "%u", &numeroAgencia);
                    clearStdinBuffer();
                    printf("Conta de origem: ");
                    scanf( "%u", &numeroConta);
                    clearStdinBuffer();

                    // Tenta encontrar a conta bancária
                    codigoErro = getAccount(contasBancaria, numeroAgencia, numeroConta, &contaTemporaria);

                    // Verifica ocorreu erro
                    if(codigoErro){
                        // Tenta obter dados do cliente de destino enviando Id do cliente
                        getPerson(
                            clientes,
                            contaTemporaria.personId,
                            &pessoaTemporaria
                        );
                        // Dados do cliente de origem
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente: %s\n"
                            "Agência: %u\n"
                            "Conta: %u\n"
                            "Saldo: R$%.2f\n\n",
                            pessoaTemporaria.name,
                            contaTemporaria.agencyNumber,
                            contaTemporaria.accountNumber,
                            (contaTemporaria.balance / 100.0)
                        );

                        // Lê os dados do cliente destino
                        printf("Agência de destino: ");
                        scanf( "%u", &numeroAgenciaDestino);
                        clearStdinBuffer();
                        printf("Conta de destino: ");
                        scanf( "%u", &numeroContaDestino);
                        clearStdinBuffer();

                        // Tenta encontrar a conta bancária
                        codigoErro = getAccount(contasBancaria, numeroAgenciaDestino, numeroContaDestino, &contaTemporaria);

                        // Verifica ocorreu erro
                        if(codigoErro){
                            // Tenta obter dados do cliente de destino enviando Id do cliente
                            getPerson(
                                clientes,
                                contaTemporaria.personId,
                                &pessoaTemporaria
                            );
                            // Dados do cliente de destino
                            printf(
                                "Cliente: %s\n"
                                "Agência: %u\n"
                                "Conta: %u\n\n",
                                pessoaTemporaria.name,
                                contaTemporaria.agencyNumber,
                                contaTemporaria.accountNumber
                            );

                            // Lendo o valor da transferência
                            printf("Valor da transferência: ");
                            scanf( "%f", &valorMonetario);

                            // Tenta realizar a transferência bancária
                            codigoErro = bankTransfer(
                                contasBancaria,
                                numeroAgencia,
                                numeroConta,
                                numeroAgenciaDestino,
                                numeroContaDestino,
                                valorMonetario
                            );

                            // Verifica se ocorreu erro
                            if(codigoErro == 1){
                                printf(
                                    "\033[H\033[2J\033[3J" // Limpa a tela
                                    "Transferência realizada com sucesso. \n"
                                );
                            }else if(codigoErro == -1){
                                printf(
                                    "\033[H\033[2J\033[3J" // Limpa a tela
                                    "Saldo insuficiente. \n"
                                );
                            }else{
                                printf(
                                    "\033[H\033[2J\033[3J" // Limpa a tela
                                    "Erro ao realizar transferência. \n"
                                );
                            }
                        }else{
                            printf(
                                "\033[H\033[2J\033[3J" // Limpa a tela
                                "Conta não encontrada. \n"
                            );
                        }
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Conta não encontrada. \n"
                        );
                    }
                    break;
                case 'E':
                case 'e':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "E – Exibir extrato de uma conta. \n\n"
                        "Agência: "
                    );
                    scanf( "%u", &numeroAgencia);
                    clearStdinBuffer();
                    printf("Conta: ");
                    scanf( "%u", &numeroConta);
                    clearStdinBuffer();

                    // Tenta encontrar a conta bancária
                    codigoErro = getAccount(contasBancaria, numeroAgencia, numeroConta, &contaTemporaria);

                    // Verifica ocorreu erro
                    if(codigoErro){
                        // Tenta obter dados do cliente enviando Id do cliente
                        getPerson(
                            clientes,
                            contaTemporaria.personId,
                            &pessoaTemporaria
                        );
                        // Dados do cliente
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Cliente: %s\n"
                            "Agência: %u\n"
                            "Conta: %u\n"
                            "Saldo: R$%.2f\n"
                            "--------------------------------\n",
                            pessoaTemporaria.name,
                            contaTemporaria.agencyNumber,
                            contaTemporaria.accountNumber,
                            (contaTemporaria.balance / 100.0)
                        );

                        printf("Extrato de quantos dias? ");
                        scanf("%lu", &codigoParaConsultar);

                        // Mostra o extrato bancário
                        bankStatment(contasBancaria, contaTemporaria.agencyNumber, contaTemporaria.accountNumber, codigoParaConsultar);

                        // Aguarda receber um caractere para continuar execução
                        printf("\nPressione 'q' para continuar...\n");
                        while((getchar() == '\n'));
                        clearScreen(); // Limpa a tela
                    }else{
                        printf(
                            "\033[H\033[2J\033[3J"
                            "Conta não encontrada. \n"
                        );
                    }
                    break;
                case 'V':
                case 'v':
                    // V - Voltar ao menu anterior
                    clearScreen(); // Limpa a tela
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    // S – Sair
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Saindo... \n"
                    );

                    codigoErro = 0;
                    // Libera da memória e salva em arquivo
                    codigoErro += closePersonList(clientes);
                    codigoErro += closeAccountList(contasBancaria);

                    // Verifica se ocorreu erro
                    if(codigoErro == 2){
                        printf("Dados salvos com sucesso. \n");
                    }else{
                        printf("Erro ao salvar os dados. Cod.: %d\n", codigoErro);
                    }                   

                    // Encerra o programa
                    return EXIT_SUCCESS;
                default:
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Comando não encontrado. Tente novamente. \n"
                    );
            }
            break;
        case 'S':
        case 's':
            // S – Sair
            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela
                "Saindo... \n"
            );
            
            codigoErro = 0;
            // Libera da memória e salva em arquivo
            codigoErro += closePersonList(clientes);
            codigoErro += closeAccountList(contasBancaria);

            // Verifica se ocorreu erro
            if(codigoErro == 2){
                printf("Dados salvos com sucesso. \n");
            }else{
                printf("Erro ao salvar os dados. Cod.: %d\n", codigoErro);
            }
            
            // Encerra o programa
            return EXIT_SUCCESS;
        default:
            // Menú secreto
            if(vezesExecutado == 3 && opcaoEscolhida == '~'){
                printf(
                    "\033[5;31m============== Menú secreto ============== \n"
                    "Opção: "
                );
                scanf(" %c", &opcaoEscolhida);
                switch (opcaoEscolhida){
                    case '1':
                        printf(
                            "removeAllAccountsOf()\n"
                            "CPF/CNPJ: "
                        );
                        scanf("%lu", &pessoaTemporaria.cpf_cnpj);
                        removeAllAccountsOf(contasBancaria, pessoaTemporaria.cpf_cnpj);
                    case '2':
                        printf(
                            "removeAccount()\n"
                            "Agência: "
                        );
                        scanf( "%u", &numeroAgencia);
                        printf("Conta: ");
                        scanf( "%u", &numeroConta);
                        removeAccount(contasBancaria, numeroAgencia, numeroConta);
                    case '3':
                        printf(
                            "bankDraft()\n"
                            "Agência: "
                        );
                        scanf( "%u", &numeroAgencia);
                        printf("Conta: ");
                        scanf( "%u", &numeroConta);
                        printf("Valor: ");
                        scanf( "%f", &valorMonetario);
                        bankDraft(contasBancaria, numeroAgencia, numeroConta, "master", valorMonetario);
                }
                printf("\033[0m");
                clearScreen(); // Limpa a tela
                break;
            }

            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela
                "Comando não encontrado. Tente novamente. \n"
            );
    }
    main(); // Retorna ao menú principal
    return EXIT_SUCCESS;
}
