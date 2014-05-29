include lib/dump.4th

-1 value shmid
-1 value /shm
-1 value ptr

: main
    1024 to /shm
    999 /shm 896 shmget to shmid

    cr
    ." shmid is " shmid . cr

    shmid shmat to ptr

    hex
    cr ." ptr : " ptr . cr

    ptr mem-c@ . cr

    shmid shmdt abort" shmdt"
    shmid shmrm abort" shmrm"
;

main

