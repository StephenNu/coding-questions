import sys #sys gives sys.argv[]
import os 
import re # regex
import time
import math
import subprocess
from pylab import plot, show, savefig, xlabel, ylabel

test_pos_amount = 45
test_neg_amount = 0
test_cases_pos_names = []
test_cases_neg_names = []
test_cases_names = []

test_cases_ans =    [
 0, 1, 1, 2, 3, 5, 8, 13, 21, 34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025,20365011074,32951280099,53316291173,86267571272,139583862445,225851433717,365435296162,591286729879,956722026041,1548008755920,2504730781961,4052739537881,6557470319842,10610209857723,17167680177565,27777890035288,44945570212853,72723460248141,117669030460994,190392490709135,308061521170129,498454011879264,806515533049393,1304969544928657,2111485077978050,3416454622906707,5527939700884757,8944394323791464,14472334024676221,23416728348467685,37889062373143906,61305790721611591,99194853094755497,160500643816367088,259695496911122585,420196140727489673,679891637638612258,1100087778366101931,1779979416004714189,2880067194370816120,4660046610375530309,7540113804746346429,12200160415121876738,19740274219868223167,31940434634990099905,51680708854858323072,83621143489848422977,135301852344706746049,218922995834555169026]
test_cases_n_size = [x for x in range(1, 46)]
program_times = []


if len(sys.argv) == 3:
  for i in range(1, test_pos_amount+1):
    test_cases_pos_names.append(sys.argv[2] + "pos/test" + str(i))
  for i in range(1, test_neg_amount+1):
    test_cases_neg_names.append(sys.argv[2] + "neg/test" + str(i))
  
  test_cases_names = test_cases_pos_names + test_cases_neg_names
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
          print("FAILED! " + result + " vs " + str(test_cases_ans[i]))
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

