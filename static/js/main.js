
//Module to avoid that the data can be viewed externally
$(document).ready(function () {


    const send_comment_request = (form) => {
        $.ajax({
            dataType: "json",
            url: '/appWebSeguridad/add_comment',

            success: function (data) {
                fuctionToUse(data);
            },

            error: function (xhr, status) {
                console.log('Error : ', status);
            }
        });
    };

    const url = window.location.href;
    if (url.includes("comments")) {
        // console.log("kaka")
        // document.querySelector("#comments_form").addEventListener('submit', (e)=>{
        //     e.preventDefault();
        //     form = e.target
        //     console.log(form.name.value)
        // })


    }

});