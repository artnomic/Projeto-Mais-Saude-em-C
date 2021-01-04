#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

int calculaIdade(const char* nascimento){

    int ano, mes, anoAtu, mesAtu, anoDiff, mesDiff;

    char data[] = "01/01/2016";
    char hora[] = " - 00:00:00";
    char *datahora=(char*)malloc(1*sizeof(char));

    strcpy(data, nascimento);
    datahora = strcat(data, hora);

    //ponteiro para struct que armazena data e hora
    struct tm tm;
    struct tm *data_hora_atual;

    sscanf( datahora, "%d/%d/%d - %d:%d:%d", &tm.tm_mday, &mes, &ano, &tm.tm_hour, &tm.tm_min, &tm.tm_sec );

    //variável do tipo time_t para armazenar o tempo em segundos
    time_t segundos;
    //obtendo o tempo em segundos
    time(&segundos);
    //para converter de segundos para o tempo local
    data_hora_atual = localtime(&segundos);

    anoAtu = data_hora_atual->tm_year+1900;
    mesAtu = data_hora_atual->tm_mon+1;

    mesDiff = mesAtu - mes;
    anoDiff = anoAtu - ano;

    if(mesDiff < 0){
        anoDiff = anoDiff - 1;
    }

    printf("Idade: %i\n", anoDiff);

    return anoDiff;

}

int gravarArquivo(const char* nomeArquivo, const char* linha){
    char *Str=(char*)malloc(1*sizeof(char));
    int result;
    FILE *arq = fopen(nomeArquivo, "a");  // Cria um arquivo texto para gravação
    if (arq == NULL){
        return 0;
    }

    /* grava a linha */
    result = fputs(linha, arq);

    /* grava a linha */
    strcpy(Str,"\n");
    result = fputs(Str, arq);

    if (result == EOF)
        return 0;
    fclose(arq);
    return 1;
}

char* replaceWord(const char* s, const char* oldW, const char* newW)
{
    char* result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++) {
        if (strstr(&s[i], oldW) == &s[i]) {
            cnt++;

            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char*)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s) {
        // compare the substring with the result
        if (strstr(s, oldW) == s) {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

void limpabuffer(void) // Funçao utilitária para limpar o buffer do teclado
{
    int c;
    while ( (c = getchar()) != '\n' && c != EOF ) { }
}

void clear(void)
{
  while ( getchar() != '\n' );
}

int main()
{
    int userTentativas;
    char userInput[30];
    char passInput[30];

    char *menuAtendimento=(char*)malloc(1*sizeof(char));
    char *nomePaciente=(char*)malloc(1*sizeof(char));
    char *cpfPaciente=(char*)malloc(1*sizeof(char));
    char *telPaciente=(char*)malloc(1*sizeof(char));
    char *endRuaPaciente=(char*)malloc(1*sizeof(char));
    char *endNumPaciente=(char*)malloc(1*sizeof(char));
    char *endCompPaciente=(char*)malloc(1*sizeof(char));
    char *endBairroPaciente=(char*)malloc(1*sizeof(char));
    char *endCidadePaciente=(char*)malloc(1*sizeof(char));
    char *endEstPaciente=(char*)malloc(1*sizeof(char));
    char *endCepPaciente=(char*)malloc(1*sizeof(char));
    char *nascPaciente=(char*)malloc(1*sizeof(char));
    char *emailPaciente=(char*)malloc(1*sizeof(char));
    char *dataDiagPaciente=(char*)malloc(1*sizeof(char));
    char *optAgravPaciente=(char*)malloc(1*sizeof(char));
    char *agravPaciente=(char*)malloc(1*sizeof(char));
    char *confirmCadast=(char*)malloc(1*sizeof(char));

    char *dadosPaciente=(char*)malloc(1*sizeof(char));
    char *dadosComorbido=(char*)malloc(1*sizeof(char));

    userTentativas = 1;
    // userLogado = 0; // não esta logado
    char user[6] = "admin";
    char pass[5] = "1234";
        printf("--------------------------------------------------------------------------------\n\n");
        printf("                                PROJETO MAIS SAUDE\n\n");
        printf("--------------------------------------------------------------------------------\n\n");
    while(userTentativas > 0){
        /* Pega o usuario */
        printf("Digite seu login: ");
        gets(userInput);
        /* pega a senha */
        printf("Digite sua senha: ");
        gets(passInput);

        /* verifica o usuario e senha */
        if(strcmp(userInput, user) == 0 && strcmp(passInput, pass) == 0){
            printf("Usuario logado! [%s] \n\n", userInput);
            printf("Digite qualquer tecla para continuar \n\n");
            getch();
            break;
        } else{
            /* se o numero de tentativas de login for == 4, sair do programa */
            if(userTentativas == 4){
                printf("Excedeu o limite de tentativas \n");
                printf("Digite qualquer tecla para continuar \n\n");
                getch();
                exit(0);
            } else{ /* informa o erro e pede para tentar novamente */
                printf("Usuario e senha invalidos! [%s] \n", userInput);
                printf("Digite qualquer tecla para continuar \n\n");
                getch();
            }
            /* conta as tentativas */
            userTentativas = userTentativas + 1;
        }
    }

    /* boas vindas */
    printf("Ola %s, seja bem vindo ao Mais Saude! \n\n", userInput);

    menu: printf("\n\nSelecione uma das opcoes abaixo: \n\n");
    printf("1 - Cadastrar novo caso \n");
    printf("2 - Sair \n\n");

    printf("Digite a opcao:");
    gets(menuAtendimento);

 //   printf("Menu Selecionado: %i, Obrigado \n\n", menuAtendimento);
 //   getch();

    if( strcmp(menuAtendimento, "2") == 0){
        printf("Obrigado!\n\nAperte qualquer tecla para sair.");
        getch();
        exit(0);
    }else{
        cadastro: printf("\n\n--------------------------------------------------------------------------------\n\n");
        printf("                    MENU DE ATENDIMENTO - MAIS SAUDE\n\n");
        printf("--------------------------------------------------------------------------------\n\n");
        printf("DADOS DO PACIENTE: \n\n");

        printf("NOME: ");
        gets(nomePaciente);

        printf("CPF: ");
        gets(cpfPaciente);

        printf("TELEFONE: ");
        gets(telPaciente);

        printf("ENDERECO: ");
        gets(endRuaPaciente);

        printf("NUMERO: ");
        gets(endNumPaciente);

        printf("COMPLEMENTO: ");
        gets(endCompPaciente);

        printf("BAIRRO: ");
        gets(endBairroPaciente);

        printf("CIDADE: ");
        gets(endCidadePaciente);

        printf("ESTADO (SIGLA): ");
        gets(endEstPaciente);

        printf("CEP: ");
        gets(endCepPaciente);

        printf("DATA DE NASCIMENTO (DD/MM/AAAA): ");
        gets(nascPaciente);

        printf("EMAIL: ");
        gets(emailPaciente);

        printf("DIAGNOSTICO (DATA - DD/MM): ");
        gets(dataDiagPaciente);

        printf("COMORBIDADES \n\n");
        printf("1 - DIABETES \n");
        printf("2 - OBESIDADE \n");
        printf("3 - HIPERTENSAO \n");
        printf("4 - TUBERCULOSE \n");
        printf("9 - OUTROS \n\n");
        printf("0 - NAO POSSUI COMORBIDADES \n\n");

        printf("SELECIONE UMA DAS OPCOES: ");
        gets(optAgravPaciente);

        optAgravPaciente = replaceWord(optAgravPaciente, "\n", "\0");

        /* tentei primeiro atribuir o valor de agravPaciente diretamente, depois substitui pela funão strcpy */
        if( strcmp(optAgravPaciente, "1") == 0 ){
            agravPaciente = strcpy(agravPaciente, "DIABETES");
        } else if( strcmp(optAgravPaciente, "2") == 0 ){
            agravPaciente = strcpy(agravPaciente, "OBESIDADE");
        } else if( strcmp(optAgravPaciente, "3") == 0 ){
            agravPaciente = strcpy(agravPaciente, "HIPERTENSAO");
        } else if( strcmp(optAgravPaciente, "4") == 0 ){
            agravPaciente = strcpy(agravPaciente, "TUBERCULOSE");
        } else if( strcmp(optAgravPaciente, "9") == 0 ){
            agravPaciente = strcpy(agravPaciente, "OUTROS");
        } else {
            agravPaciente = strcpy(agravPaciente, "SEM_COMORBIDADES");
        }

        nomePaciente = replaceWord(nomePaciente, "\n", " ");
        cpfPaciente = replaceWord(cpfPaciente, "\n", " ");
        telPaciente = replaceWord(telPaciente, "\n", " ");
        endRuaPaciente = replaceWord(endRuaPaciente, "\n", " ");
        endNumPaciente = replaceWord(endNumPaciente, "\n", " ");
        endCompPaciente = replaceWord(endCompPaciente, "\n", " ");
        endBairroPaciente = replaceWord(endBairroPaciente, "\n", " ");
        endCidadePaciente = replaceWord(endCidadePaciente, "\n", " ");
        endEstPaciente = replaceWord(endEstPaciente, "\n", " ");
        endCepPaciente = replaceWord(endCepPaciente, "\n", " ");
        emailPaciente = replaceWord(emailPaciente, "\n", " ");
        dataDiagPaciente = replaceWord(dataDiagPaciente, "\n", " ");
        agravPaciente = replaceWord(agravPaciente, "\n", " ");
        nascPaciente = replaceWord(nascPaciente, "\n", " ");

        printf("--------------------------------------------------------------------------------\n\n");

        printf("OS DADOS A CIMA ESTAO CORRETOS? DESEJA CONFIRMAR? \n\n");
        printf("1 - SIM \n");
        printf("2 - NAO \n\n");
        printf("Digite a opcao:");

        gets(confirmCadast);

        if( strcmp(confirmCadast, "2") == 0 ){
            goto cadastro;
        } else{
            printf("--------------------------------------------------------------------------------\n\n");
        }

        dadosPaciente = strcpy(dadosPaciente, "");
        dadosPaciente = strcat(dadosPaciente, nomePaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, cpfPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, telPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endRuaPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endNumPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endCompPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endBairroPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endCidadePaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endEstPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, endCepPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, nascPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, emailPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, dataDiagPaciente);
        dadosPaciente = strcat(dadosPaciente, ";");
        dadosPaciente = strcat(dadosPaciente, agravPaciente);
        dadosPaciente = strcat(dadosPaciente, "\n");

        gravarArquivo("DadosDoPaciente.txt", dadosPaciente);

        getch();

        int idadePaciente;
        char *strIdadePaciente=(char*)malloc(1*sizeof(char));
        idadePaciente = calculaIdade(nascPaciente);

        if(idadePaciente >= 65 && strcmp(agravPaciente, "SEM_COMORBIDADES") != 0){
            //printf("ELEGIVEL");

            dadosComorbido = strcpy(dadosComorbido, "");

            dadosComorbido = strcat(dadosComorbido, endCepPaciente);
            dadosComorbido = strcat(dadosComorbido, ";");

            int length = snprintf( NULL, 0, "%d", idadePaciente);
            snprintf(strIdadePaciente, length + 1, "%d", idadePaciente);

            dadosComorbido = strcat(dadosComorbido, strIdadePaciente);
            dadosComorbido = strcat(dadosComorbido, "\n");

            gravarArquivo("DadosDoGrupoDeRisco.txt", dadosComorbido);
        }
        system ("CLS");
        goto menu;


        printf("{%s}", nascPaciente);
        getch();
    }


    return 0;
}
