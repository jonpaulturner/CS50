from cs50 import get_int

def main():

#Prompt the user for a value and check if it is positive
    while True:
        height = get_int("Height? ")
        if height >= 0 and height <= 23:
           break

    for i in range(1,height+1):
        print(" "*(height-(i)),end="")
        print("#"*i,end="")
        print("  ",end="")
        print("#"*i)

if __name__ == "__main__":
    main()