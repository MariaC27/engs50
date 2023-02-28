#!/bin/bash

echo $(valgrind --leak-check=full indexer "../pages/" "test")
echo 
echo $(valgrind --leak-check=full tindexer ../pages/ indexnm_test 20)

