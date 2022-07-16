#include <sys/hw/task.h>
#include <sys/mem/heap.h>
#include <sys/debug/dbg.h>

void Task::create(char* name, uint32_t toTask, uint32_t stackSize = 4096) {
    this->name = name;

	// Get EFLAGS and CR3
    Dbg::printf("CR3.\n");
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(this->regs.cr3)::"%eax");
	asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(this->regs.eflags)::"%eax");
    Dbg::printf("CR3 Set.\n");
    
    Dbg::printf("Regs.\n");
	this->regs.eax = 0;
	this->regs.ebx = 0;
	this->regs.ecx = 0;
	this->regs.edx = 0;
	this->regs.esi = 0;
	this->regs.edi = 0;
	this->regs.eip = (uint32_t)toTask;
	this->regs.esp = (uint32_t)Heap::malloc(stackSize);
	this->next = 0;
    Dbg::printf("Regs set.\n");

	Dbg::printf("Task created.\n");
}

namespace Tasking {
	Task* currentTask;
	Task  mainTask;
	bool tasked = false;

	extern "C" void switchTask(Registers *from, Registers *to);

	void idleTask() {
		Dbg::printf("Burn the whole house down.");
		yield();
	}

	void task2() {
		for (;;) Dbg::printf("Burn the whole house down.");
	}

	void __addTask(Task* task) {
		task->next 		  = currentTask->next;
		task->next->prev  = task;
		task->prev        = currentTask;
		currentTask->next = task;
	}

	void addTask(Task* task) {
		tasked = false;
		__addTask(task);
		tasked = true;
	}

	void init() {
		/*currentTask->create("idle", (uint32_t)task2);*/
		mainTask.create("idle", (uint32_t)idleTask);
		mainTask.next=&mainTask;
		mainTask.prev=&mainTask;
		tasked = true;
		currentTask = &mainTask;
		// Task* t2;
		// t2->create("burn", (uint32_t)task2);
		// __addTask(t2);
		// __exec();
	}

	void yield() {
	    if (!tasked) return;
		Task *last = currentTask;
	    currentTask = currentTask->next;
	    switchTask(&last->regs, &currentTask->regs);
	}
}