# ESP32-LED-by-POST-Method

This sketch shows how to connect an ESP32 to a web page in a way that they interact quickly.

<p align="justify">
Unlike the GET method, the transmission by the POST method between the Web page and the server allows a fluid communication without having to reload the page continuously.
</p>

<h3> DESCRIPTION </h3>

<p align="justify">
In this example, the ESP is configured in STA (station) mode to connect to WiFi. After Shows the IP address on the serial monitor that can be accessed with a browser connected to the same WiFi. Once connected, the browser shows a colored circle that informs the status of the GPIO04 output.
</p>
<p align=center>
<img src="https://user-images.githubusercontent.com/10864822/202283679-9c7f3c8f-62fb-4261-b78e-8b6539cf53bd.GIF" width ="400">
</p>
<h3> GENERAL IDEA </h3>

<p align="justify">
Basically, the ESP32 connects to a WiFi network with the well-known function WiFi.begin(ssid, password) to get an IP to which a web browser on a computer or smartphone can connect. As soon as the browser connects to said IP, it sends a request to the ESP32 to which it responds by sending the "clientWeb.html" file that it will display on the screen.

Immediately, this page " clientWeb.html" will start sending messages to the ESP32 at short time intervals requesting information about the button state. The ESP will respond to this request with a string: "on" or "off".
</p>
<p align=center>
<img src="https://user-images.githubusercontent.com/10864822/202307093-ca25cb98-a2e3-4b85-926b-1ae4436e6286.jpg" width ="650">
</p>


<h3>THE CODE </h3>
The example consists of two programs. One for the web client and one for the web server.
<h4><u> WEB CLIENT </u></h4>

<p align="justify">
  The client-Web program will work in the internet browser of a computer or smartphone, so it is written in JavaScript nested in a "clientWeb.HTML" file.

This program is automatically loaded by the browser from the ESP32 when it makes the first connection request. So, the "clientWeb.HTML" file must be stored in the ESP32's memory.

To know how the file system works, you can follow the tutorial from random nerd tutorials: [Install ESP32 Filesystem Uploader in Arduino IDE](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)

Once the "ClientWeb.html" file is working, it starts sending requests to know the status of the button. This is done with the JavaScript function: fetch().
</p>

```
let param = "lightState";

let response = await fetch("/", {
    method: 'POST',
    headers: {
        'Content-type': 'text/plain;charset=utf-8'
    },
    body: param
});
```

<p align="justify">
The JavaScript fetch() function sends a request to the url indicated in its first parameter (in this case "/") described in the options described by the second parameter, (in this case, the POST method, data type "text /plain", and the data "lightState")
  
  This request is received by the ESP32 that acts as a web server.

  </p>

<h4><u> WEB SERVER </u></h4>

<p align="justify">
In this example, the web server is the program loaded on the ESP32. For simplicity, it only responds to a minimum number of client requests. The most important to understand its operation are:
  </p>
  
  ```
  
    server.on("/", HTTP_GET,...);
    server.on("/", HTTP_POST,...);

  ```
  
  
<p align="justify">
The first function, which uses the response to the request of the HTTP_GET type, is responsible for sending the web page "clientWeb.html" to the browser that requests it, through the delegate function: request->send().
  </p>
  
  ```
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send(SPIFFS, "/clientWeb.html", "text/html");
        });
  ```
  
<p align="justify">
  The second function, which uses the response to the POST type request, is in charge of sending information about the button's state through another function request->send().
</p>

```
server.on("/", HTTP_POST, ....{
  if (digitalRead(4))
  {
      request->send(200, "text/html", "on");//send a string "on" to the client if the button on GPIO4 is on
  }
  else
  {
      request->send(200, "text/html", "off");//send a string "off" to the client if the button on GPIO4 is off
  }
  ...
}
 ```
 This information is received by the Web client as a result of its request through the value returned by response.text();
 
```

let param = "lightState";

let response = await fetch("/", {
    method: 'POST',
    headers: {
        'Content-type': 'text/plain;charset=utf-8'
    },
    body: param
});
let result = await response.text();
let equal = result.localeCompare("on");
if (equal == 0) {
    SetCircle(1);//If the web server returns "on", the browser shows a red circle

}
```
