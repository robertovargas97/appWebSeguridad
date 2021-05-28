
// // Module to avoid that the data can be viewed externally
// $(document).ready(function () {

//     const url = window.location.href;
//     if (url.includes("comments")) {
//         console.log("kaka")
//         document.querySelector("#comments_form").addEventListener('submit', (e) => {
//             e.preventDefault();
//             // form = e.target
//             // console.log(form.name.value)
//             data = $('#comments_form').serialize();
//             $.ajax({
//                 url: '/appWebSeguridad/add_comment.cgi',
//                 type: 'POST',
//                 data: data,
//                 success: function (data) {
//                     console.log(data)
//                 },

//                 error: function (xhr, status) {
//                     console.log(data)
//                 }
//             });
//         })


//     }

// });


function add_to_cart_ajax(producto, u_correo) {
    $("#id_codigo_producto").val(producto);
    $("#id_correo").val(u_correo);
    form_data = $('#jaja_form').serialize();

    $.ajax({
        url: '/appWebSeguridad/select_product.cgi',
        data: form_data,
        type: 'POST',
        success: function (data) {
            alert("El producto se agrego con exito");
        }
    });
}

