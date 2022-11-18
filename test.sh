#!/bin/bash
_help() {
   echo
   echo "functional test of hcode"
   echo
   echo "Syntax: test [-h|s|f|k|i]"
   echo "options:"
   echo "-h     Print this Help."
   echo "-s     test the slow compression"
   echo "-f     test the fast compression"
   echo "-i     provide an input file, defaults to the bible"
   echo "-k     keep files after execution"
   echo
}
RED='\033[0;31m'
BLUE='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m' # no color
declare -i exit_code=0
test_file="./samples/bible.txt"

while getopts ":hsfki:" option; do
    case $option in
        h)
            _help
            exit;;
        s) 
            mode='-s';;
        f) 
            mode='-f';;
        i)
            test_file=$OPTARG;;
        k)
            keep_file='yes';;
        
        \?)
            echo "Error: Invalid option"
            _help
            exit;;
   esac
done

if [ -z "$mode" ]
then
   _help
   exit
fi

compressed_file="compressed-tmp-$(uuidgen).huffenc"
decompressed_file="decompressed-tmp-$(uuidgen).txt"

compression_speed="$(time ( TIMEFORMAT='%lU'; ./hcode $mode $test_file $compressed_file ) 2>&1 1>/dev/null )"
printf "Compression speed: ${BLUE} $compression_speed ${NC}\n"

decompression_speed="$(time ( TIMEFORMAT='%lU'; ./hcode -d $compressed_file $decompressed_file ) 2>&1 1>/dev/null )"
printf "Decompression speed: ${BLUE} $decompression_speed ${NC}\n"

decompressed_size="$(ls -lh $decompressed_file | awk '{print $5}')"
compressed_size="$(ls -lh $compressed_file | awk '{print $5}')"

printf "Decompressed size: ${BLUE} ${decompressed_size}B ${NC}\n"
printf "Compressed size: ${BLUE} ${compressed_size}B ${NC}\n"

cmp --silent $test_file $decompressed_file \
&& printf "${GREEN}### PASSED: Decompressed file identical to source! ###\n${NC}" \
|| (printf "${RED}### FAILED: Decompressed file different from source! ###\n${NC}" && declare -i exit_code=1)

if [[ $keep_file == 'yes' ]]; then
    exit $exit_code
fi

if [[ -f $decompressed_file ]]; then
    rm $decompressed_file
fi

if [[ -f $compressed_file ]]; then
    rm $compressed_file
fi

exit $exit_code