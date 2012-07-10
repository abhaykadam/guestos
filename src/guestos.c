/*
 *  Multi2Sim
 *  Copyright (C) 2007  Rafael Ubal Tena (raurte@gap.upv.es)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

///#include <time.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <options.h>
#include <signal.h>
#include <stdbool.h>
#include <m2skernel.h>
#include <bdev.h>
#include <fs.h>
#include <isr.h>
#include <dctrl.h>
#include <misc.h>

/* Multi2Sim version */
#ifndef VERSION
#define VERSION ""
#endif


//path length of user program
#define max_path_length 100
/* Options */
static char *sim_title = "";
static char *configfile = "";
static char *ctxconfig = "";

static char *ctx_debug_file = "";
static char *syscall_debug_file = "";
static char *opencl_debug_file = "";
static char *gpu_isa_debug_file = "";
static char *elf_debug_file = "";
static char *loader_debug_file = "";
static char *isa_call_debug_file = "";
static char *isa_inst_debug_file = "";

static char *inst_stat_file = "";
static char *inst_stop = "";
static uint64_t inst_reset = 0;
static uint64_t max_cycles = 0;
static uint64_t max_inst = 0;
static uint32_t break_point = 0;
static uint64_t sim_cycle = 0;
static uint64_t sim_inst = 0;


/* Variables */
static int sigint_received = 0;
extern int instr_slice;

/* Disk controller structure */
struct dctrl dc;

//int max_path_length = 100;
void shell();


static void sim_reg_options() {
	opt_reg_string("-title", "Simulation title", &sim_title);
	opt_reg_string("-config", "m2s-fast configuration file", &configfile);
	opt_reg_string("-ctxconfig", "Context configuration file", &ctxconfig);

	opt_reg_string("-debug:ctx", "Debug information for context creation & status updates", &ctx_debug_file);
	opt_reg_string("-debug:syscall", "Debug information for system calls", &syscall_debug_file);
	opt_reg_string("-debug:opencl", "Debug information for OpenCL programs", &opencl_debug_file);
	opt_reg_string("-debug:gpu_isa", "Debug information for GPU instructions", &gpu_isa_debug_file);
	opt_reg_string("-debug:elf", "Debug information from elf file analyzer", &elf_debug_file);
	opt_reg_string("-debug:loader", "Debug information from program loader", &loader_debug_file);
	opt_reg_string("-debug:call", "Debug information about procedure calls", &isa_call_debug_file);
	opt_reg_string("-debug:inst", "Debug information about executed instructions", &isa_inst_debug_file);

	opt_reg_string("-inst_stat", "File to dump instruction stats", &inst_stat_file);
	opt_reg_string("-inst_stop", "Stop when executing inst", &inst_stop);
	opt_reg_uint64("-inst_reset", "Cycle to reset instruction stats", &inst_reset);
	opt_reg_uint64("-max_cycles", "Cycle to stop program (0=no stop)", &max_cycles);
	opt_reg_uint64("-max_inst", "Maximum number of instructions", &max_inst);
	opt_reg_uint32("-break_point", "Value for eip to stop", &break_point);
	opt_reg_bool("-mem_safe_mode", "Safe accesses to memory", &mem_safe_mode);

	gk_reg_options();
}

/* Signal handlers */
static void sim_signal_handler(int signum) {
	FILE *f;

	switch (signum) {

	    case SIGINT:
	        //if (sigint_received)
	        //	abort();
	        sigint_received = 1;
	        fprintf(stderr, "SIGINT received\n");
	        signal(SIGINT, sim_signal_handler);
	        printf("Don't do that\n");
	        break;

	    case SIGABRT:
	        signal(SIGABRT, SIG_DFL);
	        fprintf(stderr, "cycle %lld: aborted\n", (long long) sim_cycle);
	        f = open_write(inst_stat_file);
	        if (f)
	            isa_inst_stat_dump(f);
	        isa_dump(stderr);
	        ke_dump(stderr);
	        exit(1);
	        break;
	    case SIGFPE:
	        printf("\n Inside signal handler for signal floating point error**");
	        printf("\n Inside signal handler for signal floating point error**");
	        signal(SIGFPE, SIG_DFL);
	        break;

	    case SIGSEGV:
	        signal(SIGSEGV, SIG_DFL);
	        printf ( "You are here in sim_signal_handler \nsegmentation fault\n");
	        exit(0);
	        break;

	    case SIGUSR1:
	        printf("\n Inside signal handler for signal named SIGUSR1");
	        printf("\ndoing nothing");
	        break;
	}
}


/*boot parameters file declaration*/
#define BOOT_FILE ".config"

static void set_instr_slice(char *str) {
	instr_slice = atoi(str);
}

static void add_block_dev(char *str){
	struct block_device bdev;

	strcat(str," ");
	char *attr_val = strtok(NULL, " ");
	while (attr_val!=0) {
		size_t pair_len = strtok_len(attr_val, " ");
		char *pair = strndup(attr_val, pair_len);
	
		if (strncasecmp(pair, "id=", strlen("id="))==0) {
			bdev.bd_dev = atoi(pair+strlen("id="));
		} else if (strncasecmp(pair, "block-size=", strlen("block-size="))==0) {
			bdev.bd_block_size = atoi(pair+strlen("block-size="));
		} else if (strncasecmp(pair, "path=", strlen("path="))==0) {
			bdev.bd_name = strdup((pair+strlen("path=")));
		}

		free(pair);
		attr_val = strtok(NULL, " ");
	}
	
	add_blkdev(&bdev);
}

void set_defaults(void) {
	FILE *fp;
	if ((fp=fopen(BOOT_FILE,"r"))==0) {
		perror("boot configuration file couldn't be loaded.\n");
		exit(-1);
	} 

	while(true) {
		if (feof(fp))
			break;
	
		size_t line_max = LINE_MAX;	
		char *str_line;
		
		str_line = (char*)malloc(LINE_MAX+1);
		if (str_line==0) {
			perror("ran out of memory\n");
			exit(-1);
		}		

		ssize_t line_len = getline (&str_line, &line_max, fp);
		
		if (line_len < 1) {
			free(str_line);
			continue;
		}

		char* tag = strtok(str_line, ":");
		if(strncasecmp(tag, "instr_slice", strlen("instr_slice"))==0) {
			set_instr_slice(strtok(NULL, "\n"));
		} else if(strncasecmp(tag, "disk", strlen("disk"))==0) {
			add_block_dev(strtok(NULL, "\n"));
		}

		free(str_line);
	}

	fclose(fp);
}

void install_signals(void){
	signal(SIGINT, &sim_signal_handler);
	signal(SIGABRT, &sim_signal_handler);
	signal(SIGFPE, &sim_signal_handler);
	signal(SIGUSR2, &sim_signal_handler);
}

void boot(void) {
	// to install system calls
	install_signals();
	set_defaults();
	init_pic();
	init_disk_controller(&dc);
	init_ivt();
}


////char   myargv[2][200];
char user_prog_path[200];
////	char *user_prog_path;

int main(int argc, char **argv) {
	uint64_t t;
	int myargc = 2;
	
	fprintf(stderr, "********************************************************");
	fprintf(stderr, "\n WELCOME TO GUESTOS\n");
	fprintf(stderr, "********************************************************\n");


	/* Options */
	opt_init();
	sim_reg_options();


	/* Initialize */
	ke_init();

	
	boot();

	init_filesystem();

	shell();


	if (*configfile) {
	         opt_check_config(configfile);
	}
	
	ld_load_prog_from_ctxconfig(ctxconfig);
	

	/* Simulation loop */
	signal(SIGINT, &sim_signal_handler);
	signal(SIGABRT, &sim_signal_handler);
	signal(SIGFPE, &sim_signal_handler);
	signal(SIGUSR2, &sim_signal_handler);
  
	while (!sigint_received) {

	    /* Break point */
	    if (break_point && ke->context_list_head->regs->eip == break_point) {
	        regs_dump(ke->context_list_head->regs, stdout);
	        break;
	    }

	    /* Run an instruction from each running context */
	    ke_run();
	    sim_inst += ke->running_count;
	    if (!ke->context_list_head)
	        break;

	    /* Stop conditions */
	    sim_cycle++;
	    if ((sim_cycle >= max_cycles && max_cycles) ||
	            (sim_inst >= max_inst && max_inst)) {
	        regs_dump(isa_regs, stdout);
	        ke_dump(stdout);
	        break;
	    }
	    if (sim_cycle == inst_reset && inst_reset)
	        isa_inst_stat_reset();

	    if (*inst_stop && !strcmp(isa_inst.format, inst_stop))
	        panic("instruction '%s' found", inst_stop);


	}

	/* Finalization */
	ke_done();

	shutdown();

	///opt_done();
	///debug_done();
	mhandle_done();
	pthread_exit(NULL);
}

void shutdown(void) {
	close_disk_controller(&dc);
}

void shell() {
	int number_of_processes = 0, i = 0;
	FILE *f_in;
	char temp[LINE_MAX];
	char user_prog_path[LINE_MAX];
	int uid;

	printf("\n Shell begins:\n");
	printf("\n guestos:\n");
	printf("How many user processes to run?");
	scanf("%d", &number_of_processes);
	if ((f_in = fopen("configfile", "w"))==0) {
		perror("program configuration file couldn't be loaded.\n");
		exit(-1);
	} 
	for (i = 0; i < number_of_processes; i++) {
	    printf("\n\n\n guestos:Enter the full path of user program to execute:");
	    fflush(stdin);
	    scanf("%s", user_prog_path);
	printf ("Enter Uid for process: ");
	scanf("%d", &uid);
	    printf("\n The entered file path is : %s", user_prog_path);
	    sprintf(temp, "\n[ Context %d ]", i);
	    fputs(temp, f_in);
	    sprintf(temp, "\nExe = %s\n", user_prog_path);
	    fputs(temp, f_in);
	sprintf(temp, "\nUid = %d\n", uid);
	    fputs(temp, f_in);
	}
	configfile = "configfile";
	fclose(f_in);
	return;
}
