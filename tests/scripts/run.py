#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2015 (c) Ewerton Assis
#

import os
import sys


def run_binaries(wrapper = ''):
    test_root = os.path.realpath(os.path.join(os.path.realpath(__file__), '../../'))
    bin_folder = os.path.join(test_root, 'bin')
    binaries = [f for f in os.listdir(bin_folder) if os.path.isfile(os.path.join(bin_folder, f))]
    codes = 0
    for b in binaries:
        b_path = os.path.join(bin_folder, b)
        command = "{0} {1}".format(wrapper, b_path).strip()
        print("\033[1m{0}\033[0m".format(command))
        codes += os.system(command)
        print
    return codes


if __name__ == '__main__':
    code = run_binaries()
    sys.exit(code)
