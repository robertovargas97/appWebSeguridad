
//Module to avoid that the data can be viewed externally
$(document).ready(function () {

    const url = window.location.href;
    if (url.includes("list_products")) {
        console.log("kaka")
        document.querySelector("#comments_form").addEventListener('submit', (e) => {
            e.preventDefault();
            // form = e.target
            // console.log(form.name.value)
            data = $('#comments_form').serialize();
            $.ajax({
                url: '/appWebSeguridad/add_comment.cgi',
                type: 'POST',
                data: data,
                success: function (data) {
                    console.log(data)
                },

                error: function (xhr, status) {
                    console.log(data)
                }
            });
        })


    }

});

function agregarAlCarrito(codigo, nombre, precio, nombreImagen) {
    var cantidad = document.getElementById(nombre).value
    $.ajax({
        type: "POST",
        async: false,
        url: "agregarACarrito",
        data: { "codigo": codigo, "cantidad": cantidad, "nombre": nombre, "precio": precio, "nombreImagen": nombreImagen },
        success: function (response) {
            alert("Se agregó " + nombre + " con exito")
        },
    });
}
