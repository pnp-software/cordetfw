#-----------------------------------------------------------------------       
# This module holds global variables and constants.
#-----------------------------------------------------------------------       
       
# Dictionary representation of the spec_item table.
# The dictionary key is the database ID. A dictionary entry is a 
# dictionary holding the definition of a spec_item
specItems = {}

# Dictionary of the spec_items indexed with a key given by
# 'domain:name'.
domNameToSpecItem = {}

# Identifier of the CrFw Application in the Cordet FW Project
CrFwAppId = '3'

# The list of requirements
requirements = []

# The list of adaptation points
adaptPoints = []

# Directory where generated tables for Cordet Fw Specs are stored
generatedTablesDir = 'doc/cordetfw'
