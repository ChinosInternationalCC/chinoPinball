###ChinoPinball @ MIRA 2014

***
###Nombre del proyecto y país de procedencia

ChinoPinball - España

***
###Categoría artística

OUTDOOR MAPPING

***
###Artistas

Colectivo Chinos Internacional:
 * Kuba Markiewicz 
 * Carles Gutiérrez
 * Ovidiu Cincheza
 * Angel Muñoz
 * Augusto Zuniga
 * Mery Glez

Colaboradores: 
 * Alex Geell - SoundArt
 * Alex Reche - MadMapper

[http://chinosinternational.cc/](http://chinosinternational.cc/)

[https://www.facebook.com/chinos.international.cc](https://www.facebook.com/chinos.international.cc)

[https://github.com/chinosInternationalCC](https://github.com/chinosInternationalCC)

***
### Datos de contacto

Carles Gutiérrez Valles

***
### Descripción del proyecto

ChinoPinball es un juego de videoArte mapeado con proyección. El juego es una versión de los juegos electronicos [Pinball](http://es.wikipedia.org/wiki/Pinball).

Este Pinball entre lo analógico y lo digital, es un videojuego interactivo que se controla por una sola persona. Esta está dispuesta en frente de la proyección y controlando los flippers desde un tablero digital golpea la bola para conseguir puntos y ganar misiones especiales. 

Concepto sobre los videojuegos en el espacio público.

***
### Features del ChinoPinball: 

Los controladores (hardware):

Es una aplicación interactiva y la gente puede controlarla mediante unos controles externos que utilizan Arduino y otras tecnologías.

No todo el juego es digital, también tiene actuadores físicos, que ofrecen una experiencia tangible al jugador y los espectadores. Por ejemplo, que las colisiones de la bola con ciertos elementos del escenario activan ventiladores, luces, flashes, motores, etc

El juego se controla usando una mesa diseñada y fabricada usando métodos de la fabricación digital. A partir de un modelo 3D la mesa hecha de madera esta cortada usando una cortadora laser.

![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_0.jpg)

La mesa tiene unos botones tipo arcade, y su estado se lee usando un Arduino conectado por el puerto serial con el ordenador en que corre el juego.

El Arduino también tiene conectadas salidas de relé que se pueden activar en momentos clave. Los relés pueden controlar cualquier tipo de equipo de potencia.

Para detectar el típico movimiento de tilt de pinball se usa un acelerómetro que esta metido dentro de la caja y que esta midiendo el movimiento de la caja. El simulador de la física usa esta información para generar el movimiento del tablero virtual.

El juego tiene tambien salidas por OSC (Open Sound Control) que permite la comunicación con otras herramientas que implementa este protocolo, eg. Pure Data, Max Msp, Ableton Live etc

Las salidas por DMX permite la conexión de una gama muy variada de dispositivos para efectos de luces, lasers, humo etc.

La proyección:

La perspectiva del juego depende de la posición del usuario/s. En la posición del jugador hay una mesa con los botones y desde ahí se disfruta de la perspectiva ideal. Las proyecciones y el escenario se modifican en el lugar adaptándose a cada lugar dependiendo de sus posibilidades arquitectónicas.

 Para Mira 2014, se plantea una proyección que emule la disposición de un tablero pinball usando una proyección inclinada hacia el suelo desde cierta altura, por ejemplo, desde un 2º o 3º piso y como paredes, usar una de las esquinas entre los 2 edificios mostrados en el esquema.

Pero en otros casos por ejemplo podría usarse una calle como rampa cuesta arriba y las paredes de los edificios como paredes del escenario entre otras posibilidades. 

El escenario:

Un escenario pseudo-dinámico: 

El juego tiene integrado un editor de escenario, que da posibilidad de construir un escenario en cualquier superficie (pared, suelo) y adaptando los elementos reales 3D como elementos del escenario.

El público:
Probablemente ya en futuras versiones, el público a parte de ser espectador, podrá llegar a interferir sobre el juego modificando el curso del juego. Ya desde un inicio se plantea un diseño compatible con Camaras para usar visión por ordenador ( interpretando sus posiciones y presencia ) o sensores físicos, y que dispuestos sobre el escenario o el área sirvan como actuadores dentro de los eventos del juego.

![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_1.jpg)

El proyector mapea sobre el solar y parte de las paredes de los edificios para crear el escenario 3d del juego.

Localización estimada:![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_2.png)

***
###Derechos de autor:

ChinoPinball es un proyecto OpenSource y se encuentra en github: [https://github.com/ChinosInternationalCC/chinoPinball](https://github.com/ChinosInternationalCC/chinoPinball)

***
###Soporte gráfico de la propuesta

![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_3.png)

La propuesta estética representa el espacio publico catalán, caracterizada por la linea arquitectónica de sus representantes más ilustres, Gaudi y Doménech y Muntaner. Hacemos referencia a las terrazas modernistas y su simbología a través de los tomes distribuidos a lo largo de nuestro escenario.

Estos elementos, así como los muros que contornan los límites de nuestro espacio de proyección servirán como obstáculos físicos por donde la bolita del PINBALL actuará. La fuerza que el usuario utilice al momento de ejecutar los impulsores harán que la bola virtual recorra los diferentes niveles de nuestro escenario "TERRAZA".

Cada totem se iluminará y reaccionará de manera diferente cada vez que la bolita haya "tocado" su area correspondiente, haciendo que la puntuación del usuario se acumule o se reste.

![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_4.png)

![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_5.png)
![image alt text](https://raw.githubusercontent.com/ChinosInternationalCC/chinoPinball/master/doc/PresentacionMira/image_6.png)

***
### Requisitos técnicos y material necesario para el desarrollo del proyecto

* Electrical wiring for the entire facility (Mira)

* 1 Mac Computer: 4GB, monitor, keyboard, mouse (ChinosInternational)

* Video Projector 6000-10000 Ansi Lumen 1.2-1:00 optical + VGA 10 mt to create a video projection of 7x3 mt (Mira)

* Minidisplayport cable (ChinosInternational)

* 2 Speakers and 1 Amplifier+cables (Mira)

***
### Presupuesto necesario y aportaciones propias


Aportaciones propias:

- Materiales necesarios para realizacion del proyecto (caja de controles)

- Hardware técnico y computadora

- Licencias de software (Mad Mapper)

- Alojamiento

Presupuesto necesario:
- un vuelo para una persona de Varsovia (Polonia) a Barcelona

***
### Biografía artística de Chinos International


Link: [http://chinosinternational.cc/projects/](http://chinosinternational.cc/projects/)

EXHIBITIONS:

* Instal·lació vídeo-màpping per a la cloenda de la Setmana Cultural de l’Escola d’Art i Disseny de Tortosa. Escola d’Art i Disseny de Tortosa, Tortosa, 24/05/2013
[http://vimeo.com/67030695](http://vimeo.com/67030695)

* Paperjam, Daos Club, Timisoara (Rumania) 02/05/2013

* Setmana Cultural de l’Escola d’Art i Disseny de Tortosa, Escola d’Art i Disseny de Tortosa, Tortosa, 26/04/2013

* Open mic sessions 1, Corretger 5 Gallery, BCN, 15/12/2012[ (link)](https://www.facebook.com/events/434131486641948/?ref=22)

* Supernova T-34, P52, BCN, 16/11/2012[ (link)](https://www.facebook.com/events/421286761254030/)

FESTIVALS:

* Cau d’Orellla, Freedonia, BCN, 22/03/2013

* Micro-Muteck, BCN, 9/02/2013[ (link)](https://www.facebook.com/events/306764999446826/)

WORKSHOPS:

* TV-Oscil·loscopi: Hackejant el Hardware, Escola d’Art i Disseny de Tortosa, Tortosa, 26/04/2013

* TV-Oscilloscope, TTwister gallery, BCN, 28/02/2013[ (link)](https://www.facebook.com/events/156963477794899/)

CONFERENCES:

* "Estratègies de profanació del dispositiu virtual en l’era post-digital", Escola d’Art i Disseny de Tortosa.[ ](http://jordiplanas.net/article/)26/04/2013

Muestra de obra 

Un video del prototipo del juego con efectos de luces LED: [https://vimeo.com/95458930](https://vimeo.com/95458930)

