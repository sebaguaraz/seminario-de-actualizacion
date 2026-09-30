//* 6) Integración: Modificar el WebComponent de modo que el modelo le permita agregar dinámicamente (círculos y polígonos) ubicables en cualquier punto (x,y) del área de dibujo, como así también, limpiar toda el área de dibujo. El componente tendrá que tener un botón de carga de figuras, que al realizar click, lance un prompt esperando el objeto JSON para representarlo inmediatamente en el canvas. También deberá tener un botón de limpieza.

function ejercicio6(canvas, listFigure) {

    let ctx = canvas.getContext('2d');

    console.log(listFigure)

    if (listFigure.length === 0) {
        alert("No hay figuras para dibujar")
        return;
    }

    for (const elemento of listFigure) {

        if (elemento.tipo === "circulo") {
            ctx.beginPath()
            ctx.arc(elemento.x, elemento.y, elemento.radio, 0, 2 * Math.PI)
            ctx.closePath()
            ctx.stroke()
        }
        else if (elemento.tipo === "poligono") {
            ctx.beginPath()

            ctx.moveTo(
                elemento.x + elemento.puntos[0].x, elemento.y + elemento.puntos[0].y)

            for (let i = 1; i < elemento.puntos.length; i++) {
                ctx.lineTo(
                    elemento.x + elemento.puntos[i].x,
                    elemento.y + elemento.puntos[i].y
                )
            }

            ctx.closePath()
            ctx.stroke()

        }


    }


}