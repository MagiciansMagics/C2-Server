function check_if_client_id_exists()
{
    if (error_message_bool == true)
    {
        var error_div = document.createElement("div");

        error_div.style.position = "absolute";
        error_div.style.top = "89%";
        error_div.style.left = "80%";
        error_div.style.width = "250px";
        error_div.style.height = "100px";
        error_div.style.backgroundColor = "red";
        console.log("Client id doesnt exists");

        document.body.appendChild(error_div);
    }
}

check_if_client_id_exists();