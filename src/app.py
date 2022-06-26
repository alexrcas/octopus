from flask import Flask, render_template
from flask_mqtt import Mqtt
from flask_socketio import SocketIO
import json


app = Flask(__name__,  template_folder='web/templates',
    static_folder='web/static')

app.config['MQTT_BROKER_URL'] = 'localhost'  # use the free broker from HIVEMQ
app.config['MQTT_BROKER_PORT'] = 1883  # default port for non-tls connection
app.config['MQTT_KEEPALIVE'] = 5  # set the time interval for sending a ping to the broker to 5 seconds
app.config['MQTT_TLS_ENABLED'] = False  # set TLS to disabled for testing purposes

socketio = SocketIO(app)
mqtt = Mqtt(app)


######################################################################

@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('oficina/#')


@mqtt.on_message()
def handle_mqtt_message(client, userdata, message):
    payload = message.payload.decode()
    socketio.emit(message.topic, json.loads(payload))


@mqtt.on_log()
def handle_logging(client, userdata, level, buf):
    print(level, buf)


@app.route('/')
def index():
    return render_template('index.html')

app.run(host='0.0.0.0', port=5000, debug=True)