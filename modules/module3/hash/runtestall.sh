#!/bin/bash

files=(
		test1_hash
		test2_hash
		test3_hash
)

for FILE in ${files[*]} ; do

		runtest.sh ${FILE}
done
