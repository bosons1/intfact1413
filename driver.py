#!/usr/bin/python3

import sys
import subprocess

if __name__ == "__main__":
    num = str(sys.argv[1])
    print(num)
    zero_index = 1
    while True:
        process = subprocess.Popen(["./intfact1", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        print(stdout.decode())
        print(stderr.decode())
        process = subprocess.Popen(["./intfact2", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        print(stdout.decode())
        print(stderr.decode())
        process = subprocess.Popen(["./intfacta", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        print(stdout.decode())
        print(stderr.decode())
        process = subprocess.Popen(["./intfactaa", num, str(zero_index)], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        stdout, stderr = process.communicate()
        print(stdout.decode())
        print(stderr.decode())
        # find symmetry and anti symmetry
        #if symmetry found decode using Riemann zetazero
        zero_index = zero_index + 1
        input("Enter")
