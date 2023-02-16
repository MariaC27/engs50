#!/bin/bash

echo $(valgrind --leak-check=full indexio_test 2)

