#!/bin/python

import os
from subprocess import call

projectName = "./cs475-project1"

def CleanBuild():
    # Delete old build
    call(["rm", "-r", "-f", "build"])
    call(["mkdir", "build"])

def StartBuild():
    #CMake a new build
    os.chdir("build")
    call(["cmake", ".."])
    call(["make"])

def RunBuild():
    #Run a build for testing
    call([projectName])

CleanBuild()
StartBuild()
RunBuild()