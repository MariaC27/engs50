#!/bin/bash

files=(
		concat_test
		test_queue1
		test_queue2
)

echo "the files list is: ${files[*]}"

for FILE in ${files[*]} ; do
		
		echo $(valgrind --leak-check=full --log-file="valgrind_${FILE}.txt" $FILE )
		
		if grep '0 errors\|no leaks are possible' valgrind_${FILE}.txt ; then
				echo "Success for file:  ${FILE}"
		else
				echo "Errors or leaks found. See output file for: ${FILE}"
		fi

done
