struct stat;
struct rtcdate;
struct lock_t;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int set_priority(int, int);
int get_priority(int);
int cps(void);
int thread_create(void (*) (void *), void *, void *);
int thread_join(void);
int thread_exit(void);
int lock_init(struct lock_t*);
int lock_acquire(struct lock_t*);
int lock_release(struct lock_t*);

// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, const char*, ...);
char* gets(char*, int max);
unsigned int strlen(const char*);
void* memset(void*, int, unsigned int);
void* malloc(unsigned int);
void free(void*);
int atoi(const char*);
