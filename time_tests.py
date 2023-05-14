import os
from datetime import datetime


def printProgressBar(iteration, total, prefix='', suffix='', decimals=1, length=100, fill='█', printEnd="\r"):
    """
    Call in a loop to create terminal progress bar
    @params:
        iteration   - Required  : current iteration (Int)
        total       - Required  : total iterations (Int)
        prefix      - Optional  : prefix string (Str)
        suffix      - Optional  : suffix string (Str)
        decimals    - Optional  : positive number of decimals in percent complete (Int)
        length      - Optional  : character length of bar (Int)
        fill        - Optional  : bar fill character (Str)
        printEnd    - Optional  : end character (e.g. "\r", "\r\n") (Str)
    """
    percent = ("{0:." + str(decimals) + "f}").format(100 * (iteration / float(total)))
    filledLength = int(length * iteration // total)
    bar = fill * filledLength + '-' * (length - filledLength)
    print(f'\r{prefix} |{bar}| {percent}% {suffix}', end=printEnd)
    # Print New Line on Complete
    if iteration == total:
        print()


os.system('g++ all.cpp')
tests = 9
n = 5
res = [0] * tests

count = 0
printProgressBar(0, tests * n, prefix='Progress:', suffix='Complete', length=50)
for i in range(1, tests + 1):
    sum = 0
    for j in range(n):
        count += 1
        printProgressBar(count, tests * n, prefix='Progress:', suffix='Complete', length=50)
        start_time = datetime.now()
        os.system(f'./a.out < test{i}.txt >> output.txt')
        end_time = datetime.now()
        delta = end_time - start_time
        sum += delta.seconds
        os.system('rm output.txt')
    res[i - 1] = sum / n

print(res)
