#!/bin/bash

make all || exit 1

RANDOM_RUNS=20
SIZES=(10 100 500)
MODES=(simple medium complex)

BLUE='\033[0;34m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
RED='\033[0;31m'
RESET='\033[0m'

TOTAL=0
ERRORS=0
ALL_TOTAL=0
ALL_ERRORS=0

FAILED_TESTS="/tmp/ps_failed"
VG_LOG_DIR="/tmp/ps_vg_logs"
VG_ERRORS="/tmp/ps_vg_errors"
NORM_LOG="/tmp/ps_norminette"

VG_RUNS=0
VG_ERROR_COUNT=0
VG_AVAILABLE=0
CHECKER_AVAILABLE=0
NORM_AVAILABLE=0

if command -v valgrind >/dev/null 2>&1; then
	VG_AVAILABLE=1
	mkdir -p "$VG_LOG_DIR"
fi

if [ -x ./checker_linux ]; then
	CHECKER_AVAILABLE=1
fi

if command -v norminette >/dev/null 2>&1; then
	NORM_AVAILABLE=1
fi

: > "$FAILED_TESTS"
: > "$VG_ERRORS"

section()
{
	printf "\n${BLUE}━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n"
	printf "  %s\n" "$1"
	printf "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━${RESET}\n"
}

subsection()
{
	printf "\n${YELLOW}%s${RESET}\n" "$1"
}

record_failure()
{
	ALL_ERRORS=$((ALL_ERRORS + 1))
	printf "%s\n" "$1" >> "$FAILED_TESTS"
}

start_group()
{
	TOTAL=0
	ERRORS=0
	printf "  %-40s" "$1"
}

end_group()
{
	ALL_TOTAL=$((ALL_TOTAL + TOTAL))
	ALL_ERRORS=$((ALL_ERRORS + ERRORS))

	if [ "$ERRORS" -eq 0 ]; then
		printf "${GREEN}PASS${RESET}  (%d tests)\n" "$TOTAL"
	else
		printf "${RED}FAIL${RESET}  (%d/%d failed)\n" "$ERRORS" "$TOTAL"
	fi
}

run_push_swap()
{
	local label="$1"
	local status
	local vg_status
	local vg_log

	shift

	if ./push_swap "$@" >/tmp/ps_out 2>/tmp/ps_err; then
		status=0
	else
		status=$?
	fi

	if [ "$VG_AVAILABLE" -eq 1 ]; then
		VG_RUNS=$((VG_RUNS + 1))
		vg_log="$VG_LOG_DIR/run_$VG_RUNS.log"

		if valgrind --quiet --leak-check=full \
			--show-leak-kinds=all \
			--errors-for-leak-kinds=definite,indirect,possible \
			--error-exitcode=99 \
			--log-file="$vg_log" \
			./push_swap "$@" >/dev/null 2>/dev/null; then
			vg_status=0
		else
			vg_status=$?
		fi

		if [ "$vg_status" -eq 99 ]; then
			VG_ERROR_COUNT=$((VG_ERROR_COUNT + 1))
			printf "%s|%s\n" "$label" "$vg_log" >> "$VG_ERRORS"
		fi
	fi

	return "$status"
}

check_operations()
{
	local label="$1"
	local output

	shift

	if [ "$CHECKER_AVAILABLE" -eq 0 ]; then
		return 2
	fi

	output=$(./checker_linux "$@" < /tmp/ps_out 2>&1)

	if [ "$output" != "OK" ]; then
		printf "  [CHECKER FAILED] %s: %s\n" "$label" "$output"
		return 1
	fi

	return 0
}

valid()
{
	local label="PARSING / $CURRENT_GROUP: $*"

	run_push_swap "$label" "$@"
	if [ $? -ne 0 ]; then
		ERRORS=$((ERRORS + 1))
		printf "  [EXPECTED: VALID] %s\n" "$*" >> "$FAILED_TESTS"
	fi
	TOTAL=$((TOTAL + 1))
}

invalid()
{
	local label="PARSING / $CURRENT_GROUP: $*"

	run_push_swap "$label" "$@"
	if [ $? -eq 0 ] || ! grep -qx "Error" /tmp/ps_err; then
		ERRORS=$((ERRORS + 1))
		printf "  [EXPECTED: INVALID] %s\n" "$*" >> "$FAILED_TESTS"
	fi
	TOTAL=$((TOTAL + 1))
}

run_functional()
{
	local label="$1"
	local checker_status

	shift

	printf "\n  %s\n" "$label"

	run_push_swap "FUNCTIONAL / $label" "$@"
	if [ $? -ne 0 ]; then
		printf "  ${RED}PUSH_SWAP FAILED${RESET}\n"
		record_failure "FUNCTIONAL / $label: push_swap failed"
		return
	fi

	if [ "$CHECKER_AVAILABLE" -eq 0 ]; then
		printf "  ${YELLOW}CHECKER SKIPPED${RESET}\n"
		return
	fi

	check_operations "$label" "$@"
	checker_status=$?

	if [ "$checker_status" -eq 0 ]; then
		printf "  ${GREEN}OK${RESET} — %s operations\n" \
			"$(wc -l < /tmp/ps_out)"
	else
		record_failure "FUNCTIONAL / $label: checker failed"
	fi
}

generate_cases()
{
	local size
	local sample
	local file

	for size in "${SIZES[@]}"
	do
		file="/tmp/ps_cases_$size"
		: > "$file"

		for ((sample = 1; sample <= RANDOM_RUNS; sample++))
		do
			shuf -i "1-$size" -n "$size" | paste -sd ' ' - >> "$file"
		done
	done
}

run_bench()
{
	local mode="$1"
	local size="$2"
	local name="${mode#--}"
	local numbers
	local sample=0
	local total=0
	local worst=0
	local operations
	local average
	local grade
	local failed=0
	local result="/tmp/ps_result_${name}_${size}"
	local -a args

	while IFS= read -r numbers
	do
		sample=$((sample + 1))
		read -r -a args <<< "$numbers"

		run_push_swap "BENCHMARK / $mode / $size numbers / sample $sample" \
			--bench "$mode" "${args[@]}"

		if [ $? -ne 0 ]; then
			failed=1
			record_failure "BENCHMARK / $mode / $size / sample $sample: push_swap failed"
		else
			operations=$(wc -l < /tmp/ps_out)
			operations=${operations//[[:space:]]/}

			total=$((total + operations))

			if [ "$operations" -gt "$worst" ]; then
				worst=$operations
			fi

			if [ "$CHECKER_AVAILABLE" -eq 1 ]; then
				if ! check_operations "$mode / $size / sample $sample" "${args[@]}"; then
					failed=1
					record_failure "BENCHMARK / $mode / $size / sample $sample: checker failed"
				fi
			fi
		fi

		ALL_TOTAL=$((ALL_TOTAL + 1))
	done < "/tmp/ps_cases_$size"

	average=$((total / RANDOM_RUNS))

	if [ "$size" -eq 10 ]; then
		if [ "$average" -le 10 ]; then
			grade="EXCELLENT"
		elif [ "$average" -le 20 ]; then
			grade="GOOD"
		else
			grade="PASS"
		fi
	elif [ "$size" -eq 100 ]; then
		if [ "$average" -le 700 ]; then
			grade="EXCELLENT"
		elif [ "$average" -le 900 ]; then
			grade="GOOD"
		else
			grade="PASS"
		fi
	else
		if [ "$average" -le 5500 ]; then
			grade="EXCELLENT"
		elif [ "$average" -le 7000 ]; then
			grade="GOOD"
		else
			grade="PASS"
		fi
	fi

	if [ "$failed" -eq 1 ]; then
		grade="FAIL"
	fi

	printf "%s|%s|%s\n" "$average" "$worst" "$grade" > "$result"
}

show_result()
{
	local average
	local worst
	local grade

	IFS='|' read -r average worst grade < "$1"

	case "$grade" in
		EXCELLENT)
			printf "${GREEN}%-10s${RESET}" "$grade"
			;;
		GOOD)
			printf "${YELLOW}%-10s${RESET}" "$grade"
			;;
		PASS)
			printf "${BLUE}%-10s${RESET}" "$grade"
			;;
		FAIL)
			printf "${RED}%-10s${RESET}" "$grade"
			;;
	esac

	printf " %6s / %6s" "$average" "$worst"
}

run_norminette()
{
	local status

	if [ "$NORM_AVAILABLE" -eq 0 ]; then
		printf "${YELLOW}SKIP${RESET} — Norminette not installed\n"
		return
	fi

	find . -type f \( -name "*.c" -o -name "*.h" \) \
		-not -path "./.git/*" -print0 > /tmp/ps_sources

	if [ ! -s /tmp/ps_sources ]; then
		printf "${YELLOW}SKIP${RESET} — No C files found\n"
		return
	fi

	xargs -0 norminette < /tmp/ps_sources > "$NORM_LOG" 2>&1
	status=$?

	ALL_TOTAL=$((ALL_TOTAL + 1))

	if [ "$status" -eq 0 ]; then
		printf "${GREEN}PASS${RESET} — Norminette\n"
	else
		printf "${RED}FAIL${RESET} — Norminette\n"
		cat "$NORM_LOG"
		record_failure "NORMINETTE: errors found"
	fi
}

CURRENT_GROUP=""

section "1. FUNCTIONAL TESTS"

run_functional "LOW DISORDER — SIMPLE" \
	--bench --adaptive 1 2 3 4 5 6 7 9 8

run_functional "MEDIUM DISORDER — MEDIUM" \
	--bench --adaptive 5 4 3 2 1 6 7 8 9 10

run_functional "HIGH DISORDER — COMPLEX" \
	--bench --adaptive 10 9 8 7 6 5 4 3 2 1

section "2. RANDOM PERFORMANCE BENCHMARK"

subsection "Generating random test cases"
generate_cases

printf "  Samples per size: %d\n" "$RANDOM_RUNS"
printf "  Sizes: 10, 100, 500\n"
printf "  Algorithms: simple, medium, complex\n"

for mode in "${MODES[@]}"
do
	for size in "${SIZES[@]}"
	do
		printf "  Running %-8s — %3s numbers...\n" "$mode" "$size"
		run_bench "--$mode" "$size"
	done
done

printf "\n  %-12s | %-10s | %-25s | %-25s | %-25s\n" \
	"ALGORITHM" "METRIC" "10 NUMBERS" "100 NUMBERS" "500 NUMBERS"

printf "  ─────────────┼────────────┼───────────────────────────┼───────────────────────────┼───────────────────────────\n"

for mode in "${MODES[@]}"
do
	printf "  %-12s | %-10s | " "${mode^^}" "AVG / WORST"
	show_result "/tmp/ps_result_${mode}_10"
	printf " | "
	show_result "/tmp/ps_result_${mode}_100"
	printf " | "
	show_result "/tmp/ps_result_${mode}_500"
	printf "\n"
done

section "3. PARSING TESTS"

subsection "PHASE 1 — NUMERIC VALIDATION"

CURRENT_GROUP="VALID INPUT"
start_group "$CURRENT_GROUP"
valid 3 2 1
valid -42 0 42
valid +42 -42 0
end_group

CURRENT_GROUP="INVALID TEXT AND CHARACTERS"
start_group "$CURRENT_GROUP"
invalid abc
invalid 1 abc 3
invalid 123abc
invalid abc123
invalid 3.14
invalid 1,2
invalid 1/2
invalid 1:2
invalid 1_2
invalid "1@2"
invalid "1#2"
end_group

CURRENT_GROUP="ISOLATED SIGNS"
start_group "$CURRENT_GROUP"
invalid +
invalid -
invalid + ""
invalid - ""
end_group

CURRENT_GROUP="REPEATED SIGNS"
start_group "$CURRENT_GROUP"
invalid ++1
invalid --1
invalid +-1
invalid -+1
invalid +++1
invalid ---1
invalid ++-1
invalid --+1
end_group

CURRENT_GROUP="INTERLEAVED SIGNS"
start_group "$CURRENT_GROUP"
invalid 1-2
invalid 1+2
invalid 12-3
invalid 12+3
invalid 1--2
invalid 1++2
invalid 1+-2
invalid 1-+2
invalid 1-2-3
invalid 1+2+3
invalid 1+-2+3
invalid 1 -2+3
invalid 1 2-3
invalid 1 2 3-4
invalid 1- 2
valid 1 -2
invalid 1 + 2
invalid 1 - 2
end_group

CURRENT_GROUP="TRAILING SIGNS"
start_group "$CURRENT_GROUP"
invalid 42+
invalid 42-
invalid 42++
invalid 42--
end_group

CURRENT_GROUP="MIXED INVALID CHARACTERS"
start_group "$CURRENT_GROUP"
invalid "++42abc"
invalid "--42abc"
invalid "+-42abc"
invalid "42abc+"
invalid "42abc-"
invalid "1 2abc 3"
invalid "1 abc2 3"
invalid "1 2.0 3"
invalid "1 +abc 3"
invalid "1 -abc 3"
end_group

subsection "PHASE 2 — NUMERIC LIMITS"

CURRENT_GROUP="VALID LIMITS"
start_group "$CURRENT_GROUP"
valid 2147483647
valid -2147483648
valid 2147483647 -2147483648
valid +2147483647
valid -0
valid 00
valid -00
valid 00000000002147483647
valid -00000000002147483648
end_group

CURRENT_GROUP="POSITIVE OVERFLOW"
start_group "$CURRENT_GROUP"
invalid 2147483648
invalid 2147483649
invalid 2147483650
invalid 9999999999
invalid 99999999999
invalid 999999999999
invalid 999999999999999
invalid 999999999999999999
invalid 999999999999999999999
invalid 999999999999999999999999999999999999
end_group

CURRENT_GROUP="NEGATIVE OVERFLOW"
start_group "$CURRENT_GROUP"
invalid -2147483649
invalid -2147483650
invalid -9999999999
invalid -99999999999
invalid -999999999999
invalid -999999999999999
invalid -999999999999999999
invalid -999999999999999999999
invalid -999999999999999999999999999999999999
end_group

CURRENT_GROUP="SIGNS AND LIMITS"
start_group "$CURRENT_GROUP"
invalid +2147483648
invalid -2147483649
invalid ++2147483647
invalid --2147483648
invalid +-2147483648
invalid -+2147483647
end_group

CURRENT_GROUP="LEADING ZEROS BEFORE LIMITS"
start_group "$CURRENT_GROUP"
valid 00000000002147483647
valid -00000000002147483648
valid +00000000002147483647
invalid 00000000002147483648
invalid -00000000002147483649
end_group

subsection "PHASE 3 — WHITESPACE AND EMPTY ARGUMENTS"

CURRENT_GROUP="EMPTY ARGUMENTS"
start_group "$CURRENT_GROUP"
invalid ""
invalid " "
invalid "   "
invalid ""
invalid 1 ""
invalid "" 1
invalid 1 "" 2
invalid "1 2" ""
end_group

CURRENT_GROUP="SPACES"
start_group "$CURRENT_GROUP"
valid "1 2"
valid " 1 2"
valid "1 2 "
valid " 1 2 "
valid "  1  2  "
valid "1   2"
valid "1    2    3"
valid "   1   2   3   "
end_group

CURRENT_GROUP="TABS"
start_group "$CURRENT_GROUP"
valid $'1\t2'
valid $'\t1 2'
valid $'1 2\t'
valid $'1\t\t2'
valid $'1\t2\t3'
valid $' \t1\t 2\t '
end_group

CURRENT_GROUP="NEWLINES"
start_group "$CURRENT_GROUP"
valid $'1\n2'
valid $'\n1 2'
valid $'1 2\n'
valid $'1\n\n2'
valid $'1\n2\n3'
valid $' \n1\n 2\n '
end_group

CURRENT_GROUP="CARRIAGE RETURNS"
start_group "$CURRENT_GROUP"
valid $'1\r2'
valid $'\r1 2'
valid $'1 2\r'
valid $'1\r\r2'
valid $'1\r2\r3'
end_group

CURRENT_GROUP="VERTICAL TAB AND FORM FEED"
start_group "$CURRENT_GROUP"
valid $'1\v2'
valid $'1\f2'
valid $'\v1 2'
valid $'\f1 2'
valid $'1\v2\f3'
end_group

CURRENT_GROUP="MIXED WHITESPACE"
start_group "$CURRENT_GROUP"
valid $'1 \t2'
valid $'1\t 2'
valid $'1\n\t2'
valid $'1\r\n2'
valid $' 1\t\n 2\r '
valid $'\t 1 \n 2 \r 3 \v 4 \f'
end_group

CURRENT_GROUP="SIGNS WITH WHITESPACE"
start_group "$CURRENT_GROUP"
invalid "+ 1"
invalid "- 1"
valid "1 +2"
valid "1 -2"
valid "+1 2"
valid "-1 2"
invalid $'+\t1'
invalid $'-\t1'
valid $'1\t+2'
valid $'1\n-2'
end_group

subsection "PHASE 4 — DUPLICATES"

CURRENT_GROUP="SIMPLE DUPLICATES"
start_group "$CURRENT_GROUP"
invalid 1 1
invalid 1 2 1
invalid 5 5 5
invalid -1 -1
invalid 0 0
end_group

CURRENT_GROUP="ZERO: DIFFERENT FORMATS"
start_group "$CURRENT_GROUP"
invalid 0 00
invalid 0 000
invalid 00 000
invalid 000 0000
invalid 00000 0
invalid +0 0
invalid -0 0
invalid +0 -0
invalid 00 +0
invalid 00 -0
invalid +00 000
invalid -00 000
invalid +000 -000
invalid 000000000 0
invalid -000000000 +0
end_group

CURRENT_GROUP="LEADING ZEROS"
start_group "$CURRENT_GROUP"
invalid 01 1
invalid 001 1
invalid 0001 1
invalid 00001 1
invalid 000001 1
invalid 0000001 1
invalid 00042 42
invalid 0042 042
invalid 00042 +42
invalid 00042 +00042
invalid -00042 -42
invalid -00042 -0042
invalid +00042 42
invalid +0042 +42
end_group

CURRENT_GROUP="DUPLICATES WITH SIGNS"
start_group "$CURRENT_GROUP"
invalid +1 1
invalid +01 1
invalid 001 +1
invalid -01 -1
invalid -001 -1
invalid +10 010
invalid -10 -010
valid +001 -001
invalid +42 042
invalid -42 -042
invalid +0007 7
invalid -0007 -7
end_group

CURRENT_GROUP="DUPLICATES IN SAME ARGUMENT"
start_group "$CURRENT_GROUP"
invalid "1 2 1"
invalid "1 1 2"
invalid "01 1"
invalid "5 05 005"
invalid "1 +1"
invalid "0 -0"
invalid "0 +0"
invalid "10 20 30 20"
invalid "1 2 3 4 5 1"
invalid "1 2 3 2 4"
invalid "5 4 3 2 1 5"
end_group

CURRENT_GROUP="DUPLICATES ACROSS ARGUMENTS"
start_group "$CURRENT_GROUP"
invalid "1 2" "3 2"
invalid "1 2" "02"
invalid "001" 1
invalid "0 1" "00"
invalid "10 20" "030 30"
invalid "1 2 3" "4 5 1"
invalid "100" "0100"
invalid "+42" "42"
invalid "-42" "-042"
invalid "0007 8" "+007 9"
invalid "1" "2" "3" "01"
invalid "1 2" "3" "4" "02"
invalid "001 002" "1 2"
invalid "+1 +2" "01 02"
invalid "-1 -2" "-01 -02"
invalid "1 2 3" "4 5" "3"
invalid "10 20" "30 40" "10"
invalid "1 2" "3 4" "5 6" "4"
invalid "7" "8 9" "10 7"
invalid "1 2 3 4" "5 6 7 8" "9 10 1"
invalid "42 43" "44 45" "+042"
invalid "-10 -20" "-30 -40" "-010"
invalid "001 002 003" "004 005" "3"
invalid "+1" "2" "3" "4" "5" "01"
invalid "-1" "-2" "-3" "-4" "-5" "-01"
end_group

subsection "PHASE 5 — FLAGS"

CURRENT_GROUP="DUPLICATE FLAGS"
start_group "$CURRENT_GROUP"
invalid --simple --simple 2 3 4
invalid --medium --medium 2 3 4
invalid --complex --complex 2 3 4
invalid --adaptive --adaptive 2 3 4
invalid --bench --bench 2 3 4
end_group

CURRENT_GROUP="DUPLICATE FLAGS ACROSS ARGUMENTS"
start_group "$CURRENT_GROUP"
invalid --simple "--simple 2 3 4"
invalid --medium "--medium 2 3 4"
invalid --complex "--complex 2 3 4"
invalid --adaptive "--adaptive 2 3 4"
invalid --bench "--bench 2 3 4"
end_group

CURRENT_GROUP="DUPLICATE FLAGS IN SEPARATE ARGUMENTS"
start_group "$CURRENT_GROUP"
invalid "--simple 2" "--simple 3 4"
invalid "--medium 2 3" "--medium 4"
invalid "--complex" "2 3" "--complex 4"
invalid "--adaptive 2 3" "4 --adaptive"
invalid "--bench 2" "3 --bench 4"
end_group

CURRENT_GROUP="FLAGS IN DIFFERENT POSITIONS"
start_group "$CURRENT_GROUP"
valid 2 3 4 --simple
valid 2 --simple 3 4
valid 2 3 --simple 4
valid "2 3" "--simple 4"
valid "--simple" "2 3 4"
valid "2" "--simple 3" "4"
valid "2 3 --simple" "4"
end_group

CURRENT_GROUP="INCOMPATIBLE ALGORITHMS"
start_group "$CURRENT_GROUP"
invalid --simple --medium 2 3 4
invalid --simple --complex 2 3 4
invalid --medium --complex 2 3 4
invalid --simple --adaptive 2 3 4
invalid --medium --adaptive 2 3 4
invalid --complex --adaptive 2 3 4
invalid --simple --medium --complex 2 3 4
invalid --simple --medium --adaptive 2 3 4
invalid --simple --complex --adaptive 2 3 4
invalid --medium --complex --adaptive 2 3 4
invalid --simple --medium --complex --adaptive 2 3 4
end_group

CURRENT_GROUP="UNKNOWN FLAGS"
start_group "$CURRENT_GROUP"
invalid --unknown 2 3 4
invalid --simp 2 3 4
invalid --mediumx 2 3 4
invalid --adaptivex 2 3 4
invalid --benchx 2 3 4
invalid -simple 2 3 4
invalid -bench 2 3 4
end_group

CURRENT_GROUP="FLAGS MIXED WITH INPUT"
start_group "$CURRENT_GROUP"
valid "2 --simple 3 4"
valid "2 3 --medium 4"
valid "2 3 4 --complex"
valid "2 --adaptive 3" 4
valid "2 3" "--bench 4"
valid "--simple 2" "3 --bench 4"
valid "--bench" "--simple 2 3 4"
valid "--adaptive" "--bench" "2 3 4"
end_group

section "4. NORMINETTE"

run_norminette

section "5. VALGRIND REPORT"

if [ "$VG_AVAILABLE" -eq 0 ]; then
	printf "${YELLOW}SKIP${RESET} — Valgrind not installed\n"
else
	printf "  Executions checked: %d\n" "$VG_RUNS"
	printf "  Executions with memory errors: %d\n" "$VG_ERROR_COUNT"

	if [ "$VG_ERROR_COUNT" -eq 0 ]; then
		printf "  ${GREEN}PASS${RESET}\n"
	else
		printf "  ${RED}FAIL${RESET}\n"

		while IFS='|' read -r label log
		do
			printf "\n  ${RED}%s${RESET}\n" "$label"
			cat "$log"
		done < "$VG_ERRORS"

		ALL_ERRORS=$((ALL_ERRORS + VG_ERROR_COUNT))
		ALL_TOTAL=$((ALL_TOTAL + VG_ERROR_COUNT))
	fi
fi

section "6. FINAL REPORT"

printf "  Total tests:  %d\n" "$ALL_TOTAL"
printf "  Failed tests: %d\n" "$ALL_ERRORS"

if [ "$CHECKER_AVAILABLE" -eq 0 ]; then
	printf "  Checker: ${YELLOW}SKIP — checker_linux not found${RESET}\n"
else
	printf "  Checker: ${GREEN}AVAILABLE${RESET}\n"
fi

if [ "$VG_AVAILABLE" -eq 0 ]; then
	printf "  Valgrind: ${YELLOW}SKIP${RESET}\n"
elif [ "$VG_ERROR_COUNT" -eq 0 ]; then
	printf "  Valgrind: ${GREEN}PASS${RESET}\n"
else
	printf "  Valgrind: ${RED}FAIL${RESET}\n"
fi

if [ "$NORM_AVAILABLE" -eq 0 ]; then
	printf "  Norminette: ${YELLOW}SKIP${RESET}\n"
fi

if [ -s "$FAILED_TESTS" ]; then
	printf "\n${RED}FAILED TEST CASES${RESET}\n"
	cat "$FAILED_TESTS"
else
	printf "\n${GREEN}ALL TESTS PASSED${RESET}\n"
fi

rm -f /tmp/ps_out /tmp/ps_err /tmp/ps_check
rm -f /tmp/ps_result_* /tmp/ps_cases_*
rm -f /tmp/ps_sources "$NORM_LOG"
rm -f "$FAILED_TESTS" "$VG_ERRORS"
rm -rf "$VG_LOG_DIR"