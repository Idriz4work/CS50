import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    stores = []
    data = sys.argv[1]
    text = sys.argv[2]
    with open(data) as file:
        reader = csv.DictReader(file)
        for data in reader:
            stores["name"] = stores["name"]
            stores.append(data)

    # TODO: Read DNA sequence file into a variable
    sequences = []
    with open(text) as fil2:
        reader2 = csv.DictReader(fil2)
        for text in reader2:       #AGAT AATG TATC
            sequences["AGAT","AATG","TATC"] = int(sequences["AGAT","AATG","TATC"])
            sequences.append(text)


    # TODO: Find longest match of each STR in DNA sequence
    STR = {} # dictionary
    for subsequence in STR:
       STR[subsequence] = longest_match(sequences, subsequence)



    # TODO: Check database for matching profile
    int(x) #x is the string converted into an interge
    for store in data:
        if store["name"] not in data:
            stores.append(data["name"])

    for name in data:
        print(name)
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
