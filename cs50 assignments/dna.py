#16th Assignment. dna.py utilized a dictionary to read a DNA sequence and compare against given DNA sets to identify a match. For specifications: https://cs50.harvard.edu/x/2022/psets/6/dna/

import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error: Invalid number of command line arguments.")
        exit
    # TODO: Read database file into a variable
    people = []
    keys = []
    with open(sys.argv[1], "r") as file:
        csv_reader = csv.DictReader(file)
        # save csv file contents in list as dictionary
        for row in csv_reader:
            people.append(row)
        # save list of keys in memory
        for key in row:
            keys.append(key)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as file2:
        dna_reader = file2.read()

    # TODO: Find longest match of each STR in DNA sequence
    # doe as in unidentified individual
    doe = []
    for i in range(1, len(keys)):
        # utilize list of keys minus names
        STR = keys[i]
        doe.append(longest_match(dna_reader, STR))
    # remove names from list of keys so we can use keys length in comparing for matching profiles
    del keys[0]

    # TODO: Check database for matching profiles
    match = "No match"
    for i in range(len(people)):
        count = 0
        for j in range(len(keys)):
            # if all STRs match, print the corresponding name
            if int(people[i][keys[j]]) == doe[j]:
                count = count + 1
                if count == len(keys):
                    match = people[i]["name"]
    print(match)
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

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


main()
