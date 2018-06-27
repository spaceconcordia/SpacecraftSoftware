import sys

path = list(sys.path)
sys.path.insert(0, '/root/csdc4/src/DS1624')  # '/root/csdc4/src/GPIO/acme'

try:
    from DS1624 import DS1624
    ds = DS1624(0x68)


finally:
    sys.path[:] = path  # restore
