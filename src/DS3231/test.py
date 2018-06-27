from DS3231 import DS3231
import datetime

"""
Define helper functions
"""

def print_clock_states(ds):
    print 'Current Hardware Clock: ' + ds.read_datetime().strftime('%m/%d/%Y %H:%M:%S')
    print 'Current System Clock: ' + datetime.datetime.now().strftime('%m/%d/%Y %H:%M:%S')
    print ' '


def are_clocks_synced(ds):
    """ Check if clock times differ by more than 10 seconds apart """
    return (datetime.datetime.now() - ds.read_datetime()) < datetime.timedelta(0, 10)


"""
Run the main script
"""

if __name__ == "__main__":
    ds = SDL_DS3231(0)

    clocks_synced = are_clocks_synced(ds)
    print_clock_states(ds)
    print 'Clocks Synced? ' + str(clocks_synced) + '\n'

    if not clocks_synced:
        ds.write_datetime(datetime.datetime.now())

    print_clock_states(ds)
