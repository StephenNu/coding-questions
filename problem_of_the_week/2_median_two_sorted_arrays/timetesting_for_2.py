import sys #sys gives sys.argv[]
import os 
import re # regex
import time
import math
import subprocess
from pylab import plot, show, savefig, xlabel, ylabel

test_pos_amount = 800
test_neg_amount = 0
test_cases_pos_names = []
test_cases_neg_names = []
test_cases_names = []
test_cases_ans = []
test_cases_n_size_pos = []
test_cases_n_size_neg = []
test_cases_n_size = test_cases_n_size_pos + test_cases_n_size_neg
program_times = []

def get_os_commands(fileName, fileExt):
  if fileExt == ".java":
    return {
      'compile_code'  : "javac " + fileName + fileExt,
      'run_code'      : "java " + fileName + " < "
    }
  elif re.match(r"\.c.*", fileExt):
    return {
      'compile_code'  : "g++ --std=c++11 " + fileName + fileExt,
      'run_code'      : "./a.out < "
    }
  elif fileExt == ".py":
    return {
      'compile_code'  : "echo \"running python code\"",
      'run_code'      : "python " + fileName + fileExt + " < "
    }
  else:
    return {
      'compile_code'  : "echo \"Unknown code format\"",
      'run_code'      : "echo \"\""
    }


def check_system_args():
  valid = False
  fileName = ""
  fileExt = ""

  if len(sys.argv) != 3:
    print("Need a file name, and a test directory")
  else:
    if os.path.isfile(sys.argv[1]):
      fileName, fileExt = os.path.splitext(sys.argv[1])
      fileExt = fileExt.lower()
      valid = True
    else:
      print("Passed in wrong file name")
  return {
    'valid'    : valid,
    'fileName' : fileName,
    'fileExt'  : fileExt
  }



args = check_system_args()
if args['valid']:
  cmds = get_os_commands(args['fileName'], args['fileExt'])

  for i in range(1, test_pos_amount+1):
    test_cases_pos_names.append(sys.argv[2] + "pos/test" + str(i))
  for i in range(1, test_neg_amount+1):
    test_cases_neg_names.append(sys.argv[2] + "neg/test" + str(i))
  
  test_cases_names = test_cases_pos_names + test_cases_neg_names

  for i in range(1, test_pos_amount+1):
      f = open(sys.argv[2] + "pos/answer"+str(i), 'r')
      test_cases_ans.append(f.readline().strip("\n"))
      f.close()

  result = subprocess.check_output(cmds['compile_code'], shell=True)
  for i in range(0,len(test_cases_names)):
    print("\nStarting new testCase: " + str(i+1) + " name " + test_cases_names[i])
    before = time.time()
    result = subprocess.check_output(cmds['run_code'] + test_cases_names[i], shell=True).decode("ascii")[:-1]
    after = time.time()
    total = after - before
    program_times.append(total)
    if result == test_cases_ans[i]:
      print("PASSED")
    else:
      print("FAILED! :" + result + ": vs :" + test_cases_ans[i] + ":")
  xlabel("value of n")
  ylabel("run time in seconds")
  labels = []
  for tests in test_cases_names:
      f = open(tests, 'r')
      m = [int(x) for x in f.readline().split()]
      sums = m[0] + m[1]
      test_cases_n_size.append(sums)
      f.close()
  for i in range(0, len(test_cases_n_size)):
    labels.append((test_cases_n_size[i], program_times[i]))
  labels = sorted(labels, key=lambda x: x[0])
  test_cases_n_size = []
  program_times = []
  test_cases_n_size = [x[0] for x in labels]
  program_times = [x[1] for x in labels]
  plot(test_cases_n_size, program_times)
  savefig("execution_" + args['fileName'] + ".png")
  os.system("firefox \"execution_" + args['fileName'] + ".png\" &")
else:
  print("invalid args")
