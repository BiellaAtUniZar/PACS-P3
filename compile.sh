#!/bin/bash

# Run cmake
cmake .

# Compile
make

# Define local user and remote user
local_user=$(whoami)
if [ "$local_user" == "conte" ]; then
    remote_user="a847803"
else
    remote_user="aBruno"
fi

# Define the remote server and path
remote_server="pilgor.cps.unizar.es"
remote_path="/home/$remote_user/"

# Send the compiled files to the remote server via SSH
scp ./bin/* "$remote_user@$remote_server:$remote_path"
