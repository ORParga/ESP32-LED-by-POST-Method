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

<p align=center>
<img src="https://user-images.githubusercontent.com/10864822/202307093-ca25cb98-a2e3-4b85-926b-1ae4436e6286.jpg" width ="400">
</p>


<h3>THE CODE </h3>
The example consists of two programs. One for the web client and one for the web server.
<h5> WEB CLIENT </h5>
  The client-Web program will work in the internet browser of a computer or smartphone, so it is written in JavaScript nested in a "clientWeb.HTML" file.

This program is automatically loaded by the browser from the ESP32 when it makes the first connection request. So, the "clientWeb.HTML" file must be stored in the ESP32's memory.

To know how the file system works, you can follow the tutorial from random nerd tutorials: [Install ESP32 Filesystem Uploader in Arduino IDE](https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/)
