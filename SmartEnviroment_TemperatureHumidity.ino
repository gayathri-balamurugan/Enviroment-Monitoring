#include<WiFi.h>
#include<HTTPClient.h>
#include<DHT.h>

const char* ssid = "Gayu";
const char* password = "gayu0809";

String apiKey = "YLH9RU3777NNQR39";

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(115200);

  dht.begin();

  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
}

void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity))
  {
    Serial.println("DHT11 reading failed!");
    delay(2000);
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;

    String url = "http://api.thingspeak.com/update?api_key=";
    url += "YLH9RU3777NNQR39";
    url += "&field1=";
    url += temperature;
    url += "&field2=";
    url += humidity;

    http.begin(url);

    int response = http.GET();

    Serial.print("ThingSpeak Response: ");
    Serial.println(response);

    http.end();
  }

  delay(15000);
}


