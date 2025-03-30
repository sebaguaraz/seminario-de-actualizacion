#include <iostream>
#include <string>
#include <vector>
#include <memory>


using namespace std;

class User
{
private:
    string  user;
    int password;
public:
    User(){};
    ~User(){};
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

std::vector<shared_ptr<User>> usuarios;

public:

    Empresa(){};
    ~Empresa(){};
    void insertUsers(shared_ptr<User> objetoUsuario){
        usuarios.push_back(objetoUsuario);
    }

    void showUsers(){
        for (const auto & x : usuarios)
        {
            cout << x->getname() << " "<< x->getpasword() << endl;
        }
    
    }

    bool searchUser(string usuario, int password){

        bool resultado;

        cout << "Buscando usuario... " << endl;

        for (const auto & x : usuarios)
        {
            if (x->getname() == usuario && x->getpasword()==password)
            {
                resultado =  true;
            }

            else{
                resultado =  false;
            }
            
        }
            return resultado;
    }


};



int main(){
    
    int intentos = 3;
    int contador;

shared_ptr<Empresa> empresa = make_shared<Empresa>();

shared_ptr<User> user1 = make_shared<User>();
shared_ptr<User> user2 = make_shared<User>();
shared_ptr<User> user3 = make_shared<User>();


user1->setname("sebastian");
user1->setpassword(123);

user2->setname("juan");
user2->setpassword(222);

user3->setname("diego");
user3->setpassword(333);

empresa->insertUsers(user1);
empresa->insertUsers(user2);
empresa->insertUsers(user3);


do
{
    
    string usuario;
    int password;
    
    cout << "Ingrese el usuario:" << endl;
    cin >> usuario;
    cout << "Ingrese el pasword (enteros):" << endl;
    cin >> password;
    
    shared_ptr<User> userNuevo = make_shared<User>();
    userNuevo->setname(usuario);
    userNuevo->setpassword(password);

    bool validacion = empresa->searchUser(usuario,password);

    if (validacion == true)
    {
        cout << "Bienvenido, usuario: " << userNuevo->getname()  << " !" << endl;
        break;
    }

    else{
        cout << "Usuario y/o contrasenia incorrecta. Contacte al administrador." << endl;
        contador++;
    }
    


} while (contador<3);




return 0;

}

