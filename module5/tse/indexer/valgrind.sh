#!/bin/bash

echo $(valgrind --leak-check=full indexer "../pages/" "test")

