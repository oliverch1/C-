
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib> // "clear":linux ; "cls":windows
#include<limits> // presionar una tecla
#include<thread> //time
#include<chrono> //time

using namespace std;

struct Barco {
    string nombre;
    int prioridad; // numero entero; cuanto menor es; mayor prioridad tendra, no se repite.
    char accion; // A:atracar; P:partir
};

int menu(int opc) {
    system("clear");
    cout << "MENU DE OPCIONES" << endl;
    cout << "1. Reconocimiento de embarcacion" << endl;
    cout << "2. Realizar Accion" << endl;
    cout << "3. Visualizar el estado del puerto" << endl;
    cout << "4. Salir" << endl;
    cout << endl;
    cout << "Ingrese opcion: "; cin >> opc;
    return opc;
}

bool Validacion(int num, vector<Barco> Barcos_Verificar, bool& validacion) { //validacion para evitar que la prioridad se repita
    for (const auto& barco : Barcos_Verificar) {
        if (barco.prioridad == num) {
            cout << "la prioridad ya existe, espere para volver a ingresar otra prioridad ...." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            validacion = false;
            break;
        }
        else {
            continue;
        }
    }
    return validacion;
}

void Agregar_Barcos(vector<Barco>& Barcos_Cola, const Barco& Nuevo_Barco) {
    if (Barcos_Cola.empty()) { //vector vacio, se agrega barco
        Barcos_Cola.push_back(Nuevo_Barco);
    }
    else { // vector no vacio, segun prioridad insertar el barco al vector
        auto indice = Barcos_Cola.begin();
        while (indice != Barcos_Cola.end() && indice->prioridad < Nuevo_Barco.prioridad) {
            indice++;
        }
        Barcos_Cola.insert(indice, Nuevo_Barco);
    }
}

void Procedimiento_Reconocimiento(vector<Barco>& Barcos_Atracar, vector<Barco>& Barcos_Partir) {
    bool validacion;
    Barco Nuevo_Barco;
    do {
        system("clear");
        validacion = true;
        cout << "Ingrese nombre de la embarcacion: "; cin >> Nuevo_Barco.nombre;
        cout << "Ingrese la prioridad (ejemplo: 4): "; cin >> Nuevo_Barco.prioridad;
        cout << "Ingrese la accion (A:atracar; P:partir): "; cin >> Nuevo_Barco.accion;
        if (Nuevo_Barco.accion == 'A') {
            if (Validacion(Nuevo_Barco.prioridad, Barcos_Atracar, validacion)) { //barcos a atracar
                Agregar_Barcos(Barcos_Atracar, Nuevo_Barco);
                cout << "Embarcacion agregada correctamente para Atracar ...." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
            else {
                continue;
            }
        }
        else 
            if (Nuevo_Barco.accion == 'P') { //barcos a partir
                if (Validacion(Nuevo_Barco.prioridad, Barcos_Partir, validacion)) {
                    Agregar_Barcos(Barcos_Partir, Nuevo_Barco);
                    cout << "Embarcacion agregada correctamente para Partir ...." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
                else {
                    continue;
                }
            }  
    } while (!validacion); // si la validacion falla, vuelve a pedir datos.
    
}

void Procedimiento_Accion(vector<Barco>& Barcos_Atracar, vector<Barco>& Barcos_Partir) {
    if (!Barcos_Atracar.empty()) {
        cout << "El barco " << Barcos_Atracar.front().nombre << " está atracando." << endl;
        Barcos_Atracar.erase(Barcos_Atracar.begin()); // Elimina el primer barco
    } 
    else 
        if (!Barcos_Partir.empty()) {
            cout << "El barco " << Barcos_Partir.front().nombre << " está partiendo." << endl;
            Barcos_Partir.erase(Barcos_Partir.begin()); // Elimina el primer barco
        } 
        else {
            // Si ambos vectores están vacíos
            cout << "No hay barcos para atender." << endl;
        }
    this_thread::sleep_for(chrono::seconds(2));
}

void Visualizar_Estado_Puerto(const vector<Barco>& Barcos_Atracar, const vector<Barco>& Barcos_Partir) {
    system("clear");
    cout << "------------- MOSTRANDO EL ESTADO ACTUAL DEL PUERTO --------------" << endl;
    cout << "BARCOS A ATRACAR ..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    if (Barcos_Atracar.empty()) {
        cout << "No hay barcos por atracar" << endl;
    }
    else {
        for (const auto& barco: Barcos_Atracar) {
            cout << "Nombre: " << barco.nombre << endl;
            cout << "Prioridad: " << barco.prioridad << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    cout << endl;
    cout << "BARCOS A PARTIR ..." << endl;
    this_thread::sleep_for(chrono::seconds(1));
    if (Barcos_Partir.empty()) {
        cout << "No hay barcos para partir" << endl;
    }
    else {
        for (const auto& barco : Barcos_Partir) {
            cout << "Nombre: " << barco.nombre << endl;
            cout << "Prioridad: " << barco.prioridad << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
    cout << "Presione una tecla para continuar ....."; 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void Salir () {
    cout << "Saliendo del programa..." << endl;
    exit(0);
}

int main() {
    int opc = 0;
    vector<Barco> Barcos_Atracar;
    vector<Barco> Barcos_Partir;
    do {
        opc = menu(opc);
        switch (opc) {
            case 1:
                Procedimiento_Reconocimiento(Barcos_Atracar, Barcos_Partir);
                break;
            case 2:
                Procedimiento_Accion(Barcos_Atracar, Barcos_Partir);
                break;
            case 3:
                Visualizar_Estado_Puerto(Barcos_Atracar, Barcos_Partir);
                break;
            case 4:
                Salir();
                break;
            default:
                cout << "error, opcion no valida" << endl;
                opc = 0;
                this_thread::sleep_for(chrono::seconds(1));
        }
    }while(opc>=0 && opc<5);

    return 0;
}
