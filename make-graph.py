#!/usr/bin/env python3
#
# ISC License (ISC)
#
# Copyright (c) 2016, Bernardo Sulzbach (mafagafogigante@gmail.com)
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# Author: Leonardo Ferrazza (leoferrazza@gmail.com)

import sys
import random


def main():
    nodes = int(sys.argv[1])
    edges_per_node = int(sys.argv[2])
    lines = ['(', str(nodes)]
    for i in range(nodes):
        lines.append(make_line(i, nodes, edges_per_node))
    lines.append(')')
    print('\n'.join(lines))


def make_line(index, nodes, edges_per_node):
    integers = [index]
    while len(integers) <= edges_per_node:
        candidate = random.randint(0, nodes - 1)
        if candidate != index:
            integers.append(candidate)
    return '(' + ' '.join(str(x) for x in integers) + ')'

if __name__ == '__main__':
    main()
