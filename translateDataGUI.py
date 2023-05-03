from tkinter import *

def submit_data():
    global data_array
    data = data_entry.get("1.0", END).splitlines()
    data_array = [line.strip() for line in data if line.strip()]

def convert_data_array():
    global data_array
    
    


root = Tk()

data_entry = Text(root)
data_entry.pack()

submit_button = Button(root, text="Submit", command=submit_data)
submit_button.pack()

print_button = Button(root, text="Convert data", command=convert_data_array)
print_button.pack()

data_array = []

root.mainloop()