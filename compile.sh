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
remote_path="/home/$remote_user/pacs3"

# Send the compiled files to the remote server via SSH
scp ./src/* "$remote_user@$remote_server:$remote_path/src"
scp ./CMake/PilgorCMakeLists.txt "$remote_user@$remote_server:$remote_path/CMakeLists.txt"
ssh "$remote_user@$remote_server" << EOF
cd "$remote_path" && cmake . && make
EOF
