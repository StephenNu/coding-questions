import sys #sys gives sys.argv[]
import os 
import re # regex
import time
import math
import subprocess
from pylab import plot, show, savefig, xlabel, ylabel

test_pos_amount = 7
test_neg_amount = 6
test_cases_pos_names = []
test_cases_neg_names = []
test_cases_names = []
test_cases_ans = []
test_cases_n_size = [14,14,12,12,15,18,60,14,17,8,19,19,3]
program_times = []

if len(sys.argv) == 3:
  for i in range(1, test_pos_amount+1):
    test_cases_pos_names.append(sys.argv[2] + "pos/test" + str(i))
  for i in range(1, test_neg_amount+1):
    test_cases_neg_names.append(sys.argv[2] + "neg/test" + str(i))
  
  test_cases_names = test_cases_pos_names + test_cases_neg_names
  for i in range(0, test_pos_amount):
    test_cases_ans.append("1")
  for i in range(0, test_neg_amount):
    test_cases_ans.append("0")
  if os.path.isfile(sys.argv[1]):
    fileName, fileExt = os.path.splitext(sys.argv[1])
    fileExt = fileExt.lower()
    if fileExt == ".java":
      result = subprocess.check_output(("javac " + sys.argv[1]), shell=True)
      for i in range(0,len(test_cases)):
        print("\nStarting new testCase: " + str(i+1) + " name " + test_cases_names[i])
        before = time.time()
        result = subprocess.check_output(("java " + fileName + " < " + test_cases_names[i]), shell=True).decode("ascii")[:-1]
        if result == test_cases_ans[i]:
          print("PASSED")
        else:
          print("FAILED! " + result + " vs " + test_cases_ans[i])
        after = time.time()
        total = after - before
        print("Program length of " + str(test_cases[i][1]) + " took " + str(total) + " seconds")
        n = test_cases[i][1]
    elif re.match(r"\.c.*", fileExt):
      result = subprocess.check_output(("g++ --std=c++11 " + sys.argv[1]), shell=True)
      for i in range(0,len(test_cases_names)):
        print("\nStarting new testCase: " + str(i+1) + " name " + test_cases_names[i])
        before = time.time()
        result = subprocess.check_output(("./a.out < " + test_cases_names[i]), shell=True).decode("ascii")[:-1]
        if result == test_cases_ans[i]:
          print("PASSED")
        else:
          print("FAILED! " + result + " vs " + test_cases_ans[i])
        after = time.time()
        total = after - before
        program_times.append(total)
    else:
      print("Need a valid file type")
    xlabel("value of n")
    ylabel("run time in seconds")
    labels = []
    for i in range(0, len(test_cases_n_size)):
        labels.append((test_cases_n_size[i], program_times[i]))
    labels = sorted(labels, key=lambda x: x[0])
    test_cases_n_size = []
    program_times = []
    test_cases_n_size = [x[0] for x in labels]
    program_times = [x[1] for x in labels]
    plot(test_cases_n_size, program_times)
    savefig(fileName + "_execution" + ".png")
    os.system("firefox \"" + fileName + "_execution" + ".png\" &")
  else:
    print("Passed in wrong file name")
else:
  print("Need a file name, and a test directory")

