import serial

port = serial('/dev/cu.wchusbserial14310',basestring=115200,timeout=3.0)

port.write('2')