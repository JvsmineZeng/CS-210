import re
import string
import os.path
from os import path


'''
The organizeItemsSold method reads a list of products sold for the day. Each type of item and their respective total sale quantity are then added 
to an itemized list in the format "(Item): (quantity sold)".
'''
def organizeItemsSold():

    salesList = open("items.txt", "r")              # Open items.txt for reading
    salesOrganized = {}                             # Create dictionary to store itemized list 

    print(" ------------------------------")       # Divider
    print("|     TOTAL INVENTORY SOLD     |")      # Header
    print(" ------------------------------\n")     # Divider

    for line in salesList:                          # For each sale in the sales list
        item = line.lower().strip()                 # Retrieve item name, lowercased and stripped
        if item in salesOrganized:                  # If item is in dictionary
            salesOrganized[item] += 1               # Increment quantity sold by 1
        else:                                       # If item is not in dictionary
            salesOrganized[item] = 1                # Set quantity sold to 1

    for key in list (salesOrganized.keys()):        # For each key in the dictionary
        item = key.capitalize().strip()             # Retrieve item name
        quantity = str(salesOrganized[key])         # Retrieve item's quantity sold
        print(item + ": " + quantity)               # Print item and total quantity sold

    print("\n")                                     # Print newline

    salesList.close()                               # Close items.txt file


'''
The findQuantitySold method takes an item search inquiry from the user and finds the total amount of sales of said item for the day.

@param - itemSearched: user input of an item they are requesting to find quantity sold
@return - quantity: amount of searched item sold
'''
def findQuantitySold(itemSearched):

    itemSearched = itemSearched.lower()             # Retrieve item searched, lowercased
    salesList = open("items.txt", "r")              # Open items.txt for reading
    quantity = 0                                    # Set quantity to 0

    for line in salesList:                          # For each sale in the sales list
        item = line.lower().strip()                 # Retrieve item name, lowercased and stripped
        if item == itemSearched:                    # If the item is item searched
            quantity += 1                           # Increment quantity sold by 1

    salesList.close()                               # Close items.txt file
    return quantity                                 # Return total quantity sold


'''
The buildHistogram method creates an itemized data table of products sold for the day, which will be used by Source.cpp to build a histogram. 
Similar to the organizeItemsSold method.
'''
def buildHistogram():

    salesList = open("items.txt", "r")              # Open items.txt for reading
    histogram = open("frequency.dat", "w")          # Open/create frequency.dat for writing
    salesOrganized = {}                             # Create dictionary to store itemized list

    for line in salesList:                          # For each sale in the sales list
        item = line.lower().strip()                 # Retrieve item name, lowercased and stripped
        if item in salesOrganized:                  # If item is in dictionary
            salesOrganized[item] += 1               # Increment quantity sold by 1
        else:                                       # If item is not in dictionary
            salesOrganized[item] = 1                # Set quantity sold to 1

    for key in list (salesOrganized.keys()):                                                # For each key in the dictionary
        histogram.write(str(key.capitalize()) + " " + str(salesOrganized[key]) + "\n")      # Write "(Item) (key)" to frequency.dat file

    salesList.close()       # Close items.txt file
    histogram.close()       # Close frequency.dat file