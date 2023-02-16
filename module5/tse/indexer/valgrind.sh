#!/bin/bash

echo $(valgrind --leak-check=full indexer5 3)

