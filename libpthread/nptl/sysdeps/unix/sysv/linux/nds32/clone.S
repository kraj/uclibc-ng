/* We want an #include_next, but we are the main source file.
   So, #include ourselves and in that incarnation we can use #include_next.  */
# define RESET_PID
# include <libc/sysdeps/linux/nds32/clone.S>
