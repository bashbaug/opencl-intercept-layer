# Copyright (c) 2019 Intel Corporation
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import fnmatch
import subprocess
import sys

def CompileCLToSPV(commandToRun, clFileName, spvFileName, logFileName, optionsFileName = ''):
    options = ''
    if os.path.isfile(optionsFileName):
        optionsFile = open(optionsFileName)
        options = optionsFile.readline()
        optionsFile.close()

    print('Compiling ' + clFileName)
    #print(commandToRun.split() + options.split() + [clFileName, '-o', spvFileName])

    logFile = open(logFileName, 'w')
    returncode = subprocess.call(commandToRun.split() + options.split() + [clFileName, '-o', spvFileName], stderr=logFile, stdout=logFile)
    logFile.close()

    return returncode

printHelp = False

if len(sys.argv) > 1:
    clSourceDir = sys.argv[1]
else:
    printHelp = True

if len(sys.argv) > 2:
    commandToRun = sys.argv[2]
else:
    commandToRun = 'clspv'

if ( len(sys.argv) == 2 ) and ( sys.argv[1] == '-h' or sys.argv[1] == '-?' ):
    printHelp = True

if printHelp:
    print('usage: disassemble_all.py {required: directory with .cl files} {optional: command to run, default: "clspv"}')
elif not os.path.exists(clSourceDir):
    print('error: directory ' + clSourceDir + ' does not exist!')
else:
    print('Running "' + commandToRun + '" to compile all .cl files in: ' + clSourceDir + ':')

    numberOfFiles = 0
    compileSuccess = 0

    for file in os.listdir(clSourceDir):
        if file.endswith(".cl"):
            numberOfFiles = numberOfFiles + 1
            clFileName  = clSourceDir + '/' + file
            spvFileName = clSourceDir + '/' + file[:-3] + '.spv' # strip .cl, add .spv
            logFileName = clSourceDir + '/' + file[:-3] + '.log' # strip .cl, add .log

            found = False
            optsPattern = file[:-10] + '*_options.txt' # strip _source.cl, add options pattern
            for options in os.listdir(clSourceDir):
                if fnmatch.fnmatch(options, optsPattern):
                    found = True
                    optionsFileName = clSourceDir + '/' + options
                    returncode = CompileCLToSPV(commandToRun, clFileName, spvFileName, logFileName, optionsFileName)
                    if returncode==0:
                        compileSuccess = compileSuccess + 1

            if found==False:
                returncode = CompileCLToSPV(commandToRun, clFileName, spvFileName, logFileName)
                if returncode==0:
                    compileSuccess = compileSuccess + 1

    print('Found ' + str(numberOfFiles) + ' file(s) to compile.')
    print('Compiled ' + str(compileSuccess) + ' file(s) successfully.')
