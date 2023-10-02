#include <iostream>
#include <math.h>
using namespace std;
int MOD(int a, int b){
    if(a<0)
        return b-MOD(-a,b);
    return(a%b); 
}
int MCD(int x, int y){
    int a = max(x,y);
    int b = min(x,y);
    int resultado;
    do
    {
        resultado = b;
        b = a%b;
        a = resultado;
    } while (b!=0);
    return resultado;
}
int inversa_MOD_exponente(int base, int m, int r){
    int exponente = 0;
    while(MOD(pow(base,exponente),m) != r){
        exponente++;
    }
    return exponente;
}
int inverso_multiplicativo(int a, int b){
    if(MCD(a,b) == 1)
        for (int i = 1; i < b; i++){
            if(MOD(a*i,b)==1){
                return i;
            }
        }
    return -1;
}
int main(){
    int x, y, z, a;
    /*Actividad 1*/
    cout<<"Problema 1."<<endl;
    /*a)*/
    cout<<"a)"<<endl;
    cout<<MOD(-18,20)<<endl;
    /*b)*/
    cout<<"b)"<<endl;
    cout<<MOD(25,31)<<endl;
    /*c)*/
    cout<<"c)"<<endl;
    cout<<MOD(33,10)<<endl;
    /*d)*/
    cout<<"d)"<<endl;
    cout<<MOD(-9,6)<<endl;
    cout<<endl;
    /*Actividad 2*/
    cout<<"Problema 2."<<endl;
    cout<<inverso_multiplicativo(5,27)<<endl;
    cout<<endl;
    /*Actividad 3*/
    cout<<"Problema 3."<<endl;
    cout<<inversa_MOD_exponente(2,19,7)<<endl;
    cout<<endl;
    /*Actividad 4*/
    cout<<"Problema 4."<<endl;
    cout<<"Es numero par o impar y genera todos los restos del primo p"<<endl;
}