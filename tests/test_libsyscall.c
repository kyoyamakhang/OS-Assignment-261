#include "syscall.h"

#include <assert.h>
#include <stdio.h>

static struct krnl_t *received_krnl;
static uint32_t received_pid;
static uint32_t received_syscall;
static struct sc_regs received_regs;

int _syscall(
   struct krnl_t *krnl,
   uint32_t pid,
   uint32_t nr,
   struct sc_regs *regs)
{
   received_krnl = krnl;
   received_pid = pid;
   received_syscall = nr;
   received_regs = *regs;

   return 123;
}

int main(void)
{
   struct krnl_t krnl = {0};
   struct pcb_t caller = {0};

   caller.krnl = &krnl;
   caller.pid = 42;

   int result = libsyscall(&caller, 17, 1, 2, 3);

   assert(result == 123);
   assert(received_krnl == &krnl);
   assert(received_pid == 42);
   assert(received_syscall == 17);

   assert(received_regs.a1 == 1);
   assert(received_regs.a2 == 2);
   assert(received_regs.a3 == 3);
   assert(received_regs.orig_ax == 17);

   assert(received_regs.a4 == 0);
   assert(received_regs.a5 == 0);
   assert(received_regs.a6 == 0);
   assert(received_regs.flags == 0);

   assert(libsyscall(NULL, 17, 1, 2, 3) == SYSCALL_ERR_INVALID);

   caller.krnl = NULL;
   assert(libsyscall(&caller, 17, 1, 2, 3) == SYSCALL_ERR_INVALID);

   caller.krnl = &krnl;
   caller.pid = 0;
   assert(libsyscall(&caller, 17, 1, 2, 3) == SYSCALL_ERR_INVALID);

   printf("PASS: PID and syscall arguments were forwarded correctly\n");

   return 0;
}