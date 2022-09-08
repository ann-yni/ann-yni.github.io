#13th Assignment. mario.py is a reimplementation of mario.c in python.

# TODO
from cs50 import get_int


def main():

    # prompt user for height and reprompt if value is not 1-8
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    # call function to draw hashes
    draw(height, height)


def draw(n, h):

    # stop loop if n = 0
    if n <= 0:
        return

    # recursively draw hashes starting from 1
    draw(n - 1, h)

    # draw left-side spaces
    for i in range(h - n):
        print(" ", end="")

    # draw left-side hashes
    for i in range(n):
        print("#", end="")

    # draw center spaces
    print("  ", end="")

    # draw right-side hashes
    for i in range(n):
        print("#", end="")

    # start a new line with each loop
    print("")


# run main function
main()
