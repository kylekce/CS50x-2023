# TODO
from cs50 import get_int

# Prompt user for height
while True:
    height = get_int("Height: ")
    if (height >= 1 and height <= 8):
        break

# Print pyramid
for i in range(height):
    for j in range(2):
        if j == 0:
            if i != height - 1:
                print(" " * (height - i - 1), end="")
            print("#" * (i + 1), end=" " * 2)
        else:
            print("#" * (i + 1), end="")
    print()
