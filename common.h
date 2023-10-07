//
// Created by aucker on 10/7/2023.
//

#ifndef CLOX_COMMON_H
#define CLOX_COMMON_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
 * When this flag is defined, the VM disassembles and prints each instruction
 * right before executing it. Where our previous disassembler walked an entire
 * chunk once, statically, this disassembles instructions dynamically, on the fly.
 */
#define DEBUG_TRACE_EXECUTION

#endif//CLOX_COMMON_H
