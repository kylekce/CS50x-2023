# TODO
import re


def main():
    # ask for a line of text
    text = input("Text: ")

    # get the number of letters, words, and sentences
    letters = len(re.findall('[a-zA-Z]', text))
    words = len(text.split())
    sentences = len(re.split('[.!?]', text)) - 1

    # average number of letters and sentences per 100 words
    l = letters / words * 100
    s = sentences / words * 100

    # Coleman-Liau index
    index = 0.0588 * l - 0.296 * s - 15.8

    # print the grade reading level
    if index < 1:
        print("Before Grade 1")
    elif round(index) in range(1, 16):
        print("Grade " + str(round(index)))
    else:
        print("Grade 16+")


main()
