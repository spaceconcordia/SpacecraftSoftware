from __future__ import print_function
import sys
import datetime
import time
import itertools
import os

path = list(sys.path)
sys.path.insert(0, '/root/csdc4/src/DS3231')
sys.path.insert(0, '/root/csdc4/src/DS1624')
sys.path.insert(0, '/root/csdc4/src/GPIO/acme')

from DS1624 import DS1624
from DS3231 import DS3231
from acmepins import GPIO


def menu_main():
    print(" ")
    print("Main Menu:")
    print("1. Clock")
    print("2. Sensors")
    print("3. Operations")
    print("4. Tests")

    menu_map = {
        1: menu_clock,
        2: menu_sensors,
        3: menu_payload,
        4: menu_tests
    }

    menu_input = input('>>> ')
    option = menu_map.get(menu_input, menu_main)
    option()


def menu_clock():
    def set_system_clock(dt=None):
        if dt == None:
            print("Enter date and time (YYYY-MM-DD hh:mm:dd): ")
            datetime_str = raw_input()
            dt = datetime.datetime.strptime(datetime_str, "%Y-%m-%d %H:%M:%S")
        os.system("date --set \"" + dt.strftime("%Y-%m-%d %H:%M:%S") + "\"")

    def set_hardware_clock(ds):
        print("Enter date and time (YYYY-MM-DD hh:mm:dd): ")
        datetime_str = raw_input()
        dt = datetime.datetime.strptime(datetime_str, "%Y-%m-%d %H:%M:%S")
        ds.write_datetime(dt)

    def sync_clocks(ds):
        def print_clock_states(ds):
            print('Current Hardware Clock: ' +
                  ds.read_datetime().strftime('%m/%d/%Y %H:%M:%S'))
            print('Current System Clock: ' +
                  datetime.datetime.now().strftime('%m/%d/%Y %H:%M:%S'))
            print(' ')

        def are_clocks_synced(ds):
            """ Check if clock times differ by more than 10 seconds apart """
            return (datetime.datetime.now() - ds.read_datetime()) < datetime.timedelta(0, 10)

        clocks_synced = are_clocks_synced(ds)
        print_clock_states(ds)
        print('Clocks Synced? ' + str(clocks_synced) + '\n')

        if not clocks_synced:
            set_system_clock(ds.read_datetime())

        print_clock_states(ds)

    print(" ")
    print("Clock Menu:")
    print("1. Read System Clock")
    print("2. Read Hardware Clock")
    print("3. Set System Clock")
    print("4. Set Hardware Clock")
    print("5. Sync Clocks")

    ds = DS3231(twi=0, addr=0x68)
    dt = datetime

    menu_map = {
        1: lambda: print(dt.datetime.now().strftime('%m/%d/%Y %H:%M:%S')),
        2: lambda: print(ds.read_datetime().strftime('%m/%d/%Y %H:%M:%S')),
        3: lambda: set_system_clock(ds),
        4: lambda: set_hardware_clock(ds),
        5: sync_clocks
    }

    menu_input = input('>>> ')
    option = menu_map.get(menu_input, menu_main)
    option()


def menu_sensors():
    print(" ")
    print("Sensors Menu:")
    print("1. Read Temperature")

    sensors = [
        DS1624(0x90),
        DS1624(0x91),
        DS1624(0x92),
        DS1624(0x93),
        DS1624(0x94)
    ]

    cnt = itertools.count(1)

    menu_map = {
        1: lambda: map(lambda x: print('TS ' + str(cnt.next()) + ': ' + x.read_temperature()), sensors)
    }

    menu_input = input('>>> ')
    option = menu_map.get(menu_input, menu_main)
    option()


def menu_payload():
    def deploy_payload():
        deployment_a = GPIO('J4.8', 'OUTPUT')
        deployment_b = GPIO('J4.10', 'OUTPUT')
        deployment_a.on()
        deployment_b.on()
        time.sleep(10)
        deployment_a.off()
        deployment_b.off()

    def fetch_experiment_data():
        with open("Payload/data.log") as f:
            for line in f:
                print(line, end="")
                time.sleep(0.5)

    print(" ")
    print("Operations Menu:")
    print("1. Deploy Satellite")
    print("2. Fetch Payload Data")

    menu_map = {
        1: deploy_payload,
        2: fetch_experiment_data
    }

    menu_input = input('>>> ')
    option = menu_map.get(menu_input, menu_main)
    option()


def menu_tests():
    print(" ")
    print("Tests Menu:")
    print("1. Sync Clocks with Grounstation")
    print("2. Delay Deploy Payload with Power Interrupt")


def main():
    main_loop = True

    while main_loop:
        menu_main()


if __name__ == "__main__":
    print("SPACE CONCORDIA - PROJECT ALEKSANDR")
    try:
        main()

    except:
        print("An error has occurred, program exiting now.")

    finally:
        sys.path[:] = path  # restore