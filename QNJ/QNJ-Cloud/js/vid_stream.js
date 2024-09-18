const clinet_image_vidstream = document.getElementById("qnj_client_image_screensht_vid");
var vid_url = "/dashboard/api/QNJ-7427282ggrw-v1id6str61eam3";

function qnj_vidstream() {
    fetch(vid_url)
      .then(response => {
        if (!response.ok) {
          throw new Error("Network response was not ok");
        }
        return response.blob();
      })
      .then(videoBlob => {
        const videoUrl = URL.createObjectURL(videoBlob);
        clinet_image_vidstream.src = videoUrl;
      })
      .catch(error => {
        console.error("There was a problem with the fetch operation:", error);
      });
  }

setInterval(qnj_vidstream, 1000 / 15);