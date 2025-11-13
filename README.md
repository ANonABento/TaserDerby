# 🥚 TaserDerby ⚡

## Overview

TaserDerby is a race betting application that integrates a React web frontend with an ESP32 microcontroller and a handmade taser.

Bet on a racer and if you lose, you get tased with a safe & short electric shock.

Perfect for parties!

<div style="display: flex; gap: 10px;">
  <img src="https://github.com/user-attachments/assets/1f8a2620-f4d7-4bca-a237-c4619e562487" alt="Description of Image 1" width="300" />
  <img src="https://github.com/user-attachments/assets/aad56672-dbec-4622-914f-0c04eeb1a840" alt="Description of Image 2" width="313" />
</div>

---

## 🚀 Key Features

* **Microscopic Race Simulation:** Real-time, physics-based movement visualized on an HTML Canvas.
* **Difficulty Scaling:** Adjust the required finishing rank (Top 1 to Top 8).
* **Direct Hardware Integration:** Uses a `fetch` POST request to trigger a taser upon losing.
* **Minimalist UI:** Betting and results are handled via fullscreen modals for an immersive "microscope" aesthetic.

---

## 🛠️ System Components & Repository Structure

This repository holds the entire project, organized into the following directories:

| Folder | Content | Description |
| :--- | :--- | :--- |
| **`Website/`** | React/Vite Frontend Code | Contains the full web application source and dependencies. |
| **`ESP32_Code/`** | Embedded C++ Source | Holds the Arduino sketch (`taserderby_esp32_code.ino`) for the microcontroller. |
| **`CAD/`** | Hardware Design Files | Placeholder for any 3D models or enclosure design files. |

### Hardware Requirements

<table style="width: 100%; border: none;">
  <tr>
    <td style="vertical-align: top; padding-right: 20px;">
      <ul>
        <li><strong>ESP32 Development Board</strong> (Used ESP32-C3)</li>
        <li><strong>Relay Module</strong> (5V coil, 3.3V logic)</li>
        <li><strong>External 5V Power Supply</strong> (For stable, isolated relay coil power)</li>
        <li><strong>Voltage Transformer</strong> (If using AC current for the load side)</li>
      </ul>
    </td>
    <td>
      <img width="300px" alt="TaserDerby Hardware Wiring" src="https://github.com/user-attachments/assets/63f1fb32-3ff0-4e88-8e94-f90060eb2ff2" />
    </td>
  </tr>
</table>


### Wiring Diagram
<table style="width: 100%; border: none;">
  <tr>
    <td>
      <img width="1320" height="506" alt="image" src="https://github.com/user-attachments/assets/b7fa1cd4-784f-4eef-99ef-09ae2a7ffa85" />
    </td>
  </tr>
</table>

---

## ⚙️ Setup and Installation

Clone this repository:
```
git clone https://github.com/ANonABento/TaserDerby.git
```

### Part A: ESP32 Microcontroller Configuration

This part sets up the microcontroller to listen for the "defeat" signal.

1.  Open the `taserderby_esp32_code.ino` file in the Arduino IDE.
2.  **Update Wi-Fi Credentials:** Change the following lines to match your local Wi-Fi network:
    ```cpp
    const char* ssid = "YOUR_WIFI_SSID";
    const char* password = "YOUR_WIFI_PASSWORD";
    ```
3.  Upload the sketch to your ESP32-C3.
4.  Open the Serial Monitor (115200 baud) to find and **write down the ESP32's local IP address**.

### Part B: React Web Application Configuration

This part configures the frontend to target the hardware.

1.  Navigate to the web application source: `website/DigitalDerbyApp.jsx`.
2.  **CRITICAL STEP:** Update the IP address placeholder at the top of the file with the IP address printed by the ESP32 in Part A.
    ```javascript
    // IMPORTANT: Replace with the actual IP address of your ESP32 server
    const ESP32_IP_ADDRESS = 'YOUR_ESP32_IP'; // e.g., '192.168.1.100'
    const API_LOSE_ENDPOINT = `http://${ESP32_IP_ADDRESS}/lose`; 
    ```

### Part C: Running the Web Server

1. **Clone and Navigate:** Clone the submodule, then enter the web directory.
    ```bash
    git clone --recurse-submodules
    cd TaserDerby/website
    ```

2. **Install Dependencies:**
    ```bash
    npm install
    ```

3. **Start the Development Server:**
    ```bash
    npm run dev
    ```
    The web application will now be running (usually at `http://localhost:5173`) and ready to communicate with your ESP32.

---

## 🕹️ Usage (The Game Flow)

1. **Start the Race:** The app displays the **Betting Modal**.
2. **Set Difficulty:** Adjust the slider (Top 1 to Top 8).
3. **Place Your Bet:** Click a colored racer button to start the simulation.
4. **Result:**
    * **SAFE:** If your racer finishes within the Top X.
    * **DEFEAT:** If your racer finishes outside the Top X, the `fetch` request is sent, and the taser is triggered by the relay.

---

*Note: If the taser is not triggering, check the IP address in `website/DigitalDerbyApp.jsx` and ensure both your computer and the ESP32 are on the same local Wi-Fi network.*
