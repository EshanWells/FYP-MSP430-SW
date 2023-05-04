import tkinter as tk

niceData = []
integers = []

class logData:
    def __init__(self,number,sec,mins,hour,day,month,year,temp,hum):
        self.number = number
        self.sec = sec
        self.mins = mins
        self.hour = hour
        self.day = day
        self.month = month
        self.year = year
        self.temp = temp
        self.hum = hum
        

def enter():
    text = textbox.get('1.0', 'end-1c')
    lines = text.split('\n')
    list_of_lists = []
    for line in lines:
        hex_pairs = line.split()
        for pair in hex_pairs:
            integers.append(int(pair, 16))
        list_of_lists.append(integers)
    print(list_of_lists)
    

def convert():
    print("Converting")
    for i in integers:
        byteList = integers[i]

        converted = logData(0,0,0,0,0,0,0,0,0)

        converted.number = ((byteList[2] << 8) + byteList[1]) + 1
        
        converted.sec = byteList[3]
        converted.mins = byteList[4]
        converted.hour = byteList[5]
        converted.day = byteList[6]
        converted.month = byteList[7]
        converted.year = byteList[8]

        converted.temp = ((byteList[10] << 8) + byteList[9])/10
        converted.hum = (byteList[11])/2

        niceData.append(converted)
        print(converted.number)






def graph():
    print("Oh boy here I go graphing again...")

def saveCSV():
    print("Oh boy here I go saving again...")



window = tk.Tk()
window.title("Graph and Convert Data")

textbox = tk.Text(window, height=15, width=50)
textbox.pack()

button_enter = tk.Button(window, text="Enter", command=enter)
button_enter.pack(side='left', padx=5, pady=5)

button_convert = tk.Button(window, text="Convert", command=convert)
button_convert.pack(side='left', padx=5, pady=5)

button_graph = tk.Button(window, text="Graph", command=graph)
button_graph.pack(side='left', padx=5, pady=5)

button_save = tk.Button(window, text="Save CSV", command=saveCSV)
button_save.pack(side='left', padx=5, pady=5)

window.mainloop()
