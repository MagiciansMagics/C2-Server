const add_div = document.getElementById("QNJ-data-0x00-add-data-id")
const add_button = document.getElementById("QNJ-data-0x00-add")
const add_frame_overlay = document.getElementById("data-0x00-data-overlay")
const add_frame_overlay2 = document.getElementById("data-0x00-data-overlay2")
const full_user_data_div_data_0x00 = document.getElementById("user-data-0x00-client-div-full");

function display_add_stuff() {
    if (add_div.style.display === "none" || add_div.style.display === "" && add_frame_overlay.style.display == "none" || add_frame_overlay.style.display == "") {
        add_div.style.display = "flex";
        add_frame_overlay.style.display = "flex";
    } else {
        add_div.style.display = "none";
        add_frame_overlay.style.display = "none";
    }
}

document.addEventListener("DOMContentLoaded", function() {
    fetch("/dashboard/api/QNJ-yhew5h5eh34sxghmfnbfrfg-g4g34yhr4yte!t543y78")
        .then(user_data_response => {
            if (!user_data_response.ok) {
                throw new Error('Network response was not ok ' + user_data_response.statusText);
            }
            return user_data_response.json();
        })
        .then(data => {
            displayUsers(data);
        })
        .catch(error => console.error('Error fetching the JSON file:', error));

    function displayUsers(data) {
        const user_data_div_data_0x00 = document.getElementById("user-data-0x00-client-div");

        for (const client_data in data) {
            if (data.hasOwnProperty(client_data)) {
                const data_0x00_user = data[client_data];
                const user_div_client = document.createElement("div");
                user_div_client.className = "data-0x00-user-preview";
                user_div_client.innerHTML = `
                    <div class="user-summary">
                        <img src="${data_0x00_user.profile_image}" class="user-image">
                        <h2>${data_0x00_user.first_name} ${data_0x00_user.last_name}</h2>
                        <p>Age: ${data_0x00_user.age}</p>
                        <p>Gender: ${data_0x00_user.gender}</p>
                        <p>Country: ${data_0x00_user.country}</p>
                        <p>City: ${data_0x00_user.city}</p>
                        <p>Email: ${data_0x00_user.email}</p>
                        <p>Phone number: ${data_0x00_user.phonenumber}</p>
                    </div>
                `;

                user_div_client.addEventListener("click", function() {
                    displayUserDetails(data_0x00_user);
                });

                user_data_div_data_0x00.appendChild(user_div_client);
            }
        }
    }

    function displayUserDetails(user) {
        full_user_data_div_data_0x00.innerHTML = `
            <div class="user-details">
                <h2>${user.first_name} ${user.last_name}</h2>
                <p>Age: ${user.age}</p>
                <p>Gender: ${user.gender}</p>
                <p>Country: ${user.country}</p>
                <p>City: ${user.city}</p>
                <p>Email: ${user.email}</p>
                <p>Phone number: ${user.phonenumber}</p>
            </div>
        `;
        add_frame_overlay2.style.display = "flex";
        add_frame_overlay2.style.cursor = "pointer";
        full_user_data_div_data_0x00.style.display = "block";
        add_frame_overlay2.addEventListener("click", function() {
            add_frame_overlay2.style.display = "none";
            full_user_data_div_data_0x00.style.display = "none";
        });
    }
});

// Ensure the full user data div is hidden initially
full_user_data_div_data_0x00.style.display = "none";

add_button.addEventListener("click", display_add_stuff);
