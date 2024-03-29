#!/bin/bash
# This script creates a release package for the C2 Implementation of the CORDET FW.
# The data package is created in directory ./zip. This directory in particular
# holds the delivery file as a single zip file. 
#
# Prior to running this script, you should check out the following projects
# from their repositories:
# - The FW Profile Project
# - The CORDET Framework Project
#
# This script performs the following actions:
# 1. Deleted 
# 2. Deleted 
# 3. Generates PDF documentation from the Latex sources
# 4. Deleted
# 5. Generates the doxygen documentation
# 6. Run the release acceptance tests 
# 7. Creates the delivery file
#
# Example of command to execute script: ./Release.sh -v=1.1.0 -f=./lib/fwprofile -c=.
#
#====================================================================================

read -p "Only continue if Cordet Editor Project has been exported to Download directory"
read -p "Only continue if all FW Profile diagrams have been exported"

showHelp() {
    echo "Options: "
    echo "-v=, --version=        release version number"
    echo "-f=, --fwprofile=      path to the fwprofile repository"
    echo "-c=, --cordet=         path to the cordetfw repository, defaults to current directory"
    echo "-h, --help             this help text"
    exit 0
}

# Parsing of command line parameters
for i in "$@"
do
case $i in
    -v=*|--version=*)
    VERSION=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    ;;
    -c=*|--cordet=*)
    CF_PATH=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    ;;
    -f=*|--fwprofile=*)
    FW_PATH=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
    ;;
    -h|--help)
    showHelp
    ;;
esac
done

if [ "$VERSION" == "" ]
  then
    showHelp
fi
if [ "$FW_PATH" == "" ]
then
    showHelp
fi
if [ "$CF_PATH" == "" ]
then
    CF_PATH="."
fi

export CC=gcc

OUT="./zip"
OUT_DOCS="${OUT}/docs/"
OUT_LOG="${OUT}/log/"
OUT_SRC="${OUT}/src/"
OUT_LIB="${OUT}/lib/fwprofile/src/"

make clean
rm -fr $OUT
mkdir -p $OUT
mkdir -p $OUT/tests
mkdir -p $OUT_DOCS
mkdir -p $OUT_LOG
mkdir -p $OUT_SRC
mkdir -p $OUT_LIB

CF_DOC="${CF_PATH}/doc"
CF_SRC="${CF_PATH}/src"
DOXYFILE="C2Impl_TestSuite.doxyfile"

# ====================================================================================
echo "Process Cordet Editor Project File"
python3 ${CF_PATH}/scripts/CrFwGenerator.py

# ====================================================================================
echo "PDF Generation - User Manual"
(cd ${CF_DOC}/um &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error UserManual.tex > latex_user_manual.log &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error UserManual.tex > latex_user_manual.log)
cp ${CF_DOC}/um/UserManual.pdf ${OUT_DOCS}
#cp ${CF_DOC}/um/latex_user_manual.log ${OUT_LOG}

echo "PDF Generation - CORDET FW Definition"
(cd ${CF_DOC}/cordetfw &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error cordetfw.tex > latex_cordetfw.log &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error cordetfw.tex > latex_cordetfw.log)
cp ${CF_DOC}/cordetfw/cordetfw.pdf ${OUT_DOCS}
#cp ${CF_DOC}/cordetfw/latex_cordetfw.log ${OUT_LOG}

echo "PDF Generation - User Requirements"
(cd ${CF_DOC}/req &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error UserRequirements.tex > latex_req.log &&
 pdflatex -shell-escape -interaction=nonstopmode -halt-on-error UserRequirements.tex > latex_req.log)
cp ${CF_DOC}/req/UserRequirements.pdf ${OUT_DOCS}
#cp ${CF_DOC}/req/latex_req.log ${OUT_LOG}

# ====================================================================================
echo "Create Doxygen Documentation"
set -x
(cd ${CF_DOC}/doxygen &&
	doxygen $DOXYFILE > doxygen_generation.log 2>&1)
cp -ar ${CF_DOC}/doxygen/html ${OUT_DOCS}/doxygen
cp -ar ${CF_DOC}/doxygen/doxygen_generation.log ${OUT_LOG}/doxygen_generation.log
set +x
# ====================================================================================
# Redirect both stdout and stderr to the AcceptanceTestReport.log file
echo "Run Release Acceptance Tests"
(make clean;
 make test > make_testsuite.log 2>&1 && make run-test > make_run_testsuite.log 2>&1)
 mv make_testsuite.log ${OUT_LOG}/make_testsuite.log
 mv make_run_testsuite.log ${OUT_LOG}/make_run_testsuite.log

gcov -b -o ./bin/src/BaseCmp CrFwBaseCmp >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/BaseCmp CrFwDummyExecProc >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/BaseCmp CrFwInitProc >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/BaseCmp CrFwResetProc >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InCmd CrFwInCmd >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InFactory CrFwInFactory >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InManager CrFwInManager >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InLoader CrFwInLoader >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InRegistry CrFwInRegistry >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InRep CrFwInRep >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/InStream CrFwInStream >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutCmp CrFwOutCmp >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutFactory CrFwOutFactory >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutLoader CrFwOutLoader >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutManager CrFwOutManager >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutRegistry CrFwOutRegistry >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/OutStream CrFwOutStream >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/Pckt CrFwPcktQueue >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/UtilityFunctions CrFwUtilityFunctions >> ${OUT_LOG}/CodeCoverage_Report.txt
gcov -b -o ./bin/src/AppStartUp CrFwAppSm >> ${OUT_LOG}/CodeCoverage_Report.txt

echo "Running valgrind..."
valgrind --leak-check=yes ./bin/testsuite > ${OUT_LOG}/TestSuite_Valgrind_Report.txt 2>&1

#echo "===================================================================================="
echo "Extract the non-covered parts of the C2 Implementation code"
#echo "===================================================================================="
egrep -B 9 "####| 0%" *.c.gcov >> ${OUT_LOG}/CodeCoverage_Report.txt 2>&1
 
# ====================================================================================
echo "Create Release Package"
echo ""
cp -a ${CF_DOC}/commercial/README ${OUT}
cp -a ${CF_DOC}/commercial/COPYING ${OUT}
cp -a ${CF_PATH}/Makefile ${OUT}
cp -ar ${CF_PATH}/src ${OUT}
cp -ar ${CF_PATH}/tests ${OUT}
cp -ar ${FW_PATH}/src ${OUT}/lib/fwprofile

( cd ${OUT};
  zip -r ./CordetFw_C2_Impl_MPLv2_${VERSION}.zip . >/dev/null 2>&1)

# ====================================================================================

#END

