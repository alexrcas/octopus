# Octopus

## Descripción funcional del proyecto

## Descripción técnica del proyecto

Se propone una solución muy común en el mundo del IoT (Internet of Things), basada en el protocolo MQTT y el patrón publicador/suscriptor. Los diferentes dispositivos inteligentes se comunicarán a través de este protocolo con Octopus.

[Comentar el por qué de la decisión]


![general](doc/resources/general.drawio.png)

Octopus es un sistema completo compuesto por todas las piezas necesarias para su funcionamiento: un servidor web, una base de datos y un broker MQTT, necesario para el uso de este protocolo. Todos estos componentes son englobados usando como abstracción la tecnología de contenerización, reduciendo al mínimo los problemas de portabilidad, compatibilidad y despliegue.

![octopus](doc/resources/octopus.drawio.png)

Así, a efectos de uso, Octopus es una "caja negra". Únicamente debe crearse y arrancar el contenedor con un solo comando. Una vez hecho, el sistema está listo para comunicar a los diferentes clientes IoT que se conecten, su backoffice web es accesible y su API REST está lista para ser consumida.

![sistema-final](doc/resources/sistema-final.drawio.png)

De manera interna, Octopus está compuesto por diferentes sistemas contenerizados que se comunican entre sí o son expuestos al exterior si es necesario. En principio, la base de datos no es expuesta y será accedida o manipulada a través del servidor web.

![arquitectura](doc/resources/arquitectura.png)


Formato de los topics:
```
oficina/sala/dispositivo/atributo
```

Algunos ejemplos podrían ser:
```
oficina/servidores/servidor1/temperatura
oficina/reuniones/aire/rpm
oficina/servidores/luz/brillo
```

### Aspectos de Seguridad

* Para la comunicación HTTP, se implementarán los mecanismos típicos de autenticación, autorización y cifrado comunes en cualquier aplicación web.
* La comunicación MQTT podrá también ser securizada mediante los diferentes mecanismos que ofrece el *Mosquitto*: cifrado SSL, autenticación y autorización mediante usuario/contraseña y listas de control de acceso.


## Tecnologías empleadas

* Docker y Docker-Compose como tecnología de virtualización.
* Mosquitto como Broker MQTT.
* Postgre como Base de datos.
* Python (Flask) como framework para el desarrollo del servidor web debido a su facilidad y velocidad de desarrollo. Tras una primera prueba de concepto puede valorarse Spring Boot.


## Arrancar el proyecto

El ecosistema se ofrece dockerizado y orquestado por *Docker Compose*, por lo que el único paso necesario será situarse en el directorio raíz de este proyecto y ejecutar el comando:

```
docker-compose up
```

### Consideraciones importantes sobre *Mosquitto*

Hay dos ficheros de *Mosquitto* que es necesario mencionar:

```
/mosquito/config/mosquitto.conf
/mosquitto/log/mosquitto.log
```
* El fichero `mosquitto.conf` contiene la configuración básica y es necesario para el arranque de *Mosquitto*. Este fichero está mapeado al fichero `mosquitto/mosquitto.conf` en el proyecto, por lo que las configuraciones pueden hacerse desde este mismo fichero sin necesidad de entrar en el contenedor de *Mosquitto*.
* El fichero `mosquitto.log` contiene los logs de *Mosquitto*, mostrando los clientes que se conectan y desconectan o el estado del sistema y pudiendo ser útil para depurar problemas. Este fichero por defecto no está mapeado a un volumen externo en el host anfitrión, aunque no hay inconveniente en hacerlo si se desea o bien se puede consultar desde el propio contendor. En cualquier caso, merece la pena destacar su existencia.

### Arrancar el servidor

Dado que el código fuente está escrito en Python, se recomienda crear un entorno virtual para no alterar o crear conflictos con las dependencias del sistema donde se ejecute el proyecto. Existen incontables formas y herramientas para crear un entorno virtual (como *virtualenv*). En cualquier caso, una vez creado y activado para el directorio `src`, se debe instalar las dependencias del proyecto:
```
pip install -r requirements.txt
```
Una vez instaladas las dependencias, ejecutar el servidor:
```
python app.py
```

#### Ejemplo concreto de pasos a seguir para arrancar el proyecto:
1. Descargar el proyecto y situarlo en el Escritorio.
2. Crear un entorno virtual en el escritorio con `python -m virtualenv mientorno` (el comando puede variar ligeramente según el sistema y la forma de instalar virtualenv).
3. Mover la carpeta del proyecto a la carpeta `mientorno` que habrá creado el paso 2.
4. Situarse en el directorio `mientorno` y activar el entorno virtual (es un comando simple pero varía según el sistema, consultar documentación).
5. Moverse dentro de la carpeta del proyecto descargado y ejecutar `docker-compose up`.
6. Moverse al directorio `src`, ejecutar `pip install requirements.txt` y posteriormente `python app.py`.


#### Probando el proyecto
Una vez está todo arrancado, si se accede a `http://localhost:5000` debería visualizarse el portal web.
En el proyecto existe un fichero `src/client.py` que simula dos clientes que envían datos. Si se abre una segunda terminal (recordar activar el entorno virtual) y se lanza este script, los datos en el panel web deberían comenzar a oscilar en tiempo real.

![](doc/resources/ejemplo.gif)