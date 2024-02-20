from cs50 import *

def text():
    L = 0.0
    S = 0.0
    letters = 0
    words = 1
    sentences = 0


    text = get_string ("Text: ")

    for char in text:
        if char.isalpha():
            letters += 1

        if char == " ":
            words += 1

        if char in ".!?":
            sentences +=1

    L = float (letters / words * 100)
    S = float (sentences / words * 100)


    grade = round(0.0588 * L - 0.296 * S - 15.8)
    if grade < 1:
        return "Before Grade 1"
    elif grade > 16:
        return "Grade 16+"
    else:
        print("Grade: ", end = "")
        return grade

print (text())
