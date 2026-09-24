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

        this.buttonAddFigura = document.createElement("button")
        this.buttonAddFigura.type = "button"
        this.buttonAddFigura.textContent = "Agregar Figura"

        this._figures = []

        this.appendChild(this._canvas)
        this.appendChild(this.buttonClear)
        this.appendChild(this.buttonAddFigura)

    }

    render(renderFunction) {
        this.clear();
        renderFunction(this._canvas, this.getFigures());
    }

    clear() {
        this.ctx.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    askFigure() {
        this.dispatchEvent(new CustomEvent("ask", { detail: "askFigure" }))
    }

    clearView() {
        this.dispatchEvent(new CustomEvent("clear", { detail: "clearView" }))
    }

    connectedCallback() {
        // 
        this.buttonAddFigura.onclick = this.askFigure.bind(this)
        this.buttonClear.onclick = this.clearView.bind(this)

    }

    disconnectedCallback() {

        this.buttonAddFigura.onclick = null
        this.buttonClear.onclick = null

    }

    getFigures() {
        return this._figures
    }

    setFigures(figures) {
        this._figures = figures
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

        // * crea una sola instancia de estas funciones en memoria para no perder la referencia al eliminarlas...
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
        let figures = this._model.getFigures()
        this._view.setFigures(figures)
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

        if (event.detail === "askFigure") {

            let response = prompt('Ingrese JSON de la figura. Ej: {"tipo":"circulo","x":100,"y":150,"radio":30}');

            const result = this.validateJSON(response)
            console.log(result)


            if (result === null) {
                return;
            }


            console.log("datos obtenidos...")

            this._model.setFigure(result)

        } else {
            console.log("evento desconocido")
        }


    }

}
