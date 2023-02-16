#!/bin/bash

echo $(valgrind --leak-check=full indexer 3)

