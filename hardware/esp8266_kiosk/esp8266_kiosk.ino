/*
  INTELLENZA AI Kiosk - ESP8266 local hardware test
  Board: NodeMCU 1.0 (ESP-12E Module)
  Libraries: ESP8266WiFi and ESP8266WebServer (included with ESP8266 Arduino core)

  Before uploading:
  1. Replace WIFI_SSID and WIFI_PASSWORD with your 2.4 GHz Wi-Fi credentials.
  2. Keep this test on a trusted local network. Do not port-forward this web server.
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

ESP8266WebServer server(80);
bool ledOn = false;

void setLed(bool on) {
  ledOn = on;
  // Most NodeMCU ESP-12E boards use an active-low built-in LED.
  digitalWrite(LED_BUILTIN, on ? LOW : HIGH);
}

void sendStatus() {
  String json = "{\"connected\":true,\"device\":\"INTELLENZA ESP8266\",\"ip\":\"";
  json += WiFi.localIP().toString();
  json += "\",\"led\":\"";
  json += ledOn ? "on" : "off";
  json += "\"}";
  server.send(200, "application/json", json);
}

void handleRoot() {
  const char page[] PROGMEM = R"HTML(
<!doctype html><html><head><meta name="viewport" content="width=device-width,initial-scale=1">
<title>INTELLENZA Kiosk Hardware Test</title>
<style>
body{font-family:system-ui,sans-serif;background:#07111f;color:#edf7ff;margin:0;min-height:100vh;display:grid;place-items:center}
main{width:min(90%,520px);padding:28px;border:1px solid #24445e;border-radius:22px;background:#0d1c2c}
h1{color:#65e4ff}button{padding:13px 18px;margin:6px;border:0;border-radius:12px;font-weight:700;cursor:pointer}
.on{background:#65e4ff}.off{background:#d7e4ef}pre{white-space:pre-wrap;overflow-wrap:anywhere;background:#06101a;padding:14px;border-radius:10px}
</style></head><body><main><h1>INTELLENZA AI Kiosk</h1>
<p>ESP8266 local hardware test</p><p id="state">Checking device…</p>
<button class="on" onclick="led('on')">Turn LED ON</button><button class="off" onclick="led('off')">Turn LED OFF</button>
<pre id="data">Waiting for status…</pre>
<script>
async function refresh(){try{const r=await fetch('/api/status');const d=await r.json();document.getElementById('state').textContent='Connected • LED '+d.led;document.getElementById('data').textContent=JSON.stringify(d,null,2)}catch(e){document.getElementById('state').textContent='Could not read device status'}}
async function led(s){try{await fetch('/api/led?state='+s);refresh()}catch(e){alert('Could not reach the ESP8266')}}
refresh();setInterval(refresh,5000);
</script></main></body></html>
)HTML";
  server.send(200, "text/html; charset=utf-8", FPSTR(page));
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  setLed(false);
  Serial.begin(115200);
  delay(100);
  Serial.println();
  Serial.println("INTELLENZA AI Kiosk hardware test starting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  unsigned long started = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - started < 25000) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi connection failed. Check SSID/password and 2.4 GHz network.");
    return;
  }

  Serial.print("Connected. Open http://");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, handleRoot);
  server.on("/api/status", HTTP_GET, sendStatus);
  server.on("/api/led", HTTP_GET, []() {
    if (server.arg("state") == "on") setLed(true);
    else if (server.arg("state") == "off") setLed(false);
    server.send(200, "application/json", String("{\"led\":\"") + (ledOn ? "on" : "off") + "\"}");
  });
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
  server.begin();
  Serial.println("HTTP server ready");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) server.handleClient();
}
