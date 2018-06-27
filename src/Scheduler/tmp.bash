#!/bin/bash
#/root/csdc4/src/Scheduler/tmp.bash
#e.g: bash /root/csdc4/src/Scheduler/tmp.bash /root/csdc4/src/Scheduler/timertest.timer

> /etc/systemd/system/$1
echo [Unit] >> /etc/systemd/system/$1
echo Description=Runs timertest script after delayed start >> /etc/systemd/system/$1

echo [Timer] >> /etc/systemd/system/$1

# Realtime timer
echo OnCalendar=$(date +"%F %H:%M:%S" -d "+1 min") >> /etc/systemd/system/$1

# Triggers the service immediately if it missed the last start time
echo Persistent=true >> /etc/systemd/system/$1

echo Unit=timertest.service >> /etc/systemd/system/$1

echo [Install] >> /etc/systemd/system/$1
echo WantedBy=multi-user.target >> /etc/systemd/system/$1

#cat /etc/systemd/system/$1

systemctl daemon-reload
systemctl restart $1

#systemctl start $1
#systemctl enable $1
#systemctl list-timers
