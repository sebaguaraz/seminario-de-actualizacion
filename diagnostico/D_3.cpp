#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Persona
{
private:
    string  user;
    string password;
public:
    Persona(){};
    ~Persona(){};
    string getname(){
        return user;
    };

    void setname(string user){
    this->user=user;
    }

    void setpassword(string password){
        this->password=password;
        }

    string getpasword(){
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

    void mostrarUsuarios(){
        for (const auto & x : usuarios)
        {
            cout <<"Usuario: " << x->getname() << " -- " <<"Contrasenia: " << x->getpasword() << endl;
        }
    
    }

    shared_ptr<Persona> BuscarUsuario(string usuario, string password){

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

    bool validarContrasenia(string newPassword) {
        bool mayus = false;
        bool numer = false;
        int simboloCount = 0; // Contador de símbolos especiales
    
        if (newPassword.length() < 8 || newPassword.length() > 16) {
            return false;
        }
    
        for (char c : newPassword) {
            if (isupper(c)) mayus = true;
            if (isdigit(c)) numer = true;
            if (ispunct(c)) simboloCount++; // Cuenta los símbolos especiales
        }
    
        return mayus && numer && (simboloCount >= 2); // Requiere al menos 2 símbolos
    }
    
    void cambiarcontrasenia(shared_ptr<Persona> user, const string& newPassword){

        bool resultado = validarContrasenia(newPassword);

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
    shared_ptr<Persona> user;
    shared_ptr<Empresa> empresa;

    void cambiarContrasenia(){
        string password;
        cout << "Ingrese nueva contrasenia: "; cin >> password;

        empresa->cambiarcontrasenia(user,password);

    }



    void mostrarUsuarios(){
    
        empresa->mostrarUsuarios();
    }

    public:
    Menu(shared_ptr<Persona> validarUser,shared_ptr<Empresa> empresa){
    this->user=validarUser;
    this->empresa=empresa;

    };
    
    ~Menu(){};

    void mostrarMenu(){
        int opcion;
        
        do
        {
            cout << "Bienvenido, usuario: " << user->getname() << " !! "<< endl; 
            cout << "------------------Menu-------------- " << endl;
            cout << "1- Cambiar Contrasenia. " << endl;
            cout << "2- Mostrar Usuarios y Contrasenias. " << endl;
            cout << "0- Salir del programa." << endl;
            cout << "Opcion: " << endl;
            cin >> opcion;
            switch (opcion)
            {
            case 1:
                cambiarContrasenia();
                break;
    
            case 2:
                mostrarUsuarios();
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
string password;

shared_ptr<Empresa> empresa = make_shared<Empresa>();

shared_ptr<Persona> user1 = make_shared<Persona>();
shared_ptr<Persona> user2 = make_shared<Persona>();
shared_ptr<Persona> user3 = make_shared<Persona>();

shared_ptr<Persona> userNuevo;

user1->setname("sebastian");
user1->setpassword("Catalina@32");

user2->setname("juan");
user2->setpassword("Juancortez@5");

user3->setname("diego");
user3->setpassword("Diegoguaraz22@");

empresa->insertUsers(user1);
empresa->insertUsers(user2);
empresa->insertUsers(user3);

empresa->mostrarUsuarios();






do
{  
    cout << "                                      Tiene (" << 3 - contador << "/3) intentos                    " << endl;
    cout << "Ingrese el usuario:" << endl;
    cin >>usuario;
    cout << "Ingrese el pasword:" << endl;
    cin >> password;

    shared_ptr<Persona> validarUser = empresa->BuscarUsuario(usuario,password);

    if(validarUser==nullptr){
 
        cout << " Usuario no encontrado. " << endl;
        contador++;
            if( contador==1){
                cout << "Usuario y/o contrasenia incorrecta. " << endl;
                continue;
 
            }
 
            if(contador==3){
                
                cout << "Usuario Bloqueado. Contacte al administrador." << endl;
                break;
            }
 
        continue; // no sigue ejecutando el resto del codigo. Se vuelve a ejecutar.
    }
    
    shared_ptr<Menu> menu = make_shared<Menu>(validarUser,empresa);
    menu->mostrarMenu(); 
    contador = 0; // Reiniciar el contador



    
    /*
    userNuevo = make_shared<Persona>();
    userNuevo->setname(usuario);
    userNuevo->setpassword(password);   
    
    */
   
   
    

} while (contador<3);




return 0;

}











