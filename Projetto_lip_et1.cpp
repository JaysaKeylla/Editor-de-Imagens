#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


const int MAX = 512;
const int MSTR = 51;
const int R = 1;
const int G = 2;
const int B = 3;


struct Img
{
    int largura;
    int altura;
    int pix;
    int RGB[MAX][MAX][3];
};

void converte_para_cinza(Img img_in, Img& img_out);
void salva_arq(char nome[], Img img);
void abre_img(char nome[], Img& img);

int main()
{
   char nome_arq[MSTR];
   int menu;
   cout<<"Bem-vindo, vamos iniciar a edicao da sua imagem...\n";
   cout << "Digite o nome do arquivo .ppm: \n";
   cin >> nome_arq;
   Img img_in, img_out;
   abre_img(nome_arq, img_in);
   cout<<"O que voce deseja fazer?\nDigite o numero da opcao que deseja escolher\n1-Converter para escalas de cinza\n0-sair\n";
   cin>>menu;
   if(menu==1){
   converte_para_cinza(img_in, img_out);
   }
   else if(menu===0){
   return 0;
   }
   cout << "Digite o nome do novo arquivo: \n";
   cin >> nome_arq;
   salva_arq(nome_arq, img_out);
   return 0;
}
void converte_para_cinza(Img img_in, Img& img_out)
{
    int i, j, k, media;

    img_out.largura = img_in.largura;
    img_out.altura = img_in.altura;
    img_out.pix = img_in.pix;

    for(j=0; j<img_in.altura; j++){
        for(i=0; i<img_in.largura; i++){
            media = (img_in.RGB[i][j][R] + img_in.RGB[i][j][G] + img_in.RGB[i][j][B])/3;
            img_out.RGB[i][j][R] = media;
            img_out.RGB[i][j][G] = media;
            img_out.RGB[i][j][B] = media;
        }
    }
    cout << "Imagem para tons de cinza com sucesso! \n";
}
void salva_arq(char nome[], Img img)
{
    strcat(nome, ".ppm");
    ofstream arquivo;
    arquivo.open(nome);
    arquivo << "P3" << endl;
    arquivo << img.largura << " " << img.altura << endl;
    arquivo << img.pix 
<< endl;
    int i, j, k;
    for(j=0; j<img.altura; j++){
        for(i=0; i<img.largura; i++){
            for(k=1; k<4; k++){
                arquivo << img.RGB[i][j][k] << " ";
            }
        }
        arquivo << endl;
    }
    cout << "Arquivo salvo com sucesso! \n";
    arquivo.close();
}
void abre_img(char nome[], Img& img)
{
    ifstream arquivo;
    arquivo.open(nome);
    if (!arquivo.is_open()){
        cout << "Erro, arquivo nao encontrado :( \n";
    }
    else{
        cout << "Arquivo aberto com sucesso! \n";
        char teste[MSTR];
        arquivo.getline(teste, MSTR);
        if( strcmp("P3", teste)!= 0){
        cout<< "Erro, arquivo nao compativel :( \n";
        }
        else{
            arquivo >> img.largura >> img.altura >> img.pix;
            if(img.largura <+ MAX || img.altura <= MAX){
            cout << "Arquivo suportado. \n";
            cout << "Dimencionamento " << img.altura << "X" << img.largura << endl;
            int i, j, k, cont=0;
                for(j=0; j<img.altura; j++){
                    for(i=0; i<img.largura; i++){
                        for(k=1; k<4; k++){
                            arquivo >> img.RGB[i][j][k];
                            cont++;
                        }
                    }
                }
                if(cont == img.altura * img.largura * 3){
                    cout<< "Arquivo lido com sucesso! \n";
                }else{
                    cout<< "Erro na leitura da imagem :( \n";
                }
            }
            else{
                cout << "ERRO, arquivo nao suportado :( \n";
            }
        }
        arquivo.close();
    }
}
