#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NeoPixelBus.h>
#include <ArduinoJson.h>

const char* ssid = "Labor 2.0";
const char* password = "comevisitus";

const uint16_t PixelCount = 56;
const uint8_t PixelPin = 3;

NeoPixelBus<NeoGrbFeature, Neo400KbpsMethod> strip(PixelCount, PixelPin);

enum SpaceStatus { S_INIT, S_OPEN, S_CLOSED, S_UNKNOWN };

struct Space {
    uint8_t led;
    String url;
    String name;
    unsigned long lastChange;
    SpaceStatus status = SpaceStatus::S_INIT;
};

Space spaces[PixelCount];

void enumerate_leds(int delay_time) {
    for (int i = 0; i < PixelCount; i++) {
        strip.ClearTo(RgbColor(0, 0, 0));
        strip.Show();
        delay(delay_time/4);
        strip.SetPixelColor(spaces[i].led, RgbColor(255, 0, 0));
        strip.Show();
        delay(delay_time/4);
        strip.SetPixelColor(spaces[i].led, RgbColor(0, 255, 0));
        strip.Show();
        delay(delay_time/4);
        strip.SetPixelColor(spaces[i].led, RgbColor(0, 0, 255));
        strip.Show();
        delay(delay_time/4);
    }
}

void setup() {
  Serial.begin(115200);
  Serial.println(F("Starting up"));

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print(F("Connecting to WiFi"));
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(F(" connected"));
  // Set up the LED strip (Begin must be called after Serial.begin)
  strip.Begin();
  strip.ClearTo(RgbColor(64, 64, 64));
  strip.Show();
  // not so nice, but works
  spaces[0].led = 0;
  spaces[0].name = "realraum";
  spaces[1].led = 1;
  spaces[1].name = "/usr/space";
  spaces[2].led = 2;
  spaces[2].name = "Chaos Computer Club Wien (C3W)";
  spaces[3].led = 3;
  spaces[3].name = "not on api: Fortisauris Slovak";
  spaces[4].led = 4;
  spaces[4].name = "base48";
  spaces[5].led = 5;
  spaces[5].name = "Warsaw Hackerspace";
  spaces[6].led = 6;
  spaces[6].name = "not on api: HSPSH";
  spaces[7].led = 7;
  spaces[7].name = "Salzburg";
  spaces[8].led = 8;
  spaces[8].name = "DevLoL";
  spaces[9].led = 9;
  spaces[9].name = "Brmlab";
  spaces[10].led = 10;
  spaces[10].name = "Polytechnischer Werkraum Zittau";
  spaces[11].led = 11;
  spaces[11].name = "C3D2";
  spaces[12].led = 12;
  spaces[12].name = "Chaostreff Potsdam (CCCP)";
  spaces[13].led = 13;
  spaces[13].name = "xHain";
  spaces[14].led = 14;
  spaces[14].name = "IT-Syndikat";
  spaces[15].led = 15;
  spaces[15].name = "MuCCC";
  spaces[16].led = 16;
  spaces[16].name = "OpenLab Augsburg";
  spaces[17].led = 17;
  spaces[17].name = "Binary Kitchen";
  spaces[18].led = 18;
  spaces[18].name = "Nerdberg";
  spaces[19].led = 19;
  spaces[19].name = "backspace";
  spaces[20].led = 20;
  spaces[20].name = "hackzogtum";
  spaces[21].led = 21;
  spaces[21].name = "Krautspace";
  spaces[22].led = 22;
  spaces[22].name = "Eigenbaukombinat Halle e.V.";
  spaces[23].led = 23;
  spaces[23].name = "Netz39";
  spaces[24].led = 24;
  spaces[24].name = "Stratum 0";
  spaces[25].led = 25;
  spaces[25].name = "Hacklabor";
  spaces[26].led = 26;
  spaces[26].name = "coredump";
  spaces[27].led = 27;
  spaces[27].name = "see-base";
  spaces[28].led = 28;
  spaces[28].name = "shackspace - stuttgart hackerspace";
  spaces[29].led = 29;
  spaces[29].name = "mag.lab";
  spaces[30].led = 30;
  spaces[30].name = "flipdot";
  spaces[31].led = 31;
  spaces[31].name = "CCCHH";
  spaces[32].led = 32;
  spaces[32].name = "Chaos Computer Club Basel";
  spaces[33].led = 33;
  spaces[33].name = "CCCFr";
  spaces[34].led = 34;
  spaces[34].name = "Entropia";
  spaces[35].led = 35;
  spaces[35].name = "RaumZeitLabor";
  spaces[36].led = 36;
  spaces[36].name = "CCC Frankfurt";
  spaces[37].led = 37;
  spaces[37].name = "[hsmr] Hackspace Marburg";
  spaces[38].led = 38;
  spaces[38].name = "Hackerspace Bielefeld e.V.";
  spaces[39].led = 39;
  spaces[39].name = "Hackerspace Bremen e.V.";
  spaces[40].led = 40;
  spaces[40].name = "Level2";
  spaces[41].led = 41;
  spaces[41].name = "Maschinendeck";
  spaces[42].led = 42;
  spaces[42].name = "Westwoodlabs";
  spaces[43].led = 43;
  spaces[43].name = "CCC Cologne";
  spaces[44].led = 44;
  spaces[44].name = "Chaosdorf";
  spaces[45].led = 45;
  spaces[45].name = "chaospott";
  spaces[46].led = 46;
  spaces[46].name = "Chaostreff Dortmund";
  spaces[47].led = 47;
  spaces[47].name = "warpzone "; // trailing space :D
  spaces[48].led = 48;
  spaces[48].name = "TkkrLab";
  spaces[49].led = 49;
  spaces[49].name = "Hackerspace Drenthe";
  spaces[50].led = 50;
  spaces[50].name = "FUZ";
  spaces[51].led = 51;
  spaces[51].name = "not in api: liege hackspace"; // not on dir  https://lghs.be/spaceapi
  spaces[52].led = 52;
  spaces[52].name = "HSBXL";
  spaces[53].led = 53;
  spaces[53].name = "RevSpace";
  spaces[54].led = 54;
  spaces[54].name = "Bitlair";
  spaces[55].led = 55;
  spaces[55].name = "Frack";
}

void update_leds(){
    for (uint i = 0; i < PixelCount; i++) {
      if (spaces[i].status == SpaceStatus::S_OPEN) {
        // red and green are swapped for our PL9823 leds :)
        strip.SetPixelColor(spaces[i].led, RgbColor(21, 0, 0));
      } else if(spaces[i].status == SpaceStatus::S_CLOSED) {
        strip.SetPixelColor(spaces[i].led, RgbColor(0, 24, 0));
      } else if(spaces[i].status == SpaceStatus::S_UNKNOWN) {
        strip.SetPixelColor(spaces[i].led, RgbColor(0, 0, 30));
      } else {
        strip.SetPixelColor(spaces[i].led, RgbColor(5, 5, 5));
      }
    }
    strip.Show();
}

void loop() {
    // Wait for WiFi connection
    // Create an empty array to hold Space objects
    WiFiClientSecure client;
    // configure server and url
    client.setInsecure();
    HTTPClient http;
    http.begin(client, F("https://spaceapi.ccc.de/api/spaces"));
    http.useHTTP10(true); // important for chunking and stream reading
    http.GET();
    Stream& payload = http.getStream();
    StaticJsonDocument<128> filter;
    filter["url"] = true;
    filter["space"] = true;
    filter["state"]["open"] = true;
    filter["state"]["lastchange"] = true;
    DynamicJsonDocument doc(4096);
    Serial.println(F("Parsing JSON"));
    payload.find("["); // should actually be byte 0 of the response stream
    do {
        DeserializationError error = deserializeJson(doc, payload, DeserializationOption::Filter(filter));
        if (error) {
        Serial.print(F("deserializeJson() failed: "));
            Serial.println(error.c_str());
        }
        // if space is in known_spaces, update status
        for (int i = 0; i < PixelCount; i++) {
          if (spaces[i].name == doc["space"].as<String>()) {
            Serial.print(doc["space"].as<String>());
            Serial.print(F(": "));
            Serial.println(doc["state"]["open"].as<String>());
            //spaces[i].lastChange = doc["state"]["lastchange"].as<int>();
            if (doc["state"]["open"].as<String>() == "true") {
                spaces[i].status = SpaceStatus::S_OPEN;
            } else if (doc["state"]["open"].as<String>() == "false") {
                spaces[i].status = SpaceStatus::S_CLOSED;
            } else {
                spaces[i].status = SpaceStatus::S_UNKNOWN;
            }
            update_leds();
          }
        }
        // ...
    } while (payload.findUntil(",","]"));
    http.end();
    delay(60000);
}
