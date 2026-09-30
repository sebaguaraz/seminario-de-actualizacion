// * 12. Integración: Modificar el modelo del WebComponent integrado (Ej:6), de modo que las figuras gestionadas admitan propiedades de tipo de línea y grosor. Para esto, el componente deberá tener dos inputs para seleccionar el tipo de línea y el valor de grosor. Al hacer click en el botón de carga de figuras, se seguirá aceptando el mismo JSON sin cambios, solo anexará el valor de los inputs a la estructura de datos.

function ejercicio12(canvas, listFigures) {

    const pincel2D = canvas.getContext("2d")

    console.log(listFigures)

    if (!listFigures || listFigures === undefined || listFigures.length === 0) {
        alert("Limpiando lienzo... No hay figuras para renderizar")
        return;
    }

    for (const element of listFigures) {

        if (element.tipo === "circulo") {
            pincel2D.beginPath()
            pincel2D.lineWidth = element.typeWidth
            pincel2D.lineCap = element.typeLine 
            pincel2D.arc(element.x, element.y, element.radio, 0, 2 * Math.PI)
            pincel2D.closePath()
            pincel2D.stroke()
        } else if (element.tipo === "poligono") {

            pincel2D.beginPath()
            pincel2D.lineWidth = element.typeWidth
            pincel2D.lineJoin = element.typeLine
            pincel2D.moveTo(element.puntos[0].x, element.puntos[0].y)
            for(let pos = 1; pos < element.puntos.length; pos++){
                pincel2D.lineTo(element.puntos[pos].x, element.puntos[pos].y)
            }
            pincel2D.closePath()
            pincel2D.stroke()

        }


    }

}

    // poligono
    // {
    //   "tipo": "poligono",
    //   "puntos": [
    //     {"x": 100, "y": 100},
    //     {"x": 200, "y": 50},
    //     {"x": 300, "y": 100},
    //     {"x": 250, "y": 200},
    //     {"x": 150, "y": 200}
    //   ]
    // }