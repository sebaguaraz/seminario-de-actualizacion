// * COMPONENTE que hereda y actua como elemento HTML
class Calculator_Component extends HTMLElement {

    constructor() {
        super();

        this.cuenta = "";

        this.className = "calculator_content";
        // * Elementos HTML que tiene el COMPONENTE como propiedades 

        this.view = document.createElement("div");
        this.view.className = "pantalla";
        // botones numericos
        this.button0 = document.createElement("button");
        this.button1 = document.createElement("button");
        this.button2 = document.createElement("button");
        this.button3 = document.createElement("button");
        this.button4 = document.createElement("button");
        this.button5 = document.createElement("button");
        this.button6 = document.createElement("button");
        this.button7 = document.createElement("button");
        this.button8 = document.createElement("button");
        this.button9 = document.createElement("button");

        // botones de operacion
        this.button_negative = document.createElement("button");
        this.button_positive = document.createElement("button");
        this.button_multiplication = document.createElement("button");
        this.button_division = document.createElement("button");

        // botones especiales
        this.button_point = document.createElement("button");
        this.button_equal = document.createElement("button");
        this.button_delete = document.createElement("button")

        this.view.textContent = "0";

        this.button0.textContent = 0;
        this.button0.className = "bttn_blue";
        this.button1.textContent = 1;
        this.button1.className = "bttn_blue";
        this.button2.textContent = 2;
        this.button2.className = "bttn_blue";
        this.button3.textContent = 3;
        this.button3.className = "bttn_blue";
        this.button4.textContent = 4;
        this.button4.className = "bttn_blue";
        this.button5.textContent = 5;
        this.button5.className = "bttn_blue";
        this.button6.textContent = 6;
        this.button6.className = "bttn_blue";
        this.button7.textContent = 7;
        this.button7.className = "bttn_blue";
        this.button8.textContent = 8;
        this.button8.className = "bttn_blue";
        this.button9.textContent = 9;
        this.button9.className = "bttn_blue";

        this.button_negative.textContent = "-";
        this.button_negative.className = "bttn_green"  ;
        this.button_positive.textContent = "+";
        this.button_positive.className = "bttn_green";
        this.button_multiplication.textContent = "x";
        this.button_multiplication.className = "bttn_green";
        this.button_division.textContent = "/";
        this.button_division.className = "bttn_green";
        this.button_point.textContent = ".";
        this.button_point.className = "bttn_blue";
        this.button_equal.textContent = "=";
        this.button_equal.className = "bttn_yellow";
        this.button_delete.textContent = "Borrar";
        this.button_delete.className = "bttn_red";


        this.table = document.createElement("table");
        this.table.className = "table-content";
        this.tr1 = document.createElement("tr");
        this.tr2 = document.createElement("tr");
        this.tr3 = document.createElement("tr");
        this.tr4 = document.createElement("tr");

        this.td1 = document.createElement("td");
        this.td2 = document.createElement("td");
        this.td3 = document.createElement("td");
        this.td4 = document.createElement("td");
        this.td5 = document.createElement("td");
        this.td6 = document.createElement("td");
        this.td7 = document.createElement("td");
        this.td8 = document.createElement("td");
        this.td9 = document.createElement("td");
        this.td10 = document.createElement("td");
        this.td11 = document.createElement("td");
        this.td12 = document.createElement("td");
        this.td13 = document.createElement("td");
        this.td14 = document.createElement("td");
        this.td15 = document.createElement("td");
        this.td16 = document.createElement("td");

        this.appendChild(this.view);
        this.appendChild(this.table);
        this.table.appendChild(this.tr1);
        this.table.appendChild(this.tr2);
        this.table.appendChild(this.tr3);
        this.table.appendChild(this.tr4);

        this.tr1.appendChild(this.td1);
        this.tr1.appendChild(this.td2);
        this.tr1.appendChild(this.td3);
        this.tr1.appendChild(this.td4);
        this.tr2.appendChild(this.td5);
        this.tr2.appendChild(this.td6);
        this.tr2.appendChild(this.td7);
        this.tr2.appendChild(this.td8);
        this.tr3.appendChild(this.td9);
        this.tr3.appendChild(this.td10);
        this.tr3.appendChild(this.td11);
        this.tr3.appendChild(this.td12);
        this.tr4.appendChild(this.td13);
        this.tr4.appendChild(this.td14);
        this.tr4.appendChild(this.td15);
        this.tr4.appendChild(this.td16);


        this.td1.appendChild(this.button7);
        this.td2.appendChild(this.button8);
        this.td3.appendChild(this.button9);
        this.td4.appendChild(this.button_positive);
        this.td5.appendChild(this.button4);
        this.td6.appendChild(this.button5);
        this.td7.appendChild(this.button6);
        this.td8.appendChild(this.button_multiplication);
        this.td9.appendChild(this.button1);
        this.td10.appendChild(this.button2);
        this.td11.appendChild(this.button3);
        this.td12.appendChild(this.button_negative);
        this.td13.appendChild(this.button0);
        this.td14.appendChild(this.button_point);
        this.td15.appendChild(this.button_equal);
        this.td16.appendChild(this.button_division);
        
        this.appendChild(this.button_delete);

    };

    // * este metodo se ejecuta al agregar la instancia de la clase en el DOM
    connectedCallback() {

        this.view.textContent = 0;
        // *asocia esta funcion al elemento cuando ocurre un evento y cuando se usa THIS dentro de la funcion hace referencia en que elemento ocurrio el evento. osea <BUTTON></BUTTON>
        // this.button_delete.onclick = this.deleteAccount;


        // * REFERENCIA DE THIS a ELEMENTO: asocio un arrow function ()=>{} (funcion sin nombre) a un elemento cuando ocurre un evento y cuando uso el THIS dentro de la funcion hace referencia a propiedades de la clase: MALA PRACTICA xq ARROW FUNCTION ocupa espacio en la memoria del navegador

        // * REFERENCIA DE THIS a CLASE: se pasa como parametro el contexto de la clase con .bind()
        this.button_delete.onclick = this.deleteAccount.bind(this); 

        this.button0.onclick = this.addNumber.bind(this,"0");         
        this.button1.onclick = this.addNumber.bind(this, "1"); 
        this.button2.onclick = this.addNumber.bind(this , "2"); 
        this.button3.onclick = this.addNumber.bind(this , "3"); 
        this.button4.onclick = this.addNumber.bind(this , "4"); 
        this.button5.onclick = this.addNumber.bind(this , "5"); 
        this.button6.onclick = this.addNumber.bind(this , "6"); 
        this.button7.onclick = this.addNumber.bind(this , "7"); 
        this.button8.onclick = this.addNumber.bind(this , "8"); 
        this.button9.onclick = this.addNumber.bind(this , "9"); 


        this.button_division.onclick = this.addNumber.bind(this, "/"); 
        this.button_multiplication.onclick = this.addNumber.bind(this , "*"); 
        this.button_positive.onclick = this.addNumber.bind(this , "+"); 
        this.button_negative.onclick = this.addNumber.bind(this , "-"); 

        this.button_equal.onclick = this.calculate.bind(this); 
        this.button_point.onclick = this.addNumber.bind(this , "."); 
    }


    addNumber(number) {

        if (this.cuenta === "") {
            this.cuenta = number;
        } else {
            this.cuenta += number;
        }

        this.view.textContent = this.cuenta;
    }

    deleteAccount() {

        this.view.textContent = 0;
        this.cuenta = "";

    }

    addOperation(operation) {

        this.cuenta += operation;

        this.view.textContent = this.cuenta;
    }

    calculate() {

        let result = eval(this.cuenta);

        this.view.textContent = result;

    }

    // * este metodo se ejecuta al eliminar la instancia de la clase en el DOM
    disconnectedCallback() {

    }


}

// * le dice al navegador que aprenda que la clase esta asociada con la etiqueta html <calculator-component>.
customElements.define("calculator-component", Calculator_Component);



function init() {
    // * es una instancia de la clase y un elemento HTML a la vez llamado <calculator-component> </calculator-component>
    const calculator = new Calculator_Component();


    // * cuando lo agrega al DOM. Agrega el elemento HTML
    document.body.appendChild(calculator);

}



window.onload = init;