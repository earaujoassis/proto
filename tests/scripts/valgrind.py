#!/usr/bin/env python
# -*- coding: utf-8 -*-
# Copyright 2015 (c) Ewerton Assis
#

import os
import sys

from run import run_binaries


if __name__ == '__main__':
    code = run_binaries("valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --error-exitcode={0} -v".format(os.EX_SOFTWARE))
    sys.exit(code)
