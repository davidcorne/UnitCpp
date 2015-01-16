#!/usr/bin/env python
# Written by: DGC
# -*- coding: utf-8

# python imports
import os
import re
import sys

# local imports

HEADERS = dict()

#==============================================================================
class Header(object):

    def __init__(self, name):
        self.name = name
        self.dependencies = self.find_dependencies()
        self.dependents = list()

    def find_dependencies(self):
        with open(self.name, "r") as header_file:
            lines = header_file.readlines()
        dependencies = list()
        for line in lines:
            if line.find("#include <UnitCpp/") != -1:
                line = line.replace("#include <", "").replace(">", "").strip()
                dependencies.append(line)
        return dependencies

    def __repr__(self):
        return self.name + ": " + str(self.dependencies) + " : " + str(self.dependents)
    
#==============================================================================
def resolve_includes(parsed, header):
    """
    This will be called recursivly. It will resolve includes from the file
    header and return a string containing the whole file.
    """
    if header not in parsed:
        parsed.append(header)
        with open(header, "r") as header_file:
            lines = header_file.readlines()
        content = []
        for line in lines:
            if line.find("#include <UnitCpp/") != -1:
                include = line.replace("#include <", "").replace(">", "").strip()
                content.append(resolve_includes(parsed, include))
            else:
                # keep function comments (indednted by 2)
                if line[0:2] != "//":
                    content.append(line)
        return "".join(content)
    return ""
    

#==============================================================================
def create_single_header(header):
    """
    This returns a string with the contents of header, but with the includes
    resolved.
    """
    parsed = list()
    return resolve_includes(parsed, header)
            
#==============================================================================
def  parse_deps(directory):
    for dpath, dnames, file_names in os.walk(directory):
        for file_name in file_names:
            path = os.path.join(dpath, file_name)
            if path not in HEADERS:
                header = Header(path);
                HEADERS[header.name] = header
    for header in HEADERS.values():
        for dep in header.dependencies:
            HEADERS[dep].dependents.append(header.name)
    for header in HEADERS.values():
        if not header.dependents:
            # header has no dependencies, it's a root node
            print create_single_header(header.name)
            
#==============================================================================
if (__name__ == "__main__"):
    os.chdir(os.path.join(os.path.dirname(sys.argv[0]), os.path.pardir))
    parse_deps("UnitCpp")
