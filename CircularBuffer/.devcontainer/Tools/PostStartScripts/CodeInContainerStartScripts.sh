#!/usr/bin/env bash

HomeDirectory=`pwd`

# Enable Git Credentials Helper
git config --global credential.helper "cache --timeout=36000"

################# Print Path in Color ###################
force_color_prompt=yes
export TERM=xterm-color
export GREP_OPTIONS='--color=auto' GREP_COLOR='1;32'
export CLICOLOR=1
export LSCOLORS=ExFxCxDxBxegedabagacad
export COLOR_NC='\e[0m' # No Color
export COLOR_BLACK='\e[0;30m'
export COLOR_GRAY='\e[1;30m'
export COLOR_RED='\e[0;31m'
export COLOR_LIGHT_RED='\e[1;31m'
export COLOR_GREEN='\e[0;32m'
export COLOR_LIGHT_GREEN='\e[1;32m'
export COLOR_BROWN='\e[0;33m'
export COLOR_YELLOW='\e[1;33m'
export COLOR_BLUE='\e[0;34m'
export COLOR_LIGHT_BLUE='\e[1;34m'
export COLOR_PURPLE='\e[0;35m'
export COLOR_LIGHT_PURPLE='\e[1;35m'
export COLOR_CYAN='\e[0;36m'
export COLOR_LIGHT_CYAN='\e[1;36m'
export COLOR_LIGHT_GRAY='\e[0;37m'
export COLOR_WHITE='\e[1;37m'


# From http://bashrcgenerator.com
echo export PS1=\""\[\033[38;5;16m\]\[\033[48;5;230m\]\u\[$(tput sgr0)\]@\w>\[$(tput sgr0)\]"\" >> ~/.bashrc

# Add configuration from Google's C++ style
# .clang-tidy is manually configured.
cd /workspace/cpp-17/
#wget https://raw.githubusercontent.com/googleapis/google-cloud-cpp/master/.clang-format
wget https://raw.githubusercontent.com/googleapis/google-cloud-cpp/master/.cmake-format.py
cd ${HomeDirectory}
