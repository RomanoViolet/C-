#!/usr/bin/env bash

HomeDirectory=`pwd`

# Tell Git that hooks live at a non-standard directory
if [ ! -d ${HomeDirectory}/.githooks_customized ]; then
    echo
    echo
    echo ____________ ERROR _____________
    echo
    echo "Git Repository Error: Git Hooks for VMC2 expected in .githooks_customized Not Found in ${HomeDirectory}".
    echo
    echo ____________ ERROR _____________
    echo
    echo
else
    echo
    echo
    echo ____________ Git Hooks Customized _____________
    echo
    echo "Git Hooks for VMC2 Set to .githooks_customized"
    echo
    echo _______________________________________________
    echo
    echo
    git config core.hooksPath "${HomeDirectory}/.githooks_customized"
    git lfs install
    git init
fi
