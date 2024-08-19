#!/bin/bash

# Set the number of requests
total_requests=500000

# Timeout for each request in seconds
timeout=5

# IP and port of the TCP server
ip="4.tcp.eu.ngrok.io"
port=19906

# Output log file
log_file="output.log"

# Clear the log file at the beginning
> "$log_file"

# Loop through the requests
for (( i=1; i<=$total_requests; i++ ))
do
    # Send request to the TCP server and wait for response
    echo "Request $i: Sending TCP request to ${ip}:${port}"
    (echo "Request $i: Sending TCP request" | nc -w $timeout "${ip}" "${port}" >>"$log_file" 2>&1) &
done

# Wait for all background processes to finish
wait

echo "All requests completed" | tee -a "$log_file"
