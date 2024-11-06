#include "secrets.h"
#include "discord.h"

String message = "This is a simple message!";
String embedJson = R"({
  "author": {
    "name": "Birdie♫",
    "url": "https://www.reddit.com/r/cats/",
    "icon_url": "https://picsum.photos/200"
  },
  "title": "Title lorem ipsum something very nice",
  "url": "https://google.com/",
  "description": "Text message. You can use Markdown here. *Italic* **bold** __underline__ ~~strikeout~~ [hyperlink](https://google.com) `code`",
  "color": 15258703,
  "fields": [
    {
      "name": "Text",
      "value": "More text",
      "inline": true
    },
    {
      "name": "Even more text",
      "value": "Yup",
      "inline": true
    },
    {
      "name": "Use `\"inline\": true` parameter, if you want to display fields in the same line.",
      "value": "okay..."
    },
    {
      "name": "Thanks!",
      "value": "You're welcome :wink:"
    }
  ],
  "thumbnail": {
    "url": "https://picsum.photos/600"
  },
  "image": {
    "url": "https://picsum.photos/1200/600"
  },
  "footer": {
    "text": "Woah! So cool! :smirk:",
    "icon_url": "https://picsum.photos/200"
  }
})";

void setup() {
  Serial.begin(9600);
  connectWIFI();
  sendDiscordMessage(message);
  sendDiscordEmbeds(embedJson);
  sendDiscord(message, embedJson);
}

void loop() {
}
