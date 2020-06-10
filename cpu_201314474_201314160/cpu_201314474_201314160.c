#include <linux/proc_fs.h>
#include <linux/seq_file.h> 
#include <asm/uaccess.h> 
#include <linux/hugetlb.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/fs.h>

#define BUFSIZE  	150

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SOFTWARE PARA VER EL ESTADO DEL CPU");
MODULE_AUTHOR("Romeo Axpuac -  201314474  y Soy.LmmL 201314160");


char buffer[256];
char * get_task_state(long state)
{
    switch (state) {
        case TASK_RUNNING:
            return "TAREA_EJECUTANDO";
        case TASK_INTERRUPTIBLE:
            return "TAREA_INTERRUPTIBLE";
        case TASK_UNINTERRUPTIBLE:
            return "TAREA_ININTERRUPTIBLE";
        case __TASK_STOPPED:
            return "__TAREA_DETENIDA";
        case __TASK_TRACED:
            return "__TAREA_TRAZADA";
        default:
        {
            sprintf(buffer, "ESTADO DESCONOCIDO:%ld\n", state);
            return buffer;
        }
    }
}



static int escribir_archivo(struct seq_file * archivo, void *v) {	
   	
	seq_printf(archivo, "  Carnet: 201314474_201314160                      \n");
    	seq_printf(archivo, "  Bayron Romeo Axpuac Yoc y Luis Manuel Morales Lopez\n");
    	seq_printf(archivo, "  DOCH :D                 			   \n");
	seq_printf(archivo, "  ID	PROCESOS			STATUS \n");
 	struct task_struct* task_list;
        size_t process_counter = 0;
        for_each_process(task_list) {
                seq_printf(archivo, "  [%d]	%s			%s\n",task_list->pid,task_list->comm,get_task_state(task_list->state));
                ++process_counter;
        }
        printk(KERN_INFO "== Number of process: %zu\n", process_counter);
       
	return 0;
}

static int al_abrir(struct inode *inode, struct  file *file) {
  return single_open(file, escribir_archivo, NULL);
}

static struct file_operations operaciones =
{    
    .open = al_abrir,
    .read = seq_read
};

static int iniciar(void)
{
    proc_create("cpu_201314474_201314160", 0, NULL, &operaciones);
    printk(KERN_INFO "Carnet: 201314474_201314160\n");
    return 0;
}
 
static void salir(void)
{
    remove_proc_entry("cpu_201314474_201314160", NULL);
    printk(KERN_INFO "Curso: Sistemas Operativos 1\n");
}
 
module_init(iniciar);
module_exit(salir); 
