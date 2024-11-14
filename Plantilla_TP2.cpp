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
        while(monto_a_retirar>=1000){
            cout<<"billete de 1000"<<endl;
            monto_a_retirar-=1000;}
        while(monto_a_retirar>=500){
            cout<<"billete de 500"<<endl;
            monto_a_retirar-=500;}
        while(monto_a_retirar>=200){
            cout<<"billete de 200"<<endl;
            monto_a_retirar-=200;}
        while(monto_a_retirar>=100){
            cout<<"billete de 100"<<endl;
            monto_a_retirar-=100;}                       
    }
}

// 3
void manejar_dolares(Cuenta &usuario, int opcion) {
    int opcion1,cantidad_dolares_compra,cantidad_dolares_venta,cantidad_pesos_compra,cantidad_pesos_venta,dolares_sugeridos;
    bool condicion=true;
    while(condicion){
        cout<<"elija entre comprar y vender dolares:"<<endl
            <<"1.comprar dolares"<<endl
            <<"2.vender dolares"<<endl
            <<"3.salir"<<endl;
        cin>>opcion1;
        switch(opcion1){
        case 1:
            cout<<"Especifique cuantos dolares quiere comprar:"<<endl;
            cin>>cantidad_dolares_compra;
            cantidad_pesos_compra=cantidad_dolares_compra*1000;
            cout<<"La cantidad de pesos que le salio esta compra es: $"<<cantidad_pesos_compra<<endl;
            if(cantidad_pesos_compra<=usuario.saldo_en_cuenta){
                usuario.cantidad_dolares+=cantidad_dolares_compra;
                usuario.saldo_en_cuenta-=cantidad_pesos_compra;
            }
            else{
                dolares_sugeridos=usuario.saldo_en_cuenta/1000;
                cout<<"No cuenta con suficiente dinero para realizar esta operacion, le sugerimos la compra de: $"<<dolares_sugeridos<<" dolares debido a tu saldo en cuenta"<<endl;
            }
            break;
        case 2:
            cout<<"Especifique cuantos dolares quiere vender: "<<endl;
            cin>>cantidad_dolares_venta;
            cantidad_pesos_venta=cantidad_dolares_venta*1000;
            cout<<"La cantidad de pesos que se depositarán a tu cuenta por esta venta es: $"<<cantidad_pesos_venta<<endl;
            if(usuario.cantidad_dolares>=cantidad_dolares_venta){
                usuario.cantidad_dolares-=cantidad_dolares_venta;
                usuario.saldo_en_cuenta+=cantidad_pesos_venta;
            }
            else{
                cout<<"No cuenta con suficiente dolares para realizar esta operacion, le sugerimos la venta de: $"<<usuario.cantidad_dolares<<" dolares debido a tu cantidad de dolares en cuenta"<<endl;
            }
            break;
        case 3:
            condicion=false;
            break;    
    }
    }    
}

// 4
void retirar_dolares(Cuenta &usuario, int opcion) {}

// 5
void armar_plazo_fijo(Cuenta &usuario, int opcion) {
    /*
(Para la opción 5, tener en cuenta que un plazo fijo requiere como 
mínimo 30 días de plazo, se le deberá pedir al usuario que ingrese un 
monto de pesos que quiere invertir (menor o igual al saldo en cuenta) y 
los días que va a estar la plata en el plazo fijo. Teniendo ambos datos 
ingresados, deberemos calcular el interés generado con la siguiente 
operación: 
(Monto de pesos ingresados * días ingresados * 70) / 36500 
Se mostrara por pantalla la cantidad de pesos y días que ingreso, el 
interés que va a generar durante los días ingresados y el total de pesos 
que va a obtener (plata ingresada + interés). Para poder recibir el total 
de pesos, se deberá respetar el plazo de días puesto en la opción. 
Posteriormente se le descontará la plata puesta en el plazo fijo del 
saldo en cuenta. */
//falta devolverle la plata cuando pase el tiempo pero como lo vamos a ahcer cumpa
int want, wantdi, wantintere, totfin;
PlazoFijo auxinverse;
cout<<"ingresa el monto de pesos que qures invertir en el plazo fijo"<<endl;
cin>>want;
cout<<"ingresa la cantidad de dias que deseas que dure el plazo fijo"<<endl;
cin>>wantdi;
if(want> usuario.saldo_en_cuenta || wantdi < 30){
    cout<<"tus datos son incorrectos"<<endl;
    if(want > usuario.saldo_en_cuenta){
        cout<<"no tenes esa plata en tu cuenta, no te alcanza"<<endl;
    }
    if(wantdi<30){
        cout<<"tenes q pedir minimo 30 dias para tu plazo fijo"<<endl;
    }
}
else{
    usuario.saldo_en_cuenta-=want;
    wantintere=(want*wantdi*70)/36500;
    cout<<"ingresaste "<<want<<" $ en un plazo fijo de "<<wantdi<<" dias y generaste un interes de "<<wantintere<<endl;
    cout<<"al final de el plazo fijo obtendras "<<want + wantintere << " $"<<endl;
    totfin=want + wantintere;
    auxinverse.plata_inicial=want;
    auxinverse.dias=wantdi;
    auxinverse.interes=wantintere;
    auxinverse.total=totfin;
    auxinverse.vigente= false;
    //cuando se cumplan los dias cambiar a true
    usuario.plazos_fijos.push_back(auxinverse);
    
}


}

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
