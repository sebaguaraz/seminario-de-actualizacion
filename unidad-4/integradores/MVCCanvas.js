class Model extends EventTarget {
    constructor() {
        super();
        this.listFigure = [];
    }

    changed() {
        this.dispatchEvent(new CustomEvent('changed'));
    }

    setFigure(figure) {
        this.listFigure.push(figure);
        this.changed();
    }

    getFigures() {
        return this.listFigure;
    }

    clearList() {
        this.listFigure = [];
        this.changed();
    }
}

class View extends HTMLElement {

    constructor(exerciseNumber) {
        super();

        this.exerciseNumber = exerciseNumber

        this._canvas = document.createElement('canvas');
        this._canvas.width = 800;
        this._canvas.height = 600;
        this.ctx = this._canvas.getContext('2d');
        this._canvas.style.border = "1px solid black";

        this.buttonClear = document.createElement("button");
        this.buttonClear.type = "button";
        this.buttonClear.textContent = "Limpiar";

        this.buttonAskFigure = document.createElement("button");
        this.buttonAskFigure.type = "button";
        this.buttonAskFigure.textContent = "Agregar figura";

        // * exercise 12
        this.labelTypeWidth = document.createElement("label");
        this.labelTypeWidth.textContent = "Grosor de línea: ";
        this.labelTypeWidth.htmlFor = "typeWidth";
        // * exercise 12
        this.InputTypeWidth = document.createElement("input");
        this.InputTypeWidth.id = "typeWidth";
        this.InputTypeWidth.type = "number";
        this.InputTypeWidth.min = "1";
        this.InputTypeWidth.max = "100";
        this.InputTypeWidth.step = "1";
        this.InputTypeWidth.value = "2";
        this.InputTypeWidth.required = true;
        // * exercise 12
        this.labelTypeLine = document.createElement("label");
        this.labelTypeLine.textContent = "Tipo de línea: ";
        this.labelTypeLine.htmlFor = "typeLine";
        // * exercise 12
        this.InputTypeLine = document.createElement("select");
        this.InputTypeLine.id = "typeLine";
        this.InputTypeLine.required = true;
        // * exercise 12
        this.option1 = document.createElement("option");
        this.option2 = document.createElement("option");
        // * exercise 12
        this.option1.textContent = "continua";
        this.option1.value = "continua";
        this.option2.textContent = "discontinua";
        this.option2.value = "discontinua";

        // * exercise 19
        this.labelSelectFigure = document.createElement("label")
        this.labelSelectFigure.textContent = "seleccione la figura a cargar (Círculo, Polígono, Grafico de Torta)"
        // * exercise 19
        this.inputSelectFigure = document.createElement("select")
        this.inputSelectFigure.value = "poligono"
        this.inputSelectFigure.required = true;
        // * exercise 19
        this.optionSelectPoligono = document.createElement("option")
        this.optionSelectPoligono.textContent = "poligono"
        this.optionSelectPoligono.value = "poligono"

        this.optionSelectCirculo = document.createElement("option")
        this.optionSelectCirculo.textContent = "circulo"
        this.optionSelectCirculo.value = "circulo"

        this.optionSelectGraficoTorta = document.createElement("option")
        this.optionSelectGraficoTorta.textContent = "Grafico de Torta"
        this.optionSelectGraficoTorta.value = "GraficoTorta"

        this.appendChild(this._canvas);
        this.showButtons()

    }

    showButtons() {

        this.appendChild(this.buttonClear);
        this.appendChild(this.buttonAskFigure);

        if (this.exerciseNumber === 6) {
            return
        }

        if (this.exerciseNumber === 12) {
            this.appendChild(this.labelTypeLine);
            this.appendChild(this.InputTypeLine);
            this.InputTypeLine.appendChild(this.option1);
            this.InputTypeLine.appendChild(this.option2);
            this.appendChild(this.labelTypeWidth);
            this.appendChild(this.InputTypeWidth);
            return

        }

        if (this.exerciseNumber === 19) {
            this.appendChild(this.labelTypeLine);
            this.appendChild(this.InputTypeLine);
            this.InputTypeLine.appendChild(this.option1);
            this.InputTypeLine.appendChild(this.option2);
            this.appendChild(this.labelTypeWidth);
            this.appendChild(this.InputTypeWidth);
            this.appendChild(this.labelSelectFigure)
            this.appendChild(this.inputSelectFigure)
            this.inputSelectFigure.appendChild(this.optionSelectPoligono)
            this.inputSelectFigure.appendChild(this.optionSelectCirculo)
            this.inputSelectFigure.appendChild(this.optionSelectGraficoTorta)
            return

        }

    }

    randomColor() {
        const rojo = Math.floor(Math.random() * 256);
        const verde = Math.floor(Math.random() * 256);
        const azul = Math.floor(Math.random() * 256);

        return `rgb(${rojo}, ${verde}, ${azul})`;
    }

    render(listFigures) {
        this.clear();

        if (listFigures.length === 0) {
            return;
        }

        for (const element of listFigures) {

            if (element.tipo === "circulo") {
                this.drawCircle(element);
            }

            if (element.tipo === "poligono") {

                this.drawPolygon(element);
            }

            if (element.tipo === "GraficoTorta") {

                this.drawCakeGraph(element);
            }
        }
    }

    drawCircle(element) {

        const typeWidth = element.typeWidth || 1;
        const typeLine = element.typeLine || "continua";

        this.ctx.beginPath();
        this.ctx.lineWidth = typeWidth;
        if (typeLine === "discontinua") {
            this.ctx.setLineDash([5, 5]);
        } else {
            this.ctx.setLineDash([])
        }
        this.ctx.arc(element.x, element.y, element.radio, 0, 2 * Math.PI);
        this.ctx.closePath();
        this.ctx.stroke();
    }

    drawPolygon(element) {

        const typeWidth = element.typeWidth || 1;
        const typeLine = element.typeLine || "continua";


        this.ctx.beginPath();
        this.ctx.lineWidth = typeWidth;
        if (typeLine === "discontinua") {
            this.ctx.setLineDash([5, 5]);
        } else {
            this.ctx.setLineDash([])
        }
        this.ctx.moveTo(
            element.x + element.puntos[0].x,
            element.y + element.puntos[0].y
        );

        for (let pos = 1; pos < element.puntos.length; pos++) {
            this.ctx.lineTo(element.x + element.puntos[pos].x, element.y + element.puntos[pos].y);
        }

        this.ctx.closePath();
        this.ctx.stroke();
    }

    drawCakeGraph(element) {

        this.ctx.lineWidth = element.typeWidth || 1;

        if (element.typeLine === "discontinua") {
            this.ctx.setLineDash([5, 5]);
        } else {
            this.ctx.setLineDash([]);
        }


        this.ctx.beginPath()
        this.ctx.moveTo(element.x, element.y)
        let anguloInicial = 0
        let anguloPorcion = 0
        let anguloFinal = 0
        let posicionTexto = 0

        for (const dato of element.datos) {

            this.ctx.beginPath()
            this.ctx.moveTo(element.x, element.y)

            anguloPorcion = dato.valor / 100 * Math.PI * 2
            anguloFinal = anguloInicial + anguloPorcion

            this.ctx.arc(element.x, element.y, element.radio, anguloInicial, anguloFinal)

            this.ctx.fillStyle = this.randomColor()
            this.ctx.fill()

            this.ctx.strokeStyle = "black"
            this.ctx.stroke()

            this.ctx.fillStyle = "black";
            this.ctx.fillText(dato.etiqueta, element.x + element.radio + 20, element.y + posicionTexto);

            this.ctx.closePath()

            anguloInicial = anguloFinal
            posicionTexto += 20;

        }
        this.ctx.closePath()
    }

    clear() {
        this.ctx.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    askFigure() {
        this.dispatchEvent(new CustomEvent("ask", {
            detail: {
                action: "askFigure"
            }
        }));
    }

    clearView() {
        this.dispatchEvent(new CustomEvent("clear", { detail: "clearView" }));
    }

    getData() {
        const typeLine = String(this.InputTypeLine.value) || "continua"
        const typeWidth = Number(this.InputTypeWidth.value) || 1
        const selectFigure = String(this.inputSelectFigure.value) || "poligono";
        return { typeLine, typeWidth, selectFigure };
    }

    getExerciseNumber() {
        return this.exerciseNumber
    }

    connectedCallback() {
        this.buttonAskFigure.onclick = this.askFigure.bind(this);
        this.buttonClear.onclick = this.clearView.bind(this);
    }

    disconnectedCallback() {
        this.buttonClear.onclick = null;
        this.buttonAskFigure.onclick = null;
    }
}

customElements.define('x-view', View);

class Controller {
    constructor(view, model) {
        this._view = view;
        this._model = model;

        this._onModelChanged = this.onModelChanged.bind(this);
        this._onViewAsk = this.onViewAskToClient.bind(this);
        this._onViewClear = this.onViewClear.bind(this);
    }

    enable() {
        this._model.addEventListener('changed', this._onModelChanged);
        this._view.addEventListener('ask', this._onViewAsk);
        this._view.addEventListener("clear", this._onViewClear);
    }

    disable() {
        this._model.removeEventListener('changed', this._onModelChanged);
        this._view.removeEventListener('ask', this._onViewAsk);
        this._view.removeEventListener("clear", this._onViewClear);
    }

    onModelChanged() {
        const listFigures = this._model.getFigures();
        this._view.render(listFigures);
    }

    onViewClear(event) {
        if (event.detail === "clearView") {
            this._model.clearList();
        }
    }

    validateJSON(response) {
        try {
            const data = JSON.parse(response);
            return data;
        } catch (error) {
            throw error
        }

    }

    validateFigure(result) {

        if (result === null || typeof result !== "object" || Array.isArray(result)) {
            return "El JSON debe representar un objeto";
        }

        if (result.tipo !== "circulo" && result.tipo !== "poligono" && result.tipo !== "GraficoTorta") {
            return "El tipo de figura no es válido";
        }

        if (result.tipo === "circulo" && result.radio === undefined) {
            return "El círculo necesita la propiedad radio";
        }

        if (result.tipo === "poligono" && (!Array.isArray(result.puntos) || result.puntos.length < 3)) {
            return "El polígono necesita la propiedad puntos y al menos 3 puntos";
        }

        if (result.tipo === "GraficoTorta" && (!Array.isArray(result.datos) || result.radio === undefined)) {
            return "El gráfico de torta necesita radio y datos";
        }

        return null;
    }

    onViewAskToClient(event) {
        if (event.detail.action === "askFigure") {

            let mensajePrompt;
            if (this._view.getExerciseNumber() === 19) {
                mensajePrompt = 'Ingrese el JSON de la figura sin incluir "tipo". Ejemplo: {"x":100,"y":150,"radio":30}';
            } else {
                mensajePrompt = 'Ingrese JSON de la figura. Ejemplo: {"tipo":"circulo","x":100,"y":150,"radio":30}';
            }

            const response = prompt(mensajePrompt);

            if (response === null) {
                return;
            }

            let result
            try {

                result = this.validateJSON(response);

                if (result === null || typeof result !== "object" || Array.isArray(result)) {
                    throw new Error("El JSON debe representar un objeto");
                }

            } catch (error) {
                alert(error.message);
                return
            }

            const { typeLine, typeWidth, selectFigure } = this._view.getData();

            if (this._view.getExerciseNumber() === 19) {

                result.tipo = selectFigure;
                result.typeWidth = typeWidth;
                result.typeLine = typeLine;

            }
            if (this._view.getExerciseNumber() === 12) {

                result.typeWidth = typeWidth;
                result.typeLine = typeLine;

            }

            const error = this.validateFigure(result);

            if (error !== null) {
                alert(error);
                return;
            }

            this._model.setFigure(result);
        }

    }
}
