// =========================================================
// File: Act4.3.cpp
// Author: Iram Kim Pichardo - A01710231
// Date: 10/11/2023
// =========================================================


#include <vector>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

map<char, vector<char>> adjList;

//Pregunta al usuario que ingrese en el input todas las relaciones de nodos escritas como: "(A,B)".
//Complejidad: 0(n)
void ingresarRelaciones(){
    string relacion;
    cin >> relacion;
    while(relacion != "****"){
        char nodo1 = toupper(relacion[1]); // Convertir a mayúscula
        char nodo2 = toupper(relacion[3]); // Convertir a mayúscula
        if(adjList.find(nodo1) == adjList.end()){
            adjList[nodo1] = vector<char>();
        }
        if(adjList.find(nodo2) == adjList.end()){
            adjList[nodo2] = vector<char>();
        }
        adjList[nodo1].push_back(nodo2);
        adjList[nodo2].push_back(nodo1);
        cin >> relacion;
    }
}

//Pregunta al usuario que ingrese en el input todos los nodos escritos como: "A,B,C,D".
//Complejidad: 0(n)
void ingresarNodos(){
    string nodos;
    cin >> nodos;
    stringstream ss(nodos);
    string nodo;
    while(getline(ss, nodo, ',')){
        char nodoChar = nodo[0];
        if(adjList.find(nodoChar) == adjList.end()){
            adjList[nodoChar] = vector<char>();
        }
    }
}

//Cuenta el numero de Acorns en el grafo
//Complejidad: 0(n)
int contarAcorns(){
    int contadorAcorns = 0;
    for(auto& pair : adjList){
        if(pair.second.empty()){
            contadorAcorns++;
        }
    }
    return contadorAcorns;
}

//Realiza un DFS para contar el numero de arboles en el grafo
//Complejidad: 0(n + m)
void DFS(char nodo, map<char, bool>& visitado){
    visitado[nodo] = true;
    for(char adj : adjList[nodo]){
        if(!visitado[adj]){
            DFS(adj, visitado);
        }
    }
}

//Cuenta el numero de arboles en el grafo
//Complejidad O(n + m)
int contarArboles(){
    map<char, bool> visitado;
    int contadorArboles = 0;
    for(auto& pair : adjList){
        if(!pair.second.empty() && !visitado[pair.first]){
            contadorArboles++;
            DFS(pair.first, visitado);
        }
    }
    return contadorArboles;
}


int main(){
    ingresarRelaciones();
    ingresarNodos();
    int acorns = contarAcorns();
    int arboles = contarArboles();
    cout << "There are " << arboles << " tree(s) and " << acorns << " acorn(s)." << endl;
    return 0;
}


//Total de complejidad: 0(n + m)