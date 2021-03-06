/*
ERRO NA LOGICA DO ERL
*/
#include <iostream>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <string>

#ifdef __linux__
    #define stricmp strcasecmp
    #define strnicmp strncasecmp
    
    #define ascA 97
    #define ascC 99
    #define ascE 101
#elif _WIN32
    #include <conio.h>
    
    #define ascA 131
    #define ascC 135
    #define ascE 130
#endif

#define mtzSize 20
#define strSize 100
#define maxMDC 25
#define offset 0.001
#define erl1limit 100
#define erl2limit 25

using namespace std;

int matrizE2n[mtzSize][mtzSize];
int matrizE2d[mtzSize][mtzSize];
int me_n=-1;
int me_m=-1;

double matrizaux [mtzSize][mtzSize];
int ma_n=-1; //linhas
int ma_m=-1; //colunas


double matriz1 [mtzSize][mtzSize];
int m1_n=-1; //linhas
int m1_m=-1; //colunas

double matriz2 [mtzSize][mtzSize];
int m2_n=-1; //linhas
int m2_m=-1; //colunas

double matriz3 [mtzSize][mtzSize];
int m3_n=-1; //linhas
int m3_m=-1; //colunas

double matriz4 [mtzSize][mtzSize];
int m4_n=-1; //linhas
int m4_m=-1; //colunas

char stringmatriz[strSize];
char command[strSize];
int lastmtzidx=0;
double erlDetIdx;
bool tudopiranha=1;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    void get_matriz();
    void resetvar();
    cout<<"#####################"<<endl;
    cout<<"#*  * **** *  *  ** #"<<endl;
    cout<<"#** * *  * ** * *  *#"<<endl;
    cout<<"#* ** **** * ** *  *#"<<endl;
    cout<<"#*  * *  * *  *  ** #"<<endl;
    cout<<"#####################"<<endl;
    cout<<"Por: Thiago F Costa"<<endl<<endl;
    cout<<"C.Matriz"<<endl;
    while(tudopiranha){
        cout<<"digite um comando (ex: help):"<<endl;
        resetvar();
        get_matriz();
        cout<<endl;
        cout<<endl;
    }
    return 0;
}

void resetvar(){
    memset(stringmatriz,0,strSize);
    lastmtzidx=0;
    ma_n=-1;
    ma_m=-1;
    m1_n=-1;
    m1_m=-1;
    m2_n=-1;
    m2_m=-1;
    m3_n=-1;
    m3_m=-1;
    m4_n=-1;
    m4_m=-1;
    me_n=-1;
    me_m=-1;

    for(int i=0;i<mtzSize;i++)
        for(int j=0;j<mtzSize;j++){
            matrizaux[i][j]=0;
            matriz1[i][j]=0;
            matriz2[i][j]=0;
            matriz3[i][j]=0;
            matriz4[i][j]=0;
            matrizE2d[i][j]=1;
            matrizE2n[i][j]=0;
        }
}

void get_matriz(){
    void commandProcedure();
    memset(command,0,strSize);
    cin.getline(stringmatriz,strSize);            //strcpy(stringmatriz,"erl2 2 3 7|2 1 5|5 4 1|&1 1 1|1 1 1|1 1 1|");
    for (int i=0;i<strlen(stringmatriz);i++)
        if (stringmatriz[i]!=' ')
            command[i]=stringmatriz[i];
        else
            i=strlen(stringmatriz);
    commandProcedure();
}

void commandProcedure(){
    void strtomatriz(int nmatriz);
    bool isErl();
    void toErl();
    void toInvnn();
    void mult();
    double cofator(int a,int b,double matrizZ[mtzSize][mtzSize],int mz_n,int mz_m);
    double detadj(double matrizZ[mtzSize][mtzSize],int mz_n,int mz_m);
    void toErl2();
    void isErl2();
    void deleteme();
    void toNewErl();
    void simplErl();
    void erlInside(int print);

    if (!stricmp(command,"transposta")){
        strtomatriz(1);

        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        for(int i=0;i<m1_m;i++)
            for(int j=0;j<m1_n;j++)
                    matriz1[i][j]=matrizaux[j][i];
        for(int i=0;i<m1_m;i++){
            cout<<endl;
            for(int j=0;j<m1_n;j++)
                cout<<matriz1[i][j]<<" ";
        }
    }else if(!stricmp(command,"multiE")){ 
        double escalar;
        char aux[strSize];
        int aux1=-1;
        strtomatriz(1);
        for(int i=lastmtzidx;i<strlen(stringmatriz);i++)
            if(stringmatriz[i]!=' '&&stringmatriz[i]!='|'){
                aux1++;
                aux[aux1]=stringmatriz[i];
            }

        escalar=atof(aux);
        for(int i=0;i<m1_n;i++){cout<<endl;
            for(int j=0;j<m1_m;j++){
                cout<<"("<<matriz1[i][j]<<")*("<<escalar<<") ";
                matriz1[i][j]*=escalar;
            }
        }
        cout<<endl<<endl<<"Resultado: ";
        for(int i=0;i<m1_n;i++){
            cout<<endl;
            for(int j=0;j<m1_m;j++)
                cout<<matriz1[i][j]<<" ";
        }
    }else if(!stricmp(command,"soma")){
        strtomatriz(2);
        if(m1_n==m2_n&&m1_m==m2_m){
            for(int i=0;i<m1_n;i++){cout<<endl;
                for(int j=0;j<m1_m;j++){
                    cout<<"("<<matriz1[i][j]<<")+("<<matriz2[i][j]<<") ";
                    matriz1[i][j]+=matriz2[i][j];
                }
            }
            cout<<endl<<endl<<"Resultado: ";
            for(int i=0;i<m1_n;i++){
                cout<<endl;
                for(int j=0;j<m1_m;j++)
                    cout<<matriz1[i][j]<<" ";
            }
        }else cout<<endl<<"as matrizes devem ter o mesmo tamanho para realizar a soma"<<endl;
    } else if(!stricmp(command,"multi")){
        strtomatriz(2);
        mult();
            cout<<endl<<endl<<"Resultado: ";
            for(int i=0;i<m1_n;i++){
                    cout<<endl;
                    for(int j=0;j<m2_m;j++)
                        cout<<matriz1[j][i]<<" ";
                }
    } else if(!stricmp(command,"tr")||!stricmp(command,"traco")){
        strtomatriz(1);
        double traco;
        for(int i=0;i<m1_n;i++)
                for(int j=0;j<m1_m;j++)
                    if(i==j)
                        traco+=matriz1[i][j];
        cout<<traco;
    } else if(!stricmp(command,"det22")){
        strtomatriz(1);
        double det;
        double aux1=0,aux2=0;
        if(m1_n==2&&m1_m==2){
            aux1=matriz1[0][0]*matriz1[1][1];
            aux2=matriz1[0][1]*matriz1[1][0];
            cout<<"det=a*c-b*d  "<<aux1<<"-("<<aux2<<")";
            det=aux1-aux2;
            cout<<endl<<endl<<"Resultado: "<<det;
        }else cout<<endl<<"a matriz deve ser 2x2"<<endl;
    }else if(!stricmp(command,"det33")){
        strtomatriz(1);
        double det;
        double aux1=0,aux2=0;
        if(m1_n==3&&m1_m==3){
            aux1=(matriz1[0][0]*matriz1[1][1]*matriz1[2][2])+(matriz1[0][1]*matriz1[1][2]*matriz1[2][0])+(matriz1[0][2]*matriz1[1][0]*matriz1[2][1]);
            aux2=(matriz1[0][1]*matriz1[1][0]*matriz1[2][2])+(matriz1[0][0]*matriz1[1][2]*matriz1[2][1])+(matriz1[0][2]*matriz1[1][1]*matriz1[2][0]);
            cout<<"a b c|a b"<<endl<<"d e f|d e"<<endl<<"g h i|g h"<<endl;
            cout<<"det=(a*e*i)+(b*f*g)+(c*d*h)-(b*d*i)-(a*f*h)-(c*e*g)  "<<aux1<<"-("<<aux2<<")";
            det=aux1-aux2;
            cout<<endl<<endl<<"Resultado: "<<det;
        }else cout<<endl<<"a matriz deve ser 3x3"<<endl;
    }else if(!stricmp(command,"inv22")){
        strtomatriz(1);
        double det;
        double aux1=0,aux2=0;
        if(m1_n==2&&m1_m==2){
            aux1=matriz1[0][0]*matriz1[1][1];
            aux2=matriz1[0][1]*matriz1[1][0];
            cout<<"inv=1/(det)*  d -b"<<endl<<"             -c  a"<<endl;
            det=aux1-aux2;
            cout<<"1/"<<det<<"*(d-b|-ca|)";
            for(int i=0;i<m1_n;i++)
                for(int j=0;j<m1_m;j++)
                    matriz1[i][j]*=1/det;
            aux1=matriz1[0][1];
            aux2=matriz1[1][0];
            if(aux1!=0)aux1*=-1;
            if(aux2!=0)aux2*=-1;
            cout<<endl<<endl<<"Resultado: \n"<<matriz1[1][1]<<" "<<aux1<<"\n"<<aux2<<" "<<matriz1[0][0];
        }else cout<<endl<<"a matriz deve ser 2x2"<<endl;
    }else if(!stricmp(command,"erl")){
        strtomatriz(1);
        toErl();
        cout<<endl<<endl<<"Resultado: ";
        for(int i=0;i<m1_n;i++){
            cout<<endl;
            for(int j=0;j<m1_m;j++)
                cout<<matriz1[i][j]<<" ";
        }

    }else if(!stricmp(command,"invnn")){
        strtomatriz(1);
        toInvnn();

        cout<<endl<<endl<<"Resultado: ";
            for(int i=0;i<m1_n;i++){
                cout<<endl;
                for(int j=0;j<m1_m*2;j++)
                    cout<<matriz1[i][j]<<" ";
            }
    }else if(!stricmp(command,"ssminv")){ 
        strtomatriz(2);
        toInvnn();
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz1[i][j]=matriz1[i][j+m1_m];
        mult();
        cout<<endl<<endl<<"Resultado: ";
        for(int i=0;i<m1_n;i++){
            cout<<endl;
            for(int j=0;j<m2_m;j++)
                cout<<matriz1[j][i]<<" ";
        }
    }else if(!stricmp(command,"adj")){
        strtomatriz(1);
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        ma_n=m1_n;ma_m=m1_m;
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz1[i][j]=cofator(i,j,matrizaux,ma_n,ma_m);
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        for(int i=0;i<m1_m;i++)
            for(int j=0;j<m1_n;j++)
                    matriz1[i][j]=matrizaux[j][i];
        for(int i=0;i<m1_m;i++){
            cout<<endl;
            for(int j=0;j<m1_n;j++)
                cout<<matriz1[i][j]<<" ";
        }
    }else if(!stricmp(command,"detnn")){
        strtomatriz(1);
        cout<<endl<<endl<<"Resultado: "<<detadj(matriz1,m1_n,m1_m);
    }else if(!stricmp(command,"invadj")){
        double escalar;
        int aux1=-1;
        strtomatriz(1);
        escalar=1/detadj(matriz1,m1_n,m1_m);

        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        ma_n=m1_n;ma_m=m1_m;

        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz1[i][j]=cofator(i,j,matrizaux,ma_n,ma_m);
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        for(int i=0;i<m1_m;i++)
            for(int j=0;j<m1_n;j++)
                    matriz1[i][j]=matrizaux[j][i];

        for(int i=0;i<m1_n;i++){cout<<endl;
            for(int j=0;j<m1_m;j++){
                cout<<"("<<matriz1[i][j]<<")*("<<escalar<<") ";
                matriz1[i][j]*=escalar;
            }
        }
        cout<<endl<<endl<<"Resultado: ";
        for(int i=0;i<m1_n;i++){
            cout<<endl;
            for(int j=0;j<m1_m;j++)
                cout<<matriz1[i][j]<<" ";
        }

    }else if(!stricmp(command,"cramer")){
        strtomatriz(2);
        double det=detadj(matriz1,m1_n,m1_m);
        double tempdet[mtzSize];
        for (int t=0;t<m1_m;t++){
            for(int i=0;i<m1_n;i++)
                for(int j=0;j<m1_m;j++)
                    if(j!=t)
                        matrizaux[i][j]=matriz1[i][j];
                    else
                        matrizaux[i][j]=matriz2[i][0];

            tempdet[t]=detadj(matrizaux,m1_n,m1_m);
        }
        for (int t=0;t<m1_m;t++)
            cout<<endl<<"X"<<t+1<<"="<<tempdet[t]<<"/"<<det<<" ="<<tempdet[t]/det;
    }else if(!stricmp(command,"polma")){
        char aux[strSize];
        char aux2[strSize];
        int aux1=-1;
        strtomatriz(1);
        for(int i=lastmtzidx;i<strlen(stringmatriz);i++)
            if(stringmatriz[i]!=' '&&stringmatriz[i]!='|'){
                aux1++;
                aux[aux1]=stringmatriz[i];
            }
            aux1++;
            aux[aux1]='+';
            int aux3=-1;
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz4[i][j]=0;
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz3[i][j]=matriz1[i][j];
        m3_n=m1_n;
        m3_m=m1_m;
        m2_n=m1_n;
        m2_m=m1_m;
        int lastlimit=0;
        int isX=0;
        int multvalue=1;
        int expvalue=1;
        int signal=1;
        int isExp;
        for(int i=0;i<=aux1;i++){
            if(aux[i]=='+'||aux[i]=='-'){
               isX=0;
               aux3=-1;
               multvalue=1;
               expvalue=1;
               isExp=0;
               if(aux[i]=='+')
                    signal=1;
               else
                    signal=-1;
               memset(aux2,0,strSize);
               for(int k=lastlimit;k<i;k++){
                    if((aux[k]=='0'||aux[k]=='1'||aux[k]=='2'||aux[k]=='3'||aux[k]=='4'||aux[k]=='5'||aux[k]=='6'||aux[k]=='7'||aux[k]=='8'||aux[k]=='9')&&!isX){
                        aux3++;
                        aux2[aux3]=aux[k];
                    }
                    if(aux[k]=='x'||aux[k]=='X'){
                        isX=1;
                        if(strcmp(aux2,""))
                            multvalue=atoi(aux2);
                        aux3=-1;
                    }
                    if((aux[k]=='0'||aux[k]=='1'||aux[k]=='2'||aux[k]=='3'||aux[k]=='4'||aux[k]=='5'||aux[k]=='6'||aux[k]=='7'||aux[k]=='8'||aux[k]=='9')&&isX){
                        aux3++;
                        aux2[aux3]=aux[k];
                    }
                    if(aux[k]=='^')
                        isExp=1;
               }
               if(!isX){
                   if(strcmp(aux2,""))
                        multvalue=atoi(aux2);
                   for(int q=0;q<m1_n;q++)
                        for(int w=0;w<m1_m;w++)
                            if(q==w)
                                matriz1[q][w]=1;
                            else
                                matriz1[q][w]=0;
                    for(int q=0;q<m1_n;q++){cout<<endl;
                    for(int w=0;w<m1_m;w++){
                        cout<<"("<<matriz1[q][w]<<")*("<<multvalue<<") ";
                        matriz1[q][w]*=multvalue;}}
               }else{
                   if(strcmp(aux2,""))
                    expvalue=atoi(aux2);
                    for(int q=0;q<m1_n;q++)
                        for(int w=0;w<m1_m;w++)
                            matriz1[q][w]=matriz3[q][w];
                    for(int q=0;q<m1_n;q++)
                        for(int w=0;w<m1_m;w++)
                            matriz2[q][w]=matriz3[q][w];
                    if(isExp)
                        for(int t=1;t<expvalue;t++){
                            cout<<endl<<"A^"<<expvalue<<endl;
                            mult();
                    }
                    for(int q=0;q<m1_n;q++){cout<<endl;
                    for(int w=0;w<m1_m;w++){
                        cout<<"("<<matriz1[w][q]<<")*("<<multvalue<<") ";
                        matriz1[w][q]*=multvalue;
                    }
                }
               }
                for(int q=0;q<m1_n;q++)
                for(int w=0;w<m1_m;w++)
                    if(isExp)
                        matriz4[q][w]+=matriz1[w][q]*signal;
                    else
                        matriz4[w][q]+=matriz1[w][q]*signal;

               lastlimit=i;
            }
            cout<<endl;
            }
            cout<<endl<<endl<<"Resultado: ";
            for(int i=0;i<m1_n;i++){
            cout<<endl;
            for(int j=0;j<m1_m;j++)
                cout<<matriz4[i][j]<<" ";
            }

    }else if(!stricmp(command,"deterl")){
        strtomatriz(1);
        erlInside(0);//toErl();
        double det=1;
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                if(i==j)
                    det*=matriz1[i][j];
        det*=erlDetIdx;
        cout<<"Determinante = "<<det; 
    }else if(!stricmp(command,"help")){
        cout<<"Digite um comando seguido de seus parametros"<<endl;
        cout<<"Exemplo de formata";printf("%c%c",ascC,ascA);cout<<"o:"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"Matriz EX:1 -2 0.6|0 0 1|4 6 3| (| "<<(char)ascE<<" a quebra de linha).At"<<(char)ascE<<" 10x10"<<endl;
        cout<<"Equa";printf("%c%c",ascC,ascA);cout<<"o EX:5x^5+6x^3-x^2+3"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"Opera";printf("%c%c",ascC,ascA);cout<<"o             -Comando"<<endl;
        cout<<"-----------------------------------------------------------------"<<endl;
        cout<<"Escalonamento 3.0    -erl3 Matriz1"<<endl;
        cout<<"Soma de Matrizes     -soma Matriz1 & Matriz2"<<endl;
        cout<<"Multiplica";printf("%c%c",ascC,ascA);cout<<"o de M...-multi Matriz1 & Matriz2"<<endl;
        cout<<"Mult por escalar     -soma Matriz1 numero"<<endl;
        cout<<"Traco                -traco Matriz1"<<endl;
        cout<<"Transposta           -transposta Matriz1"<<endl;
        cout<<"Inversa 2x2          -inv22 Matriz1"<<endl;
        cout<<"Determinante 2x2     -det22 Matriz1"<<endl;
        cout<<"Determinante 3x3     -det33 Matriz1"<<endl;
        cout<<"Escalonamento        -erl Matriz1"<<endl;
        cout<<"Escalonamento 2.0    -erl2 MatrizNumerador & MatrizDenominador"<<endl;
        cout<<"Inversa nxn          -invnn Matriz1"<<endl;
        cout<<"Sistema Matriz Inv...-ssmiv Matriz1 & MatrizResposta"<<endl;
        cout<<"Matriz Adjunta       -adj Matriz1"<<endl;
        cout<<"Determinante nxn     -detnn Matriz1"<<endl;
        cout<<"Sistema por cramer   -cramer Matriz1 & MatrizResposta"<<endl;
        cout<<"Polinomio Matricial  -polma Matriz1 & Equacao1"<<endl;
        cout<<"Determinate por erl  -deterl Matriz1"<<endl;
        cout<<endl<<endl;
    }else if(!stricmp(command,"erl2")){
        strtomatriz(2);
        for (int i=0;i<m1_n;i++)
            for (int j=0;j<m1_m;j++){
                matrizE2n[i][j]=matriz1[i][j];
                matrizE2d[i][j]=matriz2[i][j];
            }
        me_n=m1_n;
        me_m=m1_m;
        simplErl();
        toErl2();
        deleteme();
    }else if(!stricmp(command,"erl3")){
        strtomatriz(1);
        erlInside(1);
    }
    else{
        cout<<endl<<"comando desconhecido, tente digitar help";
    }
}

void erlInside(int print){
        void toNewErl();
        void simplErl();
        void toErl2();
        void deleteme();
        
        toNewErl();
        simplErl();
        toErl2();
        if(print)deleteme();
}

bool isErl2(){
    int last_j=-1;
    int currentj=0;
    int erl=0;
    int zeros,noterl=0,zeroline=0;
    for(int i=0;i<me_n;i++){
        zeros=0;
        for(int j=0;j<me_m;j++)
            if(matrizE2n[i][j]!=0&&matrizE2d[i][j]!=0){
                    currentj=j;
                if(matrizE2n[i][j]!=matrizE2d[i][j]){
                    erl=0;j=me_m;i=me_n; noterl=1;
                }else{
                    if(zeroline){
                       erl=0;j=me_m;i=me_n;noterl=1;
                    }
                    for (int k=0;k<me_n;k++)
                        if(matrizE2n[k][j]!=0&&matrizE2d[k][j]!=0&&k!=i){
                            erl=0;j=me_m;i=me_n;k=me_n;noterl=1;
                        }
                    if(last_j>currentj){
                        erl=0;j=me_m;i=me_n; noterl=1;
                    }else if(!noterl){
                        erl=1;j=me_m;
                        last_j=currentj;
                    }
                }
            }else{
                zeros++;
                if(zeros>=me_m)
                    zeroline=1;
            }
    }
    return erl;    
}

void simplErl(){
    for (int i=0;i<me_n;i++)
        for (int j=0;j<me_m;j++){
        if(matrizE2n[i][j]!=0&&matrizE2d[i][j]!=0)
            if(matrizE2n[i][j]%matrizE2d[i][j]==0){
                if(matrizE2n[i][j]>matrizE2d[i][j]){
                    matrizE2n[i][j]/=matrizE2d[i][j];
                    matrizE2d[i][j]=1;
                }else{
                    matrizE2d[i][j]/=matrizE2n[i][j];
                    matrizE2n[i][j]=1;
                }
            }else{
                for(int t=maxMDC;t>1;t--)             
                    if(matrizE2n[i][j]%t==0&&matrizE2d[i][j]%t==0){
                        matrizE2n[i][j]/=t;
                        matrizE2d[i][j]/=t;
                    }
            }
            if(matrizE2d[i][j]==0){
               matrizE2d[i][j]=1;
               matrizE2n[i][j]=0;
            }
            if(matrizE2n[i][j]==0){
               matrizE2d[i][j]=1;
               matrizE2n[i][j]=0;
            }
            if(matrizE2d[i][j]<0){
                matrizE2n[i][j]*=-1;
                matrizE2d[i][j]*=-1;
            }
        }
}

void mmcPlus(int i,int j,int num, int dnom){
	if(num!=0&&dnom!=0)	
		if(matrizE2d[i][j]==dnom)
		    matrizE2n[i][j]+=num;
		else{
		    matrizE2n[i][j]=matrizE2n[i][j]*dnom+num*matrizE2d[i][j];
		    matrizE2d[i][j]*=dnom;
		}
    simplErl();
}

void deleteme(){
    int onlyOnes=1;
    for(int i=0;i<me_n;i++)
        for(int j=0;j<me_m;j++)
            if(matrizE2d[i][j]!=1)
                onlyOnes=0;
    if(onlyOnes){
        for(int i=0;i<me_n;i++){
        cout<<endl;
        for(int j=0;j<me_m;j++)
            cout<<matrizE2n[i][j]<<" ";
        }
    }else{
        cout<<endl<<"Numerador: ";
        for(int i=0;i<me_n;i++){
        cout<<endl;
        for(int j=0;j<me_m;j++)
            cout<<matrizE2n[i][j]<<" ";
        }
        cout<<endl<<"Denominador: ";
        for(int i=0;i<me_n;i++){
        cout<<endl;
        for(int j=0;j<me_m;j++)
            cout<<matrizE2d[i][j]<<" ";
        }
    }
}

void toErl2(){
        int currentline=0;
        int currentcol=0;
        int current0,aux2=0,aux3=0;
        erlDetIdx=1;
        int auxn,auxd;
        while(!isErl2()){
            current0=0;
            aux2=0;
            for(int k=0;k<me_m;k++)//for(int k=me_m-1;k>=0;k--)//
                if(matrizE2n[currentline][k]!=0&&matrizE2d[currentline][k]!=0){
                    current0++;
                    if(matrizE2n[currentline][k]!=matrizE2d[currentline][k]&&aux2==0){
                        auxn=matrizE2n[currentline][k];
                        auxd=matrizE2d[currentline][k];
                        currentcol=k;
                        cout<<"L"<<currentline+1<<"*"<<auxd<<"/"<<auxn<<endl;
                        erlDetIdx=erlDetIdx*auxd/auxn;
                        for(int j=0;j<me_m*2;j++){
                        	if(matrizE2n[currentline][j]!=0&&matrizE2d[currentline][j]!=0){
		                        matrizE2n[currentline][j]*=auxd;
		                        matrizE2d[currentline][j]*=auxn;
		                    }
                        }
                        simplErl();
                        break;//OU BREAK OU FOR DECRECENDO
                    }else if(aux2==0){
                        aux2++;
                        currentcol=k;
                    }
                }
            if(current0==0){
                for (int i=currentline;i<me_n-1;i++)
                    for(int j=0;j<me_m*2;j++){
                        matrizE2n[i][j]=matrizE2n[i+1][j];
                        matrizE2d[i][j]=matrizE2d[i+1][j];
                    }
                for(int j=0;j<me_m*2;j++)
                        matrizE2n[me_n-1][j]=0;
            }else{
                //deleteme();
                for(int k=0;k<me_n;k++)
		                if((matrizE2n[k][currentcol]!=0&&matrizE2d[k][currentcol]!=0)&&k!=currentline){
		                    auxn=matrizE2n[k][currentcol];
		                    auxd=matrizE2d[k][currentcol];
		                    if(auxn>0&&auxd>0)
		                        auxn*=-1;
		                    cout<<"L"<<k+1<<"+("<<auxn<<"/"<<auxd<<"L"<<currentline+1<<")"<<endl; 
		                    for(int i=0;i<me_m*2;i++){
		                        //mmcPlus(k,i,auxd*matrizE2n[currentline][i],auxn*matrizE2d[currentline][i]);
                                        mmcPlus(k,i,auxn*matrizE2n[currentline][i],auxd*matrizE2d[currentline][i]);
		                        
		                    }
		                }
            }
            currentline++;
            if(currentline>=me_n){currentline=0;aux3++;}
            if(aux3>erl2limit)break;
            simplErl();
        }
}

void toNewErl(){
    me_n=m1_n;
    me_m=m1_m;
    long int test;
    int denom;
    for (int i=0;i<me_n;i++)
        for (int j=0;j<me_m;j++){
            denom=1;
            test=(long int)matriz1[i][j];
            if((matriz1[i][j]-test)!=0){
                do{
                   matriz1[i][j]*=10; 
                   denom*=10;
                   test=(long int)matriz1[i][j];
                }while(matriz1[i][j]-test!=0);
            }
            matrizE2n[i][j]=matriz1[i][j];
            matrizE2d[i][j]=denom;
        }
}
void toOldErl(){
    m1_n=me_n;
    m1_m=me_m;
    for (int i=0;i<me_n;i++)
        for (int j=0;j<me_m;j++)
            matriz1[i][j]=(double)matrizE2n[i][j]/matrizE2d[i][j];
    
}
void strtomatriz(int nmatriz){
    char aux[strSize];
    int aux1=-1;
    int aux2=-1;
    if(nmatriz>=1){
        aux1=-1;
        aux2=-1;
        m1_n++;
        m1_m++;
        memset(aux,0,strSize);
        for (int i=strlen(command);i<strlen(stringmatriz);i++){
            if(stringmatriz[i]=='&'){lastmtzidx=i+1;i=strlen(stringmatriz);}
            else if(stringmatriz[i]!=' '&&stringmatriz[i]!='|'){
                aux1++;
                aux[aux1]=stringmatriz[i];
            }else if(strcmp(aux,"")){
                if(m1_n==0)m1_m++;
                aux2++;
                aux1=-1;
                matriz1[m1_n][aux2]=atof(aux);
                memset(aux,0,strSize); lastmtzidx=i;
                if(stringmatriz[i]!=' '){
                  m1_n++;
                  aux2=-1;
                }
            }
        }
    }

    if(nmatriz>=2){
        aux1=-1;
        aux2=-1;
        m2_n++;
        m2_m++;
        memset(aux,0,strSize);
        for (int i=lastmtzidx;i<strlen(stringmatriz);i++){
            if(stringmatriz[i]=='&'){lastmtzidx=i+1;i=strlen(stringmatriz);}
            else if(stringmatriz[i]!=' '&&stringmatriz[i]!='|'){
                aux1++;
                aux[aux1]=stringmatriz[i];
            }else if(strcmp(aux,"")){
                if(m2_n==0)m2_m++;
                aux2++;
                aux1=-1;
                matriz2[m2_n][aux2]=atof(aux);
                memset(aux,0,strSize); lastmtzidx=i;
                if(stringmatriz[i]!=' '){
                  m2_n++;
                  aux2=-1;
                }
            }
        }
    }
}
int det11(int l){
    if(l)
        return 0;
    else
        return 1;
}
double cofator(int a,int b,double matrizZ[mtzSize][mtzSize],int mz_n,int mz_m){
    double detadj(double matrizZ[mtzSize][mtzSize],int mz_n,int mz_m);
    double matrizcof [mtzSize][mtzSize];
    int mc_n=-1; //linhas
    int mc_m=-1; //colunas
    mc_n=mz_n-1;
    mc_m=mz_m-1;
    int aux1=-1,aux2;
    for(int i=0;i<mz_n;i++){
        if(a!=i)
            aux1++;
        aux2=-1;
        for(int j=0;j<mz_m;j++){
            if(j!=b){
                aux2++;
                if(i!=a)
                    matrizcof[aux1][aux2]=matrizZ[i][j];
            }
        }
    }
    if(mc_n==1){
        if((a+b)%2==0)
        return (matrizZ[det11(a)][det11(b)]);//matrizcof[0][0];
        else
        return (matrizZ[det11(a)][det11(b)])*-1;//matrizcof[0][0]*-1;
    }else if(mc_n==2){
        if((a+b)%2==0)
        return (matrizcof[0][0]*matrizcof[1][1])-(matrizcof[0][1]*matrizcof[1][0]);
        else
        return (matrizcof[0][0]*matrizcof[1][1])-(matrizcof[0][1]*matrizcof[1][0])*-1;
    }else if(mc_n==3){
        if((a+b)%2==0)
        return (matrizcof[0][0]*matrizcof[1][1]*matrizcof[2][2])+(matrizcof[0][1]*matrizcof[1][2]*matrizcof[2][0])+(matrizcof[0][2]*matrizcof[1][0]*matrizcof[2][1])-(matrizcof[0][1]*matrizcof[1][0]*matrizcof[2][2])+(matrizcof[0][0]*matrizcof[1][2]*matrizcof[2][1])+(matrizcof[0][2]*matrizcof[1][1]*matrizcof[2][0]);
        else
        return (matrizcof[0][0]*matrizcof[1][1]*matrizcof[2][2])+(matrizcof[0][1]*matrizcof[1][2]*matrizcof[2][0])+(matrizcof[0][2]*matrizcof[1][0]*matrizcof[2][1])-(matrizcof[0][1]*matrizcof[1][0]*matrizcof[2][2])+(matrizcof[0][0]*matrizcof[1][2]*matrizcof[2][1])+(matrizcof[0][2]*matrizcof[1][1]*matrizcof[2][0])*-1;
    }else
    if((a+b)%2==0)
        return detadj(matrizcof,mc_n,mc_m);
    else
        return detadj(matrizcof,mc_n,mc_m)*-1;

}
int getAuxZ(int isL,int idx,int n, int m){
    switch(idx){
        default:
        if(isL)
            return n;
        else
            return m;
        break;

    }
}

double detadj(double matrizZ[mtzSize][mtzSize],int mz_n,int mz_m){
    int zerosl=0,l=0;
    int zerosc=0,c=0;
    int currentz=0;
    int z=0,isL;
    for(int i=0;i<mz_n;i++){
            currentz=0;
        for(int j=0;j<mz_m;j++){
            if(matrizZ[i][j]==0)
                currentz++;
        }
        if(currentz>zerosl){
            l=i;
            zerosl=currentz;
        }
    }
    for(int i=0;i<mz_m;i++){
            currentz=0;
        for(int j=0;j<mz_n;j++){
            if(matrizZ[j][i]==0)
                currentz++;
        }
        if(currentz>zerosc){
            c=i;
            zerosc=currentz;
        }
    }
    if(zerosc>zerosl){
        z=c;
        isL=0;
        cout<<endl<<"expansao pela coluna: "<<z+1<<endl;
    }else{
        z=l;
        isL=1;
        cout<<endl<<"expansao pela linha: "<<z+1<<endl;
    }
    double output=0;
    double temp;
    for(int i=0;i<getAuxZ(isL,0,mz_n,mz_m);i++){
        if(isL){
            if(matrizZ[z][i]!=0){
                temp=cofator(z,i,matrizZ,mz_n,mz_m);
                output+=matrizZ[z][i]*temp; cout<<matrizZ[z][i]<<"*"<<temp<<"+";
            }
        }else{
            if(matrizZ[i][z]!=0){
                temp=cofator(i,z,matrizZ,mz_n,mz_m);
                output+=matrizZ[i][z]*temp; cout<<matrizZ[i][z]<<"*"<<temp<<"+";
            }
        }
    }

    return output;
}
double module(double in){
    if (in>0)
        return in;
    else
        return in*-1;
}
double offsetRound(double in){
    int Num=(int)in;
    if(module(in-Num)<=offset)
        return Num;
    else
        return in;

}
bool isErl(){
    int last_j=-1;
    int currentj=0;
    int erl=0;
    int zeros,noterl=0,zeroline=0;
    for(int i=0;i<m1_n;i++){
        zeros=0;
        for(int j=0;j<m1_m;j++)
            if(offsetRound(matriz1[i][j])!=0){//matriz1[i][j]!=0){//
                    currentj=j;
                if(offsetRound(matriz1[i][j])!=1){
                    erl=0;j=m1_m;i=m1_n; noterl=1;
                }else{
                    if(zeroline){
                       erl=0;j=m1_m;i=m1_n;noterl=1;
                    }
                    for (int k=0;k<m1_n;k++)
                        if(offsetRound(matriz1[k][j])!=0&&k!=i){
                            erl=0;j=m1_m;i=m1_n;k=m1_n;noterl=1;
                        }
                    if(last_j>currentj){
                        erl=0;j=m1_m;i=m1_n; noterl=1;
                    }else if(!noterl){
                        erl=1;j=m1_m;
                        last_j=currentj;
                    }
                }
            }else{
                zeros++;
                if(zeros>=m1_m)
                    zeroline=1;
            }
    }
    return erl;
}

void toErl(){
        int currentline=0;
        int currentcol=0;
        int current0,aux2=0,aux3=0;
        erlDetIdx=1;
        double aux1;
        while(!isErl()){
            current0=0;
            aux2=0;
            for(int k=me_m-1;k>=0;k--)//for(int k=0;k<m1_m;k++)
                if(offsetRound(matriz1[currentline][k])!=0){
                    current0++;
                    if(offsetRound(matriz1[currentline][k])!=1&&aux2==0){
                        aux1=matriz1[currentline][k];
                        currentcol=k;
                        cout<<"L"<<currentline+1<<"/"<<aux1<<endl;
                        erlDetIdx*=aux1;
                        for(int j=0;j<m1_m*2;j++)
                            matriz1[currentline][j]/=aux1;
                    }else if(aux2==0){
                        aux2++;
                        currentcol=k;
                    }
                }
            if(current0==0){
                for (int i=currentline;i<m1_n-1;i++)
                    for(int j=0;j<m1_m*2;j++)
                        matriz1[i][j]=matriz1[i+1][j];
                for(int j=0;j<m1_m*2;j++)
                        matriz1[m1_n-1][j]=0;
            }else{
                for(int k=0;k<m1_n;k++)
                    if(matriz1[k][currentcol]!=0&&k!=currentline){
                        aux1=matriz1[k][currentcol];
                        if(aux1>0)
                            aux1*=-1;
                        cout<<"L"<<k+1<<"+("<<aux1<<"L"<<currentline+1<<")"<<endl;
                        for(int i=0;i<m1_m*2;i++)
                            matriz1[k][i]+=matriz1[currentline][i]*aux1;
                    }
            }
            currentline++;
            if(currentline>=m1_n){currentline=0; aux3++;}
            if(aux3>erl1limit){cout<<"float error"<<endl<<endl;break;}
        }
}

void toInvnn(){
    void toOldErl();
    if(m1_m==m1_n&&m1_n<=mtzSize/2){
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                if(i==j)
                    matrizaux[i][j]=1;
                else
                    matrizaux[i][j]=0;
        for(int i=0;i<m1_n;i++)
            for(int j=m1_m;j<m1_m*2;j++)
                matriz1[i][j]=matrizaux[i][j-m1_m];
        //m1_m*=2;
        erlInside(0);//toErl();
        toOldErl();
    }else cout<<"A matriz � muito grande ou n�o � nxn"<<endl;
}

void mult(){
    if(m2_n==m1_m){
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matrizaux[i][j]=matriz1[i][j];
        for(int i=0;i<m1_n;i++)
            for(int j=0;j<m1_m;j++)
                matriz1[i][j]=0;

        for(int i=0;i<m2_n;i++){cout<<endl;
            for(int j=0;j<m1_m;j++){
                for(int k=0;k<m1_m;k++){
                    cout<<"("<<matrizaux[j][k]<<"*"<<matriz2[k][i]<<")";
                    if(k!=m1_m-1)cout<<"+";
                    matriz1[i][j]+=matrizaux[j][k]*matriz2[k][i];
                }cout<<" ";
            }
        }
    }else cout<<endl<<"o n de colunas da primeira deve ser igual ao n de linhas da segunda "<<m1_m<<m2_n<<endl;
}
