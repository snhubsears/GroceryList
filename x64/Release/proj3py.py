import re
import string
import os.path
from os import path

# Reads grocery list file and outputs list depending on user's choice'
def OpenList(chosenItem):
    # my_list variable holds each item in grocery list
    my_list = []
    # diff_items variable holds each different item from grocery list
    diff_items = []
    # quantity_list variable holds grocery item and quantity purchased
    quantity_list = []
    found = False

    # if file exists, open it
    if (path.exists("proj3input.txt")):
        # opens proj4input.txt as "file" variable
        with open("proj3input.txt") as file:
            # line variable holds read file line, not including newline
            line = file.readline().strip('\n\r')
            # while line isn't empty, add to my_list
            while line != '':
                # add line variable to my_list
                my_list.append(line)
                # if line variable doesn't exist in diff_items, add it to diff_items
                if line not in diff_items:
                    diff_items.append(line)
                # store read file line into line variable again
                line = file.readline().strip('\n\r')
        # for each item in diff_items, increase counter and output item with counter representing quantity purchased
        for i in range(0, len(diff_items)):
            # counter variable holding how many times each item is in my_list
            counter = 0
            # for each variable in my_list, increase counter if matching current diff_items variable
            for j in range(0, len(my_list)):
                # if diff_items variable matches my_list variable, increase counter
                if my_list[j] == diff_items[i]:
                    counter += 1
            # if user selected option 1, output diff_items string with its quantity purchased
            if chosenItem == "":
                print(diff_items[i] + " purchased " + str(counter) + " times.")
                found = True
            # output diff_items string with its quantity purchased if matching user's chosen item
            elif chosenItem == diff_items[i]:
                print(diff_items[i] + " purchased " + str(counter) + " times.")
                found = True
            # if user selected option 3, output current item and quantity to quantity_list
            elif chosenItem == "\n\n":
                quantity_list.append(diff_items[i] + " " + str(counter))
                found = True
            # if end of diff_items and chosenItem hasn't been found, output error
            if i == len(diff_items)-1 and found == False:
                print("Item not found")
    # if user selected option 3
    if chosenItem == "\n\n":
        # create frequency.dat file as "writer" variable overwriting any previous
        with open("frequency.dat", 'w') as writer:
            # for each item in quantity_list, write string to writer file
            for i in range(0, len(quantity_list)):
                writer.write(quantity_list[i])
                # if not final item, output newline
                if i < len(quantity_list) - 1:
                    writer.write("\n")
    return 0