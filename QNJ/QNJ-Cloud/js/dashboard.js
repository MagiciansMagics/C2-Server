const user_data_display = document.getElementById("QNJ-BUTTON-DATA-CLIENT");
const user_data_username = document.getElementById("QNJ-USERNAME-TEXT-SP");
const requests_text = document.getElementById("QNJ_REQUEST_AMOUNT");
const time_span_var = document.getElementById("QNJ-Time-GET");
const display_client_b = document.getElementById("QNJ-DISPLAY-CLIENT-DATA");
const client_data_bar = document.getElementById("QNJ-CLIENT-DATA-BAR-DISPLAY");
const doomsday_bar_main = document.getElementById("QNJ-DOOMSDAY-ID-SWITCH");
const doomsday_bar_overlay = document.getElementById("DOOMSDAY-SWITCH-overlay-ID");
const client_connection_data = document.getElementById("QNJ-CONNECTIONS-DATA-SP");
const client_connection_container_div = document.getElementById("QNJ-CLIENT-DISPLAY-CONNECTION-BAR");
var first_click = true

user_data_display.appendChild(user_data_username);

function Display_Client_Data_Bar()
{ 
  if (first_click == true)
  {
    client_data_bar.style.display = "block";
    first_click = false;
  }
  else
  {
    client_data_bar.style.display = "none";
    first_click = true;
  }
}

function Display_DoomsDay_BAr()
{
  doomsday_bar_main.style.display = "flex";
  doomsday_bar_overlay.style.display = "flex";
}

function QNJ_CLOSE_DOOMS_DAY_SWITCH()
{
  doomsday_bar_main.style.display = "none";
  doomsday_bar_overlay.style.display = "none";
}

client_connection_container_div.appendChild(client_connection_data);