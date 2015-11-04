#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2015 (c) Ewerton Assis
#

import os
import sys

from run import run_binaries


if __name__ == '__main__':
    if ('CI' in os.environ and os.environ['CI'] == 'true'):
        valgrind_wrapper = "valgrind --leak-check=full --error-exitcode={0} -v"
    else:
        valgrind_wrapper = "valgrind --track-origins=yes --leak-check=full --errors-for-leak-kinds=all --show-leak-kinds=all --error-exitcode={0} -v"
    code = run_binaries(valgrind_wrapper.format(os.EX_SOFTWARE))
    sys.exit(code)
