# shared_mem_with_semaphore
It's just a demo when learning IPC with shared memory and synced with semaphore
The shared memory API is System V style.
The code can be run under redhat
Linux epgtool335-50.seln.ete.ericsson.se 2.6.32-131.0.15.el6.x86_64 #1 SMP Tue May 10 15:42:40 EDT 2011 x86_64 x86_64 x86_64 GNU/Linux

The result is as below,
[root@epgtool335-50 ~]# ./client 50 0 & ./client 50 0 & ./client 50 0
[1] 19629
[2] 19630
[1]-  Done                    ./client 50 0

[root@epgtool335-50 ~]# ./server
index = 0: pid 19629: message 34
index = 1: pid 19630: message 28
index = 2: pid 19631: message 31
index = 3: pid 19629: message 35
index = 4: pid 19630: message 29
index = 5: pid 19631: message 32
index = 6: pid 19629: message 36
index = 7: pid 19630: message 30
index = 8: pid 19631: message 33
index = 9: pid 19629: message 37
index = 10: pid 19630: message 31
index = 11: pid 19631: message 34
index = 12: pid 19629: message 38
index = 13: pid 19630: message 32
index = 14: pid 19631: message 35
index = 15: pid 19629: message 39
index = 0: pid 19630: message 33
index = 1: pid 19631: message 36
index = 2: pid 19630: message 34
index = 3: pid 19631: message 37
index = 4: pid 19629: message 40
index = 5: pid 19630: message 35
index = 6: pid 19631: message 38
index = 7: pid 19629: message 41
index = 8: pid 19630: message 36
index = 9: pid 19631: message 39
index = 10: pid 19629: message 42
index = 11: pid 19630: message 37
index = 12: pid 19631: message 40
index = 13: pid 19629: message 43
index = 14: pid 19630: message 38
index = 15: pid 19631: message 41
index = 0: pid 19629: message 44
index = 1: pid 19630: message 39
index = 2: pid 19631: message 42
index = 3: pid 19629: message 45
index = 4: pid 19630: message 40
index = 5: pid 19631: message 43
index = 6: pid 19629: message 46
index = 7: pid 19630: message 41
index = 8: pid 19631: message 44
index = 9: pid 19630: message 42
index = 10: pid 19629: message 47
index = 11: pid 19629: message 48
index = 12: pid 19631: message 45
index = 13: pid 19630: message 43
index = 14: pid 19631: message 46
index = 15: pid 19629: message 49
index = 0: pid 19630: message 44
index = 1: pid 19631: message 47
index = 2: pid 19630: message 45
index = 3: pid 19631: message 48
index = 4: pid 19630: message 46
index = 5: pid 19631: message 49

It can be observerd that the message from client are in order.
