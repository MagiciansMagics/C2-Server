const total_clients_span_id = document.getElementById("QNJ_TCP_CLIENT_AMOUNT");
const qnj_screen_share_id = document.getElementById("QNJ-SCREEN-SHARE-CLIENT-ID");
const qnj_screen_share_id_main = document.getElementById("QNJ-SCREEN-SHARE-CLIENT-MAIN-ID");
function QNJ_REPEAT_GET_REQUEST_AM()
{
  fetch("/dashboard/api/QNJ-Jg94japEjgnammykglA316-geadgE69")
  .then(response => response.json())
  .then(data => {
    requests_text.innerText = data["requests"];
  })
}
fetch("/dashboard/api/QNJ-Megj4aj3194g2-h5mantt4N-!33gc31E69")
  .then(response => response.json())
  .then(data => {
    total_clients_span_id.innerText = data["online_clients"];
    console.log(data["offline_clients"]);
    console.log(data["total_clients"]);
  })

/*
function updateTime() {
  fetch("/dashboard/api/QNJ-Jg94japEjgnammykglA316-geadgE69")
  .then(response => response.json())
  .then(data => {
    time_span_var.innerText = data["time_var"];
  });
}
updateTime();
setInterval(updateTime, 1000);

*/

QNJ_REPEAT_GET_REQUEST_AM();
setInterval(QNJ_REPEAT_GET_REQUEST_AM, 30000)