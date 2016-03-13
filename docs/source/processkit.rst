JetSpace Processkit
===================

Overview
--------

The Processkit allows you to get information about running processes on your Linux machine. It can generate a list
of all running processes or show detailed information about one process.

API
----

Processkit
^^^^^^^^^^

jetspace_get_pids
""""""""""""""""""""

::

 int *jetspace_get_pids(int *size)

| **Parameter:**
| ``size`` - pointer to an integer. It will contain the size of the returned array.
| **Return:**
|   array of PIDs

Returns an array of the size ``size``. The array contains all PIDs of all running processes.

jetspace_get_process
""""""""""""""""""""
::

 JetSpaceProcess *jetspace_get_process(int pid)
 
| **Parameter:**
| ``pid`` - PID of the process you want information aobut.
| **Return:**
|   Allocated JetSpaceProcess. You need to free this manualy after using.

Return detailed information about a single process.

Datatypes
---------

JetSpaceProcess
^^^^^^^^^^^^^^^

::

 struct _jetspace_process
 {
    int pid;        // PID of the process
    char *name;     // name of the process
    char state;     // status of the process
    int priority;   // nice value of the process
 }

Compile
-------

All functions are defined in ``jetspace/processkit.h``

To compile your application with the Processkit you can use -ljetspace-processkit.

Example Application
-------------------

::

 // TODO
