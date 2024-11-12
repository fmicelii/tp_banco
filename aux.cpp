#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    ifstream archivo;
    bool usuarioEncontrado = false, contraseñaCorrecta = false;
    string nusuario, contraseña, linea, usuarioBD, contraseñaBD;
    
    cout << "Ingresa tu nombre de usuario y tu contraseña. Si no están en la base de datos, se registrará un usuario con los datos que brindes." << endl;
    cout << "Usuario: ";
    getline(cin, nusuario);
    cout << "Contraseña: ";
    getline(cin, contraseña);

    archivo.open("bdd.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de la base de datos." << endl;
        return 1;
    }

    // Lectura del archivo y comparación
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, usuarioBD, ',');      // Extraer usuario
        getline(ss, contraseñaBD, ',');   // Extraer contraseña

        if (nusuario == usuarioBD) {
            usuarioEncontrado = true;
            if (contraseña == contraseñaBD) {
                contraseñaCorrecta = true;
                break; // Ambos son correctos, salir del bucle
            }
        }
    }
    archivo.close();

    // Comprobar resultados
    if (usuarioEncontrado) {
        if (contraseñaCorrecta) {
            cout << "Felicidades, tu sesión fue iniciada correctamente." << endl;
        } else {
            cout << "Pusiste mal la contraseña." << endl;
        }
    } else {
        cout << "No estás en la base de datos, ¡ya te registramos!" << endl;
        ofstream archivoRegistro("bdd.txt", ios::app);
        if (archivoRegistro.is_open()) {
            archivoRegistro << nusuario << "," << contraseña << ",." << endl;
            archivoRegistro.close();
        } else {
            cout << "Error al abrir el archivo para registrar el usuario." << endl;
        }
    }
}
