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
<h5> WEB CLIENT </h5>

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
  </p>
  
