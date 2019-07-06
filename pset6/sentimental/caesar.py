import sys
from cs50 import get_string

def is_int(string):
    try:
        int(string)
        return True
    except ValueError:
        return False

def main():

    #Make sure there's one system argument
    while True:
        if len(sys.argv) != 2:
            sys.exit('1')
        elif is_int(sys.argv[1]) == False:
            sys.exit('1')
        elif int(sys.argv[1]) < 0:
            sys.exit('1')
        else:
            break

    n = sys.argv[1]
    #n %= 26

    text = get_string('plaintext: ')
    ctext = ''

    for i in range(0, len(text)):
        if text[i].isalpha() is True:
            if text[i].isupper() is True:
                aindex = ord(text[i]) - 65
                cindex = (aindex + int(n)) % 26
                ctext += chr(cindex + 65)
            elif text[i].islower() is True:
                aindex = ord(text[i]) - 97
                cindex = (aindex + int(n)) % 26
                ctext += chr(cindex + 97)
            else:
                ctext += text[i]

        else:
            ctext += text[i]

    print ('ciphertext: ' + ctext)



if __name__ == "__main__":
    main()
