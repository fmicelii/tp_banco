 #include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    int i=0,j;
    ifstream archivo;
    bool var1=false, var2=false;
    string frase, nusuario, contraseña, aux, fraseaux;
    int opcion = 0;
    cout<<"ingresa tu nombre de usuario y tu contraseña si no estan en la base de datos se registrará un usuario con los datos que nos brindes"<<endl;
    getline(cin, nusuario);
    getline(cin, contraseña);
    archivo.open("bdd.txt", ios::in);
    while(getline(archivo, frase, '.')){
        
        while(getline(archivo,fraseaux,',')){
            cout<<fraseaux;
            cout<<" ";
            if(nusuario==fraseaux){
                var1=true;
                j=1;
                cout<<"usercorrecto";
            }
            if(j==i && var1){
                if(contraseña==fraseaux){
                    var2=true;
                    cout<<"contra correcta";

                }
            }
        }
        cout<<endl;
        i++;
    }
    archivo.close();
    cout<<endl;
    cout<<var1<<" "<<var2<<endl;
    cout<<endl;
    if(var1){
        if(var2){
            cout<<"felicidades tu sesion fue iniciada correctamente"<<endl;
        }
        else{
            cout<<"pusiste mal la contraseña salamin "<<endl;
        }
    }
    else{
        cout<<"no estas en la base de datos, ya te registramos!"<<endl;
        ofstream file1;
        file1.open("bdd.txt", ios::app);
        if (file1.is_open()){
            
            file1<<nusuario<<","<<contraseña<<",."<<endl;
        }
        file1.close();
    }
    
}