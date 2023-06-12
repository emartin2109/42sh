#! /bin/bash

RESET="\e[0m"
BOLD="\e[1m"
RED="\e[31m"
GREEN="\e[32m"
GRAY="\e[90m"

# Check command line arguments
if [ $# -ne 2 ] || [ ! -x $1 ] || [ ! -f $2 ]; then
    echo "Usage: $0 <shell executable> <test file>"
    exit 1
fi

shell_path=$(realpath "$1")
test_path=$(realpath "$2")

temp_dir=$(mktemp -d "/tmp/shell-tester.XXXXXX")
cd "$temp_dir" || exit 1

test_count=$(jq -c '.[]' "$test_path" | wc -l)
echo -e "${GRAY}running $test_count tests in $temp_dir${RESET}"

exit_code=0
for key in $(jq -r 'keys_unsorted[]' "$test_path"); do
    command=$(jq -r ".[\"$key\"].command" "$test_path")
    expected=$(jq -r ".[\"$key\"].output" "$test_path")
    status=$(jq -r ".[\"$key\"].status" "$test_path")

    echo -en "${GRAY}running $key${RESET}"
    output=$(echo "$command" | "$shell_path" 2>&1)
    out_status=$?

    if [ "$output" != "$expected" ] || [ "$out_status" -ne "$status" ]; then
        echo -e " ${RED}${BOLD}failed (status: $out_status, expected $status)${RESET}"
        echo -e "${RED}expected:${RESET}"
        echo "$expected"
        echo -e "${RED}got:${RESET}"
        echo "$output"
        exit_code=1
    else
        echo -e " ${GREEN}passed${RESET}"
    fi
done

rm -rf "$temp_dir"
exit $exit_code
