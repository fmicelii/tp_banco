#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Estructura para representar un movimiento
struct movimiento
{
    int sueldo_viejo,sueldo_actual;
};

// Estructura para representar un plazo fijo
struct PlazoFijo
{
    int monto_inicial;
    int dias;
    int intereses;
    int total;
    bool sigue_vigente;

};

// Estructura para representar una cuenta bancaria
struct Cuenta
{
    string nombre_usuario, contrasenia;
    vector<movimiento> movimientos;
    vector<PlazoFijo> plazos_fijos;
    int cant_dolares=0, saldo=0;
};

// Función para mostrar el menú principal
void menu_principal(Cuenta usuario)
{
    cout << endl;
    cout << "Bienvenido/a al sistema bancario, " << usuario.nombre_usuario << endl;
    cout << "Saldo en cuenta: $ " << usuario.saldo << endl;
    cout << "Dólares: USD$ " << usuario.cant_dolares << endl;
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


void ingresar_efectivo(Cuenta &usuario,movimiento mov_generico, vector <movimiento> &ingresos){
    int monto_a_ingresar;
    cout<<"ingrese la cantidad de efectivo que desea ingresar:"<<endl;
    cin>>monto_a_ingresar;
    mov_generico.sueldo_viejo=usuario.saldo;
    usuario.saldo+=monto_a_ingresar;
    mov_generico.sueldo_actual=usuario.saldo;
    ingresos.push_back(mov_generico);

}

void retirar_efectivo(Cuenta &usuario,movimiento mov_generico, vector <movimiento> &retiros) {
    int monto_a_retirar;
    cout<<"ingrese la cantidad de efectivo a retirar(multiplo de 100):"<<endl;
    cin>>monto_a_retirar;
    if(monto_a_retirar>usuario.saldo){
        cout<<"error"<<endl;
    }
    else if(monto_a_retirar%100!=0){
        cout<<"error"<<endl;
    }
    else{
        mov_generico.sueldo_viejo=usuario.saldo;
        usuario.saldo-=monto_a_retirar;
        mov_generico.sueldo_actual=usuario.saldo;
        retiros.push_back(mov_generico);
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


void dolares(Cuenta &usuario, movimiento mov_generico, vector <movimiento> &ingresos_dolares,vector <movimiento> &ventas_dolares) {
    int opcion1,cant_dolares_compra,cant_dolares_venta,cant_pesos_compra,cant_pesos_venta,dolares_sugeridos;
    bool cond =true;
    while(cond){
        cout<<"elija entre comprar y vender dolares:"<<endl
            <<"1.comprar dolares"<<endl
            <<"2.vender dolares"<<endl
            <<"3.salir"<<endl;
        cin>>opcion1;
        switch(opcion1){
        case 1:
            cout<<"Especifique cuantos dolares quiere comprar:"<<endl;
            cin>>cant_dolares_compra;
            cant_pesos_compra=cant_dolares_compra*1000;
            cout<<"La cantidad de pesos que le salio esta compra es: $"<<cant_pesos_compra<<endl;
            if(cant_pesos_compra<=usuario.saldo){
                mov_generico.sueldo_viejo=usuario.cant_dolares;
                usuario.cant_dolares+=cant_dolares_compra;
                mov_generico.sueldo_actual=usuario.cant_dolares;
                ingresos_dolares.push_back(mov_generico);
                usuario.saldo-=cant_pesos_compra;
            }
            else{
                dolares_sugeridos=usuario.saldo/1000;
                cout<<"No cuenta con suficiente dinero para realizar esta operacion, le sugerimos la compra de: $"<<dolares_sugeridos<<" dolares debido a tu saldo en cuenta"<<endl;
            }
            break;
        case 2:
            cout<<"Especifique cuantos dolares quiere vender: "<<endl;
            cin>>cant_dolares_venta;
            cant_pesos_venta=cant_dolares_venta*1000;
            cout<<"La cantidad de pesos que se depositarán a tu cuenta por esta venta es: $"<<cant_pesos_venta<<endl;
            if(usuario.cant_dolares>=cant_dolares_venta){
                mov_generico.sueldo_viejo=usuario.cant_dolares;
                usuario.cant_dolares-=cant_dolares_venta;
                mov_generico.sueldo_actual=usuario.cant_dolares;
                ventas_dolares.push_back(mov_generico);
                usuario.saldo+=cant_pesos_venta;
            }
            else{
                cout<<"No cuenta con esa cantidad de dolares, puede vender: $"<<usuario.cant_dolares<<endl;
            }
            break;
        case 3:
            cond=false;
            break;    
    }
    }    
}


void retirar_dolares(Cuenta &usuario, movimiento mov_generico, vector <movimiento> &retiros_dolares) {
    int dolares_a_retirar;
    cout<<"ingrese la cantidad de dolares que desea retirar(multiplo de 10):"<<endl;
    cin>>dolares_a_retirar;
    if(dolares_a_retirar>usuario.cant_dolares){
        cout<<"error"<<endl;
    }
    else if(dolares_a_retirar%10!=0){
        cout<<"error"<<endl;
    }
    else{
        mov_generico.sueldo_viejo=usuario.cant_dolares;
        usuario.cant_dolares-=dolares_a_retirar;
        mov_generico.sueldo_actual=usuario.cant_dolares;
        retiros_dolares.push_back(mov_generico);
        while(dolares_a_retirar>=100){
            cout<<"billete de 100 dolares"<<endl;
            dolares_a_retirar-=100;}
        while(dolares_a_retirar>=50){
            cout<<"billete de 50 dolares"<<endl;
            dolares_a_retirar-=50;}
        while(dolares_a_retirar>=20){
            cout<<"billete de 20 dolares"<<endl;
            dolares_a_retirar-=20;}
        while(dolares_a_retirar>=10){
            cout<<"billete de 10 dolares"<<endl;
            dolares_a_retirar-=10;}                       
    }
}

void armar_plazo_fijo(Cuenta &usuario, int opcion) {
    
    int cant_a_invertir, duracion, intereses_generados, total;
    PlazoFijo auxiliar;
    cout<<"ingresa el monto de pesos que queres invertir en el plazo fijo"<<endl;
    cin>>cant_a_invertir;
    cout<<"ingresa la cantidad de dias que deseas que dure el plazo fijo"<<endl;
    cin>>duracion;
    if(cant_a_invertir> usuario.saldo || duracion < 30){
        cout<<"datos incorrectos"<<endl;
        if(cant_a_invertir > usuario.saldo){
        cout<<"no tenes suficiente dinero"<<endl;
        }
        if(duracion<30){
            cout<<"tenes q pedir minimo 30 dias para tu plazo fijo"<<endl;
        }
    }
    else{
        usuario.saldo-=cant_a_invertir;
        intereses_generados=(cant_a_invertir*duracion*70)/36500;
        cout<<"ingresaste "<<cant_a_invertir<<" $ en un plazo fijo de "<<duracion<<" dias y generaste un interes de "<<intereses_generados<<endl;
        cout<<"al final de el plazo fijo obtendras "<<cant_a_invertir + intereses_generados << " $"<<endl;
        total=cant_a_invertir + intereses_generados;
        auxiliar.monto_inicial=cant_a_invertir;
        auxiliar.dias=duracion;
        auxiliar.intereses=intereses_generados;
        auxiliar.total=total;
        auxiliar.sigue_vigente= true;
        usuario.plazos_fijos.push_back(auxiliar);
    
}


}

void cancelar_plazo_fijo(Cuenta &usuario, int opcion) {
    
    int eleccion;
    if(!usuario.plazos_fijos.empty()){
        cout<<"estos son los plazos fijos que tenes en este momento"<<endl;
        for(int i=0;i<usuario.plazos_fijos.size() ;i++){
            if(usuario.plazos_fijos[i].sigue_vigente){
                cout<<"tenes: "<<usuario.plazos_fijos.size()<<" plazos fijos "<<endl;
                cout<<i+1<<". invertiste: "<< usuario.plazos_fijos[i].monto_inicial;
                cout<<" en un plazo de "<< usuario.plazos_fijos[i].dias<<" dias y generaste una ganacia de: "<<usuario.plazos_fijos[i].intereses<<endl;
            }
        }
        cout<<"que plazo queres dar de baja "<<usuario.nombre_usuario<<"?"<<endl;
        cin>>eleccion;
        if(usuario.plazos_fijos[eleccion-1].sigue_vigente==false){
            cout<<"este plazo no esta vigente"<<endl;
        }
        usuario.plazos_fijos[eleccion-1].sigue_vigente=false;
        if(usuario.plazos_fijos[eleccion-1].sigue_vigente==false){
            cout<<"Plazo fijo eliminado, se te devolvió el dinero"<<endl;
            usuario.saldo+=usuario.plazos_fijos[eleccion-1].monto_inicial;
            int garet=eleccion-1;
            usuario.plazos_fijos.erase(usuario.plazos_fijos.begin()+garet);
        }
        else{
            cout<<"Error"<<endl;
        }
    }

}

void pedir_prestamo(Cuenta &usuario, int opcion, vector <movimiento> &prestamos,movimiento mov_generico) {
    bool cond=true;
    int opcion_prestamo;
    while(cond){
        cout<<"Seleccione una opcion de préstamo: "<<endl
            <<"1.primer préstamo"<<endl
            <<"2.segundo préstamo"<<endl
            <<"3.tercer préstamo"<<endl
            <<"4.salir"<<endl;
        cin>>opcion_prestamo;    
        switch(opcion_prestamo){
            case 1:
                if(usuario.saldo<=20000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    cond=false;
                    continue;
                }
                else{
                    mov_generico.sueldo_viejo=usuario.saldo;
                    usuario.saldo+=(usuario.saldo*5)/100;
                    mov_generico.sueldo_actual=usuario.saldo;
                    prestamos.push_back(mov_generico);
                    cout<<"el dinero del préstamo se añadió a tu cuenta"<<endl;
                }
                break;
            case 2:
                if(usuario.saldo<=50000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    cond=false;
                    continue;
                }
                else{
                    mov_generico.sueldo_viejo=usuario.saldo;
                    usuario.saldo+=(usuario.saldo*10)/100;
                    mov_generico.sueldo_actual=usuario.saldo;
                    prestamos.push_back(mov_generico);
                    cout<<"el dinero del préstamo fue acreditado a tu cuenta"<<endl;
                }
                break;
            case 3:
                if(usuario.saldo<=100000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    cond=false;
                    continue;
                }
                else{
                    mov_generico.sueldo_viejo=usuario.saldo;
                    usuario.saldo+=(usuario.saldo*15)/100;
                    mov_generico.sueldo_actual=usuario.saldo;
                    prestamos.push_back(mov_generico);
                    cout<<"el dinero del préstamo fue acreditado a su cuenta"<<endl;
                }
                break;
            case 4:
                cond=false;
                break;    
            default:
                cout<<"esta opcion no esta disponible"<<endl;
                break;            
        }    
}
}

void ver_movimientos(Cuenta usuario,vector <movimiento> ingresos,vector <movimiento> retiros,vector <movimiento> prestamos,vector <movimiento> ingresos_dolares,vector <movimiento> ventas_dolares,vector <movimiento> retiros_dolares) {
    
    if(!usuario.plazos_fijos.empty()){
        cout<<"estos son los plazos fijos que tenes en este momento"<<endl;
        for(int i=0;i<usuario.plazos_fijos.size() ;i++){
            if(usuario.plazos_fijos[i].sigue_vigente){
                cout<<"tenes: "<<usuario.plazos_fijos.size()<<" plazos fijos "<<endl;
                cout<<i+1<<". invertiste: "<< usuario.plazos_fijos[i].monto_inicial;
                cout<<" en un plazo de "<< usuario.plazos_fijos[i].dias<<" dias y generaste una ganacia de: "<<usuario.plazos_fijos[i].intereses<<endl;
            }
        }
    }
    if(!ingresos.empty()){
        cout<<"Sus ingresos de dinero son: "<<endl;
        for(int i=0;i<(ingresos.size());i++){
            cout<<"saldo anterior: "<<ingresos[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<ingresos[i].sueldo_actual<<endl;
        }
    }
    if(!retiros.empty()){    
        cout<<"Sus retiros de dinero son: ";
        for(int i=0;i<retiros.size();i++){
            cout<<"saldo anterior: "<<retiros[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<retiros[i].sueldo_actual<<endl;
        }
    }
    if(!prestamos.empty()){
        cout<<"Sus prestamos son: "<<endl;
        for(int i=0;i<prestamos.size();i++){
            cout<<"saldo anterior: "<<prestamos[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<prestamos[i].sueldo_actual<<endl;
        }
    }
    if(!ingresos_dolares.empty()){    
        cout<<"Sus compras de dolares fueron: "<<endl;
        for(int i=0;i<ingresos_dolares.size();i++){
            cout<<"saldo anterior: "<<ingresos_dolares[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<ingresos_dolares[i].sueldo_actual<<endl;
        }
    }
    if(!ventas_dolares.empty()){    
        cout<<"Sus ventas de dolares fueron: "<<endl;
        for(int i=0;i<ventas_dolares.size();i++){
            cout<<"saldo anterior: "<<ventas_dolares[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<ventas_dolares[i].sueldo_actual<<endl;
        }
    }
    if(!retiros_dolares.empty()){    
        cout<<"Sus retiros de dolares fueron: "<<endl;
        for(int i=0;i<retiros_dolares.size()-1;i++){
            cout<<"saldo anterior: "<<retiros_dolares[i].sueldo_viejo<<endl;
            cout<<"saldo posterior: "<<retiros_dolares[i].sueldo_actual<<endl;
        }
    }    
}   


void actualizar_datos(Cuenta &usuario, int opcion, string nombre) {
    ifstream archivo("./usuarios.txt");
    ofstream archivo_temporal(".auxiliar.txt");
    string linea;
    bool encontrado = false;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!archivo_temporal.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }
    
    string auxilia;
    cout<<"que deseas cambiar, tu contraseña o tu usuario"<<endl;
    cin>>auxilia;
    if(auxilia=="usuario"){
        string nuevo_nombre;
        cout<<"que nombre le queres poner?"<<endl;
        cin>>nuevo_nombre;
        while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre_usuario, contrasenia, saldo, dolares, resto;
        getline(ss, nombre_usuario, ',');
        getline(ss, contrasenia, ',');
        getline(ss, saldo, ',');       
        getline(ss, dolares, ',');     
        getline(ss, resto);      

        if (nombre_usuario == nombre) {
            encontrado = true;
            archivo_temporal << nuevo_nombre << "," << contrasenia << ","
                      << usuario.saldo << "," 
                      << usuario.cant_dolares << "," 
                      << resto << endl;
        } else {
            archivo_temporal << linea << endl;
        }
    }

    archivo.close();
    archivo_temporal.close();

    }
    else if(auxilia=="contraseña"){
        
        string nueva_contrasenia, confirmacion;
        cout<<"que contraseña le queres poner?"<<endl;
        cin>>nueva_contrasenia;
        cout<<"confirmar contraseña"<<endl;
        cin>>confirmacion;
        if(nueva_contrasenia==confirmacion){
            while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre_usuario, contrasenia, saldo, dolares, resto;
        getline(ss, nombre_usuario, ',');       
        getline(ss, contrasenia, ',');    
        getline(ss, saldo, ',');       
        getline(ss, dolares, ',');       
        getline(ss, resto);              

        if (nombre_usuario == nombre) {
            encontrado = true;
            archivo_temporal << nombre_usuario<< "," << confirmacion << ","
                      << usuario.saldo << "," 
                      << usuario.cant_dolares << "," 
                      << resto << endl;
        } else {
            archivo_temporal << linea << endl;
        }
    }

    archivo.close();
    archivo_temporal.close();
        }
    }
    if (encontrado) {
        remove("./bdd.txt");
        rename("./auxiliar.txt", "./bdd.txt");
        cout << "Datos del usuario actualizados" << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("./auxiliar.txt");
        cout << "No se encontró al usuario" << endl;
    }
}
void act_datos(Cuenta usuario, string name, int plazos_fijos) {
    ifstream archivo("./bdd.txt");
    ofstream archivo_temporal("./auxiliar.txt");
    string linea;
    bool encontrado = false;

    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!archivo_temporal.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string nombre_usuario, contrasenia, saldo, dolares, resto;
        getline(ss, nombre_usuario, ',');      
        getline(ss, contrasenia, ',');   
        getline(ss, saldo, ',');         
        getline(ss, dolares, ',');        
        getline(ss, resto);             

        if (nombre_usuario == name) {
            encontrado = true;
            archivo_temporal << nombre_usuario << "," << contrasenia << ","
                      << usuario.saldo << "," 
                      << usuario.cant_dolares << "," 
                      << plazos_fijos+(usuario.plazos_fijos.size()) << endl;
        } else {
            archivo_temporal << linea << endl;
        }
    }

    archivo.close();
    archivo_temporal.close();

    if (encontrado) {
        remove("./usuarios.txt");
        rename("./auxiliar.txt", "./bdd.txt");
        cout << "Datos del usuario actualizados" << endl;
    } else {
        remove("./auxiliar.txt");
        cout << "Usuario no encontrado." << endl;
    }
}


int main()
{
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
    int saldoo, dolaress, plazos_fijoss;
    ifstream archivo;
    bool usuarioEncontrado = false;
    bool contraseñaCorrecta = false; 
    bool sesion1=true;
    string nombre_usuario, contraseña, linea, usuarioo, contraseniaa,sald, dol,pf;
    
    cout << "Ingresa tu nombre de usuario y tu contraseña. Si no están en la base de datos, se registrará un usuario con los datos que brindes." << endl;
    cout << "Usuario: ";
    getline(cin, nombre_usuario);
    cout << "Contraseña: ";
    getline(cin, contraseña);

    archivo.open("bdd.txt", ios::in);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo de la base de datos." << endl;
        return 1;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, usuarioo, ',');     
        getline(ss, contraseniaa, ',');   
        getline(ss, sald, ',');
        getline(ss, dol, ',');
        getline(ss, pf, ',');


        if (nombre_usuario == usuarioo) {
            usuarioEncontrado = true;
            if (contraseña == contraseniaa) {
                contraseñaCorrecta = true;

                break; 
            }
        }
    }
    archivo.close();
    if (usuarioEncontrado) {
        if (contraseñaCorrecta) {
            cout << "sesión iniciada correctamente." << endl;
            cout<<"en tu cuenta tenes:"<<sald<<" pesos, "<<dol<<" dolares y "<<pf<<" plazos fijos armados"<<endl; 
            saldoo = stoi(sald); 
            dolaress= stoi(dol);
            plazos_fijoss= stoi(pf);
            usuario.saldo=saldoo;
            usuario.cant_dolares=dolaress; 

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
            archivoRegistro << nombre_usuario << "," << contraseña << ",." << endl;
            archivoRegistro.close();
            sesion1=true;
            usuario.nombre_usuario=nombre_usuario;
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
            ingresar_efectivo(usuario, opcion,movimientoto,ingresos);
            break;
        case 2:
            retirar_efectivo(usuario, opcion,movimientoto,retiros);
            break;
        case 3:
            dolares(usuario, opcion,movimientoto,ingresos_dolares,ventas_dolares);
            break;
        case 4:
            retirar_dolares(usuario, opcion,movimientoto,retiros_dolares);
            break;
        case 5:
            armar_plazo_fijo(usuario, opcion);
            break;
        case 6:
            cancelar_plazo_fijo(usuario, opcion);
            break;
        case 7:
            pedir_prestamo(usuario, opcion,prestamos,movimientoto);
            break;
        case 8:
            ver_movimientos(usuario,ingresos,retiros,prestamos,ingresos_dolares,ventas_dolares,retiros_dolares);
            break;
        case 9:
            actualizar_datos(usuario, opcion, nombre_usuario);
            break;
        case 10:
            sald=usuario.saldo;
            cout << "Gracias por utilizar nuestro sistema " << usuario.nombre_usuario << ", vuelva pronto." << endl;
            act_datos(usuario, nombre_usuario, plazos_fijoss);



            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
        }

    }
    
}
