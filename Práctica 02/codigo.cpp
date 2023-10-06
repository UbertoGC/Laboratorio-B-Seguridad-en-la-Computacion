#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
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
int MOD(int a, int b){
    if(a<0)
        return b-MOD(-a,b);
    return(a%b); 
}
string Vignere(string texto, string palabra, int n_mod = 27){
    int j=0;
    string traducido = "";
    for (int i = 0; i < texto.size(); i++){
        if(j == palabra.size()){
            j = 0;
        }

        int de_texto = 0;
        if(texto[i] <= 'N'){
            de_texto = int(texto[i]) - 'A';
        }
        else if(texto[i] == char(165)){
            de_texto = int('O') - 'A';
        }
        else{
            de_texto = int(texto[i]) - 'A' + 1;
        }

        int de_palabra = 0;
        if(palabra[j] <= 'N'){
            de_palabra = int(palabra[j]) - 'A';
        }
        else if(palabra[j] == char(-47)){
            de_palabra = int('O') - 'A';
        }
        else{
            de_palabra = int(palabra[j]) - 'A' + 1;
        }

        int data = MOD(de_texto + de_palabra, n_mod);
        if(data <= 13){
            traducido += char(data + 'A');
        }
        else if(data == 14){
            traducido += char(-47);
        }
        else{
            traducido += char(data + 'A' - 1);
        }
        j++;
    }
    return traducido;
}
string Des_Vignere_clave(string texto, string palabra, int n_mod = 27){
    int j=0;
    string traducido = "";
    for (int i = 0; i < texto.size(); i++){
        if(j == palabra.size()){
            j = 0;
        }
        int de_texto = 0;
        if(texto[i] <= 'N'){
            de_texto = int(texto[i]) - 'A';
        }
        else if(texto[i] == char(-47)){
            de_texto = int('O') - 'A';
        }
        else{
            de_texto = int(texto[i]) - 'A' + 1;
        }

        int de_palabra = 0;
        if(palabra[j] <= 'N'){
            de_palabra = int(palabra[j]) - 'A';
        }
        else if(palabra[j] == char(165)){
            de_palabra = int('O') - 'A';
        }
        else{
            de_palabra = int(palabra[j]) - 'A' + 1;
        }

        int data = MOD(de_texto - de_palabra, n_mod);
        if(data <= 13){
            traducido += char(data + 'A');
        }
        else if(data == 14){
            traducido += char(-47);
        }
        else{
            traducido += char(data + 'A' - 1);
        }
        j++;
    }
    return traducido;
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
vector<pair<char,int>> frecuencias(string texto){
    char letra;
    int contador[27]{0};
    map<char, int> frecuencia;
    for (int i = 0; i < texto.size(); i++){
        if(texto[i] == char(-47)){
            contador[14]++;
        }
        else if(texto[i] <= 'N'){
            contador[texto[i]-'A']++;
        }
        else{
            contador[texto[i]-'A'+1]++;
        }
    }
    for (int i = 0; i < 27; i++){
        if(i == 14){
            frecuencia.insert({char(-47),contador[i]});
        }
        else if(i < 14){
            frecuencia.insert({char(i+65),contador[i]});
        }
        else{
            frecuencia.insert({char(i+64),contador[i]});
        }
    }   
    vector<pair<char,int>> convertir;
    for (const auto &item : frecuencia)
        convertir.emplace_back(item);
    pair<char,int> primero = *convertir.begin();
    convertir.erase(convertir.begin(),convertir.begin()+1);
    convertir.insert(convertir.begin()+14,primero);
    return convertir;
}
int main(){
    setlocale(LC_ALL, "");
    string original = "CREERQUEESPOSIBLEESELPASONUMEROUNOHACIAELEXITODESPERTARSEYPENSARENALGOPOSITIVOPUEDECAMBIARELTRANSCURSODETODOELDIANOERESLOSUFICIENTEMENTEVIEJOCOMOPARANOINICIARUNNUEVOCAMINOHACIATUSSUENOSLEVANTATECADAMANANACREYENDOQUEVASAVIVIRELMEJORDIADETUVIDA";
    cout<<"Cifrado con POSITIVO"<<endl;
    string cifrado1 = Vignere(original, "POSITIVO");
    cout<<cifrado1<<endl;
    vector<pair<char,int>> frecuencia1 = frecuencias(cifrado1);
    cout<<"Repeticion con clave POSITIVO"<<endl;
    for (int i = 0; i < 26; i++){
        cout<<frecuencia1[i].first<<" : "<<frecuencia1[i].second<<endl;
    }
    string cifrado2 = Vignere(original, "HIELO");
    vector<pair<char,int>> frecuencia2 = frecuencias(cifrado2);
    cout<<"Repeticion con clave HIELO"<<endl;
    for (int i = 0; i < 26; i++){
        cout<<frecuencia2[i].first<<" : "<<frecuencia2[i].second<<endl;
    }
    string cifrado3 = Vignere(original, "MAR");
    vector<pair<char,int>> frecuencia3 = frecuencias(cifrado3);
    cout<<"Repeticion con clave MAR"<<endl;
    for (int i = 0; i < 26; i++){
        cout<<frecuencia3[i].first<<" : "<<frecuencia3[i].second<<endl;
    }
    string descifrado1 = Des_Vignere_clave("WPIXHVYYOSRTECSZBEEGHUUFWRWTZGRWUFSRIWESSXVOHAIHOHWWHCWHUZOBOZEAOYBMCRLTEYOTI","HIELO");
    cout<<descifrado1<<endl;
    string descifrado2 = Des_Vignere_clave("XHGDQESDMPKÑDEEDKNGJZPFJSUIFZOLFCINFJCESVZTGBFXCIUDAYNUUDIZYWWZBEYNVQWIVUNKZEPHDODQUZZLBDNDRWTHQSERÑIVMLERCMGIFLSORZXTSDIGLOXQSDJHWVCIWQXQJCKMBPOKMPSKMUVIMNJDNBLCSZHXHNYYUIXDBSOXHZLXWVGDJGXHWLTDWKÑSAQIMZLNBVMLXHUOQQXIQGWGUFTWKZKMOKUDNINSIFJDUOZIJBSVVOWFAIEÑGYOWPSOAP","UNODELOSMASGRANDESCRIPTOGRAFOS");
    cout<<descifrado2<<endl;
    return 0;
}