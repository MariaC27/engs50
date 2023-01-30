#!/bin/bash

files=(
		#error-test.c
		# gettest
		# puttest
	  applytest
		# removetest
)

echo "the files list is: ${files[*]}"

for FILE in ${files[*]} ; do
		
		echo $(valgrind --leak-check=full --log-file="valgrind.txt" $FILE )
		
		if grep '0 errors\|no leaks possible' $FILE; then
				echo "Success"
		else
				echo "Errors or leaks found. See output file."
		fi

done
