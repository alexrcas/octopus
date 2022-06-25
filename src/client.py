import paho.mqtt.client as mqtt
import json
import time
# The callback for when the client receives a CONNACK response from the server.

client = mqtt.Client('P1')

client.connect("localhost", 1883, 60)# Blocking call that processes network traffic, dispatches callbacks and# handles reconnecting.# Other loop*() functions are available that give a threaded interface and a# manual interface.

temp = 30
bright = 50
factor = 1

while True:

    client.publish('oficina/reuniones/luz/brillo', json.dumps({'data': bright}))
    client.publish('oficina/servidores/servidor1/temperatura', json.dumps({'data': temp}))

    temp = temp + 1 * factor
    bright = bright + 1 * factor

    if (temp >= 60):
        factor = -1
    
    if (temp <= 30):
        factor = 1

    time.sleep(0.15)