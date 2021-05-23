//Função: gerenciar transações financeira
//Data início: 11/05/2021
#include <stdio.h>
#include <locale.h> // Localização, caracteres
#include <string.h> // Necessário para manipular strings (strcpy)
#include "./lib/listaDeDados.h" // Biblioteca que gerencia os dados
#define EXIT_SUCCESS 0
#define EXIT_ERROR -1

// Var declaration section
_PERSON_LIST *clientes;
_PERSON pessoaTemporaria;
unsigned long codigoParaConsultar;
unsigned int vezesExecutado = 0;
short int codigoErro;
char opcaoEscolhida;
int personIndex=0;

int main(){
   	setlocale(LC_ALL,"Portuguese");

    // Verifica quantas vezes a função main() foi executada
    if(vezesExecutado == 0){
        // Cria/carrega na memória lista de pessoas com nome 'clientes'
        clientes = newPesonList();
    }
    vezesExecutado++;

    printf(
        "============== Menú principal ============== \n"
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
                "============ Gerenciar Clientes ============ \n"
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
                        "Id: "
                    );
                    scanf("%hd", &pessoaTemporaria.id);
                    printf("Nome: ");
                    scanf(" %s", pessoaTemporaria.name);
                    printf("CPF/CNPJ: ");
                    scanf("%lu", &pessoaTemporaria.cpf_cnpj);
                    printf("Telefone: ");
                    // scanf("%d", &pessoaTemporaria.phoneNumber);
                    printf(
                        "Digite o endereço.\n"
                        "Estado: "
                    );
                    // scanf(" %s", pessoaTemporaria.address.state);
                    printf("Cidade: ");
                    // scanf(" %s", pessoaTemporaria.address.city);
                    printf("Bairro: ");
                    // scanf(" %s", pessoaTemporaria.address.bairro);
                    printf("Rua: ");
                    // scanf(" %s", pessoaTemporaria.address.street);
                    printf("Número: ");
                    // scanf("%hd", &pessoaTemporaria.address.number);
                    printf("CEP: ");
                    // scanf("%d", &pessoaTemporaria.address.zipcode);

                    // Entradas para teste.
                    // Foram suprimidos os scanf para teste
                    //pessoaTemporaria.id = 336;
                    //strcpy(pessoaTemporaria.name, "Fulano");
                    //pessoaTemporaria.cpf_cnpj = 1345312345;
                    pessoaTemporaria.phoneNumber = 63747364;
                    strcpy(pessoaTemporaria.address.state, "DF");
                    strcpy(pessoaTemporaria.address.city, "Brasília");
                    strcpy(pessoaTemporaria.address.bairro, "Asa Norte");
                    strcpy(pessoaTemporaria.address.street, "Longe");
                    pessoaTemporaria.address.number = 333;
                    pessoaTemporaria.address.zipcode = 445345345;
                    // Fim teste

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
                        "Foram encontrados: %d cliente(s). \n",
                        clientes->quantity
                    );

                    // Verifica se existem clientes cadastados
                    if(isEmpityPersonList(clientes)){
                        printf(
                            "\033[H\033[2J\033[3J" // Limpa a tela
                            "Nenhum cliente cadastrado.\n"
                        );
                        break; // Sai de "case 'l'"
                    }

                    // Lista todos os cliente cadastrados
                    for(personIndex = 0; personIndex < clientes->quantity; personIndex++){
                        printf(
                            "-----------------------------------\n"
                            "Id: %d\n"
                            "Nome: %s\n"
                            "CPF/CNPJ: %ld\n",
                            //"Telefone: %d\n"
                            //"Estado: %s\n"
                            //"Cidade: %s\n"
                            //"Bairro: %s\n"
                            //"Rua: %s\n"
                            //"Número: %d\n"
                            //"CEP: %d\n",
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
                    //while((getchar() == '\n'));

                    printf("\033[H\033[2J\033[3J"); // Limpa a tela
                    break;
                case 'B':
                case 'b':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "B – Buscar cliente cadastrado \n\n"
                        "Digite o Id ou CPF/CNPJ: "
                    );
                    scanf("%lu", &codigoParaConsultar);

                    // Obtém o cliente e armazena em pessoaTemporaria. Armazena possíveis erros em "codigoErro"
                    codigoErro = getPerson(clientes, codigoParaConsultar, &pessoaTemporaria); // (lista, código do cliente, ponteiro para armazenar o cliente)

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
                        printf("\033[H\033[2J\033[3J"); // Limpa a tela
                    }else{
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
                            "Nome: "
                        );
                        // Limpa buffer stdin
                        while(getchar() != '\n');
                        fgets(pessoaTemporaria.name, MAX_NAME, stdin);
                        // Limpa buffer stdin
                        while(getchar() != '\n');
                        printf("Telefone: ");
                        scanf("%d", &pessoaTemporaria.phoneNumber);
                        printf(
                            "Digite o endereço.\n"
                            "Estado: "
                        );
                        scanf(" %s", pessoaTemporaria.address.state);
                        printf("Cidade: ");
                        scanf(" %s", pessoaTemporaria.address.city);
                        printf("Bairro: ");
                        scanf(" %s", pessoaTemporaria.address.bairro);
                        printf("Rua: ");
                        scanf(" %s", pessoaTemporaria.address.street);
                        printf("Número: ");
                        scanf("%hu", &pessoaTemporaria.address.number);
                        printf("CEP: ");
                        scanf("%d", &pessoaTemporaria.address.zipcode);

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
                        printf("\nTem certeza que deseja exluir o cliente? (s/n)\n");
                        scanf(" %c", &opcaoEscolhida);
                        
                        // Verifica a resposta
                        if(opcaoEscolhida == 's'){
                            // Excluí o cliente e armazena possíveis erros em "codigoErro"
                            codigoErro = removePerson(clientes, codigoParaConsultar);
                        
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
                    printf("\033[H\033[2J\033[3J"); // Limpa a tela
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Saindo... \n"
                    );

                    // Libera da memória e salva em arquivo
                    codigoErro = closePersonList(clientes);

                    // Verifica se ocorreu erro
                    if(codigoErro == 1){
                        printf("Clientes salvos com sucesso. \n");
                    }else{
                        printf("Erro ao salvar os clientes. Cod.: %d\n", codigoErro);
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
                "============= Gerenciar Contas ============= \n"
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
            scanf(" %c", &opcaoEscolhida);

            // Escolhe para qual parte do programa ir
            switch(opcaoEscolhida){
                case 'R':
                case 'r':
                    printf(
                        "R – Listagem de todas as contas cadastradas. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'C':
                case 'c':
                    printf(
                        "C – Cadastrar uma conta para um cliente. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'L':
                case 'l':
                    printf(
                        "L – Listar todas as contas de um cliente. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'W':
                case 'w':
                    printf(
                        "W – Realizar um saque em uma conta. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'D':
                case 'd':
                    printf(
                        "D – Realizar um depósito em uma conta. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'T':
                case 't':
                    printf(
                        "T – Realizar transferência entre contas. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'E':
                case 'e':
                    printf(
                        "E – Exibir extrato de uma conta. \n"
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Em implementação... \n"
                    );
                    break;
                case 'V':
                case 'v':
                    printf("\033[H\033[2J\033[3J"); // Limpa a tela
                    main(); // Volta ao menú anterior
                    return EXIT_SUCCESS; // Previne falhas ao navegar pelos menus
                    break;
                case 'S':
                case 's':
                    printf(
                        "\033[H\033[2J\033[3J" // Limpa a tela
                        "Saindo... \n"
                    );

                    // Libera da memória e salva em arquivo
                    codigoErro = closePersonList(clientes);

                    // Verifica se ocorreu erro
                    if(codigoErro == 1){
                        printf("Clientes salvos com sucesso. \n");
                    }else{
                        printf("Erro ao salvar os clientes. Cod.: %d\n", codigoErro);
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
            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela
                "Saindo... \n"
            );
            
            // Libera da memória e salva em arquivo
            codigoErro = closePersonList(clientes);

            // Verifica se ocorreu erro
            if(codigoErro == 1){
                printf("Clientes salvos com sucesso. \n");
            }else{
                printf("Erro ao salvar os clientes. Cod.: %d\n", codigoErro);
            }
            
            // Encerra o programa
            return EXIT_SUCCESS;
        default:
            printf(
                "\033[H\033[2J\033[3J" // Limpa a tela
                "Comando não encontrado. Tente novamente. \n"
            );
    }
    main(); // Retorna ao menú principal
    return EXIT_SUCCESS;
}
