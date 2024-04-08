#if !defined(BARESNAKE_CPU_EXCEPTION)
#error You must define BARESNAKE_CPU_EXCEPTION before including this file
#endif

#ifndef BARESNAKE_CPU_EXCEPTION_LAST
#define BARESNAKE_CPU_EXCEPTION_LAST(X) CHAD_INTERPRETER_TOKEN(X)
#endif

BARESNAKE_CPU_EXCEPTION(DIVISION_BY_ZERO, 0)
BARESNAKE_CPU_EXCEPTION(DEBUG_EXCEPTION, 1)
BARESNAKE_CPU_EXCEPTION(NON_MASKABLE_INTERRUPT, 2)
BARESNAKE_CPU_EXCEPTION(BREAKPOINT_EXCEPTION, 3)
BARESNAKE_CPU_EXCEPTION(INTO_DETECTED_OVERFLOW, 4)
BARESNAKE_CPU_EXCEPTION(OUT_OF_BOUNDS_EXCEPTION, 5)
BARESNAKE_CPU_EXCEPTION(INVALID_OPCODE_EXCEPTION, 6)
BARESNAKE_CPU_EXCEPTION(NO_COPROCESSOR_EXCEPTION, 7)
BARESNAKE_CPU_EXCEPTION(DOUBLE_FAULT, 8)
BARESNAKE_CPU_EXCEPTION(COPROCESSOR_SEGMENT_OVERRUN, 9)
BARESNAKE_CPU_EXCEPTION(BAD_TSS, 10)
BARESNAKE_CPU_EXCEPTION(SEGMENT_NOT_PRESENT, 11)
BARESNAKE_CPU_EXCEPTION(STACK_FAULT, 12)
BARESNAKE_CPU_EXCEPTION(GENERAL_PROTECTION_FAULT, 13)
BARESNAKE_CPU_EXCEPTION(PAGE_FAULT, 14)
BARESNAKE_CPU_EXCEPTION(UNKNOWN_INTERRUPT_EXCEPTION, 15)
BARESNAKE_CPU_EXCEPTION(COPROCESSOR_FAULT, 16)
BARESNAKE_CPU_EXCEPTION(ALIGNMENT_CHECK_EXCEPTION, 17)
BARESNAKE_CPU_EXCEPTION(MACHINE_CHECK_EXCEPTIONi, 18)

#undef BARESNAKE_CPU_EXCEPTION
#undef BARESNAKE_CPU_EXCEPTION_LAST
