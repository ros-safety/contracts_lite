#!/bin/bash

for exec in $(find . -executable -type f -name 'test*'); do $exec; done
