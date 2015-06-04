#!/bin/bash

# usage:
# ./syncit <hostname> <remoteuser> <remotedir>

# dependencies:
# sudo apt-get install sshpass inotify-tools

function sync {
  sshpass -p $REMOTE_PASSWORD rsync --exclude-from=.rsyncingore --delete -avz $LOCAL_DIRECTORY $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIRECTORY
}

WATCH_IGNORE=".git"

LOCAL_DIRECTORY=./
REMOTE_HOST=$1
REMOTE_USER=$2
REMOTE_PASSWORD=
REMOTE_DIRECTORY=$3

read -s -p "Password: " REMOTE_PASSWORD
echo

sync
while inotifywait -q --exclude WATCH_IGNORE -r .$LOCAL_DIRECTORY/*; do
  sync
done
