#!/bin/bash

files=(
		puttest
		gettest
		applytest
		removetest
)

for FILE in ${files[*]} ; do

		runtest.sh ${FILE}
done
