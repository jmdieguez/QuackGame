#!/bin/bash

NAME="quackgame"
BIN_DIR="/usr/bin"
ASSETS_DIR="/var/$NAME"
CONFIG_DIR="/etc/$NAME"
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

set -e # Finalizar ante error
trap 'echo -e "${RED}Error: La instalación ha fallado en la línea $LINENO.${RESET}"; exit 1' ERR

# 1. Descargar e instalar dependencias
echo -e "${GREEN}Instalando dependencias...${RESET}"
sudo apt update
sudo apt install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev qtbase5-dev qt5-qmake qtmultimedia5-dev

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

# 2. Compilar el proyecto
echo -e "${GREEN}Compilando el proyecto...${RESET}"
make GLOBAL_INSTALL=true

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

# 3. Copiar/mover los binarios

sudo cp build/quack_game_server "$BIN_DIR"
sudo cp build/quack_game_client "$BIN_DIR"
sudo cp build/quack_game_editor "$BIN_DIR"

# 4. Copiar assets y archivos de configuración
echo -e "${GREEN}Instalando binarios en $BIN_DIR, assets en $ASSETS_DIR y configuraciones en $CONFIG_DIR...${RESET}"
sudo mkdir -p "$ASSETS_DIR" "$CONFIG_DIR" "$CONFIG_DIR/maps"
sudo cp -r assets/* "$ASSETS_DIR/"
sudo cp -r config/* "$CONFIG_DIR/"
sudo cp -r server/game/maps/* "$CONFIG_DIR/maps/"

printf '%*s\n' "$(tput cols)" | tr ' ' '-'

echo -e "${GREEN}Instalación completa.${RESET}"
