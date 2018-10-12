#! /usr/bin/env python2
import csv
import matplotlib.pyplot as plt
import argparse
import os

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate comparative plots')
    parser.add_argument('files', metavar='CSVs', nargs='+',
                        help='CSV files of runtimes to plot.')

    args = parser.parse_args()
    for file in args.files:
        with open(file, 'r') as data:
            info = os.path.splitext(file)[0]
            info = info.split('_')
            struct_name = info[0]
            ops = info[2]
            type = info[3]
            reader = csv.reader(data)
            xlabel, ylabel = next(reader)
            plt.xlabel('%s %s (%s)' % (xlabel, ops, type))
            plt.ylabel(ylabel)
            n, et = zip(*reader)
            n = [int(x) for x in n]
            et = [int(y) for y in et]
            plt.plot(n, et, 'o', label=struct_name,)


    plt.legend(loc='upper right')
    plt.show()

