
//Module to avoid that the data can be viewed externally
// $(document).ready(function () {

//     const url = window.location.href;
//     if (url.includes("list_products")) {
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

function add_to_cart_ajax(producto, correo) {
    const url = window.location.href;
    console.log("SIIIIII FUNCIONAAA")
    if (url.includes("list_products")) {
        $.ajax({
            type: "POST",
            async: false,
            url: '/appWebSeguridad/select_product.cgi',
            data: { "producto": producto, "correo": correo},
            success: function (response) {
                alert("Se agregó producto con exito")
            },
        });
    }
}



