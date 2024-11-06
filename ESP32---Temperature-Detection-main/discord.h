#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "discordCert.h"

const char ssid[] = WIFI_SSID;
const char pass[] = WIFI_PASS;
const String discord_webhook = DISCORD_WEBHOOK;
const String discord_tts = DISCORD_TTS;


WiFiMulti WiFiMulti;

void connectWIFI() {
  WiFiMulti.addAP(ssid, pass);
  WiFi.mode(WIFI_STA);
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println("WiFi Connected");
}

void sendDiscord(String content, String embedJson) {
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client) {
    client -> setCACert(DISCORD_CERT);
    {
      HTTPClient https;
      if (https.begin(*client, discord_webhook)) {
        https.addHeader("Content-Type", "application/json");

      Serial.println("Before payload");
        String jsonPayload = "{\"content\":\"" + content + "\",\"tts\":" + discord_tts + ",\"embeds\": [" + embedJson + "]}";
        int httpCode = https.POST(jsonPayload);
Serial.println("after POST");
        if (httpCode > 0) {
          Serial.println(httpCode);
          Serial.println(https.getString());
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.print("HTTP Response: ");
            Serial.println(payload);
          }
        } else {
          Serial.print("HTTP Post failed: ");
          Serial.println(https.errorToString(httpCode).c_str());
        }

        https.end();
      }
    }

    delete client;
  }
}

void sendDiscordMessage(String content) {
  sendDiscord(content, "");
}

void sendDiscordEmbeds(String embeds) {
  sendDiscord("", embeds);
}
