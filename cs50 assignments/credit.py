#14th Assignment. credit.py is a reimplementation of credit.c in python.

# TODO
from cs50 import get_string

# ask user for a credit card number
card = get_string("Number: ")
length = len(card)
luhns = 0
# calculate luhn's number starting from the second to last digit
for i in range(length):
    if i % 2 == 0:
        luhns = luhns + int(card[length - 1 - i])
    else:
        if int(card[length - 1 - i]) * 2 > 9:
            luhns = luhns + 1 + ((int(card[length - 1 - i]) % 10) * 2)
        else:
            luhns = luhns + (int(card[length - 1 - i]) * 2)
# if luhn's number does not end in 0, the card is invalid
if luhns % 10 == 0:
    # check which card brand or if invalid
    if length == 15 and int(card[0]) == 3 and (int(card[1]) == 4 or int(card[1]) == 7):
        print("AMEX")
    elif length == 16 and int(card[0]) == 5 and (int(card[1]) > 0 and int(card[1]) < 6):
        print("MASTERCARD")
    elif int(card[0]) == 4 and (length == 13 or length == 16):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")
