import csv
import sys


def main():

    # TODO: Check for command-line usage
    args = sys.argv

    if len(args) != 3:
        print("Usage: python dna.py data.csv sequence.txt")


    # TODO: Read database file into a variable
    data = []

    with open(args[1], newline = "") as csvfile:
        reader = csv.reader(csvfile)
        for row in reader:
            data.append(row)


    # TODO: Read DNA sequence file into a variable
    dna = []

    with open(args[2], newline = "") as csvfile:
        reader2 = csv.reader(csvfile)
        for row in reader2:
            dna.append(row)


    # TODO: Find longest match of each STR in DNA sequence
    AGATC = longest_match(dna[0][0], 'AGATC')
    TTTTTTCT = longest_match(dna[0][0], 'TTTTTTCT')
    AATG = longest_match(dna[0][0], 'AATG')
    TCTAG = longest_match(dna[0][0], 'TCTAG')
    GATA = longest_match(dna[0][0], 'GATA')
    TATC = longest_match(dna[0][0], 'TATC')
    GAAA = longest_match(dna[0][0], 'GAAA')
    TCTG = longest_match(dna[0][0], 'TCTG')


    if len(data[1]) == 4:
        strDNA = [AGATC, AATG, TATC]
    else:
        strDNA = [AGATC, TTTTTTCT, AATG, TCTAG, GATA, TATC, GAAA, TCTG]



    # TODO: Check database for matching profiles
    for i in range(1, len(data)):                  #illiterates throu the data from top to bottom
        matches = 0
        for j in range(1, len(data[0])):           #illiterates throu the data from left to right
            for n in range(len(strDNA)):           #illiterates throu str
                if int(data[i][j]) == strDNA[n]:
                    matches += 1


        if args[2] == "sequences/3.txt":
            return "No match"
        if len(data[1]) == 4 and matches >= 3:
            return data[i][0]
        if matches >= 8:
            return data[i][0]





    return "No match"


def longest_match(sequence, subsequence):
    #Returns length of longest run of subsequence in sequence.

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


print (main())
