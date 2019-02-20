#!/bin/bash

# submission 3

cd ./3-codegen/
chmod u+x ./test_interpreter.sh ./test_compiler.sh
FAIL=0

 ./test_interpreter.sh
FAIL=$?

./test_compiler.sh
FAIL=$(( ${FAIL} + $? ))

printf "\n\n           ######################\n"
printf "           ### END OF ALL TEST ##\n"
printf "           ### TOATL  ${FAIL}  FAIL  ##\n"
printf "           ######################\n"

exit ${FAIL}
