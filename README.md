# Quack Game

Remake del juego [Quack Game](https://store.steampowered.com/app/312530/Duck_Game/). Realizado en C++ con [SDL2pp](git@github.com:libSDL2pp/libSDL2pp.git) y Qt.

<div style="text-align: center;">
  <img src="assets/logo.png" alt="QuackGame logo" style="width: 300px;">
</div>

# Manual del usuario

**Quack Game** es un juego de acción multijugador donde controlas a un pato en batallas rápidas y competitivas. El objetivo es enfrentarte a otros jugadores en diferentes arenas utilizando una variedad de armas y objetos que encuentras durante el juego. Podrás dispararle a cajas misteriosas que tienen armas, armaduras ¡o incluso granadas a punto de explotar!

Cada partida es dinámica y requiere rapidez, estrategia y un poco de suerte para ser el último pato en pie. Es perfecto para jugar con amigos y disfrutar de momentos entretenidos llenos de risas y competencia amistosa. ¡Prepárate para sumergirte en intensas y divertidas peleas de patos! 

![Screenshot](/docs/juego.png)

## ¿Cómo instalar el juego?

Abrir una Terminal y ejecutar las siguientes líneas:

Para descargar el repositorio del juego:

```bash
git clone git@github.com:jmdieguez/QuackGame.git
```

Desde la ubicación donde se descargó, ejecutar lo siguiente para moverse a la carpeta del juego.

```bash
cd QuackGame
```

A continuación, optar por una de las siguientes opciones:

### Opción 1: Instalar el juego globalmente (recomendado)

Se cuenta con un instalador el cual puede usarse ejecutando el archivo **install.sh** de la siguiente manera:

```bash
./install.sh
```

Esto te permitirá ejecutar los programas del juego desde cualquier directorio, y es bastante conveniente.

### Opción 2: Compilar y correr desde el directorio del juego

Como requisito para esta opción hace falta instalar manualmente las dependencias del juego con los siguientes comandos:

```bash
sudo apt update
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev qtbase5-dev qt5-qmake qtmultimedia5-dev
```

Una vez instaladas las dependencias, el juego puede compilarse con:

```bash
make
```

Esto creará una carpeta llamada **build** dentro de la carpeta del juego. Dentro de ella estarán los archivos binarios ejecutables. Más adelante, será importante ejecutar estos archivos desde la carpeta raíz del juego, como por ejemplo:

```bash
./build/...
```

# ¿Cómo jugar?

## Correr un servidor

Para poder jugar múltiples partidas entre amigos hace falta que alguien tenga un **Servidor** levantado. Para hacerlo, una vez instalado el juego, se corre una de las siguientes líneas, según qué opción de instalación se ha elegido. El **puerto** es el número de puerto donde se recibirán conexiones de clientes. Por ejemplo, se puede usar el número 8099.

```bash
quack_game_server <puerto>         # Instalación opción 1
                                   # o
./build/quack_game_server <puerto> # Instalación opción 2
```

Esto mantendrá abierto el servidor en la terminal. Para finalizarlo se debe escribir la letra **q** y pulsar Enter. Solo hace falta crear partidas dentro del servidor una vez que tus amigos se conecten (siguiente paso).

## Crear y unirse a partidas

Una vez que se tenga un servidor corriendo, se puede conectar a él a través de:

```bash
quack_game_client <servidor> <puerto>           # Instalación opción 1
                                                # o
./build/quack_game_client <servidor> <puerto>   # Instalación opción 2
```

Esto abrirá una interfaz en la cual podrás optar por crear una partida o unirte a una existente.

![Crear o unirse a una partida](/docs/crear_partida.png)

Y listo! Una vez que todos tus amigos estén unidos a la partida, podrá comenzar la acción!

## Controles

1 Jugador

* Apuntar hacia arriba: W
* Agacharse: S
* Moverse a la izquierda: A
* Moverse hacia la derecha: D
* Saltar: Espacio
* Agarrar un arma del suelo: E
* Disparar: T
* Soltar: G

2 Jugador

* Apuntar hacia arriba: UP
* Agacharse: DOWN
* Moverse a la izquierda: LEFT
* Moverse hacia la derecha: RIGHT
* Saltar: SHIFT
* Agarrar un arma del suelo: I
* Disparar: O
* Soltar: L

## Cheats

* Escribir 'ak' para spawnear AK-47
* Escribir 'sh' para spawnear Shotgun
* Escribir 'gr' para spawnear Granada
* Escribir 'ba' para spawnear Banana
* Escribir 'co' para spawnear Cowboy Pistol
* Escribir 'du' para spawnear Dueling Pistol
* Escribir 'ma' para spawnear Magnum
* Escribir 'pe' para spawnear Pew Pew Laser
* Escribir 'sn' para spawnear Sniper
* Escribir 'ri' para spawnear Laser Rifle

## Crear un mapa personalizado

Para poder crear tu propio mapa personalizado podrás usar el Editor de niveles con una de las siguientes líneas, donde <archivo> es el nombre del mapa que crearás. Considera que debe finalizar con la extensión **.yaml**:

```bash
quack_game_editor <archivo>.yaml            # Instalación opción 1
                                            # o 
./build/quack_game_editor <archivo>.yaml    # Instalación opción 2
```

Esto abrirá la siguiente interfaz con una grilla de 32x16 baldosas:

![Editor](/docs/editor.png)

A partir de los botones, podrás ubicar los puntos de aparición de patos, armas, y cajas, como también los componentes del mapa cuyas dimensiones son las siguientes:

* Big Wall y Long Ground: 3x1
* Single Ground: 1x1
* Slim Wall: 1x3

# Créditos

Realizado por

* Trinidad Bucciarelli

* José Manuel Dieguez

* Matias Rueda

# Recursos

[libSDL2pp](https://github.com/libSDL2pp/libSDL2pp)

Tileset extraído del juego OpenSource [Tonde Iko](git@github.com:greggman/hft-tonde-iko.git) (BSD-3-Clause license)

# Documentación

Se podrá encontrar el manual de proyecto y la documentación técnica dentro de la carpeta [docs](https://github.com/jmdieguez/QuackGame/tree/main/docs)
