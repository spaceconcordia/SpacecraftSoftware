import smbus

bus=smbus.SMBus(0)
address = 0x68

def get_temperature(address):
	byte_tmsb = bus.read_byte_data(address, 0x11)
	byte_tlsb = bin(bus.read_byte_data(address, 0x12))[2:].zfill(8)
	return byte_tmsb + int(byte_tlsb[0])*2**(-1) + int(byte_tlsb[1])*2**(-2)

print get_temperature(address)

