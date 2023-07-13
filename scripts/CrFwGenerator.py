__author__ = 'Alessandro Pasetti, P&P software GmbH'

#===============================================================================
# Script to generate artefacts used in the preparation of the data package
# of the Cordet Framework.
# The input to the code generator is the project export file of the 
# Cordet Framework.
#
# This script should be run from the top level directory of the Cordet FW Project 
# (e.g. from: /home/ap/Projects/cordetf/) with a command like:
#
#   python3 ./scripts/CrFwGenerator.py ~/Downloads/cordetfw_editor_CordetFw.zip
#
# The argument of the script is the project export file of the Cordet FW Project
# inside the Cordet Editor.
#
# The configuration information for the script is defined in module config.py.
# This configuration information includes in particular the location of the 
# directories where the generated products are created.
# 
# @copyright P&P Software GmbH, All Rights Reserved
#
#===============================================================================

import sys
import os
import argparse
import shutil
import csv
import pdb
import json
import operator
import re
import copy
import zipfile

from Config import specItems, generatedTablesDir, requirements, adaptPoints, \
                   domNameToSpecItem, CrFwAppId
from Format import convertEditToLatex



#===============================================================================
# Create table with all adaptation points
def generateCrFwAPs():
    with open(generatedTablesDir+'/CrFwAdaptPoint.csv', 'w') as fd:
        fd.write('Domain|Name|Title|Implementation|DefaultValue|Kind|Remarks\n')
        adaptPointsSorted = sorted(adaptPoints, key=lambda d: d['domain']+d['name'])
        for ap in adaptPointsSorted:
            if ap['application'] != CrFwAppId:
                continue
            apDomain = ap['domain']
            if apDomain.startswith('AP-'):
                apDomain = apDomain[3:]
            apName = ap['name']

            fd.write(apDomain + '|' +
                     apName + '|' +
                     convertEditToLatex(ap['title']) + '|' +
                     convertEditToLatex(ap['implementation']) + '|' +
                     convertEditToLatex(ap['value']) + '|' +
                     convertEditToLatex(ap['p_kind']) + '|' +
                     convertEditToLatex(ap['remarks']) + '\n')


#===============================================================================
# Create table with the requirements
def generateCrFwReqs():
    with open(generatedTablesDir+'/CrFwRequirement.csv', 'w') as fd:
        fd.write('Domain|Name|Kind|Text|Implementation|Verification|Remarks\n')
        reqsSorted = sorted(requirements, key=lambda d: d['domain']+d['name'])
        for req in reqsSorted:
            if req['application'] != CrFwAppId:
                continue
            reqDomain = req['domain']
            reqName = req['name']
            if req['p_kind'] == 'CNS':
                reqKind = 'C'
            elif req['p_kind'] == 'STD':
                reqKind = 'S'
            elif req['p_kind'] == 'PRP':
                reqKind = 'P'
            elif req['p_kind'] == 'AP':
                reqKind = 'A'
            else:
                reqKind = '??'

            fd.write(reqDomain + '|' +
                     reqName + '|' +
                     reqKind + '|' +
                     convertEditToLatex(req['value']) + '|' +
                     convertEditToLatex(req['implementation']) + '|' +
                     convertEditToLatex(req['t1']) + '|' +
                     convertEditToLatex(req['remarks']) + '\n')


#===============================================================================
# Delete the tmp directory if it exists; otherwise create it.
# Expand the Cordet FW Project file in the tmp directory,
# read the configuration file and initialize the global variables,
# and then generate all products
def procCordetFw(cordetFwPrFile):
    if os.path.isdir('tmp'):
        shutil.rmtree('tmp')
    os.makedirs('tmp')
        
    try:    
        with zipfile.ZipFile(cordetFwPrFile, 'r') as fd:
            fd.extractall('tmp')    
    except Exception as e:
        print('ERROR: Failure to uncompress Cordet FW Project file '+cordetFwPrFile)
        print('       '+repr(e))
        return
        
    with open('tmp/spec_items.csv') as fd:
        fdDict = csv.DictReader(fd)
        for row in fdDict:
            if not row['status'] in ('NEW', 'CNF', 'MOD'):
                continue
            specItems[row['id']] = row
            if row['cat'] == 'Requirement':
                requirements.append(row)
            if row['cat'] == 'AdaptPoint':
                adaptPoints.append(row)
            domNameToSpecItem[row['domain']+':'+row['name']] = row
       
    # Build tables required for the Cordet FW Documents
    generateCrFwReqs()
    generateCrFwAPs()
    
        
#===============================================================================
## Dummy main to be used to test the functions defined in this module.
if __name__ == "__main__":
    if (len(sys.argv) == 1):
        cordetFwPrFile = '/home/ap/Downloads/cordetfw_editor_CordetFw.zip'
        if not os.path.isfile(cordetFwPrFile):
            print('ERROR: this file is missing: '+cordetFwPrFile)
            exit()
    elif (len(sys.argv) == 2):
        cordetFwPrFile = sys.argv[1]
        if not os.path.isfile(cordetFwPrFile):
            print('ERROR: first argument is not a file'+cordetFwPrFile)
            exit()
    else:
        print("Usage: python3 CrFwGenerator CordetFwPrFile")

    procCordetFw(cordetFwPrFile)
