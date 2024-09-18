function check_if_client_id_exists() {
    if (error_message_bool === true) {
        var error_div = document.createElement("div");
        var error_p = document.createElement("p");

        error_div.style.position = "absolute";
        error_div.style.top = "90%";
        error_div.style.left = "150%"; // Start off-screen
        error_div.style.width = "250px";
        error_div.style.height = "80px";
        error_div.style.backgroundColor = "red";
        error_div.style.transition = "left 0.5s ease";
        error_div.style.borderRadius = "3px";

        error_p.innerHTML = "Client does not exist";
        error_p.style.color = "#000";
        error_p.style.fontWeight = "800";
        error_p.style.position = "absolute";
        error_p.style.top = "50%";
        error_p.style.left = "50%";
        error_p.style.transform = "translate(-50%, -50%)";
        error_p.style.width = "158px";

        error_div.appendChild(error_p);
        document.body.appendChild(error_div);

        setTimeout(function() {
            error_div.style.left = "86%";
        }, 100);
    }
}

check_if_client_id_exists();
