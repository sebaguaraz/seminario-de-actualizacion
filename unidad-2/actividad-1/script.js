class View extends HTMLElement {

    constructor() {

        super()

        this.className = "calculator_content";

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


        this.button0.textContent = 0;
        this.button0.value = 0
        this.button0.className = "bttn_blue";

        this.button1.textContent = 1;
        this.button1.value = 1
        this.button1.className = "bttn_blue";

        this.button2.textContent = 2;
        this.button2.value = 2
        this.button2.className = "bttn_blue";

        this.button3.textContent = 3;
        this.button3.value = 3
        this.button3.className = "bttn_blue";

        this.button4.textContent = 4;
        this.button4.value = 4
        this.button4.className = "bttn_blue";

        this.button5.textContent = 5;
        this.button5.value = 5
        this.button5.className = "bttn_blue";

        this.button6.textContent = 6;
        this.button6.value = 6
        this.button6.className = "bttn_blue";

        this.button7.textContent = 7;
        this.button7.value = 7
        this.button7.className = "bttn_blue";

        this.button8.textContent = 8;
        this.button8.value = 8
        this.button8.className = "bttn_blue";

        this.button9.textContent = 9;
        this.button9.value = 9
        this.button9.className = "bttn_blue";

        this.button_negative.textContent = "-";
        this.button_negative.value = "-";
        this.button_negative.className = "bttn_green";

        this.button_positive.textContent = "+";
        this.button_positive.value = "+";
        this.button_positive.className = "bttn_green";

        this.button_multiplication.textContent = "x";
        this.button_multiplication.value = "*";
        this.button_multiplication.className = "bttn_green";

        this.button_division.textContent = "/";
        this.button_division.value = "/";
        this.button_division.className = "bttn_green";

        this.button_point.textContent = ".";
        this.button_point.value = ".";
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

    }

    connectedCallback() {

        this.button_delete.onclick = this.deleteAccount.bind(this)

        this.button0.onclick = this.getNumber.bind(this);
        this.button1.onclick = this.getNumber.bind(this);
        this.button2.onclick = this.getNumber.bind(this);
        this.button3.onclick = this.getNumber.bind(this);
        this.button4.onclick = this.getNumber.bind(this);
        this.button5.onclick = this.getNumber.bind(this);
        this.button6.onclick = this.getNumber.bind(this);
        this.button7.onclick = this.getNumber.bind(this);
        this.button8.onclick = this.getNumber.bind(this);
        this.button9.onclick = this.getNumber.bind(this);


        this.button_division.onclick = this.getNumber.bind(this);
        this.button_multiplication.onclick = this.getNumber.bind(this);
        this.button_positive.onclick = this.getNumber.bind(this);
        this.button_negative.onclick = this.getNumber.bind(this);

        this.button_equal.onclick = this.calculate.bind(this);
        this.button_point.onclick = this.getNumber.bind(this);
    }

    disconnectedCallback() {

        this.button0.onclick = null
        this.button1.onclick = null
        this.button2.onclick = null
        this.button3.onclick = null
        this.button4.onclick = null
        this.button5.onclick = null
        this.button6.onclick = null
        this.button7.onclick = null
        this.button8.onclick = null
        this.button9.onclick = null

        this.button_division.onclick = null
        this.button_multiplication.onclick = null
        this.button_positive.onclick = null
        this.button_negative.onclick = null

        this.button_equal.onclick = null
        this.button_point.onclick = null

    }

    //* sirve para que el controlador o el modelo le manden datos a la vista y la vista se actualice.
    setNumber(result) {
        this.view.textContent = result
    }

    //* sirve para que la vista le entregue datos al controlador o al modelo.
    getNumber(event) {

        let value = event.target.value

        this.dispatchEvent(new CustomEvent("buttonClick", { detail: value }))
    }

    calculate() {

        this.dispatchEvent(new CustomEvent("request", { detail: "calculate" }))

    }

    deleteAccount() {

        this.dispatchEvent(new CustomEvent("request", { detail: "delete" }))


    }



}




class Controller {

    constructor(object_view, object_model) {

        this.view = object_view
        this.model = object_model

    }

    enable() {

        this.view.addEventListener("request", this.onViewRequest.bind(this))

        this.view.addEventListener("buttonClick", this.onViewRequestButton.bind(this))

        this.model.addEventListener("change", this.onModelChange.bind(this))

    }

    onModelChange() {
        console.log("cambio el modelo, controlador! avisale a la vista q actualice...")
        const result = this.model.getData()
        this.view.setNumber(result)

    }


    onViewRequest(event) {

        if (event.detail == "calculate") {

            let result = this.model.calculate()
            this.view.setNumber(result)

            this.model.clear()

        } else if (event.detail == "delete") {

            this.model.clear()
            this.view.setNumber(this.model.getData())

        }

    }

    onViewRequestButton(event) {
        console.log(event.detail)
        this.model.setData(event.detail)

    }


}


class Model extends EventTarget {

    constructor() {
        super()
        this.account = ""
        this.result = 0
    }

    //* recibe el dato que llega desde la vista cuando ocurre EVENTO "REQUEST", lo guarda dentro del modelo
    setData(data) {


        if (this.account == "") {
            this.account = data
        } else {
            this.account += data
        }

        this.changed()

    }

    //* devuelve el valor del modelo cuando ocurre el evento CHANGE EN LA CLASE, al controlador para darselo a la vista y actualice 
    getData() {
        return this.account
    }

    calculate() {

        this.result = eval(this.account);
        return this.result

    }

    clear() {

        this.account = ""
        this.result = 0
    }

    changed() {

        this.dispatchEvent(new CustomEvent("change"))

    }

}


customElements.define("x-view", View);







function init() {

    const object_view = new View();
    const object_model = new Model();
    const controller = new Controller(object_view, object_model)

    controller.enable()

    // * cuando lo agrega al DOM. Agrega el elemento HTML
    document.body.appendChild(object_view);

}



window.onload = init;
