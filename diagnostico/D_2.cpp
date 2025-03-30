#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Persona
{
private:
    string  user;
    int password;
public:
    Persona(){};
    ~Persona(){};
    string getname(){
        return user;
    };

    void setname(string user){
    this->user=user;
    }

    void setpassword(int password){
        this->password=password;
        }

    int getpasword(){
        return password;
    };
};



class Empresa
{
private:

std::vector<shared_ptr<Persona>> usuarios;

public:

    Empresa(){};
    ~Empresa(){};
    void insertUsers(shared_ptr<Persona> objetoUsuario){
        usuarios.push_back(objetoUsuario);
    }

    void showUsers(){
        for (const auto & x : usuarios)
        {
            cout << x->getname() << " " << x->getpasword() << endl;
        }
    
    }

    shared_ptr<Persona> BuscarUsuario(string usuario, int password){

        cout << "Buscando usuario... " << endl;

        for (const auto & x : usuarios)
        {
            if (x->getname() == usuario && x->getpasword()==password)
            {
                return x;
            }
          
        }
        
        return nullptr;
    }


};






class Menu
{
private:
    shared_ptr<Persona> validarUser;
    shared_ptr<Empresa> empresa;



    void changePassword(){
        int password;
        cout << "Ingrese nueva contrasenia: (enteros) "; cin >> password;
        validarUser->setpassword(password);
        cout << "Actualizado! " << endl;
    }

    void ShowUsers(){
    
        empresa->showUsers();
    }

    public:
    Menu(shared_ptr<Persona> validarUser,shared_ptr<Empresa> empresa){
    this->validarUser=validarUser;
    this->empresa=empresa;

    };
    ~Menu(){};
    void showMenu(){
        int opcion;
        
        do
        {
            cout << "Bienvenido, usuario: " << validarUser->getname() << " !! "<< endl; 
            cout << "------------------Menu-------------- " << endl;
            cout << "1- Cambiar Contrasenia. " << endl;
            cout << "2- Mostrar Usuarios y Contrasenias. " << endl;
            cout << "0- Salir del programa." << endl;
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                changePassword();
                break;
    
            case 2:
                ShowUsers();
                break;
            
            case 0:
                cout << "Usted salio del programa. " << endl;
                break;
            }
        } while (opcion!=0);
        
    
    }
};



int main(){
    
    int contador=0;
    int opcion;

    string usuario;
    int password;

shared_ptr<Empresa> empresa = make_shared<Empresa>();

shared_ptr<Persona> user1 = make_shared<Persona>();
shared_ptr<Persona> user2 = make_shared<Persona>();
shared_ptr<Persona> user3 = make_shared<Persona>();


user1->setname("sebastian");
user1->setpassword(123);

user2->setname("juan");
user2->setpassword(222);

user3->setname("diego");
user3->setpassword(333);

empresa->insertUsers(user1);
empresa->insertUsers(user2);
empresa->insertUsers(user3);

empresa->showUsers();

shared_ptr<Persona> userNuevo;

shared_ptr<Menu> menu;



do
{
    cout << "                                      Tiene (" << 3- contador << "/3) intentos                    " << endl;
    cout << "Ingrese el usuario:" << endl;
    cin >> usuario;
    cout << "Ingrese el pasword (enteros):" << endl;
    cin >> password;
    
    userNuevo = make_shared<Persona>();
    userNuevo->setname(usuario);
    userNuevo->setpassword(password);

    shared_ptr<Persona> validarUser = empresa->BuscarUsuario(usuario,password);

    if(validarUser){
    
    menu = make_shared<Menu>(validarUser,empresa);
    menu->showMenu(); 
    contador = 0; // Reiniciar el contador
        
    }
    else if(contador==0 || contador==1){
        cout << "Usuario y/o contrasenia incorrecta. " << endl;
        contador++;
    }
       
    else{
        cout << "Usuario Bloqueado. Contacte al administrador." << endl;
        break;

    }


} while (contador<3);




return 0;

}
