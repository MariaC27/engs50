#!/bin/bash

files=(
		qputgettest
		qclosetest
		qapplytest
		qsearchtest
		qconcattest
)

for FILE in ${files[*]} ; do

		runtest.sh ${FILE}
done
