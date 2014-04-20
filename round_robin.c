/*
 * Simple implementation of round robin process scheduling
 *
 * @author anupkhadka
 */

#include <stdio.h>

#define NUM_PROCESS 3
typedef int time_t;
typedef struct process_ {
	int pid;
	time_t burst;
	time_t slice;
	time_t execTime;
	struct process_ *prev;
	struct process_ *next;
} process_t;
process_t *queue_head = NULL;
process_t *queue_tail = NULL;

static void addToProcessQueue(process_t *proc) {
	proc->next = NULL;
	if(queue_head == NULL) {
		proc->prev = NULL;
		queue_head = proc;
		queue_tail = queue_head;
	} else {
		queue_tail->next = proc;
		proc->prev = queue_tail;	
		queue_tail = proc;
	}
}

static void delFromProcessQueue(process_t *proc) {
	//unsafe, but we are guaranteed to find this proc on this demo
	if(queue_head->pid == proc->pid && 
       queue_tail->pid == proc->pid) {
		queue_head = NULL;
		queue_tail = NULL;
	} else if(queue_head->pid == proc->pid) {
		queue_head = proc->next;
	} else if(queue_tail->pid == proc->pid) {
		queue_tail->prev->next = NULL;
		queue_tail = queue_tail->prev;
	} else {
		proc->prev->next = proc->next;
		proc->next->prev = proc->prev;
	}
}

int isOnlyProcess(process_t *proc) {
	return (queue_head->pid == proc->pid) && (queue_tail->pid == proc->pid);
}

process_t* getFirst() {
	return queue_head;
}

process_t* getNext(process_t *proc) {
	return proc->next != NULL ? proc->next : queue_head;
} 

int main() {
	int i;
	time_t total_time = 0;
	time_t time_on_curr_cycle = 0;
	process_t pid_arr[NUM_PROCESS];
	process_t *proc = NULL;
	
	//Initialize random values to proceses and print their info
	pid_arr[0].pid = 1;
	pid_arr[0].burst = 6;
	pid_arr[0].slice = 2;
	pid_arr[0].execTime = 0;
	addToProcessQueue(&pid_arr[0]);
	
	pid_arr[1].pid = 2;
	pid_arr[1].burst = 3;
	pid_arr[1].slice = 2;
	pid_arr[1].execTime = 0;
	addToProcessQueue(&pid_arr[1]);

	pid_arr[2].pid = 3;
	pid_arr[2].burst = 5;
	pid_arr[2].slice = 2;
	pid_arr[2].execTime = 0;
	addToProcessQueue(&pid_arr[2]);

	printf("Processes info:\n");	
	for(i = 0; i < NUM_PROCESS; i++) {
		printf("PID            : %d\n", pid_arr[i].pid);
		printf("   Burst time  : %d\n", pid_arr[i].burst);
		printf("   Slice time  : %d\n", pid_arr[i].slice);
	}
	printf("############################################\n");		
	printf("Time: %d, CPU State: Idle\n", total_time);
	
	proc = getFirst();
	while(proc) {
		//round-robin through process until all processes are executed
		while(proc->execTime < proc->burst && time_on_curr_cycle < proc->slice) {
			total_time++;
			time_on_curr_cycle++;
			proc->execTime++;
			printf("Time: %d, CPU State: Processing pid: %d\n", total_time, proc->pid);
		}

		time_on_curr_cycle = 0;
		if(proc->execTime == proc->burst) {
			//process completed, remove from pending list
			process_t *del = proc;
			if(!isOnlyProcess(proc)) {
				proc = getNext(proc);
			} else {
				proc = NULL;
			}
			delFromProcessQueue(del);
		} else {
			proc = getNext(proc);
		}
	}	
	
	printf("CPU State: All process complete\n");
}
