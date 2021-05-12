//Função: gerenciar transações financeira
//Data: 11/05/2021
#include <stdio.h>
#include <locale.h>
#define EXIT_SUCCESS 0

int main(){
   	setlocale(LC_ALL,"Portuguese");
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
                        "C – Cadastrar um cliente \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
                    break;
                case 'L':
                case 'l':
                    printf(
                        "L – Listar todos os clientes cadastrados \n"
                        "\033[H\033[2J\033[3J"
                        "Em implementação... \n"
                    );
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
