"""
This is the other side of the "Send.ino" script.

Asks for data from the microcontroller, cleans it up, and sends it to a file.
To get this working on your device, you may need to change the port. I use COM7,
but yours may be different.

Double-check the command and baud rate.
They MUST match the script on the microcontroller, or it will not work.
"""

import serial


# The program will send this command  over the connected Serial port to ask for data.
# Double check that this matches the command in the "Send.ino" script.
command = b'please'


def get_data(port='COM7', baud=115200):
    """Gets data from the serial port. You may need to change the port and baud."""
    raw = []

    # Opens the serial prot and asks for data.
    with serial.Serial(port, baud, timeout=1) as ser:
        # Writes the command, so the microcontroller sends data.
        ser.write(command)
        while True:
            # Read one line at a time.
            line = ser.readline()
            # Add the lines to an array, so it can use them later.
            raw.append(line)
            # If there is nothing to read, it exits.
            if line == b'':
                break

    return raw


def clean_data(raw):
    """Converts the data from raw binary to ASCII.
        Gets rid of newlines, carriage returns, the works.
        For GPS data it takes out the annoying N and Ws. """
    clean = []

    for line in raw:
        line = line.decode('ascii')
        line = line.replace('N', '')
        line = line.replace('W', '')
        line = line.strip()
        line = line.strip('\r\n')
        clean.append(line)

    return clean


def create_file(raw, file_path):
    """Makes a CSV file at the specified path."""
    raw = clean_data(raw)

    # Creates a file at the specified path.
    with open(file_path, 'w') as file:
        # For each line in the raw data it writes it into the file.
        for line in raw:
            file.write(f'{line}\n')


def main():
    # Actually procure data.
    # You can set the port and baud from here.
    # Leaving this without parameters calls get_data(port='COM7', baud=115200)
    raw = get_data()
    # Writes it to a file.
    create_file(raw, 'file1.csv')


if __name__ == '__main__':
    main()
