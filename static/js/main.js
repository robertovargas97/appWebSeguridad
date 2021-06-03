
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
    console.log(localStorage.getItem('codes'));

    localStorage.setItem(`prod_${producto}`, producto);
    $(`#prod_${producto}`).prop("disabled", true);

    $("#id_codigo_producto").val(producto);
    $("#id_correo").val(u_correo);
    form_data = $('#jaja_form').serialize();
    //console.log(form_data);
    $.ajax({
        url: '/select_product.cgi',
        data: form_data,
        type: 'POST',
        success: function (data) {
            alert("Se agrego al carrito correctamente");
        }
    });
}

function delete_from_cart_ajax(producto, u_correo) {
    localStorage.removeItem(`prod_${producto}`);

    $("#id_codigo_producto").val(producto);
    $("#id_correo").val(u_correo);
    form_data = $('#jaja_form').serialize();
    console.log(form_data);
    $.ajax({
        url: '/delete_from_car.cgi',
        data: form_data,
        type: 'POST',
        success: function (data) {
            console.log(data);
            alert("Eliminado del carrito correctamente");
            location.reload();
        }
    });
}



/*
function buy_cart_ajax(producto, u_correo) {
    $("#id_codigo_producto").val(producto);
    $("#id_correo").val(u_correo);
    form_data = $('#jaja_form').serialize();
    console.log(form_data);
    $.ajax({
        url: '/appWebSeguridad/buy_car.cgi',
        data: form_data,
        type: 'POST',
        success: function (data) {
            alert(data);
        }
    });
}*/

/*
function empty_cart_ajax(producto, u_correo) {
    $("#id_codigo_producto").val(producto);
    $("#id_correo").val(u_correo);
    form_data = $('#jaja_form').serialize();
    console.log(form_data);
    $.ajax({
        url: '/appWebSeguridad/empty_car.cgi',
        data: form_data,
        type: 'POST',
        success: function (data) {
            alert(data);
        }
    });
}*/


   // cout << "<script> var codes = [];";
        // cout << "</ script>";
        // cout << "<script>";
        // cout << "codes.push('" << codigo_producto << "');";
        // cout << "</ script>";
        // cout << "<script>";
        // cout << "localStorage.setItem('codes', JSON.stringify(codes));";
        // cout << "</ script>";