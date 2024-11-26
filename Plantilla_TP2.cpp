#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Estructura para representar un movimiento
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
void ingresar_efectivo(Cuenta &usuario, int opcion,movimiento movimiento_generico, vector <movimiento> &ingresos) {
    int monto_ingresado;
    cout<<"ingrese la cantidad de efectivo que desea ingresar:"<<endl;
    cin>>monto_ingresado;
    movimiento_generico.sueldo_anterior=usuario.saldo_en_cuenta;
    usuario.saldo_en_cuenta+=monto_ingresado;
    movimiento_generico.sueldo_posterior=usuario.saldo_en_cuenta;
    ingresos.push_back(movimiento_generico);

}

// 2
void retirar_efectivo(Cuenta &usuario, int opcion,movimiento movimiento_generico, vector <movimiento> &retiros) {
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
        movimiento_generico.sueldo_anterior=usuario.saldo_en_cuenta;
        usuario.saldo_en_cuenta-=monto_a_retirar;
        movimiento_generico.sueldo_posterior=usuario.saldo_en_cuenta;
        retiros.push_back(movimiento_generico);
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
void manejar_dolares(Cuenta &usuario, int opcion,movimiento movimiento_generico, vector <movimiento> &ingresos_dolares,vector <movimiento> &ventas_dolares) {
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
                movimiento_generico.sueldo_anterior=usuario.cantidad_dolares;
                usuario.cantidad_dolares+=cantidad_dolares_compra;
                movimiento_generico.sueldo_posterior=usuario.cantidad_dolares;
                ingresos_dolares.push_back(movimiento_generico);
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
                movimiento_generico.sueldo_anterior=usuario.cantidad_dolares;
                usuario.cantidad_dolares-=cantidad_dolares_venta;
                movimiento_generico.sueldo_posterior=usuario.cantidad_dolares;
                ventas_dolares.push_back(movimiento_generico);
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
void retirar_dolares(Cuenta &usuario, int opcion,movimiento movimiento_generico, vector <movimiento> &retiros_dolares) {
    int dolares_a_retirar;
    cout<<"ingrese la cantidad de dolares que desea retirar(multiplo de 10):"<<endl;
    cin>>dolares_a_retirar;
    if(dolares_a_retirar>usuario.cantidad_dolares){
        cout<<"error"<<endl;
    }
    else if(dolares_a_retirar%10!=0){
        cout<<"error"<<endl;
    }
    else{
        movimiento_generico.sueldo_anterior=usuario.cantidad_dolares;
        usuario.cantidad_dolares-=dolares_a_retirar;
        movimiento_generico.sueldo_posterior=usuario.cantidad_dolares;
        retiros_dolares.push_back(movimiento_generico);
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

// 5
void armar_plazo_fijo(Cuenta &usuario, int opcion) {
    
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
        auxinverse.vigente= true;
        //cuando se cumplan los dias cambiar a false
        usuario.plazos_fijos.push_back(auxinverse);
    
}


}

// 6
void cancelar_plazo_fijo(Cuenta &usuario, int opcion) {
    /*
    Para la opción 6, se le deberá mostrar todos los plazos fijos realizados 
    hasta el momento y la opción de poder cancelarlos, en el caso de no 
    tener ningún plazo fijo armado, mostrar un mensaje de error y 
    devolverlo al menú. En el caso de querer cancelar un plazo fijo, se le 
    deberá devolver la plata al usuario sin la comisión generada por el plazo 
    de días dejado.
    */
    int vareli;
    if(!usuario.plazos_fijos.empty()){
        cout<<"estos son los plazos fijos que tenes en este momento"<<endl;
        for(int i=0;i<usuario.plazos_fijos.size() ;i++){
            if(usuario.plazos_fijos[i].vigente){
                cout<<"tenes: "<<usuario.plazos_fijos.size()<<" plazos fijos "<<endl;
                cout<<i+1<<". invertiste: "<< usuario.plazos_fijos[i].plata_inicial;
                cout<<" en un plazo de "<< usuario.plazos_fijos[i].dias<<" dias y generaste una ganacia de: "<<usuario.plazos_fijos[i].interes<<endl;
            }
        }
        cout<<"que plazo queres dar de baja "<<usuario.nusuario<<"?"<<endl;
        cin>>vareli;
        if(usuario.plazos_fijos[vareli-1].vigente==false){
            cout<<"este plazo no esta vigente"<<endl;
        }
        usuario.plazos_fijos[vareli-1].vigente=false;
        if(usuario.plazos_fijos[vareli-1].vigente==false){
            cout<<"usuario borrado exitosamente se te devolvio la plata que invertiste pero sin ningun interes"<<endl;
            usuario.saldo_en_cuenta+=usuario.plazos_fijos[vareli-1].plata_inicial;
            int garet=vareli-1;
            usuario.plazos_fijos.erase(usuario.plazos_fijos.begin()+garet);
        }
        else{
            cout<<"hubo un error"<<endl;
        }
    }



}

// 7
void pedir_prestamo(Cuenta &usuario, int opcion, vector <movimiento> &prestamos,movimiento movimiento_generico) {
    bool condicion=true;
    int opcion_prestamo;
    /*Para la opción 7, se le deberá mostrar 3 opciones de préstamo, cada 
opción cumple con un requisito para pedirlo. 
El 1er préstamo, se podrá pedir en el caso de que el usuario tenga en el 
saldo de su cuenta un monto superior a $20.000. El préstamo ofrece un 
5% del saldo de la cuenta, este valor se deberá sumar al saldo en 
cuenta que tenía. 
El 2do préstamo, se podrá pedir en el caso de que el usuario tenga en 
el saldo de su cuenta un monto superior a $50.000. El préstamo ofrece 
un 10% del saldo de la cuenta, este valor se deberá sumar al saldo en 
cuenta que tenía. 
El 3er préstamo, se podrá pedir en el caso de que el usuario tenga en el 
saldo de su cuenta un monto superior a $100.000. El préstamo ofrece 
un 15% del saldo de la cuenta, este valor se deberá sumar al saldo en 
cuenta que tenía.*/
    while(condicion){
        cout<<"Seleccione una opcion de préstamo: "<<endl
            <<"1.1er préstamo"<<endl
            <<"2.2do préstamo"<<endl
            <<"3.3er préstamo"<<endl
            <<"4.Salir"<<endl;
        cin>>opcion_prestamo;    
        switch(opcion_prestamo){
            case 1:
                if(usuario.saldo_en_cuenta<=20000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    condicion=false;
                    continue;
                }
                else{
                    movimiento_generico.sueldo_anterior=usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta+=(usuario.saldo_en_cuenta*5)/100;
                    movimiento_generico.sueldo_posterior=usuario.saldo_en_cuenta;
                    prestamos.push_back(movimiento_generico);
                    cout<<"el dinero del préstamo fue acreditado a su cuenta"<<endl;
                }
                break;
            case 2:
                if(usuario.saldo_en_cuenta<=50000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    condicion=false;
                    continue;
                }
                else{
                    movimiento_generico.sueldo_anterior=usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta+=(usuario.saldo_en_cuenta*10)/100;
                    movimiento_generico.sueldo_posterior=usuario.saldo_en_cuenta;
                    prestamos.push_back(movimiento_generico);
                    cout<<"el dinero del préstamo fue acreditado a su cuenta"<<endl;
                }
                break;
            case 3:
                if(usuario.saldo_en_cuenta<=100000){
                    cout<<"Usted no puede acceder a este prestamo"<<endl;
                    condicion=false;
                    continue;
                }
                else{
                    movimiento_generico.sueldo_anterior=usuario.saldo_en_cuenta;
                    usuario.saldo_en_cuenta+=(usuario.saldo_en_cuenta*15)/100;
                    movimiento_generico.sueldo_posterior=usuario.saldo_en_cuenta;
                    prestamos.push_back(movimiento_generico);
                    cout<<"el dinero del préstamo fue acreditado a su cuenta"<<endl;
                }
                break;
            case 4:
                condicion=false;
                break;    
            default:
                cout<<"esta opcion no esta disponible"<<endl;
                break;            
        }    
}
}
// 8
void ver_movimientos(Cuenta usuario,vector <movimiento> ingresos,vector <movimiento> retiros,vector <movimiento> prestamos,vector <movimiento> ingresos_dolares,vector <movimiento> ventas_dolares,vector <movimiento> retiros_dolares) {
    
    if(!usuario.plazos_fijos.empty()){
        cout<<"estos son los plazos fijos que tenes en este momento"<<endl;
        for(int i=0;i<usuario.plazos_fijos.size() ;i++){
            if(usuario.plazos_fijos[i].vigente){
                cout<<"tenes: "<<usuario.plazos_fijos.size()<<" plazos fijos "<<endl;
                cout<<i+1<<". invertiste: "<< usuario.plazos_fijos[i].plata_inicial;
                cout<<" en un plazo de "<< usuario.plazos_fijos[i].dias<<" dias y generaste una ganacia de: "<<usuario.plazos_fijos[i].interes<<endl;
            }
        }
    }
    if(!ingresos.empty()){
        cout<<"Sus ingresos de dinero son: "<<endl;
        for(int i=0;i<(ingresos.size());i++){
            cout<<"saldo anterior: "<<ingresos[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<ingresos[i].sueldo_posterior<<endl;
        }
    }
    if(!retiros.empty()){    
        cout<<"Sus retiros de dinero son: ";
        for(int i=0;i<retiros.size();i++){
            cout<<"saldo anterior: "<<retiros[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<retiros[i].sueldo_posterior<<endl;
        }
    }
    if(!prestamos.empty()){
        cout<<"Sus prestamos son: "<<endl;
        for(int i=0;i<prestamos.size();i++){
            cout<<"saldo anterior: "<<prestamos[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<prestamos[i].sueldo_posterior<<endl;
        }
    }
    if(!ingresos_dolares.empty()){    
        cout<<"Sus compras de dolares fueron: "<<endl;
        for(int i=0;i<ingresos_dolares.size();i++){
            cout<<"saldo anterior: "<<ingresos_dolares[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<ingresos_dolares[i].sueldo_posterior<<endl;
        }
    }
    if(!ventas_dolares.empty()){    
        cout<<"Sus ventas de dolares fueron: "<<endl;
        for(int i=0;i<ventas_dolares.size();i++){
            cout<<"saldo anterior: "<<ventas_dolares[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<ventas_dolares[i].sueldo_posterior<<endl;
        }
    }
    if(!retiros_dolares.empty()){    
        cout<<"Sus retiros de dolares fueron: "<<endl;
        for(int i=0;i<retiros_dolares.size()-1;i++){
            cout<<"saldo anterior: "<<retiros_dolares[i].sueldo_anterior<<endl;
            cout<<"saldo posterior: "<<retiros_dolares[i].sueldo_posterior<<endl;
        }
    }    
}   

// 9
void actualizar_datos(Cuenta &usuario, int opcion, string name) {
    /*
se le preguntará al usuario qué datos desea actualizar. 
En el caso de que elija cambiar su nombre de usuario, se le solicitará 
únicamente un nuevo nombre para la cuenta, y en el caso de querer 
cambiar la contraseña se le solicitará una nueva contraseña y que 
repita la contraseña, en el caso de que las contraseñas no coincidan 
mostrar un error y pedirle que vuelva a ingresar los datos, en el caso de 
que las contraseñas coincidan, se deberá mostrar un mensaje de éxito,

        */
    ifstream file_ent("./bdd.txt");
    ofstream file_temp("./bdd_aux.txt");
    string linea;
    bool encontrado = false;

    if (!file_ent.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!file_temp.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }
    
    string auxil;
    cout<<"que deseas cambiar, tu contraseña o tu usuario"<<endl;
    cin>>auxil;
    if(auxil=="usuario"){
        string newname;
        cout<<"que nombre le queres poner?"<<endl;
        cin>>newname;
        //aca reemplazar el nombre de usuario por la variable newname
        while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contraseña
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << newname << "," << contrasenia << ","
                      << usuario.saldo_en_cuenta << "," 
                      << usuario.cantidad_dolares << "," 
                      << resto << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();

    }
    else if(auxil=="contraseña"){
        
        string newcon, checon;
        cout<<"que contraseña le queres poner?"<<endl;
        cin>>newcon;
        cout<<"confirmar contraseña"<<endl;
        cin>>checon;
        if(newcon==checon){
            //aca reemplazar la contraseña en el txt por newcon
            while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contraseña
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << nusuario<< "," << checon << ","
                      << usuario.saldo_en_cuenta << "," 
                      << usuario.cantidad_dolares << "," 
                      << resto << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();
        }
    }
    if (encontrado) {
        // Reemplazamos el archivo original con el temporal
        remove("./bdd.txt");
        rename("./bdd_aux.txt", "./bdd.txt");
        cout << "Datos del usuario actualizados con éxito." << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("./bdd_aux.txt");
        cout << "Usuario no encontrado." << endl;
    }
}
void f5_datos(Cuenta usuario, string name, int pf) {
    ifstream file_ent("./bdd.txt");
    ofstream file_temp("./bdd_aux.txt");
    string linea;
    bool encontrado = false;

    if (!file_ent.is_open()) {
        cout << "Error al abrir el archivo original." << endl;
        return;
    }

    if (!file_temp.is_open()) {
        cout << "Error al crear el archivo temporal." << endl;
        return;
    }

    // Leer línea por línea del archivo original
    while (getline(file_ent, linea)) {
        stringstream ss(linea);
        string nusuario, contrasenia, saldo, dolares, resto;
        getline(ss, nusuario, ',');       // Extrae nombre de usuario
        getline(ss, contrasenia, ',');    // Extrae contraseña
        getline(ss, saldo, ',');          // Extrae saldo
        getline(ss, dolares, ',');        // Extrae dólares
        getline(ss, resto);               // Extrae lo restante

        if (nusuario == name) {
            // Si encontramos al usuario, actualizamos saldo y dólares
            encontrado = true;
            file_temp << nusuario << "," << contrasenia << ","
                      << usuario.saldo_en_cuenta << "," 
                      << usuario.cantidad_dolares << "," 
                      << pf+(usuario.plazos_fijos.size()) << endl;
        } else {
            // Escribimos la línea original en el archivo temporal
            file_temp << linea << endl;
        }
    }

    file_ent.close();
    file_temp.close();

    if (encontrado) {
        // Reemplazamos el archivo original con el temporal
        remove("./bdd.txt");
        rename("./bdd_aux.txt", "./bdd.txt");
        cout << "Datos del usuario actualizados con éxito." << endl;
    } else {
        // Eliminamos el archivo temporal si no se encontró el usuario
        remove("./bdd_aux.txt");
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
    int salditoBD, dolaritosBD, pfBD;
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
            cout<<"tenes en tu cuenta "<<saldoBD<<" pesos, "<<dolaresBD<<" dolares y "<<cantidad_plazo_fijosBD<<" plazos fijos armados"<<endl;
            //sacamos del txt los valores de la cuenta 
            salditoBD = stoi(saldoBD);// con stoi los pasamos de string a int 
            dolaritosBD= stoi(dolaresBD);
            pfBD= stoi(cantidad_plazo_fijosBD);
            //los metemos en la sesion que esta iniciada
            usuario.saldo_en_cuenta=salditoBD;
            usuario.cantidad_dolares=dolaritosBD; 

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
            manejar_dolares(usuario, opcion,movimientoto,ingresos_dolares,ventas_dolares);
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
            actualizar_datos(usuario, opcion, nusuario);
            break;
        case 10:
            saldoBD=usuario.saldo_en_cuenta;
            cout << "Gracias por utilizar nuestro sistema " << usuario.nusuario << ", vuelva pronto." << endl;
            f5_datos(usuario, nusuario, pfBD);



            break;
        default:
            cout << "Opción no válida. Intente nuevamente." << endl;
            break;
        }
        }

    }
    
}
