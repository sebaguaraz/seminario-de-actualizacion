// Espera a que el HTML esté cargado
document.addEventListener("DOMContentLoaded", main);

function main() {
    // Elemento donde se muestra la cuenta
    const pantalla = document.getElementById("view");
    
    // Esta variable guarda toda la expresión que el usuario va formando
    let expresion = "0";

    // Obtener los botones por su id
    const cero = document.getElementById("0");
    const uno = document.getElementById("1");
    const dos = document.getElementById("2");
    const tres = document.getElementById("3");
    const cuatro = document.getElementById("4");
    const cinco = document.getElementById("5");
    const seis = document.getElementById("6");
    const siete = document.getElementById("7");
    const ocho = document.getElementById("8");
    const nueve = document.getElementById("9");

    const suma = document.getElementById("positive");
    const resta = document.getElementById("negative");
    const multiplicacion = document.getElementById("multiplication");
    const division = document.getElementById("division");
    const igual = document.getElementById("equal");
    const borrar = document.getElementById("clear");

    // Mostrar el valor inicial en la pantalla
    pantalla.textContent = expresion;

    // ---- Función que actualiza la pantalla con la expresión actual ----
    function actualizarPantalla() {
        pantalla.textContent = expresion;
    }

    // ---- Función para agregar un número ----
    function agregarNumero(digito) {
        // Si la expresión es "0" o está vacía, reemplazamos; si no, concatenamos
        if (expresion === "0" || expresion === "") {
            expresion = digito;
        } else {
            expresion = expresion + digito;
        }
        actualizarPantalla();
    }

    // ---- Asignar los eventos a cada número ----
    cero.addEventListener("click", () => agregarNumero("0"));
    uno.addEventListener("click", () => agregarNumero("1"));
    dos.addEventListener("click", () => agregarNumero("2"));
    tres.addEventListener("click", () => agregarNumero("3"));
    cuatro.addEventListener("click", () => agregarNumero("4"));
    cinco.addEventListener("click", () => agregarNumero("5"));
    seis.addEventListener("click", () => agregarNumero("6"));
    siete.addEventListener("click", () => agregarNumero("7"));
    ocho.addEventListener("click", () => agregarNumero("8"));
    nueve.addEventListener("click", () => agregarNumero("9"));

    // ---- Función para agregar un operador (+, -, *, /) ----
    function agregarOperador(op) {
        // Si la expresión está vacía, no agregamos operador
        if (expresion === "") return;

        // Agregar el operador
        expresion = expresion + op;
        actualizarPantalla();
    }

    // ---- Asignar eventos a los operadores ----
    suma.addEventListener("click", () => agregarOperador("+"));
    resta.addEventListener("click", () => agregarOperador("-"));
    multiplicacion.addEventListener("click", () => agregarOperador("*"));
    division.addEventListener("click", () => agregarOperador("/"));

    // ---- Función para calcular el resultado ----
    function calcular() {
        try {
            // Evaluar la expresión (eval convierte el texto en una operación matemática)
            let resultado = eval(expresion);
            // Mostrar el resultado en la pantalla
            pantalla.textContent = resultado;
        } catch (error) {
            // Si hay algún error (por ejemplo, división por cero o expresión mal formada)
            pantalla.textContent = "Error";
            expresion = "0";
            actualizarPantalla();
        }
    }

    // ---- Función para borrar todo ----
    function borrarTodo() {
        expresion = "0";
        actualizarPantalla();
    }

    // ---- Asignar eventos a igual y borrar ----
    igual.addEventListener("click", calcular);
    borrar.addEventListener("click", borrarTodo);
}