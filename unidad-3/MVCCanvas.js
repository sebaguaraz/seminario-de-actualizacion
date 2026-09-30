class Model extends EventTarget {
    constructor() {
        super();
        this.listFigure = []
    }

    changed() {
        this.dispatchEvent(new CustomEvent('changed'));
    }

    setFigure(figure) {
        this.listFigure.push(figure)
        this.changed()
    }

    getFigures() {
        return this.listFigure
    }

    clearList() {
        this.listFigure = []
        this.changed()
    }



}

class View extends HTMLElement {
    constructor() {

        super();
        this._canvas = document.createElement('canvas');
        this._canvas.width = 800;
        this._canvas.height = 600;
        this.ctx = this._canvas.getContext('2d');
        this._canvas.style = "border: 1px solid black; "

        this.buttonClear = document.createElement("button")
        this.buttonClear.type = "button"
        this.buttonClear.textContent = "Limpiar"

        this.labelTypeWidth = document.createElement("label")
        this.labelTypeWidth.textContent = "Grosor de línea: "
        this.labelTypeWidth.htmlFor = "typeWidth"
        this.InputTypeWidth = document.createElement("input")
        this.InputTypeWidth.id = "typeWidth"
        this.InputTypeWidth.type = "number"
        this.InputTypeWidth.min = "1"
        this.InputTypeWidth.max = "100"
        this.InputTypeWidth.step = "1"
        this.InputTypeWidth.required = true

        this.labelTypeLine = document.createElement("label")
        this.labelTypeLine.textContent = "Tipo de línea: "
        this.labelTypeLine.htmlFor = "typeLine"
        this.InputTypeLine = document.createElement("select")
        this.InputTypeLine.id = "typeLine"
        this.InputTypeLine.value = "1"
        this.InputTypeLine.required = true

        this.option1 = document.createElement("option")
        this.option2 = document.createElement("option")
        this.option3 = document.createElement("option")

        this.option1.textContent = "miter"
        this.option1.value = "miter"
        this.option2.textContent = "round"
        this.option2.value = "round"
        this.option3.textContent = "bevel"
        this.option3.value = "bevel"


        this.appendChild(this._canvas)
        this.appendChild(this.buttonClear)

        this.appendChild(this.labelTypeLine)
        this.appendChild(this.InputTypeLine)
        this.InputTypeLine.appendChild(this.option1)
        this.InputTypeLine.appendChild(this.option2)
        this.InputTypeLine.appendChild(this.option3)
        this.appendChild(this.labelTypeWidth)
        this.appendChild(this.InputTypeWidth)

    }

    render(renderFunction, listFigures) {
        this.clear();
        renderFunction(this._canvas, listFigures);
    }

    clear() {
        this.ctx.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    askFigure() {
        let typeLine = String(this.InputTypeLine.value)
        let typeWidth = Number(this.InputTypeWidth.value)
        console.log(typeWidth);

        this.dispatchEvent(new CustomEvent("ask",
            {
                detail: {
                    action: "askFigure",
                    valueLine: typeLine,
                    valueWidth: typeWidth
                }
            }
        ))
    }

    clearView() {
        this.dispatchEvent(new CustomEvent("clear", { detail: "clearView" }))
    }

    connectedCallback() {
        // 
        this.buttonClear.onclick = this.clearView.bind(this)

    }

    disconnectedCallback() {

        this.buttonClear.onclick = null

    }

    setWidth(width) {
        this._canvas.width = width
    }

    setHeight(height) {
        this._canvas.height = height

    }

    getWidth() {
        return this._canvas.width
    }

    getHeight() {
        return this._canvas.height

    }


}
customElements.define('x-view', View);


class Controller {
    constructor(view, model) {
        this._view = view;
        this._model = model;

        // * crea una sola variable que guarde una sola vez la referencia a la funcion en memoria para no perderlas al eliminarlas...
        this._onModelChanged = this.onModelChanged.bind(this);
        this._onViewAsk = this.onViewAskToClient.bind(this);
        this._onViewClear = this.onViewClear.bind(this);

    }

    enable() {
        this._model.addEventListener('changed', this._onModelChanged);
        this._view.addEventListener('ask', this._onViewAsk);
        this._view.addEventListener("clear", this._onViewClear)
    }

    disable() {
        this._model.removeEventListener('changed', this._onModelChanged);
        this._view.removeEventListener('ask', this._onViewAsk);
        this._view.removeEventListener("clear", this._onViewClear)

    }

    onModelChanged() {
        let listFigures = this._model.getFigures()
        this._view.render(ejercicio12, listFigures)
    }


    onViewClear(event) {
        if (event.detail === "clearView") {
            this._model.clearList()
            this._view.clear()
        }
    }

    validateJSON(response) {

        try {

            const object = JSON.parse(response)

            return object

        } catch (error) {
            alert(error.message)
            return null
        }

    }

    onViewAskToClient(event) {

        if (event.detail.action === "askFigure") {

            let response = prompt('Ingrese JSON de la figura. Ej: {"tipo":"circulo","x":100,"y":150,"radio":30}');

            const result = this.validateJSON(response)
            if (result === null) {
                return;
            }

            result.typeWidth = event.detail.valueWidth
            result.typeLine = event.detail.valueLine

            if (!result.typeWidth || result.typeWidth === 0) {
                alert("Falta ingresar un valor en el input (Grosor de línea) o el tipo de linea no esta especificado. ")
                return;
            }

            console.log("datos obtenidos...")

            this._model.setFigure(result)

        } else {
            console.log("evento desconocido")
        }


    }

}
