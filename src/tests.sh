#!/bin/bash

OS=$(uname -s)
path="data.txt"
doesnotexist="doesnotexist.txt"
method="md5"
if [ $OS = "Linux" ]
then
method="md5sum"
fi

tests=(
    "$path $doesnotexist"
    "$path"
    "-b $path"
    "-be $path"
    "-bn $path"
    "-bs $path"
    "-bt $path"
    "-ben $path"
    "-bes $path"
    "-bet $path"
    "-bens $path"
    "-bent $path"
    "-benst $path"

    "-e $path"
    "-en $path"
    "-es $path"
    "-et $path"
    "-ens $path"
    "-ent $path"
    "-enst $path"

    "-n $path"
    "-ns $path"
    "-nt $path"
    "-nst $path"

    "-s $path"
    "-st $path"

    "-t $path"
)

gnu_tests=(
    "--number-nonblank $path"
    "--number $path"
    "--squeeze-blank $path"
)

function test {
    cat=$(cat $1 2>/dev/null | $method)
    my_cat=$(./my_cat $1 2>/dev/null | $method)

    if [ "$cat" != "$my_cat" ]
    then
    echo "FAILED $1"
    else
    echo "OK $1"
    fi
}

for i in ${!tests[*]}
do
test "${tests[$i]}"
done

if [ $OS = "Linux" ]
then
for i in ${!gnu_tests[*]}
do
test "${gnu_tests[$i]}"
done
fi

echo "my_cat tests complete"
