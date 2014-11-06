lights
======

light controller

things to conisder...   
IP address of the device... edit it under index.html >> make it the same as the computer running node      
The baudrate, it should be the same on both devices, for arduino uno, speed it up, mini pro > 9600     
Make sure the correct usb device is selected in node. >> ls /dev/ | grep usb >> to see what usb devices are connected     

git pull and then npm install the packages, it needs atleast node 0.10 (wasn't working for 0.8)

