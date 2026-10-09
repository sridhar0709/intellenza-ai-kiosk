# INTELLENZA AI Kiosk: ESP8266 hardware test

This first firmware is a free, local-network test for the NodeMCU ESP-12E. It does not use a paid AI API or third-party Arduino libraries.

## What it does
- Joins a 2.4 GHz Wi-Fi network.
- Prints the device's local IP address in Serial Monitor.
- Hosts a small local test page at `http://DEVICE_IP/`.
- Exposes `/api/status` and `/api/led?state=on|off`.
- Toggles the board's built-in LED.

## Upload steps
1. Install Arduino IDE from https://www.arduino.cc/en/software.
2. In Arduino IDE, open Preferences and add this Boards Manager URL:
   `https://arduino.esp8266.com/stable/package_esp8266com_index.json`
3. Open Boards Manager, search for **esp8266**, and install **esp8266 by ESP8266 Community**.
4. Open `esp8266_kiosk.ino`.
5. Replace `YOUR_WIFI_NAME` and `YOUR_WIFI_PASSWORD` with your local **2.4 GHz** Wi-Fi credentials. Do not commit real credentials to GitHub.
6. Connect the NodeMCU with a USB data cable.
7. Choose **Tools → Board → ESP8266 Boards → NodeMCU 1.0 (ESP-12E Module)**.
8. Choose the correct serial port under **Tools → Port**. On Windows, it may appear as a CH340/USB-SERIAL device.
9. Click Verify, then Upload.
10. Open Serial Monitor at **115200 baud**. After connecting, copy the IP address printed by the board.
11. From a phone or computer on the same Wi-Fi network, open `http://THE_PRINTED_IP/`. Test the LED buttons.

## Troubleshooting
- **Port missing:** try another known data-capable USB cable, install the USB-serial driver offered by the board's chip manufacturer if needed, and reconnect the board.
- **Upload timeout:** close Serial Monitor, select the correct port, then retry. Some boards need a manual reset/flash-mode sequence.
- **Wi-Fi fails:** check spelling and use a 2.4 GHz network. Many ESP8266 boards cannot join a 5 GHz-only network.
- **Page does not open:** confirm the computer/phone and ESP8266 are on the same network and that the router is not isolating clients.

## Safety and integration note
This is an unauthenticated local test server. Use only on a trusted private network and **never expose its port directly to the internet**. The Vercel kiosk uses HTTPS, while this device test uses local HTTP; browsers commonly block direct requests from HTTPS pages to local HTTP devices. This test intentionally verifies the board independently first. A later integration phase must account for browser security and network access.

## Event FAQ content
The separate Vercel site remains the public-facing voice kiosk. Confirm event fees, registration dates, and venue details with the event organizers before relying on them at the live event.
