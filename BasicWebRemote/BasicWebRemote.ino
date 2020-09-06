#include <ir_Coolix.h>
#include <ir_Sanyo.h>
#include <ir_Hitachi.h>
#include <ir_Panasonic.h>
#include <ir_Vestel.h>
#include <ir_Airwell.h>
#include <ir_MitsubishiHeavy.h>
#include <ir_Midea.h>
#include <ir_Gree.h>
#include <IRtimer.h>
#include <ir_Delonghi.h>
#include <ir_Samsung.h>
#include <ir_Sharp.h>
#include <ir_Kelvinator.h>
#include <ir_NEC.h>
#include <ir_Electra.h>
#include <IRsend.h>
#include <IRac.h>
#include <ir_Daikin.h>
#include <ir_Carrier.h>
#include <IRremoteESP8266.h>
#include <i18n.h>
#include <ir_Trotec.h>
#include <ir_Tcl.h>
#include <ir_Goodweather.h>
#include <ir_Corona.h>
#include <ir_Neoclima.h>
#include <ir_Toshiba.h>
#include <ir_Teco.h>
#include <ir_Magiquest.h>
#include <ir_Argo.h>
#include <ir_Haier.h>
#include <IRrecv.h>
#include <ir_LG.h>
#include <IRutils.h>
#include <ir_Whirlpool.h>
#include <ir_Amcor.h>
#include <ir_Fujitsu.h>
#include <ir_Mitsubishi.h>
#include <IRtext.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Add this library: https://github.com/markszabo/IRremoteESP8266
#include <IRremoteESP8266.h>

#define IR_SEND_PIN D2

#define DELAY_BETWEEN_COMMANDS 1000

IRsend irsend(IR_SEND_PIN);

const char* ssid = "";
const char* password = "";

ESP8266WebServer server(80);

const int led = BUILTIN_LED;

String rowDiv = "    <div class=\"row\" style=\"padding-bottom:1em\">\n";
String endDiv = "    </div>\n";

// Buttons are using the bootstrap grid for sizing - http://getbootstrap.com/css/#grid
String generateButton(String colSize, String id, String text, String url) {

  return  "<div class=\"" + colSize + "\" style=\"text-align: center\">\n" +
          "    <button id=\"" + id + "\" type=\"button\" class=\"btn btn-default\" style=\"width: 100%\" onclick='makeAjaxCall(\"" + url + "\")'>" + text + "</button>\n" +
          "</div>\n";
}

void handleRoot() {
  digitalWrite(led, 0);
  String website = "<!DOCTYPE html>\n";
  website = website + "<html>\n";
  website = website + "  <head>\n";
  website = website + "    <meta charset=\"utf-8\">\n";
  website = website + "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
  website = website + "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  website = website + "    <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\">\n";
  website = website + "  </head>\n";
  website = website + "  <body>\n";
  website = website + "    <div class=\"container-fluid\">\n";
  // -------------------------Test --------------------
//  website = website + ""
  website = website + " <div class=\"tab\"> "
  website = website + "<button class="tablinks" onclick="openCity(event, 'London')">London</button>"
  website = website + "<button class="tablinks" onclick="openCity(event, 'Paris')">Paris</button>"
  website = website + ""
  website = website + "</div>"
  
  // ------------------------- Power Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-3", "tvpower","TV Power", "tvpower");
  website = website + generateButton("col-xs-3", "switchon","Switch On", "switchon");
  website = website + generateButton("col-xs-3", "switchoff","Switch Off", "switchoff");
  website = website + generateButton("col-xs-3", "satpower","Sat Power", "satpower");
  website = website + endDiv;
  // ------------------------- Channel Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-3", "sschannel1","PS4", "sschannel1");
  website = website + generateButton("col-xs-3", "sschannel2","FTV", "sschannel2");
  //website = website + generateButton("col-xs-3", "sschannel3","---", "sschannel3");
  website = website + generateButton("col-xs-3", "sschannel4","SAT", "sschannel4");
  website = website + generateButton("col-xs-3", "sstvsound","TVS", "sstvsound");
  website = website + endDiv;
  // ------------------------- Volume Controls --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "up","Switch Up", "up");
  website = website + endDiv;
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "down","Switch Down", "down");
  website = website + endDiv;
  // ------------------------- Satelite Controls --------------------------
  // Not working well
//  website = website + rowDiv;
//  website = website + generateButton("col-xs-offset-4 col-xs-4", "satup","Sat Up", "satup");
//  website = website + generateButton("col-xs-4", "satblue","Sat Blue", "satblue");
//  website = website + endDiv;
//  website = website + rowDiv;
//  website = website + generateButton("col-xs-4", "satexit","Sat Exit", "satexit");
//  website = website + generateButton("col-xs-4", "satdown","Sat Down", "satdown");
//  website = website + generateButton("col-xs-4", "satok","Sat Ok", "satok");
//  website = website + endDiv;
  // ------------------------- Chromecast --------------------------
  website = website + rowDiv;
  website = website + generateButton("col-xs-12", "chromecast","Chromecast", "chromecast");
  website = website + endDiv;
  website = website + rowDiv;
//  website = website + generateButton("col-xs-12", "togglesource","TV Source", "togglesource");
  website = website + generateButton("col-xs-12", "tvsource","TV Source", "tvsource");
  website = website + endDiv;
  website = website + endDiv;
  website = website + "    <script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js\"></script>\n";
  website = website + "    <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\"></script>\n";
  website = website + "    <script> function makeAjaxCall(url){$.ajax({\"url\": url})}</script>\n";
  website = website + "  </body>\n";
  website = website + "</html>\n";

  server.send(200, "text/html", website);
  digitalWrite(led, 1);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 1);
}

void setup(void){
  irsend.begin();
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS Responder Started");
  }

  server.on("/", handleRoot);

  server.on("/down", [](){
    Serial.println("Switch Down");
    irsend.sendNEC(0x807FA05F, 32);
    server.send(200, "text/plain", "Switch Down");
  });

  server.on("/up", [](){
    Serial.println("Switch Up");
    irsend.sendNEC(0x807F30CF, 32);
    server.send(200, "text/plain", "Switch Up");
  });

  server.on("/switchon", [](){
    Serial.println("Switch on");
    irsend.sendNEC(0x807F3AC5, 32);
    server.send(200, "text/plain", "Switch Power");
  });

  server.on("/switchoff", [](){
    Serial.println("Switch off");
    irsend.sendNEC(0x807FF807, 32);
    server.send(200, "text/plain", "Switch Power");
  });

  server.on("/sschannel1", [](){
    Serial.println("Surround Sound Channel 1");
    irsend.sendNEC(0x68DC1B9A, 32);
    server.send(200, "text/plain", "Surround Sound Channel 1");
  });

  server.on("/sschannel2", [](){
    Serial.println("Surround Sound Channel 2");
    irsend.sendNEC(0x4BB6F00F, 32);
    server.send(200, "text/plain", "Surround Sound Channel 2");
  });

  server.on("/sschannel3", [](){
    Serial.println("Surround Sound Channel 3");
    irsend.sendNEC(0x4BB6708F, 32);
    server.send(200, "text/plain", "Surround Sound Channel 3");
  });

  server.on("/sschannel4", [](){
    Serial.println("Surround Sound Channel 4");
    irsend.sendNEC(0x4BB6B04F, 32);
    server.send(200, "text/plain", "Surround Sound Channel 4");
  });

  server.on("/sstvsound", [](){
    Serial.println("Surround Sound sstvsound");
    irsend.sendNEC(0x4BB6906F, 32);
    server.send(200, "text/plain", "Surround Sound sstvsound");
  });

  server.on("/tvpower", [](){
    Serial.println("TV power");
    irsend.sendNEC(0xA90, 12);
    server.send(200, "text/plain", "TV Power");
  });

  server.on("/tvsource", [](){
    Serial.println("TV Source");
    irsend.sendSony(0xA50, 12);
    server.send(200, "text/plain", "TV Source");
  });

//  server.on("/togglesource", [](){
//    Serial.println("TV Source");
//    irsend.sendNEC(0x20DFD02F, 32);
//    delay(DELAY_BETWEEN_COMMANDS);
//    irsend.sendNEC(0x20DFD02F, 32);
//    server.send(200, "text/plain", "TV Source");
//  });

  server.on("/satpower", [](){
    Serial.println("Sat Power");
    irsend.sendNEC(0x20E4CBF8, 102);
    server.send(200, "text/plain", "Sat Power");
  });

  server.on("/satok", [](){
    Serial.println("Sat Ok");
    irsend.sendNEC(0xA25DFA05, 32);
    server.send(200, "text/plain", "Sat OK");
  });

  server.on("/satexit", [](){
    Serial.println("Sat Exit");
    irsend.sendNEC(0xA25D06F9, 32);
    server.send(200, "text/plain", "Sat Exit");
  });

  server.on("/satup", [](){
    Serial.println("Sat UP");
    irsend.sendNEC(0xA25DC03F, 32);
    server.send(200, "text/plain", "Sat UP");
  });

  server.on("/satdown", [](){
    Serial.println("Sat Down");
    irsend.sendNEC(0xA25D7A85, 32);
    server.send(200, "text/plain", "Sat Down");
  });

  server.on("/satblue", [](){
    Serial.println("Sat Blue");
    irsend.sendNEC(0xA25D52AD, 32);
    server.send(200, "text/plain", "Sat Blue");
  });

  server.on("/chromecast", [](){
    Serial.println("Chromecast");
    irsend.sendNEC(0x20DFD02F, 32);
    delay(DELAY_BETWEEN_COMMANDS);
    irsend.sendNEC(0x20DFD02F, 32);
    delay(DELAY_BETWEEN_COMMANDS);
    irsend.sendNEC(0x4BB6906F, 32);
    server.send(200, "text/plain", "Chromecast");
  });


  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void){
  server.handleClient();
}
