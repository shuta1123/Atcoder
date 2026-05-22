#!/bin/bash

# append to .bashrc
cat $SRC_FOLDER/bash_append/.bashrc >> ~/.bashrc

# vscode settings files
cp -r $SRC_FOLDER/.vscode $WORKSPACE_FOLDER

# online-judge-tools files
mkdir -p ~/.local/share/online-judge-tools/
cp $SECRET_FOLDER/atcoder/cookie.jar ~/.local/share/online-judge-tools/cookie.jar

# atcoder-cli files
mkdir -p ~/.config/atcoder-cli-nodejs/
cp -r $SRC_FOLDER/atcoder-cli/* ~/.config/atcoder-cli-nodejs/
cp $SECRET_FOLDER/atcoder/session.json ~/.config/atcoder-cli-nodejs/session.json

# python venv setup
cd $WORKSPACE_FOLDER
sudo chown -R vscode:vscode venv
python3 -m venv venv
source venv/bin/activate
pip install -r $SRC_FOLDER/requirements.txt
deactivate