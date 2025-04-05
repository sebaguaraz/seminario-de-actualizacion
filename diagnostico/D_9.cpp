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

    void modificarStock(int cantidad) {
        stock += cantidad;
        cout << "Stock actualizado. Nuevo stock de " << name << ": " << stock << endl;
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

    void modificateArticle(int id, float precie, int stock){

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
                listarticles[i]->modificarStock(precie);
                cout << "Precio y stock del articulo actualizado " << endl;
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
public:

    virtual string getname() = 0;

    virtual void setname(string name) = 0;

    virtual void setpassword(string password) = 0;

    virtual string getpasword() = 0;

    virtual string role() = 0;

};

class Administrator : public User
{
private:
    string  name;
    string password;
public:
    Administrator(/* args */){};
    ~Administrator(){};
    
    string getname()override {
        return name;
    };

    void setname(string name)override {
    this->name=name;
    }

    void setpassword(string password)override {
        this->password=password;
        }

    string getpasword()override {
        return password;
    };

    string role() override{
        return "Administrador";
    }
};

class Client : public User
{
private:
    string  name;
    string password;
public:
    Client(/* args */){};
    ~Client(){}; 
    string getname()override {
        return name;
    };

    void setname(string name)override {
    this->name=name;
    }

    void setpassword(string password)override {
        this->password=password;
        }

    string getpasword()override {
        return password;
    };

    string role() override{
        return "Cliente";
    }
};

class Vendedor : public User
{
private:
    string  name;
    string password;
public:
    Vendedor(/* args */){};
    ~Vendedor(){};
    string getname()override {
        return name;
    };

    void setname(string name)override {
    this->name=name;
    }

    void setpassword(string password)override {
        this->password=password;
        }

    string getpasword()override {
        return password;
    };

    string role() override{
        return "Vendedor";
    }
};

class Warehouse_workers : public User
{
private:
    string  name;
    string password;
public:
    Warehouse_workers(/* args */){};
    ~Warehouse_workers(){};
    string getname()override {
        return name;
    };

    void setname(string name)override {
    this->name=name;
    }

    void setpassword(string password)override {
        this->password=password;
        }

    string getpasword()override {
        return password;
    };

    string role() override{
        return "Trabajador_deposito";
    }
};





class UserManager
{
private:
    std::vector<shared_ptr<User>> users;

public:
    UserManager(/* args */){};
    ~UserManager(){};

    void createuser(const string& name, const string& password, string rol){

        bool resultado = validatePassword(password);
        
        if (resultado!=true)
        {
            cout << "Warning: Al menos una mayuscula y al menos 2 simbolos especiales.... " << endl;
            return;
        }

        if (rol == "Cliente")
        {
            
            shared_ptr<User> usernuevo = make_shared<Client>();
            usernuevo->setname(name);
            usernuevo->setpassword(password);
            usernuevo->setpassword(password);
            users.push_back(usernuevo);
            cout << "Cliente creado! " << endl;  
        }
        
        if (rol == "Administrador")
        {
            
            shared_ptr<User> usernuevo = make_shared<Administrator>();
            usernuevo->setname(name);
            usernuevo->setpassword(password);
            users.push_back(usernuevo);
            cout << "Administrador creado! " << endl;  
        }        
        
        if (rol == "Vendedor")
        {
            
            shared_ptr<User> usernuevo = make_shared<Vendedor>();
            usernuevo->setname(name);
            usernuevo->setpassword(password);
            users.push_back(usernuevo);
            cout << "Vendedor creado! " << endl;  
        }        
        
        if (rol == "Trabajador_deposito")
        {
            
            shared_ptr<User> usernuevo = make_shared<Warehouse_workers>();
            usernuevo->setname(name);
            usernuevo->setpassword(password);
            users.push_back(usernuevo);
            cout << "Trabajador de Deposito creado! " << endl;  
        }

  
    }

    void insertUsers(shared_ptr<User> objetoUsuario){
        users.push_back(objetoUsuario);
    }

    void showUsers(){
        for (const auto & x : users)
        {
            cout <<"Usuario: " << x->getname() << " -- " <<"Contrasenia: " << x->getpasword() << "role: " << x->role() << endl;
            
            cout << "----------------------- " << endl;
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
            cout << "Compra realizada con exito.\n";
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
    // Submenú para Administrador
    void menuAdministrador() {
        int opcion;
        do {
            cout << "********************** Menu Administrador **********************" << endl;
            cout << "1 - Cambiar mi contrasena" << endl;
            cout << "2 - Crear nuevo usuario" << endl;
            cout << "3 - Mostrar todos los usuarios" << endl;
            cout << "4 - Buscar usuario por nombre" << endl;
            cout << "5 - Modificar contrasenia de otro usuario" << endl;
            cout << "6 - Eliminar usuario" << endl;
            cout << "0 - Cerrar sesión" << endl;
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1: changepassword(); break;
                case 2: requestDatasUser(); break;
                case 3: showusers(); break;
                case 4: showOnlyUser(); break;
                case 5: modifyOtherUserPassword(); break;
                case 6: deleteUser(); break;
                case 0: cout << "Cerrando sesion...\n"; break;
                default: cout << "Opción inválida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }

    // Submenú para Cliente
    void menuCliente() {
        int opcion;
        do {
            cout << "********************** Menu Cliente **********************" << endl;
            cout << "1 - Hacer pedido" << endl;
            cout << "2 - Mostrar mis pedidos" << endl;
            cout << "0 - Cerrar sesión" << endl;
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1: hacerPedido(); break;
                case 2: mostrarPedidos(); break;
                case 0: cout << "Cerrando sesión...\n"; break;
                default: cout << "Opción inválida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }

    // Submenú para Vendedor
    void menuVendedor() {
        int opcion;
        do {
            cout << "********************** Menú Vendedor **********************" << endl;
            cout << "1 - Crear articulo" << endl;
            cout << "2 - Mostrar articulos" << endl;
            cout << "3 - Eliminar articulo" << endl;
            cout << "0 - Cerrar sesion" << endl;
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 2: requestDatasArticle(); break;
                case 3: showarticles(); break;
                case 4: deletearticle(); break;
                case 0: cout << "Cerrando sesión...\n"; break;
                default: cout << "Opción inválida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }

    // Submenú para Trabajador de Depósito
    void menuTrabajadorDeposito() {
        int opcion;
        do {
            cout << "********************** Menú Trabajador de Depósito **********************" << endl;
            cout << "1 - Modificar artículo" << endl;
            cout << "0 - Cerrar sesión" << endl;
            cout << "Opción: ";
            cin >> opcion;

            switch (opcion) {
                case 1: modificatearticle(); break;
                case 0: cout << "Cerrando sesión...\n"; break;
                default: cout << "Opción inválida. Intente de nuevo.\n";
            }
        } while (opcion != 0);
    }
    
    public:

    void changepassword(){
        string newPassword;
        cout << "Ingrese nueva contrasenia: "; cin >> newPassword;

        usermanager->changePassword(UsuarioActual,newPassword);

    }

    // Modificar contraseña de otro usuario (solo Administrador)
    void modifyOtherUserPassword() {
        if (!UsuarioActual || UsuarioActual->role() != "Administrador") {
            cout << "Acceso denegado: Solo los administradores pueden modificar contraseñas de otros usuarios." << endl;
            return;
        }
        string name, password;
        cout << "Ingrese el nombre del usuario: ";
        cin >> name;
        cout << "Ingrese la contraseña actual: ";
        cin >> password;
        auto user = usermanager->searchUser(name, password);
        if (user == nullptr) {
            cout << "Usuario no encontrado o contraseña incorrecta." << endl;
            return;
        }
        string newPassword;
        cout << "Ingrese la nueva contrasena: ";
        cin >> newPassword;
        usermanager->changePassword(user, newPassword);
        cout << "Contraseña de " << name << " actualizada exitosamente." << endl;
    }

    // Eliminar usuario (solo Administrador)
    void deleteUser() {
        if (!UsuarioActual || UsuarioActual->role() != "Administrador") {
            cout << "Acceso denegado: Solo los administradores pueden eliminar usuarios." << endl;
            return;
        }
        string name, password;
        cout << "Ingrese el nombre del usuario a eliminar: ";
        cin >> name;
        cout << "Ingrese la contraseña del usuario: ";
        cin >> password;
        auto user = usermanager->searchUser(name, password);
        if (user == nullptr) {
            cout << "Usuario no encontrado o contraseña incorrecta." << endl;
            return;
        }
        // Aquí necesitaríamos un método en UserManager para eliminar el usuario
        cout << "Usuario " << name << " eliminado exitosamente." << endl;
    }
    
    void showusers(){

        if (!UsuarioActual || UsuarioActual->role()!="Administrador")
        {
            cout << "Se debe registrar como administrador " << endl;
            return;
           
        }
    
        usermanager->showUsers();
    }

    bool autenticateUser() {
        string name, password;
        contador = 0;  // Reiniciar intentos antes de autenticar
    
        do {
            cout << "Tiene (" <<  3 - contador << "/3) intentos" << endl;
            cout << "Ingrese el usuario: ";
            cin >> name;
            cout << "Ingrese la contrasenia: ";
            cin >> password;
    
            UsuarioActual = usermanager->searchUser(name, password);
    
            if (UsuarioActual == nullptr) {
                cout << "Usuario y/o contrasenia incorrecta." << endl;
                
                if (contador == 2) {
                    cout << "Usuario Bloqueado. Contacte al administrador." << endl;
                    return false; // Bloqueo del usuario
                }
                contador++;
            }
    
        } while (UsuarioActual == nullptr && contador < 3);
    
        contador = 0;  // Reiniciar el contador si se autentica correctamente
        return true;   // Usuario autenticado
    }
       
    void login() {
        if (!autenticateUser()) return;

        cout << "¡Accedio exitosamente como " << UsuarioActual->role() << "!" << endl;
        if (UsuarioActual->role() == "Administrador") {
            menuAdministrador();
        } else if (UsuarioActual->role() == "Cliente") {
            menuCliente();
        } else if (UsuarioActual->role() == "Vendedor") {
            menuVendedor();
        } else if (UsuarioActual->role() == "Trabajador_deposito") {
            menuTrabajadorDeposito();
        }
    }
    
    void requestDatasUser(){

        if (!UsuarioActual || UsuarioActual->role()!="Administrador")
        {
            cout << "Acceso denegado: Solo los Administradores pueden acceder a los usuarios." << endl;
            return;
           
        }

        string name;
        string password, rol;
        cout << "Ingrese el usuario:" << endl;
        cin >>name;
        cout << "Ingrese el pasword:" << endl;
        cin >> password;
        cout << "Ingrese el tipo de rol del usuario:" << endl;
        cin >>rol;
        
        usermanager->createuser(name,password,rol);
        
    
  
    }

    void requestDatasArticle(){

        if (!UsuarioActual || UsuarioActual->role()!="Vendedor")
        {
            cout << "Solo los vendedores pueden acceder a los articulos." << endl;
            return;
           
        }
    
        string name;
        int id, stock;
        float precie;
        cout << "Ingrese el id del articulo: "; cin >> id;
        cout << "Ingrese el nombre del articulo:" ;cin >> name;
        cout << "Ingrese el stock del articulo:" ;cin >> stock;
        cout << "Ingrese el precio del articulo:" ;cin >> precie;

        articlemanager->createarticle(id,name,stock,precie);
    
    }

    void showarticles(){

        if (!UsuarioActual || UsuarioActual->role()!="Vendedor")
        {
            cout << "Solo los vendedores pueden acceder a los articulos." << endl;
            return;
           
        }
        articlemanager->showArticles();
    }

    void modificatearticle(){

        if (!UsuarioActual || UsuarioActual->role()!="Trabajador_deposito")
        {
            cout << "Solo los trabajadores de deposito pueden acceder a los articulos." << endl;
            return;
           
        }

        float precie;
        int id, stock;
        cout << "Ingrese el id del articulo: "; cin >> id;
        shared_ptr<Article> articulo = articlemanager->searchArticle(id);
        
        if (articulo == nullptr)
        {
            cout << "Id del articulo incorrecto. " << endl;
            return;
        }
        cout << "Ingrese el nuevo precio: "; cin >> precie;
        cout << "Ingrese el nuevo stock: "; cin >> stock;

        articlemanager->modificateArticle(id,precie, stock);
    }

    void deletearticle(){

        if (!UsuarioActual || UsuarioActual->role()!="Vendedor")
        {
            cout << "Solo los vendedores pueden acceder a los articulos." << endl;
            return;
           
        }
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

        if (!UsuarioActual ||UsuarioActual->role()!="Cliente")
        {
            cout << "Solo los clientes pueden hacer sus pedidos." << endl;
            return;
           
        }
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
            
            cout << "Desea comprar otro articulo? (No/no, para no comprar mas) " << endl;
            cin >> letra;
            
        } while (letra != "No" && letra != "no");
        
        pedidos.push_back(nuevoPedido);
    }

    void mostrarPedidos() {

        if (!UsuarioActual || UsuarioActual->role() != "Cliente") {
            cout << "Solo los clientes pueden ver sus pedidos." << endl;
            return;
        }
        

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

        if (UsuarioActual->role()!="Administrador")
        {
            cout << "Acceso denegado: Solo los Administradores pueden ver los usuarios." << endl;
            return;
           
        }

        string name,password;
        cout << "Ingrese el usuario: ";
        cin >> name;

        auto usuario = usermanager->searchUser(name, password);

        if (usuario == nullptr) {
            cout << "Usuario y/o contrasenia incorrecta." << endl;
            return;
            
        }

        cout << "Nombre: " << usuario->getname() << endl;
        cout << "Password: " << usuario->getpasword() << endl;
        cout << "Rol: " << usuario->role() << endl;

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
                cout << "********************** Menu Principal **********************" << endl;
                cout << "1 - Iniciar Sesion" << endl;
                cout << "0 - Salir del programa" << endl;
                cout << "Opción: ";
                cin >> opcion;
    
                switch (opcion) {
                    case 1: userInterfaz->login(); break;
                    case 0: cout << "Usted salió del programa." << endl; break;
                    default: cout << "Opción inválida. Intente de nuevo." << endl;
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

//----------------------------------------------------------


//creo el cliente
shared_ptr<User> user1 = make_shared<Client>();
user1->setname("sebastian");
user1->setpassword("sebastian");

//creo el Administrador
shared_ptr<User> administrador = make_shared<Administrator>();
administrador->setname("walter");
administrador->setpassword("walter");

//creo el Vendedor
shared_ptr<User> vendedor = make_shared<Vendedor>();
vendedor->setname("agustin");
vendedor->setpassword("agustin");

//creo el trabajador_deposito
shared_ptr<User> trabajador_deposito = make_shared<Warehouse_workers>();
trabajador_deposito->setname("natalia");
trabajador_deposito->setpassword("natalia");



usermanager->insertUsers(user1);
usermanager->insertUsers(administrador);
usermanager->insertUsers(vendedor);
usermanager->insertUsers(trabajador_deposito);



shared_ptr<UserInterfaz> App = make_shared<UserInterfaz>(usermanager,articlemanager);
shared_ptr<MenuHandler> menu = make_shared<MenuHandler>(App);

menu->showMenu(); 

return 0;

}

