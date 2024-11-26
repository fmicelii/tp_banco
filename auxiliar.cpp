#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
struct movimiento
{
    int sueldo_anterior,sueldo_posterior;
};

// Estructura para representar un plazo fijo
struct PlazoFijo
{
    int plata_inicial;
    int dias;
    int interes;
    int total;
    bool vigente;

};

// Estructura para representar una cuenta bancaria
struct Cuenta
{
    // Datos de la cuenta bancaria
    string nusuario, contrasenia;
    vector<movimiento> movimientos;
    vector<PlazoFijo> plazos_fijos;
    int cantidad_dolares=0, saldo_en_cuenta=0;
};
int main() {
    vector <Cuenta> usuarios;
    movimiento movimientoto;
    vector <movimiento> ingresos;
    vector <movimiento> retiros;
    vector <movimiento> prestamos;
    vector <movimiento> ingresos_dolares;
    vector <movimiento> retiros_dolares;
    vector <movimiento> ventas_dolares;
    Cuenta usuario;
    int opcion;
    //int salditoBD = stoi(saldoBD);
    ifstream archivo;
    bool usuarioEncontrado = false, contraseñaCorrecta = false, sesion1=true;
    string nusuario, contraseña, linea, usuarioBD, contraseñaBD,saldoBD, dolaresBD,cantidad_plazo_fijosBD;
    
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
        getline(ss, saldoBD, ',');
        getline(ss, dolaresBD, ',');
        getline(ss, cantidad_plazo_fijosBD, ',');


        if (nusuario == usuarioBD) {
            usuarioEncontrado = true;
            if (contraseña == contraseñaBD) {
                contraseñaCorrecta = true;
                //aca extraer los datos de el txt

                break; // Ambos son correctos, salir del bucle
            }
        }
    }
    archivo.close();

    // Comprobar resultados
    if (usuarioEncontrado) {
        if (contraseñaCorrecta) {
            //usuario.saldo_en_cuenta+=salditoBD;
            cout << "Felicidades, tu sesión fue iniciada correctamente." << endl;
            cout<<saldoBD<<"-"<<dolaresBD;
            sesion1=true;
        } else {
            cout << "Pusiste mal la contraseña." << endl;
            sesion1=false;
            return 1;

        }
    } else {
        cout << "No estás en la base de datos, ¡ya te registramos!" << endl;
        ofstream archivoRegistro("bdd.txt", ios::app);
        if (archivoRegistro.is_open()) {
            archivoRegistro << nusuario << "," << contraseña << ",." << endl;
            archivoRegistro.close();
            sesion1=true;
            usuario.nusuario=nusuario;
            usuario.contrasenia=contraseña;
            usuarios.push_back(usuario);
        } else {
            cout << "Error al abrir el archivo para registrar el usuario." << endl;
        }
    }
}
