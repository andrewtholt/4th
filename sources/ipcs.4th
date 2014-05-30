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

    [hex] aa55aa55  ptr  mem!

    ." mem-c@:" ptr mem-c@ . cr
    ." mem-w@:" ptr mem-w@ . cr
    ." mem@  :" ptr mem@   . cr

    [hex] 55aa55aa  ptr  mem-w!

    shmid shmdt abort" shmdt"
\    shmid shmrm abort" shmrm"
;

main

