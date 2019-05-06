import smbus
import time
bus = smbus.SMBus(1)
address = 0x48

def write(reg,value):
        bus.write_byte_data(address, reg, value)
        return 0
        
def write_word(reg,value):
        # have to switch the endianness
        if (value > 255):
          upperByte = value>>8
          lowerByte = value - (upperByte<<8)
          newResult = (lowerByte<<8) + upperByte
        else:
          upperByte = 0
          lowerByte = value - (upperByte<<8)
          newResult = (lowerByte<<8) + upperByte 
        bus.write_word_data(address, reg, newResult)
        return 0
        
def read(reg):
        result = bus.read_byte_data(address, reg)
        print "address " + str(hex(reg)) + " = " + str(hex(result))

def read_word(reg):
        result = bus.read_word_data(address, reg)
        # have to switch the endianness
        if (result > 255):
          upperByte = result>>8
          lowerByte = result - (upperByte<<8)
          newResult = (lowerByte<<8) + upperByte
        else:
          upperByte = 0
          lowerByte = result - (upperByte<<8)
          newResult = (lowerByte<<8) + upperByte  
        print "address " + str(hex(reg)) + " = " + str(hex(newResult)) 
     

read_word(0x00)
#write_word(0x7f,9897)   # loads 682 into the 10 bit camera data
#write_word(0x7f,10240)   # test pattern [vertical shades]
#write_word(0x7f,14336)   # test pattern [diagonal shades]
#write_word(0x7f,12288)   # test pattern [horizontal shades]
write_word(0x7,904)  # use exposure pin 920, don't use exposure pin 904
read_word(0x7)
write_word(0x7f,0)      # use actual data 
read_word(0x7f)