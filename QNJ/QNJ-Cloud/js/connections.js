const clientElements = document.querySelectorAll('.qnj-extrated-client-vec');

// Log the number of elements found
clientElements.forEach((element, index) => {
  // Log the current element being processed

  // Get the text content of the current element
  const clientConnectionDataText = element.textContent;

  // Clear the original content
  element.textContent = '';
  // Split the text into components
  const components = clientConnectionDataText.split(' ');

  // Create and append new spans for each component
  components.forEach((component, componentIndex) => {
    // Create a new span element
    const newSpan = document.createElement('span');

    // Set the text of the new span
    newSpan.textContent = component;

    // Set a unique id for each span
    if (componentIndex === 0)
    {
      newSpan.id = `component-${index}-id`;
    }
    if (componentIndex === 1)
    {
      newSpan.id = `component-${index}-stat`;
    }
    if (componentIndex === 2)
    {
      newSpan.id = `component-${index}-raddr`;
    }
    if (componentIndex === 3)
    {
      newSpan.id = `component-${index}-ipaddr`;
    }
    if (componentIndex === 4)
    {
      newSpan.id = `component-${index}-os`;
    }
    if (componentIndex === 5)
    {
      newSpan.id = `component-${index}-osrel`;
    }
    if (componentIndex === 6)
    {
      newSpan.id = `component-${index}-arch`;
    }
    newSpan.className = `component-0-${componentIndex}`

    if (componentIndex > 6) {
      newSpan.style.display = "none";
    }
    // Append the new span to the current element
    element.appendChild(newSpan);
  });

  // Create a new button
  const clientButton = document.createElement('button');
  clientButton.textContent = 'Extra info'; // Set the button text
  clientButton.id = `client-button-${index}`; // Set a unique ID for the button
  clientButton.className = "QNJ-DELETE-CLIENT-ID-CLASS";

  // Optionally, add an event listener to the button
  clientButton.addEventListener('click', () => {
    const overlay_div = document.createElement("div");
    const client_data_frame = document.createElement("div");
    const close_client_data_frame_button = document.createElement("button");
    const client_text_p_id = document.createElement("p");
    const client_text_p_stat = document.createElement("p");
    const client_text_p_raddr = document.createElement("p");
    const client_text_p_ipaddr = document.createElement("p");
    const client_text_p_os = document.createElement("p");
    const client_text_p_osrel = document.createElement("p");
    const client_text_p_arch = document.createElement("p");

    overlay_div.style.position = "absolute";
    overlay_div.style.top = "0px";
    overlay_div.style.left = "0px";
    overlay_div.style.width = "100vw";
    overlay_div.style.height = "108%";
    overlay_div.style.backgroundColor = "rgba(80, 80, 80, 0.6)";
    overlay_div.style.zIndex = "1"

    client_data_frame.style.position = "absolute";
    client_data_frame.style.top = "50%"
    client_data_frame.style.left = "50%";
    client_data_frame.style.transform = "translate(-50%, -50%)";
    client_data_frame.style.backgroundColor = "rgb(0, 0, 0)";
    client_data_frame.style.width = "700px"
    client_data_frame.style.height = "500px";
    client_data_frame.style.padding = "5px";

    close_client_data_frame_button.style.position = "absolute";
    close_client_data_frame_button.style.width = "35px";
    close_client_data_frame_button.style.height = "35px";
    close_client_data_frame_button.innerHTML = "X";
    close_client_data_frame_button.style.color = "#fff";
    close_client_data_frame_button.style.left = "93%";
    close_client_data_frame_button.style.top = "2%";
    close_client_data_frame_button.style.cursor = "pointer";
    close_client_data_frame_button.style.backgroundColor = "rgb(0,0,0,0)";
    close_client_data_frame_button.style.fontWeight = "600";

    client_id = document.getElementById(`component-${index}-id`);
    client_stat = document.getElementById(`component-${index}-stat`);
    client_raddr = document.getElementById(`component-${index}-raddr`);
    client_ipaddr = document.getElementById(`component-${index}-ipaddr`);
    client_os = document.getElementById(`component-${index}-os`);
    client_osrel = document.getElementById(`component-${index}-osrel`);
    client_arch = document.getElementById(`component-${index}-arch`);
    client_text_p_id.innerHTML = "Id: " + client_id.textContent;
    client_text_p_stat.innerHTML = "Status: " + client_stat.textContent;
    client_text_p_raddr.innerHTML = "Remote address: " + client_raddr.textContent;
    client_text_p_ipaddr.innerHTML = "Ip address: " + client_ipaddr.textContent;
    client_text_p_os.innerHTML = "Operating system: " + client_os.textContent;
    client_text_p_osrel.innerHTML = "Operating system release: " + client_osrel.textContent;
    client_text_p_arch.innerHTML = "Cpu Architecture: " + client_arch.textContent;

    client_text_p_id.style.fontWeight = "600";
    client_text_p_stat.style.fontWeight = "600";
    client_text_p_raddr.style.fontWeight = "600";
    client_text_p_ipaddr.style.fontWeight = "600";
    client_text_p_os.style.fontWeight = "600";
    client_text_p_osrel.style.fontWeight = "600";
    client_text_p_arch.style.fontWeight = "600";

    client_text_p_id.style.marginBottom = "10px";
    client_text_p_stat.style.marginBottom = "10px";
    client_text_p_raddr.style.marginBottom = "10px";
    client_text_p_ipaddr.style.marginBottom = "10px";
    client_text_p_os.style.marginBottom = "10px";
    client_text_p_osrel.style.marginBottom = "10px";
    client_text_p_arch.style.marginBottom = "10px";

    document.body.appendChild(overlay_div);
    overlay_div.appendChild(client_data_frame);
    client_data_frame.appendChild(close_client_data_frame_button);
    client_data_frame.appendChild(client_text_p_id);
    client_data_frame.appendChild(client_text_p_stat);
    client_data_frame.appendChild(client_text_p_raddr);
    client_data_frame.appendChild(client_text_p_ipaddr);
    client_data_frame.appendChild(client_text_p_os);
    client_data_frame.appendChild(client_text_p_osrel);
    client_data_frame.appendChild(client_text_p_arch);
    // Add your button action logic here

    close_client_data_frame_button.addEventListener("click", () => {
      overlay_div.style.display = "none";
      client_data_frame.style.display = "none";
    });
  });

  // Append the button to the current element
  element.appendChild(clientButton);

  // Log completion of processing for the current element
});