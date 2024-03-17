#include <ESP8266WiFi.h>

const int greenPin = 12;

void setup(){
  Serial.begin(115200);
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, HIGH);
  delay (1000);
  digitalWrite(greenPin, LOW);
  Serial.println(F("\nESP8266 WiFi Inited"));

  // set WiFi to station mode
  WiFi.mode(WIFI_STA);

  // if connected then disconnect
  WiFi.disconnect();
  delay(100);
}

void loop(){
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t* bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Scanning WiFi..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0) {
    Serial.println(F("cannot found any wifi"));
  } else if (scanResult > 0) {
    Serial.printf(PSTR("%d wifi found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++) {
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);

      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    bssid[0], bssid[1], bssid[2],
                    bssid[3], bssid[4], bssid[5],
                    rssi,
                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                    hidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
  } else {
    Serial.printf(PSTR("WiFi scanning error %d"), scanResult);
  }

  // 在再次扫描之前稍等片刻
  delay(1000);
  Serial.println(F(""));
}