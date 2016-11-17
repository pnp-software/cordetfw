#!/bin/bash
# This script creates a release package for the C2 Implementation of the CORDET FW.
# The data package is created in directory ~/Dump.
#
# The script should be run from the directory where the CORDET Scripts are located.
#
# This script performs the following actions:
# 1. Checks out all FW Profile core, test suite, demo application and examples code, 
# 2. Checks out all documentation sources 
# 3. Generates PDF documentation from the Latex sources
# 4. Updates the copyright note in the code sources
# 5. Generates the doxygen documentation
# 6. Run the release acceptance tests (RunAcceptanceTest.sh)
# 7. Creates the delivery file
#====================================================================================

showHelp() {
    echo "Options: "
    echo "-v=, --version=        release version number"
    echo "-e=, --examples=       path to the cordet-examples repository"
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
    -e=*|--examples=*)
    EXAMPLE_PATH=`echo $i | sed 's/[-a-zA-Z0-9]*=//'`
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
if [ "$EXAMPLE_PATH" == "" ]
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
mkdir -p $OUT/examples
mkdir -p $OUT/examples/src
mkdir -p $OUT/tests
mkdir -p $OUT_DOCS
mkdir -p $OUT_LOG
mkdir -p $OUT_SRC
mkdir -p $OUT_LIB

CF_DOC="${CF_PATH}/doc"
CF_SRC="${CF_PATH}/src"
DOXYFILE="C2Impl_TestSuite.doxyfile"

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
(cd ${CF_DOC}/doxygen &&
	doxygen $DOXYFILE > doxygen_generation.log)
cp -ar ${CF_DOC}/doxygen/html ${OUT_DOCS}/doxygen

# ====================================================================================
# Redirect both stdout and stderr to the AcceptanceTestReport.log file
echo "Run Release Acceptance Tests"
(make clean;
 make test && make run-test && make coverage-info)

echo "Running valgrind..."
valgrind --leak-check=yes ./bin/testsuite > ${OUT_LOG}/TestSuite_Valgrind_Report.txt 2>&1

#echo "===================================================================================="
echo "Extract the non-covered parts of the C2 Implementation code"
#echo "===================================================================================="
egrep -B 6 "####| 0%" *.c.gcov >> ${OUT_LOG}/CodeCoverage_Report.txt 2>&1
 
# ====================================================================================
echo "Create Release Package"
echo ""
cp -a ${CF_DOC}/commercial/README ${OUT}
cp -a ${CF_DOC}/commercial/COPYING ${OUT}
cp -a ${CF_PATH}/Makefile ${OUT}
cp -ar ${CF_PATH}/src ${OUT}
cp -ar ${CF_PATH}/tests ${OUT}
cp -ar ${FW_PATH}/src ${OUT}/lib/fwprofile
cp -a ${EXAMPLE_PATH}/CompileAndLinkMa.sh ${OUT}/examples/
cp -a ${EXAMPLE_PATH}/CompileAndLinkS1.sh ${OUT}/examples/
cp -a ${EXAMPLE_PATH}/CompileAndLinkS2.sh ${OUT}/examples/
cp -ar ${EXAMPLE_PATH}/src/ ${OUT}/examples/

( cd ${OUT};
  zip -r ./CordetFw_C2_Impl_LGPLv3_${VERSION}.zip .)

# ====================================================================================

#END

