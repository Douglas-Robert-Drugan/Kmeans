#!/usr/bin/env python

# Python script for Kmeans Clustering 

import csv
import os

def init_Program(filename, x, y, numLines, xCol, yCol):
    cmd = "make"
    os.system(cmd)
    cmd = "./kmeansclustering " + filename + " " + x + " " + y + " " + str(numLines) + " " + str(xCol) + " " + str(yCol)
    os.system(cmd)

    
def parse(filename, x, y, xCol, yCol):
    f = open(filename, "rU")
    reader = csv.reader(f)
    rc = sum(1 for each in reader)
    f.seek(0)   #reposition
    #subtract header
    rc = rc - 1
    #df = pd.Series(d).to_frame('rows')
    #cmd = "wc -l <" + filename
    #numLines = int(os.popen(cmd).read()[:-1])
    print rc    #commented out wc -l... huge performance hit but now works with universal line endings
    init_Program(filename, x, y, rc, xCol, yCol)
    
    
def user_params():
    inpFlag = False
    while inpFlag == False:
        inpFlag = True
        filename = raw_input("Enter the name of file to be analyzed: ")
        try:
            f = open(filename, "r")
        except IOError:
            inpFlag = False
            print "Error File does not exist"
    inpFlag = [False, False]
    while inpFlag[0] == False and inpFlag[1] == False:
        x = raw_input("Input X field: ")
        y = raw_input ("Input Y field: ")
        f = open(filename, "rU")
        reader = csv.reader(f)
        headers = reader.next()
        count = 0
        for i in headers:
            if x == i:
                xCol = count
                inpFlag[0] = True
            if y == i:
                inpFlag[1] = True
                yCol = count
            count=count+1
        if inpFlag[0] == False or inpFlag[1] == False:
            inpFlag[0] = False 
            inpFlag[1] = False
            print "error, one of the specified fields does not exist"
    print xCol      # to get x Col to save
    print yCol      # to get y Col to save
    parse(filename, x, y, xCol, yCol)

    
user_params()