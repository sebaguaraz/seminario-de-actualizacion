void cambiarContrasenia(){
    string password;
    cout << "Ingrese nueva contrasenia: "; cin >> password;

    empresa->cambiarcontrasenia(UsuarioActual,password);

}