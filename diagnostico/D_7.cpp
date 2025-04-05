#include <iostream>
#include <string>
#include <vector> //lo utilizo para un vector de clientes.
#include <memory>
using namespace std;

class Article
{
private:
    string name;
    int stock, id;
    float precie;
public:
    Article(int id, string name){
        this->id = id;
        this->name=name;
    };
    ~Article(){};

    void setprecie(float precie){
        this->precie=precie;
        };

    string getname() {return name;};

    int getid() {return id;};

    void setstock(int stock){ 
            
        this->stock=stock;
    }

    int getstock() {return stock;};

    float getprecie() {return precie;};

    void getinformation(){
    
        cout << "id: " << id << " - " << name << " - " << precie << " - " << stock << endl; 
    }

    bool reduceStock(int cantidad) {
        if (stock >= cantidad  ) {
            stock -= cantidad;
            return true;  // Reducción exitosa
        }
        return false;  // No hay suficiente stock
    }
    
};


class ArticleManager
{
private:
    
    std::vector<shared_ptr<Article>> listarticles;
public:
    ArticleManager(){};
    ~ArticleManager(){};

    void createarticle(const int& id, const string& name, const int& stock, const float& precie){
    
    
        auto articulonuevo = make_shared<Article>(id, name);
        articulonuevo->setstock(stock);
        articulonuevo->setprecie(precie);
        listarticles.push_back(articulonuevo);
        cout << "Articulo creado! " << endl;  
    
    }

    void insertArticles(shared_ptr<Article> articulonuevo){
        listarticles.push_back(articulonuevo);
    }

    void showArticles(){
    
        for (const auto & x : listarticles)
        {
            x->getinformation();
        }
        
    }

    void modificateArticle(int id, float precie){

        if (listarticles.empty())
        {
            cout << " no hay articulos en el catalogo " << endl;
            return;
            
        }

        for (int i = 0; i<listarticles.size(); i++)
        {
            if (id==listarticles[i]->getid())
            {
                listarticles[i]->setprecie(precie);
                cout << "Precio del articulo actualizado " << endl;
                return;
            }
            
        }

        cout << "Articulo no encontrado " << endl;
    }

    void deleteArticle(int id){
        

        if (listarticles.empty())
        {
            cout << " no hay articulos en el catalogo " << endl;
            return;
            
        }
        
        for (int i = 0; i<listarticles.size(); i++)
        {
            if (id==listarticles[i]->getid())
            {
                listarticles.erase(listarticles.begin() + i);
                cout << "Articulo eliminado " << endl;
                break;
            }
            
            
        }
    }

    shared_ptr<Article> searchArticle(int id){

        cout << "Buscando Articulo... " << endl;

        for (const auto & x : listarticles)
        {
            if (x->getid() == id)
            {
                return x;
            }
          
        }
        
        return nullptr;
    }

    
};


class User
{
private:
    string  name;
    string password;
    std::vector<shared_ptr<Article>> articlesbought;


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


class UserManager
{
private:
    std::vector<shared_ptr<User>> users;

public:
    UserManager(/* args */){};
    ~UserManager(){};

    void createuser(const string& name, const string& password){

        bool resultado = validatePassword(password);
        
        if (resultado!=true)
        {
            cout << "Warning: Al menos una mayuscula y al menos 2 simbolos especiales.... " << endl;
            return;
        }
        auto usernuevo = make_shared<User>();
        usernuevo->setname(name);
        usernuevo->setpassword(password);
        users.push_back(usernuevo);
        cout << "Usuario creado! " << endl;  

  
    }

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
    
        for (char c : password) {
            if (isupper(c)) mayus = true;
            if (ispunct(c)) simboloCount++; // Cuenta los símbolos especiales
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

struct DetallePedido {//se usa una estructura para guardar los articulos con sus respectivas cantidades, evitando modificar la clase Article.
    shared_ptr<Article> articulo;//comparte la misma referencia del objeto articulo
    int cantidad;//pero manejan diferentes cantidades...
};

class Pedido {
    private:

        shared_ptr<User> usuario;
        vector<DetallePedido> articulos;
    
    public:
        Pedido(shared_ptr<User> usuario) : usuario(usuario) {}
    
        void agregarArticulo(shared_ptr<Article> articulo, int cantidad) {
            if (!articulo->reduceStock(cantidad)) {
                cout << "Lo sentimos, no hay suficiente stock." << endl;
                return;

            }
            articulos.push_back({articulo, cantidad});

        }
    
        void mostrarPedido() const {
            cout << "Pedido de: " << usuario->getname() << endl;
            for (const auto& x : articulos) {
                cout << "Artículo: " << x.articulo->getname() << " | Cantidad: " << x.cantidad << endl;
            }
        }
    };
    




class UserInterfaz
{
private:
    shared_ptr<UserManager> usermanager;
    shared_ptr<ArticleManager> articlemanager;
    shared_ptr<User> UsuarioActual; 
    vector<shared_ptr<Pedido>> pedidos;  // Vector para guardar pedidos

    int contador;

    
    public:
    void requestDatasArticle(){
        string name;
        int id, stock;
        float precie;
        cout << "Ingrese el id del articulo: "; cin >> id;
        cout << "Ingrese el nombre del articulo:" ;cin >> name;
        cout << "Ingrese el stock del articulo:" ;cin >> stock;
        cout << "Ingrese el precio del articulo:" ;cin >> precie;

        articlemanager->createarticle(id,name,stock,precie);
    
    }

    void changepassword(){
        string newPassword;
        cout << "Ingrese nueva contrasenia: "; cin >> newPassword;

        usermanager->changePassword(UsuarioActual,newPassword);

    }

    void showusers(){
    
        usermanager->showUsers();
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
    
            UsuarioActual = usermanager->searchUser(name, password);
    
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
            cout << "1 - Cambiar contrasenia. "<< endl;
            cout << "0 - Regresar al menu. " << endl;
            cout <<"Opcion "; cin >> opcion;
    
            switch (opcion) {
                case 1: changepassword(); break;
                case 0: cout << "Regresando al menu...\n"; break;
                default: cout << "Opcion invalida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }
    
    void requestDatasUser(){
        string name;
        string password;
        cout << "Ingrese el usuario:" << endl;
        cin >>name;
        cout << "Ingrese el pasword:" << endl;
        cin >> password;
        
        usermanager->createuser(name,password);
        
    
  
    }


    void showarticles(){
        articlemanager->showArticles();
    }

    void modificatearticle(){

        float precie;
        int id;
        cout << "Ingrese el id del articulo: "; cin >> id;
        shared_ptr<Article> articulo = articlemanager->searchArticle(id);
        
        if (articulo == nullptr)
        {
            cout << "Id del articulo incorrecto. " << endl;
            return;
        }
        cout << "Ingrese el nuevo precio: "; cin >> precie;
        articlemanager->modificateArticle(id,precie);
    }

    void deletearticle(){
        int id;
        cout << "Ingrese el id del articulo a eliminar: "; cin >> id;
        shared_ptr<Article> articulo = articlemanager->searchArticle(id);
        
        if (articulo == nullptr)
        {
            cout << "Articulo no encontrado " << endl;
            return;
        }
        articlemanager->deleteArticle(id);
    }


    UserInterfaz(shared_ptr<UserManager> usermanager, shared_ptr<ArticleManager> articlemanager){
        UsuarioActual = nullptr;
        this->usermanager = usermanager;
        this->articlemanager = articlemanager;


    };
    
    ~UserInterfaz(){};

    void hacerPedido() {
        if (UsuarioActual == nullptr) {
            cout << "Usuario no logueado aun. Necesita iniciar sesion primero!" << endl;
            return;
        }

        string letra;
        int id, cantidad;
        shared_ptr<Pedido> nuevoPedido= make_shared<Pedido>(UsuarioActual);//se crea UN pedido
        do
        {
            cout << "Ingrese el ID del articulo a comprar: "; cin >> id;
        
            shared_ptr<Article> article = articlemanager->searchArticle(id);
                if (article == nullptr) {
                    cout << "ID del articulo incorrecto." << endl;
                    continue;
                }
    
            cout << "Ingrese la cantidad: "; cin >> cantidad;
            nuevoPedido->agregarArticulo(article, cantidad);//se agregan los articulos q desee


            cout << "Compra realizada con exito.\n";
            
            
            cout << "Desea comprar otro articulo? (No/no, para no comprar mas) " << endl;
            cin >> letra;
            
        } while (letra != "No" && letra != "no");
        
        pedidos.push_back(nuevoPedido);
    }

    void mostrarPedidos() {
        if (pedidos.empty()) {
            cout << "No hay pedidos registrados." << endl;
            return;
        }

        cout << "Pedidos realizados:\n";
        for (const auto& pedido : pedidos) {
            pedido->mostrarPedido();
        }
    }
        
    
    void showOnlyUser(){
        string name,password;
        cout << "Ingrese el usuario: ";
        cin >> name;
        cout << "Ingrese la contrasenia: ";
        cin >> password;

        auto usuario = usermanager->searchUser(name, password);

        if (usuario == nullptr) {
            cout << "Usuario y/o contrasenia incorrecta." << endl;
            return;
            
        }

        cout << "Nombre: " << usuario->getname() << endl;
        cout << "Password: " << usuario->getpasword() << endl;
    }


 
};

class MenuHandler 
{
    private:
        shared_ptr<UserInterfaz> userInterfaz;
    
    public:
        MenuHandler(shared_ptr<UserInterfaz> ui){
        userInterfaz=ui;}
        
        void showMenu() {
            int opcion;
            do {
                cout << "------------------Menu-------------- " << endl;
                cout << "1- Iniciar Sesion. " << endl;
                cout << "2- Crear cuenta de Usuario. " << endl;
                cout << "3- Mostrar usuarios. " << endl;
                cout << "4- Mostrar un usuario por nombre. " << endl;
                cout << "5- Crear Articulo. " << endl;
                cout << "6- Mostrar Articulos. " << endl;
                cout << "7- Modificar Articulo. " << endl;
                cout << "8- Eliminar Articulo. " << endl;
                cout << "9- Hacer Pedido. " << endl;
                cout << "10- Mostrar Pedido. " << endl;
                cout << "0- Salir del programa." << endl;
                cout << "Opcion: "; cin >> opcion;
                
                switch (opcion) {
                    case 1: userInterfaz->login(); break;
                    case 2: userInterfaz->requestDatasUser(); break;
                    case 3: userInterfaz->showusers(); break;
                    case 4: userInterfaz->showOnlyUser(); break;
                    case 5: userInterfaz->requestDatasArticle(); break;
                    case 6: userInterfaz->showarticles(); break;
                    case 7: userInterfaz->modificatearticle(); break;
                    case 8: userInterfaz->deletearticle(); break;
                    case 9: userInterfaz->hacerPedido(); break;
                    case 10: userInterfaz->mostrarPedidos(); break;
                    case 0: cout << "Usted salio del programa. " << endl; break;
                    default: cout << "Opcion invalida. Intente de nuevo." << endl;
                }
            } while (opcion != 0);
        }
    };




int main(){


shared_ptr<UserManager> usermanager = make_shared<UserManager>();
shared_ptr<ArticleManager> articlemanager = make_shared<ArticleManager>();

//creo los articulos
auto article1 = make_shared<Article>(1,"Lavandina x 1L");
auto article2 = make_shared<Article>(2, "Detergente x 500ml");
auto article3 = make_shared<Article>(3, "Jabon en polvo x 250g");

article1->setstock(4);
article2->setstock(5);
article3->setstock(10);

article1->setprecie(875.25);
article2->setprecie(1102.45);
article3->setprecie(650.22);

articlemanager->insertArticles(article1);
articlemanager->insertArticles(article2);
articlemanager->insertArticles(article3);


//creo los usuarios
auto user1 = make_shared<User>();
auto user2 = make_shared<User>();
auto user3 = make_shared<User>();

user1->setname("sebastian");
user1->setpassword("Catalina32@");

user2->setname("juan");
user2->setpassword("Juancortez5@");

user3->setname("diego");
user3->setpassword("Diegoguaraz22@");

usermanager->insertUsers(user1);
usermanager->insertUsers(user2);
usermanager->insertUsers(user3);


shared_ptr<UserInterfaz> App = make_shared<UserInterfaz>(usermanager,articlemanager);
shared_ptr<MenuHandler> menu = make_shared<MenuHandler>(App);

menu->showMenu(); 
    


return 0;

}

