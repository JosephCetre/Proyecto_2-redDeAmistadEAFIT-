// Proyecto_2-redDeAmistadEAFIT-

//Joseph Buenaños
//Cristian Buitrago 


#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

// Red social para gestionar amistades
class GrafoNoDirigido {
private:
    unordered_map<string, vector<string>> amigos;
    int totalConexiones;

    // DFS para recorrer amigos
    void buscarProfundidad(const string& persona, unordered_set<string>& yaVistos) {
        yaVistos.insert(persona);
        cout << persona << " ";

        for (const string& amigo : amigos[persona]) {
            if (yaVistos.find(amigo) == yaVistos.end()) {
                buscarProfundidad(amigo, yaVistos);
            }
        }
    }

public:
    // Constructor
    GrafoNoDirigido() {
        totalConexiones = 0;
    }

    // Agregar una persona a la red
    void agregarPersona(const string& nombre) {
        if (amigos.find(nombre) == amigos.end()) {
            amigos[nombre] = vector<string>();
            cout << nombre << " fue agregado a la red.\n";
        } else {
            cout << nombre << " ya estaba en la red.\n";
        }
    }

    // Conectar dos personas (amistad mutua)
    void hacerAmigos(const string& persona1, const string& persona2) {
        // Crear personas si no existen
        if (!existe(persona1)) agregarPersona(persona1);
        if (!existe(persona2)) agregarPersona(persona2);

        // Evitar conexiones duplicadas
        auto& amigosPersona1 = amigos[persona1];
        if (find(amigosPersona1.begin(), amigosPersona1.end(), persona2) == amigosPersona1.end()) {
            // Hacer amistad mutua
            amigos[persona1].push_back(persona2);
            amigos[persona2].push_back(persona1);
            totalConexiones++;
            cout << persona1 << " y " << persona2 << " son amigos ahora.\n";
        } else {
            cout << persona1 << " y " << persona2 << " ya eran amigos.\n";
        }
    }

    // Mostrar la red completa
    void verRed() {
        cout << "\n== Red Social ==\n";
        for (const auto& item : amigos) {
            cout << item.first << " es amigo de: ";
            for (const string& amigo : item.second) {
                cout << amigo << ", ";
            }
            cout << "\n";
        }
    }

    // Verificar si una persona existe
    bool existe(const string& nombre) {
        return amigos.find(nombre) != amigos.end();
    }

    // Verificar si dos personas son amigas
    bool sonAmigos(const string& p1, const string& p2) {
        if (!existe(p1) || !existe(p2)) return false;
        const auto& listaAmigos = amigos[p1];
        return find(listaAmigos.begin(), listaAmigos.end(), p2) != listaAmigos.end();
    }

    // Contar amigos de una persona
    int cuantosAmigos(const string& nombre) {
        if (existe(nombre)) {
            return amigos[nombre].size();
        }
        return -1;
    }

    // Obtener total de personas
    int totalPersonas() {
        return amigos.size();
    }

    // Obtener total de amistades
    int totalAmistades() {
        return totalConexiones;
    }

    // Recorrer amigos en anchura
    void recorridoAnchura(const string& inicio) {
        if (!existe(inicio)) {
            cout << "La persona no existe.\n";
            return;
        }

        unordered_set<string> visitados;
        queue<string> cola;

        visitados.insert(inicio);
        cola.push(inicio);

        cout << "\nAmigos de " << inicio << " (busqueda ancha):\n";

        while (!cola.empty()) {
            string actual = cola.front();
            cola.pop();
            cout << actual << " ";

            for (const string& amigo : amigos[actual]) {
                if (visitados.find(amigo) == visitados.end()) {
                    visitados.insert(amigo);
                    cola.push(amigo);
                }
            }
        }
        cout << "\n";
    }

    // Recorrer amigos en profundidad
    void recorridoProfundidad(const string& inicio) {
        if (!existe(inicio)) {
            cout << "La persona no existe.\n";
            return;
        }

        unordered_set<string> visitados;
        cout << "\nAmigos de " << inicio << " (busqueda profunda):\n";
        buscarProfundidad(inicio, visitados);
        cout << "\n";
    }
};

// Main de ejecución principal
int main() {
    GrafoNoDirigido redSocial;

    cout << "=== Red Social (Proyecto Joseph y Cristian) ===\n\n";

    // Agregar personas
    cout << "Agregando gente a la red...\n";
    redSocial.agregarPersona("Joseph");
    redSocial.agregarPersona("Cristian");
    redSocial.agregarPersona("Sofia");
    redSocial.agregarPersona("Miguel");
    redSocial.agregarPersona("Laura");

    // Conectar amigos
    cout << "\nConectando amistades...\n";
    redSocial.hacerAmigos("Joseph", "Cristian");
    redSocial.hacerAmigos("Joseph", "Sofia");
    redSocial.hacerAmigos("Cristian", "Miguel");
    redSocial.hacerAmigos("Sofia", "Laura");
    redSocial.hacerAmigos("Miguel", "Laura");

    // Mostrar la red
    redSocial.verRed();

    // Información de la red
    cout << "\n=== Datos de la Red ===\n";
    cout << "Total de personas: " << redSocial.totalPersonas() << "\n";
    cout << "Total de amistades: " << redSocial.totalAmistades() << "\n";
    
    cout << "Amigos de Joseph: " << redSocial.cuantosAmigos("Joseph") << "\n";
    cout << "Amigos de Cristian: " << redSocial.cuantosAmigos("Cristian") << "\n";
    
    cout << "\nJoseph y Cristian son amigos? " 
         << (redSocial.sonAmigos("Joseph", "Cristian") ? "Si" : "No") << "\n";
    cout << "Joseph y Miguel son amigos? " 
         << (redSocial.sonAmigos("Joseph", "Miguel") ? "Si" : "No") << "\n";

    // Mostrar conexiones
    redSocial.recorridoAnchura("Joseph");
    redSocial.recorridoProfundidad("Cristian");

    return 0;
}