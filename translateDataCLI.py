while 1:

    hex_input = input("Enter 1 log entry, 16 bytes total (no spaces): ")
    byte_list = [hex_input[i:i+2] for i in range(0, len(hex_input), 2)]

    # Ensure that exactly 16 bytes are entered
    if len(byte_list) != 16:
        print("Error: Please enter exactly 16 bytes of data.")
    else:
        # Convert the hexadecimal bytes to integers and store as a byte array
        byteArray = bytearray([int(byte, 16) for byte in byte_list])

        identifier       = byteArray[0]

        entryNumberLow   = byteArray[1]
        entryNumberHigh  = byteArray[2]
        
        sec              = byteArray[3]
        mins             = byteArray[4]
        hour             = byteArray[5]
        day              = byteArray[6]
        month            = byteArray[7]
        year             = byteArray[8]

        tempLow          = byteArray[9]
        tempHigh         = byteArray[10]
        relHum           = byteArray[11]

        ambientLightLow  = byteArray[12]
        ambientLightHigh = byteArray[13]

        nextNodeLow      = byteArray[14]
        nextNodehigh     = byteArray[15]

        
        
        entryNumber = ((entryNumberHigh << 8) + entryNumberLow) + 1

        temp = ((tempHigh << 8) + tempLow)/10
        humidity = relHum/2

        degree_sign = u'\N{DEGREE SIGN}'

        entryString = "Entry Number: " + str(entryNumber)
        timeString = (str(hour) + ":" + str(mins) + ":" + str(sec) + " " + str(day) + "/" + str(month) + "/" + str(year))
        tempString = "\nTemperature: " + str(temp) + degree_sign + "C"
        humString = "\nHumidity: " + str(humidity) + "%"
        
        coolString = entryString + timeString + tempString + humString

        print(coolString)

