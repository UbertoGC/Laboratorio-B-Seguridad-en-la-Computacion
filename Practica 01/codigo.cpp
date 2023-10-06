#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <algorithm>
#include <vector>
#include <Windows.h>
#include <cstdio>
#include <string>
#include <io.h>
#include <fcntl.h>
using namespace std;
int MCD(list<int> numeros){
    int mcd, residuo;
    for (auto it:numeros){
        if(it == *(numeros.begin())){
            mcd = it;
        }
        else{
            do
            {
                residuo = mcd % it;
                mcd = it;
                it = residuo;
            } while (residuo != 0);
        }
    }
    return mcd;
}
map<char, int> frecuencias(string archivo){
    ifstream documento(archivo);
    char letra;
    int contador[26]{0};
    map<char, int> frecuencia;
    while (!documento.eof()){
        documento>>letra;
        contador[letra-'A']++;
    }
    documento.close();
    for (int i = 0; i < 26; i++)
        frecuencia.insert({char(i+65),contador[i]});
    return frecuencia;
}
map<string,pair<int,list<int>>> cadenas_repetidas(string texto){
    map<string,pair<int,list<int>>> resultados;
    string cadena;
    for (int i = 0; i < texto.size()-2; i++){
        cadena="";
        cadena+=texto[i];
        cadena+=texto[i+1];
        cadena+=texto[i+2];
        string cadena2;
        if(resultados.find(cadena) != resultados.end()){
            resultados[cadena].first++;
            resultados[cadena].second.push_back(i);
        }
        else{
            list<int> ubicacion1;
            ubicacion1.push_back(i);
            resultados.insert({cadena,{1,ubicacion1}});
        }
    }
    return resultados;
}
void kasiski(string texto){
    map<string,pair<int,list<int>>> cadenas = cadenas_repetidas(texto);
    list<int> datos;
    for (auto it:cadenas){
        if(it.second.first > 1){
            cout<<it.first<<" --- "<<it.second.first<<endl;
            auto i = it.second.second.begin();
            auto j = it.second.second.begin();
            i++;
            cout<<"|";
            for (; i != it.second.second.end(); i++){
                int diferencia = *i - *j;
                cout<<diferencia<<"|";
                datos.push_back(diferencia);
                j++;
            }
            cout<<endl;
        }
    }
}
string hexadecimal(int n){
    string r="";
    int resultado, residuo;
    int digitos[20];
    int i=0;
    do{
        residuo = n%16;
        resultado = n / 16;
        digitos[i] = residuo;
        n = resultado;
        i++;
    }while(resultado > 15);
    digitos[i] = resultado;
    for (int j = i; j >= 0; j--){
        if(digitos[j] > 9){
            r += char('A' + digitos[j] - 10);
        }
        else{
            r += to_string(digitos[j]);
        }
    }
    return r;
}
void UNICODE_8(string texto){
    ofstream documento("unicode8_traduccion.txt");
    for (int i = 0; i < texto.size(); i++){
        int ascii = int(texto[i]);
        string conversion = hexadecimal(ascii);
        documento<<conversion;
    }
    documento.close();
}
string ANADIENDO_AQUI(string texto){
    ofstream documento("anadiendoaqui.txt");
    string nuevo_texto="";
    for (int i = 0; i < texto.size(); i++){
        if(i%20 == 19){
            nuevo_texto+="AQUI";
        }
        nuevo_texto+=texto[i];
    }
    while (nuevo_texto.size() % 4){
        int aleatorio = rand()%26 + 'A';
        nuevo_texto+=char(aleatorio);
    }
    documento<<nuevo_texto;
    documento.close();
    return nuevo_texto;
}
int main(){
    string archivo = "HERALDOSNEGROS_pre.txt";
    map<char, int> contador;
    contador = frecuencias(archivo);
    vector<pair<char,int>> convertir;
    for (const auto &item : contador) {
        convertir.emplace_back(item);
    }
    sort(convertir.begin(),convertir.end(),[](const auto &x,const auto &y){return x.second > y.second;});
    /**/
    cout<<"CARACTERES CON MAYOR FRECUENCIA: "<<endl;
    for (int i = 0; i < 5; i++){
        cout<<convertir[i].first<<": "<<convertir[i].second<<endl;
    }
    string texto = "";
    char letra;
    ifstream documento(archivo);
    while (!documento.eof()){
        documento>>letra;
        texto+=letra;
    }
    documento.close();
    /**/
    cout<<endl<<"METODO KASISKI: "<<endl;
    kasiski(texto);
    /**/
    cout<<endl<<"CIFRADO UNICODE-8: "<<endl;
    UNICODE_8(texto);
    convertir.clear();
    contador.clear();
    contador = frecuencias("unicode8_traduccion.txt");
    for (const auto &item : contador) {
        convertir.emplace_back(item);
    }
    sort(convertir.begin(),convertir.end(),[](const auto &x,const auto &y){return x.second > y.second;});
    cout<<"CARACTERES CON MAYOR FRECUENCIA: "<<endl;
    for (int i = 0; i < 5; i++){
        cout<<convertir[i].first<<": "<<convertir[i].second<<endl;
    }
    string texto2 = "";
    documento.open("unicode8_traduccion.txt");
    while (!documento.eof()){
        documento>>letra;
        texto2+=letra;
    }
    documento.close();
    cout<<"METODO KASISKI: "<<endl;
    kasiski(texto2);
    /**/
    cout<<endl<<"ANADIENDO LA CADENA AQUI: "<<endl;
    string texto3 = ANADIENDO_AQUI(texto);
    convertir.clear();
    contador.clear();
    contador = frecuencias("anadiendoaqui.txt");
    for (const auto &item : contador) {
        convertir.emplace_back(item);
    }
    sort(convertir.begin(),convertir.end(),[](const auto &x,const auto &y){return x.second > y.second;});
    cout<<"CARACTERES CON MAYOR FRECUENCIA: "<<endl;
    for (int i = 0; i < 5; i++){
        cout<<convertir[i].first<<": "<<convertir[i].second<<endl;
    }
    cout<<"METODO KASISKI: "<<endl;
    kasiski(texto3);
    return 0;
}