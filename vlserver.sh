#!/bin/sh
### BEGIN INIT INFO
#
# Provides:      ddns
# Required-Start:       $local_fs  $remote_fs
# Required-Stop:        $local_fs  $remote_fs
# Default-Start:        2 3 4 5
# Default-Stop:         0 1 6
# Short-Description:    initscript
# Description:  This file should be used to construct scripts to be placed in /etc/init.d.
#
### END INIT INFO

## Fill in name of program here.
PROG="vlserver"
PROG_PATH="/data/app/live" #::# Not need, but sometimes helpful (if $PROG resides in /opt for example).
PROG_ARGS="8090"
PID_PATH="$PROG_PATH/$PROG.pid"
MSG_PREFIX=" *"

start() {
    if [ -e "$PID_PATH" ]; then
        ## Program is running, exit with error.
        echo "$MSG_PREFIX $PROG is currently running..."
    else
        ## Change from /dev/null to something like /var/log/$PROG if you want to save output.
        $PROG_PATH/$PROG $PROG_ARGS 2>&1 >/dev/null &
        echo "$MSG_PREFIX $PROG started"
    fi
}

stop() {
    if [ -e "$PID_PATH" ]; then
        ## Program is running, so stop it
        pid=`cat $PID_PATH | head -n 1`
        kill -9 $pid &  rm -f  "$PID_PATH"
        echo "$MSG_PREFIX $PROG stopped"
    else
        ## Program is not running, exit with error.
        echo "$MSG_PREFIX $PROG not started!"
    fi
}

## Check to see if we are running as root first.

if [ "$(id -u)" != "0" ]; then
    echo "This script must be run as root" 1>&2
    exit 1
fi

case "$1" in
    start)
        start
        exit 0
    ;;
    stop)
        stop
        exit 0
    ;;
    reload|restart|force-reload)
        stop
        start
        exit 0
    ;;
    **)
        echo "Usage: $0 {start|stop|reload}" 1>&2
        exit 1
    ;;
esac

