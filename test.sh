#!/bin/bash
_help() {
   echo
   echo "functional test of hcode"
   echo
   echo "Syntax: test [-h|s|f|k|i|t]"
   echo "options:"
   echo "-h     Print this Help."
   echo "-s     test the slow compression"
   echo "-f     test the fast compression"
   echo "-i     provide an input file, defaults to the bible"
   echo "-k     keep files after execution"
   echo "-t     target compression percentage to pass, accepts 2 decimals, defaults to 10"
   echo
}
_cleanup() {
    if [[ $keep_file == 'yes' ]]; then
        exit $exit_code
    fi

    if [[ -f $decompressed_file ]]; then
        rm $decompressed_file
    fi

    if [[ -f $compressed_file ]]; then
        rm $compressed_file
    fi
}

RED='\033[0;31m'
BLUE='\033[0;36m'
GREEN='\033[0;32m'
NC='\033[0m' # no color
test_file="./samples/bible.txt"
compression_target=10

while getopts ":hsfkt:i:" option; do
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
        t)
            compression_target=$OPTARG;;
        
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
trap _cleanup EXIT
printf "Running test with sample ${BLUE} $test_file ${NC} ...\n"
compression_speed="$(time ( TIMEFORMAT='%lU'; ./hcode $mode $test_file $compressed_file ) 2>&1 1>/dev/null )"
printf "Compression speed: ${BLUE} $compression_speed ${NC}\n"

decompression_speed="$(time ( TIMEFORMAT='%lU'; ./hcode -d $compressed_file $decompressed_file ) 2>&1 1>/dev/null )"
printf "Decompression speed: ${BLUE} $decompression_speed ${NC}\n"

decompressed_size_human_readable="$(ls -lh $decompressed_file | awk '{print $5}')"
compressed_size_human_readable="$(ls -lh $compressed_file | awk '{print $5}')"

printf "Decompressed size: ${BLUE} ${decompressed_size_human_readable}B ${NC}\n"
printf "Compressed size: ${BLUE} ${compressed_size_human_readable}B ${NC}\n"

cmp --silent $test_file $decompressed_file \
&& printf "${GREEN}### PASSED: Decompressed file identical to source file! ###\n${NC}" \
|| { printf "${RED}### FAILED: Decompressed file different from source file! ###\n${NC}"; exit 1; }

source_size=$(stat -c%s "$test_file")
compressed_size=$(stat -c%s "$compressed_file")
if [[  $compressed_size -gt $source_size ]]; then
    printf "${RED}### FAILED: Compressed file bigger than source file! ###\n${NC}"; exit 1
else
    printf "${GREEN}### PASSED: Compressed file smaller than source file! ###\n${NC}"
fi

compression_percentage=$(bc <<< "scale=2; ($source_size - $compressed_size)/$source_size * 100")
if (( $(echo "$compression_percentage < $compression_target" | bc -l) )); then
    printf "${RED}### FAILED: compression of $compression_percentage %% is lower than the target of $compression_target %% ! ###\n${NC}"; exit 1
else
    printf "${GREEN}### PASSED: compression of $compression_percentage %% is higher than the target of $compression_target %% ! ###\n${NC}"
fi