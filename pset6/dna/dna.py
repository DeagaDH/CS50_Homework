# Match a given DNA sequence to a person from a database

import csv
import sys
import re
def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    #Initialize dictionary of empty lists
    dna_list = []

    # Save data from the csv file into a list of dictionaries
    with open(sys.argv[1], 'r') as csv_file:
        lines = csv.DictReader(csv_file)

        # Append to teams list
        for line in lines:
            #Convert values from keys other than name into ints
            key_list = list(line.keys())

            for key in key_list:
                if key!='name':
                    line[key]=int(line[key])

            #Append to dna_list
            dna_list.append(line)


    # Save data from txt file into a variable (string)
    with open(sys.argv[2],'r') as dna_file:
        sequence = ''.join(dna_file.readlines())

    #Get substrings corresponding to the DNA samples to check
    samples = list(dna_list[0].keys())
    samples.remove('name') #Name is not a sample to check!

    #Get the count of each sample saved into a count_dict
    count_dict = {}

    #Check for matches for each substring
    for substring in samples:
        #Solution to find largest substring adapted from https://stackoverflow.com/a/61131908/15140545
        #Using regular expressions

        #Get a group with all the consecutive repeats of 'substring' in sequence
        groups = re.findall(r'(?:'+substring+')+', sequence)

        #Find largest value
        try:
            #Get the largest repeat. Here, it its a string (ie, if AGTA repeats 4 times, largest = AGTAAGTAAGTAAGTA here)
            largest = max(groups, key=len)

            #Convert to number of times the substring repeats itself
            largest = len(largest)/len(substring)

        except ValueError:
            largest = 0 #For cases with no matches whatsoever

        #Add entry to count_dict
        count_dict[substring] = largest

    #Iterate through all entries in dna_list looking for a match
    for person in dna_list:

        #Iterate through all samples
        for substring in samples:

            #Check for a match
            if (count_dict[substring] == person[substring]):
                match = True

            else:
                match = False
                break #Break out of here on first mismatch; not  a match!

        #Check for a match
        if match:
            print(person['name'])
            return

    #If a match isn't found, print no match and exit
    print('No match')
    return


main()


