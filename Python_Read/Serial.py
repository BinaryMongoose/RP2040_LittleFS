import serial


def get_data(port='COM7', baud=115200):
    raw = []

    with serial.Serial(port, baud, timeout=1) as ser:
        ser.write(b'hello')
        while True:
            line = ser.readline()
            raw.append(line)
            if line == b'':
                break

    return raw


def read_port(port='COM7', baud=115200):
    with serial.Serial(port, baud, timeout=1) as ser:
        line = ser.readline()


def clean_data(raw):
    clean = []

    for line in raw:
        line = line.decode('ascii')
        line = line.replace('N', '')
        line = line.replace('W', '')
        line = line.strip()
        line = line.strip('\r\n')
        clean.append(line)

    return clean


def create_file(raw, file_name):
    raw = clean_data(raw)

    with open(file_name, 'w') as file:
        for line in raw:
            file.write(f'{line}\n')


def main():
    raw = get_data()
    create_file(raw, 'file1.csv')


if __name__ == '__main__':
    main()
