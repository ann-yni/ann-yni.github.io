# TODO
from cs50 import get_string
# ask user to input text passage
text = get_string("Text: ")
length = len(text)
letters = 0
words = 1
sentences = 0
# find variables for Coleman-Liau equation (number of letters, words, sentences)
for i in range(length):
    if text[i].isalpha():
        letters = letters + 1
    elif text[i] == " ":
        words = words + 1
    elif text[i] == "!" or text[i] == "." or text[i] == "?":
        sentences = sentences + 1
L = 100 * (letters / words)
S = 100 * (sentences / words)
# calculate Coleman-Liau grade-level
grade = round(0.0588 * L - 0.296 * S - 15.8)
# print result
if grade > 15:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade " + str(grade))