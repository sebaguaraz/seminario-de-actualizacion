#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class User
{
private:
    string  name;
    string password;
public:
    User(){};
    ~User(){};
    string getname(){
        return name;
    };

    void setname(string name){
    this->name=name;
    }

    void setpassword(string password){
        this->password=password;
        }

    string getpasword(){
        return password;
    };
};


class Business
{
private:

std::vector<shared_ptr<User>> users;

public:

    Business(){};
    ~Business(){};
   
    void insertUsers(shared_ptr<User> objetoUsuario){
        users.push_back(objetoUsuario);
    }

    void showUsers(){
        for (const auto & x : users)
        {
            cout <<"Usuario: " << x->getname() << " -- " <<"Contrasenia: " << x->getpasword() << endl;
        }
    
    }

    shared_ptr<User> searchUser(string name, string password){

        cout << "Buscando usuario... " << endl;

        for (const auto & x : users)
        {
            if (x->getname() == name && x->getpasword()==password)
            {
                return x;
            }
          
        }
        
        return nullptr;
    }

    bool validatePassword(string password) {
        bool mayus = false;
        int simboloCount = 0; // Contador de símbolos especiales
    
        cout << "Contrasenia ingresada: " << password << endl;  // Debug
        
        if (password.length() < 8 || password.length() > 16) {
            return false;
        }
        
        // Conjunto de caracteres especiales
        string especiales = "!@#$%^&*()_+-=[]{}|;:,.<>?";
    
        for (char c : password) {
            if (isupper(c)) mayus = true;
            if (especiales.find(c) != string::npos) {  // Si el caracter está en la lista de especiales
                simboloCount++;
            }
        }
    
        return mayus && (simboloCount >= 2); // Requiere al menos 2 símbolos
    }
    
    
    void changePassword(shared_ptr<User> user, string newPassword){

        bool resultado = validatePassword(newPassword);
        

        if (resultado!=true)
        {
            cout << "Warning: Al menos una mayuscula y al menos 2 simbolos especiales.... " << endl;
            return;
            
        }
            user->setpassword(newPassword);
            cout << "Actualizado! " << endl;

    }
    
};



class Menu
{
private:
    shared_ptr<User> usernuevo;
    shared_ptr<Business> business;
    shared_ptr<User> UsuarioActual;
    int contador;

    void changepassword(){
        string password;
        cout << "Ingrese nueva contrasenia: "; cin >> password;

        business->changePassword(UsuarioActual,password);

    }

    void showusers(){
    
        business->showUsers();
    }

    bool autenticateUser() {
        string name, password;
        contador = 0;  // Reiniciar intentos antes de autenticar
    
        do {
            cout << "Tiene (" << 3 - contador << "/3) intentos" << endl;
            cout << "Ingrese el usuario: ";
            cin >> name;
            cout << "Ingrese la contrasenia: ";
            cin >> password;
    
            UsuarioActual = business->searchUser(name, password);
    
            if (UsuarioActual == nullptr) {
                cout << "Usuario y/o contrasenia incorrecta." << endl;
                contador++;
    
                if (contador == 3) {
                    cout << "Usuario Bloqueado. Contacte al administrador." << endl;
                    return false; // Bloqueo del usuario
                }
            }
    
        } while (UsuarioActual == nullptr && contador < 3);
    
        contador = 0;  // Reiniciar el contador si se autentica correctamente
        return true;   // Usuario autenticado
    }
    

    

    void login() {
        if (!autenticateUser()) return;  // Si falla la autenticacin, termina la función
        
    
        int opcion;
        cout << "Accedio exitosamente!" << endl;
    
        do {
            cout << "1 - Cambiar contrasenia\n0 - Regresar al menu\nOpcion: ";
            cin >> opcion;
    
            switch (opcion) {
                case 1: changepassword(); break;
                case 0: cout << "Regresando al menu...\n"; break;
                default: cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }
    


  
    void createUser(){
        string name;
        string password;
        cout << "Ingrese el usuario:" << endl;
        cin >>name;
        cout << "Ingrese el pasword:" << endl;
        cin >> password;
        
        bool resultado = business->validatePassword(password);

        if (resultado!=true)
        {
            cout << "Warning: Al menos una mayuscula y al menos 2 simbolos especiales.... " << endl;
            return;
        }
        
        
        usernuevo = make_shared<User>();
        usernuevo->setname(name);
        usernuevo->setpassword(password);
        business->insertUsers(usernuevo);
        cout << "Usuario creado! " << endl;  


    
    }

    public:


    Menu(shared_ptr<Business> business){
    this->business=business;

    };
    
    ~Menu(){};
 
    void showMenu(){
        int opcion;
        
        do
        {
            cout << "------------------Menu-------------- " << endl;
            cout << "1- Iniciar Sesion. " << endl;
            cout << "2- Crear cuenta de Usuario. " << endl;
            cout << "3- Mostrar usuarios. " << endl;
            cout << "0- Salir del programa." << endl;
            cout << "Opcion: " << endl;
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                login();
                break;
    
            case 2:
                createUser();
                break;
            case 3:
                showusers();
                break;
            
            case 0:
                cout << "Usted salio del programa. " << endl;
                break;
            
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                break;
            }
        } while (opcion!=0);
        
    
    }
};





int main(){
    
int contador=0;
int opcion;

string usuario;
string password;

shared_ptr<Business> business = make_shared<Business>();

shared_ptr<User> user1 = make_shared<User>();
shared_ptr<User> user2 = make_shared<User>();
shared_ptr<User> user3 = make_shared<User>();

shared_ptr<User> userNuevo;

user1->setname("sebastian");
user1->setpassword("Catalina@32");

user2->setname("juan");
user2->setpassword("Juancortez@5");

user3->setname("diego");
user3->setpassword("Diegoguaraz22@");

business->insertUsers(user1);
business->insertUsers(user2);
business->insertUsers(user3);

business->showUsers();



shared_ptr<Menu> menu = make_shared<Menu>(business);
menu->showMenu(); 
    


return 0;

}











