/************************************************************
    PROJETO EDUCACIONAL -  ESTRUTURA DE DADOS
    ALUNO: PAULO HENRIQUE AMIGONI
    ALUNO: DEUS (SÓ ELE SABE COMO FUNCIONA REALMENTE)

    PROJETO NOME: 7 a 1
    PROFESSOR: ORLANDO SARAIVA JR.
    FONTE: https://github.com/orlandosaraivajr/FATEC_ED18/blob/master/Projeto_7_a_1.pdf

    TRILHA SONORA: SPOTFY (BRAZILIAN MUSIC - CAIPIRINHA)

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <typeinfo>

using namespace std;




/* FUNCAO PARA ABRIR OS ARQUIVOS */
FILE* AbreArquivo(char modo, char caminho[30]){
    FILE *arquivo;
    switch(modo){
        case 'g':
            arquivo = fopen(caminho,"wt"); //ESCREVE
            break;
        case 'l':
            arquivo = fopen(caminho,"rt"); //LE
            break;
        case 'a':
            arquivo = fopen(caminho,"a"); //APPEND
            break;
    }
    if(arquivo==NULL){
        printf("Nao foi possivel abrir o arquivo");
        exit(0);
    }
    return arquivo;
}

/* FUNCAO PARA FECHAR O ARQUIVO */
void FecharArquivo(FILE *arquivo){
    fclose(arquivo);
}


/* LIMPAR O BANCO ANTES DE RECEBER OS NOVOS DADOS */
void LimpaBancoRepetidas(){
    FILE *arquivo;
    arquivo = AbreArquivo('g', "banco.txt");
    FecharArquivo(arquivo);
}

/* QUANDO PASSAR POR ABRIR O PACOTE ELE VERIFICA SE
   A FIGURINHA NÃO VEM REPETIDA NO MESMO ENVELOPE,
   SE VIER PEGA OUTRO NUMERO*/
bool Existe(int valores[],int tam, int valor){
    for(int i = 0;i<tam;i++){
        if(valores[i]==valor && valor > 0 && valor <= 681)
            return true;
    }
    return false;
}


/* ABRE OS PACOTES DE FIGURINHAS, CADA PACOTE CONTEM 5 FIGURINHAS */
void AbrirPacote(int numeros[],int quantNumeros,int Limite){



    srand(time(NULL));
    int v;
    for(int i=0;i<quantNumeros;i++){
        v = rand() % Limite;
            while(Existe(numeros,i,v)){
                v = rand() % Limite;
            }
       numeros[i] = v;
    }




}

/* CADASTRA O VETOR DAS FIGURINHAS , LEMBRANDO QUE O  ARQUIVO É APAGADO E REFEITO COM OS VALORES NOVOS */
void Cadastrarpacote(int figurinha, int quantidade){
    FILE *arquivo;
    arquivo = AbreArquivo('a', "banco.txt");
    fprintf(arquivo, "%d %d\n",figurinha, quantidade);
    FecharArquivo(arquivo);
}

/* LISTA AS INFORMAÇÕES DO ALBUM DE FIGURINHAS, QUANTAS COMPREI, QUANTAS REPETIDAS, O QUE FALTA ... */
void listaAlbum(){
 FILE *arquivo;
    int a, qtd;
    int desc_lida = 0;
    int repetidas=0, faltantes=0, coladas=0, total=0;


for(int a = 1; a <= 681; a++){
                arquivo = fopen("banco.txt","r");
                 while(!feof(arquivo)){
                    setbuf(stdin,NULL);
                    fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);
                    if(desc_lida == a){


                            if(qtd == 0){
                                faltantes = faltantes+1;
                            }


                            if(qtd >= 1){
                                coladas = coladas+1;
                            }


                            if(qtd > 1){
                                repetidas = repetidas+(qtd-1);
                            }


                            total = total+qtd;
                        }
                    }

                     fclose(arquivo);
             }





    printf("\n\n=========================================================================\n");
    cout << "\t" << faltantes << " figurinhas para ser completo\n";
	cout << "\t" << coladas << " figurinhas coladas em seu album\n";
	cout << "\t" << repetidas << " figurinhas repetidas em seu album\n";
	cout << "\t" << total << " figurinhas compradas\n";
	printf("=========================================================================\n");




}


/* FAZ A OPERACAO DE CADASTRAR A FIGURINHA VERIFANDO SE NAO TIVER ELE COLA NO ALBUM SE NAO ELE ADICIONA COMO REPETIDA */
void FazerOperacao(int numero, int total){

  int recebido[681];
  int novo[681];
  int t;

     for(int w =0; w < total; w++){
                recebido[numero] = numero;
                novo[w] = 0;
        }



    FILE *arquivo;
    int i, a, qtd;
    int desc_lida = 0;

                arquivo = fopen("banco.txt","r");
                cout << "\n";
                 while(!feof(arquivo)){
                    setbuf(stdin,NULL);
                    fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);
                               if(desc_lida == numero){

                                if(qtd == 0){
                                        cout << "\t\t" << numero << " Colada" ;
                                    }else{
                                        cout << "\t\t" << numero << " Repetida" ;
                               }

                                novo[numero] = qtd+1;


                               }else{

                                novo[desc_lida] = qtd;
                             }
                     }

               fclose(arquivo);

             LimpaBancoRepetidas();

                    for(int t = 1; t <= 681; t ++){
                    if(novo[t] >=0 && novo[t] <= 681){
                        Cadastrarpacote(t,novo[t]);
                        }
                    }







}

/* LISTA A FIGURINHA SE JA FOI COLADA - SOMENTE 1 POR VEZ */
void verificaColada(int numero){


    int novo[681];
    FILE *arquivo;
    int i, a, qtd;
    int desc_lida = 0;

    arquivo = fopen("banco.txt","r");
     while(!feof(arquivo)){
        setbuf(stdin,NULL);
        fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);
                   if(desc_lida == numero){

                    if(qtd == 0){
                            cout << "Voce ainda nao tem a figurinha nº " << numero << endl;
                        }else if(qtd == 1){
                            cout << "Voce ja tem a Figurinha nº " << numero  << endl;
                        }else if(qtd > 1){
                            cout << "Voce ja tem essa figurinha  nº " << numero << " e tem " << (qtd - 1) << " repetida " << endl;
                        }else{
                        }

                   }


         }

   fclose(arquivo);




}

/* LISTA AS FIGURINHAS FALTANTES PARA COLAR AINDA NO ALBUM */
void verificaFalta(){

    int novo[681];

    FILE *arquivo;
    int   a, qtd;
    int desc_lida = 0;

    for(a =1; a <=681; a++){

    arquivo = fopen("banco.txt","r");
     while(!feof(arquivo)){
        setbuf(stdin,NULL);
        fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);
         if(desc_lida == a  && qtd == 0){

                cout  << desc_lida << "\n";

            }
         }
   fclose(arquivo);
       }




}

/* LISTA AS FIGURINAS REPETIDAS, TRAZ O NUMERO E QUANTIDADE */
void verificaRepetidas(){


    int novo[681];
    FILE *arquivo;
    int a, qtd;
    int desc_lida = 0;
    for(a =1; a <=681; a++){
    arquivo = fopen("banco.txt","r");

     while(!feof(arquivo)){
        setbuf(stdin,NULL);
        fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);
         if(desc_lida == a  && qtd > 1){
                if(a > 0 and a <= 681){
                cout  << desc_lida << " ("<<qtd-1<<")" << "\n";

                }
            }
         }

   fclose(arquivo);

       }


}

/* TROCAR A FIGURINHA, RECEBE A FIGURINHA QUE DESEJA TROCAR, E QUE VC PRECISA,
   CASO A QUE RECEBI JA TENHA COLADA NO ALBUM ENVIA PARA REPETIDAS,
   E DECREMENTADO DO REPETIDAS E COLADO NO ALBUM, SE CASO TIVER JA COLADA NO
   ALBUM O SISTEMA NAO DEIXA ELE TIRAR */
void trocarFigurinha(int numero, int add){


    int rep[681];
    FILE *arquivo;
    int i, a, qtd;
    int desc_lida = 0;
    int validar = 0;

                arquivo = fopen("banco.txt","rt");
                 while(!feof(arquivo)){
                    setbuf(stdin,NULL);
                    fscanf(arquivo,"%d %d\n",&desc_lida, &qtd);

                    if(desc_lida == numero){
                       if(qtd == 0){
                        rep[desc_lida] = qtd;
                        cout << "Voce ainda nao tem essa figurinha com o nº " << numero <<  endl;
                        validar = 1;
                       }

                       if(qtd == 1){
                        rep[desc_lida] = qtd;
                        cout << "Voce tem somente a figuria que esta no album colada, nao pode trocar" << endl;
                        validar = 1;
                       }
                       if(qtd > 1){

                        rep[desc_lida] = qtd-1;
                          cout << "Figurinha nº " << numero << " foi trocada " << endl;
                    }

                    }else{
                    rep[desc_lida] = qtd;

                   }



                    if(desc_lida == add && validar == 0){
                       if(qtd == 0){
                        rep[desc_lida] = qtd+1;
                        cout << "Voce adicionou a figurinha com o nº " << add << " em seu album" <<  endl;
                       }

                       if(qtd == 1){
                        rep[desc_lida] = qtd+1;
                        cout << "Voce ja tinha essa figuria com o nº " << add  <<" mais adicionamos na caixa de repetidas"  << endl;
                       }
                       if(qtd > 1){

                        rep[desc_lida] = qtd+1;
                          cout << "Como voce ja tinha essa figurinha com nº " << add << " adicionamos ela na caixa de repetidas " << endl;
                    }

                    }else{
                    rep[desc_lida] = qtd;
                    }


}

 fclose(arquivo);
 LimpaBancoRepetidas();
                  for(int i=1; i<=681; i++){
                    Cadastrarpacote(i,rep[i]);
                    }




}





int main(){

 int    opcao;

  do{

    int    figurinhas_por_pacote = 5;
    int    pacote;
    char   desc[50];
    char   quant[50];
    float  valor;
    int    vFigura;
    int    vFiguraAdd;


        printf("\n\n");
        printf("\t           __                 __           __   __   __\n");
        printf("\t /\\  |    |__) |  |  |\\/|    |  \\  /\\     /  ` /  \\ |__)  /\\ \n");
        printf("\t/~~\\ |___ |__) \\__/  |  |    |__/ /~~\\    \\__, \\__/ |    /~~\\ \n");
        printf("\t\n\n");



        printf("\n\t\t\t\t   MENU");
        printf("\n\t\t==========================================");
        printf("\n\t\t 1 - Abrir pacote de figurinha");
        printf("\n\t\t 2 - Inserir figurinha avulsa");
        printf("\n\t\t 3 - Verificar se a figurinha esta colada");
        printf("\n\t\t 4 - Listar Figurinhas Faltantes");
        printf("\n\t\t 5 - Listar Figurinhas Repetidas");
        printf("\n\t\t 6 - Trocar Figurinhas Repetidas");
        printf("\n\t\t 7 - Informacoes gerais");
        printf("\n\t\t 8 - Sair");
        printf("\n\t\t==========================================");

        printf("\n\t\tDigite uma opcao: ");
        scanf("%d", &opcao);
        printf("\n\n");


        switch(opcao){


            case 1:

                    int numeros[3];
                    cout<<"Digite a quantidade de pacotes: ";
                    cin>>pacote;
                    AbrirPacote(numeros,(figurinhas_por_pacote * pacote),682);
                    for(int a = 0;a<(figurinhas_por_pacote * pacote);a++){
                      FazerOperacao(numeros[a],(figurinhas_por_pacote * pacote));

                    }

            break;



            case 2:

                    cout<<"Digite a a Figurinha que deseja inserir avulsa: ";
                    cin>>vFigura;
                      FazerOperacao(vFigura,1);
           break;


            case 3:
                vFigura=0;
                cout<<"Informe a figurinha que quer verificar: ";
                cin>>vFigura;
                verificaColada(vFigura);
             break;

             case 4:
                verificaFalta();
             break;

             case 5:
                verificaRepetidas();
             break;

             case 6:
                cout<<"Informe a figurinha repetida que voce deseja trocar: ";
                cin>>vFigura;

                cout<<"Informe a figurinha que deseja adicionar: ";
                cin>>vFiguraAdd;


                trocarFigurinha(vFigura,vFiguraAdd);
             break;


             case 7:
                listaAlbum();
             break;

             case 8:
                printf("\n\nFinalizando...\n\n");
             break;

             default:
                printf("\n\nOpcao invalida! Tente Novamente!\n\n");
            }
    }while(opcao!=7);




}
