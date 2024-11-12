#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Estructura para representar un movimiento
struct Movimiento
{
};

// Estructura para representar un plazo fijo
struct PlazoFijo
{
};

// Estructura para representar una cuenta bancaria
struct Cuenta
{
    string nusuario, contrasenia;
    // Datos de la cuenta bancaria
    vector<Movimiento> movimientos;
    vector<PlazoFijo> plazos_fijos;
    int cantidad_dolares=0, saldo_en_cuenta=0;
};

// Función para mostrar el menú principal
void menu_principal(Cuenta usuario)
{
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nusuario << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo_en_cuenta << endl;
    cout << "Dólares: USD$ " << usuario.cantidad_dolares << endl;
    cout << "Plazos fijos armados: " << usuario.plazos_fijos.size() << endl;
    cout << endl;
    cout << "1 - Ingresar efectivo." << endl;
    cout << "2 - Retirar efectivo." << endl;
    cout << "3 - Comprar y/o vender dólares." << endl;
    cout << "4 - Retirar dólares." << endl;
    cout << "5 - Armar plazo fijo." << endl;
    cout << "6 - Cancelar plazo fijo." << endl;
    cout << "7 - Pedir préstamo." << endl;
    cout << "8 - Ver movimientos." << endl;
    cout << "9 - Actualizar datos." << endl;
    cout << "10 - Salir del sistema." << endl;
    cout << endl;
    cout << "Elegir una opcion del menú: " << endl;
}

// 1
void ingresar_efectivo(Cuenta &usuario, int opcion) {
    int monto_ingresado;
    cout<<"ingrese la cantidad de efectivo que desea ingresar:"<<endl;
    cin>>monto_ingresado;
    usuario.saldo_en_cuenta+=monto_ingresado;
}

// 2
void retirar_efectivo(Cuenta &usuario, int opcion) {
    int monto_a_retirar;
    cout<<"ingrese la cantidad de efectivo que desea retirar(multiplo de 100):"<<endl;
    cin>>monto_a_retirar;
    if(monto_a_retirar>usuario.saldo_en_cuenta){
        cout<<"error"<<endl;
    }
    else if(monto_a_retirar%100!=0){
        cout<<"error"<<endl;
    }
    else{
        usuario.saldo_en_cuenta-=monto_a_retirar;
        for(int i=0;(1000/monto_a_retirar)<=1.0;i++){
            cout<<"billete de 1000"<<endl;
            monto_a_retirar-=1000;}
        for(int i=0;(500/monto_a_retirar)<=1.0;i++){
            cout<<"billete de 500"<<endl;
            monto_a_retirar-=500;}
        for(int i=0;(200/monto_a_retirar)<=1.0;i++){
            cout<<"billete de 200"<<endl;
            monto_a_retirar-=200;}
        for(int i=0;(100/monto_a_retirar)<=1.0;i++){
            cout<<"billete de 100"<<endl;
            monto_a_retirar-=100;}                        
    }
}

// 3
void manejar_dolares(Cuenta &usuario, int opcion) {

}

// 4
void retirar_dolares(Cuenta &usuario, int opcion) {}

// 5
void armar_plazo_fijo(Cuenta &usuario, int opcion) {}

// 6
void cancelar_plazo_fijo(Cuenta &usuario, int opcion) {}

// 7
void pedir_prestamo(Cuenta &usuario, int opcion) {}

// 8
void ver_movimientos(Cuenta usuario) {}

// 9
void actualizar_datos(Cuenta &usuario, int opcion) {}

int main()
{
    vector <Cuenta> usuarios;
    Cuenta usuario;
    int opcion;
    ifstream archivo;
    bool usuarioEncontrado = false, contraseñaCorrecta = false, sesion1=true;
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
            sesion1=true;
        } else {
            cout << "Pusiste mal la contraseña." << endl;
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
    
    if(sesion1){
        while (opcion != 10){
        menu_principal(usuario);
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            ingresar_efectivo(usuario, opcion);
            break;
        case 2:
            retirar_efectivo(usuario, opcion);
            break;
        case 3:
            manejar_dolares(usuario, opcion);
            break;
        case 4:
            retirar_dolares(usuario, opcion);
            break;
        case 5:
            armar_plazo_fijo(usuario, opcion);
            break;
        case 6:
            cancelar_plazo_fijo(usuario, opcion);
            break;
        case 7:
            pedir_prestamo(usuario, opcion);
            break;
        case 8:
            ver_movimientos(usuario);
            break;
        case 9:
            actualizar_datos(usuario, opcion);
            break;
        case 10:
            cout << "Gracias por utilizar nuestro sistema " << usuario.nusuario << ", vuelva pronto." << endl;
            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
        }

    }
    
}
