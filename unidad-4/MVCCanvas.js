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

    constructor() {
        super();

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

        this.labelTypeWidth = document.createElement("label");
        this.labelTypeWidth.textContent = "Grosor de línea: ";
        this.labelTypeWidth.htmlFor = "typeWidth";

        this.InputTypeWidth = document.createElement("input");
        this.InputTypeWidth.id = "typeWidth";
        this.InputTypeWidth.type = "number";
        this.InputTypeWidth.min = "1";
        this.InputTypeWidth.max = "100";
        this.InputTypeWidth.step = "1";
        this.InputTypeWidth.value = "2";
        this.InputTypeWidth.required = true;

        this.labelTypeLine = document.createElement("label");
        this.labelTypeLine.textContent = "Tipo de línea: ";
        this.labelTypeLine.htmlFor = "typeLine";

        this.InputTypeLine = document.createElement("select");
        this.InputTypeLine.id = "typeLine";
        this.InputTypeLine.required = true;

        this.option1 = document.createElement("option");
        this.option2 = document.createElement("option");
        this.option3 = document.createElement("option");

        this.option1.textContent = "miter";
        this.option1.value = "miter";
        this.option2.textContent = "round";
        this.option2.value = "round";
        this.option3.textContent = "bevel";
        this.option3.value = "bevel";

        this.InputTypeLine.appendChild(this.option1);
        this.InputTypeLine.appendChild(this.option2);
        this.InputTypeLine.appendChild(this.option3);
        this.InputTypeLine.value = "miter";

        this.appendChild(this._canvas);
        this.appendChild(this.buttonClear);
        this.appendChild(this.buttonAskFigure);
        this.appendChild(this.labelTypeLine);
        this.appendChild(this.InputTypeLine);
        this.appendChild(this.labelTypeWidth);
        this.appendChild(this.InputTypeWidth);
    }

    render(listFigures) {
        this.clear();

        if (listFigures.length === 0) {
            return;
        }

        for (const element of listFigures) {
            const typeWidth = element.typeWidth || 1;
            const typeLine = element.typeLine

            if (element.tipo === "circulo") {
                this.ctx.beginPath();
                this.ctx.lineWidth = typeWidth;
                this.ctx.lineJoin = "miter";
                this.ctx.arc(element.x, element.y, element.radio, 0, 2 * Math.PI);
                this.ctx.closePath();
                this.ctx.stroke();

            } else if (element.tipo === "poligono") {
                this.ctx.beginPath();
                this.ctx.lineWidth = typeWidth;
                this.ctx.lineJoin = typeLine;
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
        }
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
        const typeLine = String(this.InputTypeLine.value);
        const typeWidth = Number(this.InputTypeWidth.value);
        return { typeLine, typeWidth };
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
            this._view.clear();
        }
    }

    validateJSON(response) {
        try {
            const data = JSON.parse(response);
            return data;
        } catch (error) {
            alert(error.message);
            return null;
        }
    }

    onViewAskToClient(event) {
        if (event.detail.action === "askFigure") {

            const response = prompt('Ingrese JSON de la figura. Ej: {"tipo":"circulo","x":100,"y":150,"radio":30}');

            if (response === null) {
                return;
            }

            const result = this.validateJSON(response);
            if (!result) {
                alert("El JSON ingresado no es válido.");
                return;
            }

            const { typeLine, typeWidth } = this._view.getData();

            if (!typeLine || !typeWidth) {
                alert("Falta ingresar un valor válido de grosor y tipo de línea.");
                return;
            }

            result.typeWidth = typeWidth;
            result.typeLine = typeLine;

            this._model.setFigure(result);
        }

    }
}