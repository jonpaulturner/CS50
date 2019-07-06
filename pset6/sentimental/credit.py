from cs50 import get_string

sum1 = 0
sum2 = 0
while True:
    ccnum = get_string("Number: ")
    if ccnum.isdigit() == True and len(ccnum) > 0:
        break

#digit = 0

#ccnumrev = ccnum[::-1]

index = len (ccnum) - 1

while index >= 0:
    #check last digit, and every other digit going back
    dig1 = float(ccnum[index])
    sum1 += dig1
    index -= 1

    if index < 0:
        break
    else:
        dig2 = float(ccnum[index])
        dig2 *= 2
        if dig2 < 10:
            sum2 += dig2

        else:
            sum2 += 1 + (dig2-10)
        index -= 1

#Check if the sums of the individual digit sums end in zero
if (sum1 + sum2) % 10 == 0 and ccnum.isdigit() == True:
    #if len(ccnum) == 15 and ccnum[:2] == '24' or ccnum[:2] == '37':
    if len(ccnum) == 15 and (ccnum[:2] == '24' or '27'):
        print('AMEX')
    elif (len(ccnum) == 13 or 16) and ccnum[:1] == '4':
        print('VISA')
    elif (len(ccnum) == 16) and (ccnum[:2] == '52' or '52'or '53' or '54' or '55'):
        print('MASTERCARD')
    else:
        print('INVALID')
else:
    print('INVALID')




