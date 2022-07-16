#pragma once

#include <stdint.h>
#include <sys/tables/idt/irq.h>

#define NUM_SYSCALLS 1

void Syscall_init();