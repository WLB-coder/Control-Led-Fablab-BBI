#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

const char* ssid = "aiman";
const char* password = "marie2002";
const char* ap_ssid = "ESP OK"; // Nom du point d'accès WiFi créé par l'ESP32
const char* ap_password = "12345678"; // Mot de passe du point d'accès WiFi
IPAddress ap_ip(192, 168, 1, 10); // Adresse IP fixe pour le point d'accès WiFi

WebServer server(80);
const int dhtPin = 4; // Broche du capteur DHT11
DHT dht(dhtPin, DHT11);

const int ledPin = 2; // Broche de la LED
bool ledState = false;

void handleRoot() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String htmlPage = R"=====(
<!DOCTYPE html>
<html>
<head>

    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Weather App</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
<div class="card">
    <div class="container">
        <marquee behavior="scroll" direction="left" scrollamount="18">
            <h1 class="lumineux-texte">Bienvenue au <br> <i>Fablab BBI</i></h1>
        </marquee>
    </div>
    <div class="weather">
        <p>Température: </p>
        <p><span class="circle" id="temperature">N/A</span></p>
        <p>Humidité: </p>
        <p><span class="circle" id="humidity">N/A</span></p>  
        <br><br><br>
        <button class="led-toggle on" onclick="toggleLED()">Toggle LED</button>                  
        <div class="details">
            <div class="col">
                <div>
                </div>
            </div>
        </div>
    </div>
</div>

<script>
const apikey = "9af0c18ad73c1b41c20ec117e18502c7";
const apiUrl = "https://api.openweathermap.org/data/2.5/weather?units=metric&q=ouagadougou&appid=" + apikey;

function updateData() {
          var xhr = new XMLHttpRequest();
          xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
              var data = JSON.parse(xhr.responseText);
              document.getElementById("temperature").innerText = data.temperature + " °C";
              document.getElementById("humidity").innerText = data.humidity + " %";
              document.getElementById("ledState").innerText = data.ledState ? "Allumée" : "Éteinte";
            }
          };
          xhr.open("GET", "/data", true);
          xhr.send();
        }

        function toggleLED() {
          var xhr = new XMLHttpRequest();
          xhr.onreadystatechange = function() {
            if (xhr.readyState == 4 && xhr.status == 200) {
              updateData(); // Update data after toggling the LED state
              var button = document.querySelector(".led-toggle");
              button.classList.toggle("on"); // Toggle the class to change the background color
              button.classList.toggle("off"); // Toggle the class to change the background color
            }
          };
          xhr.open("GET", "/toggle", true);
          xhr.send();
        }

        setInterval(updateData, 1000); // Mettre à jour les données toutes les 2 secondes

checkweather();
</script>
<style>
*{
	marging:0;
	padding: 0;
	font-family: 'poppins'sans-serif;
	box-sizing: border-box;
}
.led-toggle {
  border-radius: 50%; /* Make the button circular */
  padding: 10px; /* Add some padding for better aesthetics */
  font-size: 16px;
  border: none;
  outline: none;
  cursor: pointer;
  background-color: #222;
  color: #fff;
  padding: 12px 24px;
  border-radius: 30px;
  font-size: 18px;
  font-weight: bold;
  cursor: pointer;
  box-shadow: 0 5px 15px rgba(0, 0, 0, 0.3);  
  transition: background-color 0.3s; /* Smooth transition for background color change */
          }
.led-toggle:hover {
            background-color: #444;
            transform: translateY(-2px);
            box-shadow: 0 8px 20px rgba(0, 0, 0, 0.4);
          }  
/* Styles for the LED ON state */
          .led-toggle.on {
            background-color: skyblue;
          }

          /* Styles for the LED OFF state */
          .led-toggle.off {
            background-color: lightcoral;
          }
.card{
	width: 90%;
	max-width: 470px;
	background: linear-gradient(135deg, #00feba, #5b548a);
	color: #fff;
	margin: 100px auto 0;
	border-radius: 20px;
	padding: 40px 35px;
	text-align: center;
}

.weather-icon{
	width: 170px;
	margin-top: 30px;
}
.weather h1{
	font-size: 80px;
	font-weight: 500;
}
.weather h2{
	font-size: 45px;
	font-weight: 400;
	margin-top: -10px;
}
.details{
	display: flex;
	align-items: center;
	justify-content:center;
	padding: 20px 20px;
	margin-top: 50px;

}
.city
{
    text-transform: capitalize;
}
.col{
	display: flex;
	align-items: center;
	text-align: center;
}
.col img{
	width: 40px;
	margin-right: 10px;
}
.humidity,.wind{
	font-size: 28px;
	margin-top: -6px; v 
}
body {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100vh;
    margin: 0;
    background-color:gray;
    opacity: 0.9;
}
.circle {
    width: 100px;
    height: 100px;
    border-radius: 50%;
    display: flex;
    justify-content: center;
    align-items: center;
    margin-left:72px;
    font-size: 24px;
    font-weight: bold;
    color: #fff;
    animation: colorChange 10s infinite alternate; /* CSS animation for color change */
  }


.container {
    text-align: center;
}
i
{
    text-align: center;
}
.lumineux-texte {
    font-size: 36px;
    font-weight: bold;
    background: linear-gradient(45deg, #FF8C00, #FF0000, #FF8C00);
    -webkit-background-clip: text;
    background-clip: text;
    color: blue;
    animation: lumineux 2s linear infinite;
}

/* Animation keyframes for color change */
          @keyframes colorChange {
            0% {
              background-color: #FF0000; /* Red */
            }
            10% {
              background-color: #FF5500; /* Orange */
            }
            20% {
              background-color: #FFAA00; /* Orange-Yellow */
            }
            30% {
              background-color: #FFFF00; /* Yellow */
            }
            40% {
              background-color: #AAFF00; /* Yellow-Green */
            }
            50% {
              background-color: #55FF00; /* Green */
            }
            60% {
              background-color: #00FF00; /* Light Green */
            }
            70% {
              background-color: #00FF55; /* Light Green-Cyan */
            }
            80% {
              background-color: #00FFAA; /* Cyan */
            }
            90% {
              background-color: #00FFFF; /* Light Blue */
            }
            100% {
              background-color: #0000FF; /* Blue */
            }
          }

@keyframes lumineux {
    0% {
        background-position: 0% 50%;
    }
    100% {
        background-position: 100% 50%;
    }
}

</style>
</body>
</html>
  )=====";

  server.send(200, "text/html", htmlPage);
}

void handleData() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  String jsonData = "{\"temperature\": " + String(temperature) + ", \"humidity\": " + String(humidity) + ", \"ledState\": " + String(ledState) + "}";
  server.send(200, "application/json", jsonData);
}

void handleToggle() {
  ledState = !ledState;
  digitalWrite(ledPin, ledState ? HIGH : LOW);
  handleData(); // Répondre avec l'état actuel de la LED
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Se connecter au réseau WiFi existant
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Configurer l'ESP32 en tant que point d'accès WiFi avec l'adresse IP fixe
  WiFi.softAPConfig(ap_ip, ap_ip, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Point d'accès WiFi créé !");
  Serial.print("Adresse IP du point d'accès WiFi: ");
  Serial.println(ap_ip);

  // Définir les gestionnaires d'URL pour le serveur
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.on("/toggle", handleToggle);

  server.begin();
  Serial.println("Serveur Web démarré !");
}

void loop() {
  server.handleClient();
}
