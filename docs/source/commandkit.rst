JetSpace Commandkit
===================

Overview
--------

The CommandKit is designed to handle command-line Arguments. these arguments can either be in 'long form' like
``--help`` or in 'short form' like ``-h``. An argument must contain both variants. An additional feature is that
the logkit can automatically generate help output when the help option (``-h or --help``) is used.


**THE API IS NOT STABLE YET, SO THIS DOCUMENT MAY CHANGE**

API
----

Commandkit - Init
^^^^^^^^^^^^^^^^^^

jetspace_cmd_line_init
"""""""""""""""""""""""

::

 void jetspace_cmd_line_init(char *appname, char *appversion);

| **Parameter:**
| ``appname``    - The name of your application
| ``appversion`` - A string describing the version of your application like ``0.91.0``
| **Return:**
| (none)

You have to call this function *before* any other functions of the Commandkit.
**IMPORTANT:** You can not pass NULL to the arguments!

jetspace_add_cmd_line_argument
""""""""""""""""""""""""""""""

::

 void jetspace_add_cmd_line_argument(char sh, char *arg, int id, char *disc, JetSpaceCMDArgCallback cb, void *data);

| **Parameter:**
| ``sh``    - short argument like ``a`` or ``x``.
| ``arg``   - long argument like ``--anything`` or ``--xorg``.
| ``id``    - ID of this argument, passed to callback as identification. Can be any number.
| ``cb``    - JetSpaceCMDArgCallback which should be called when this argument is detected.
| ``data``  - Data which should be passed to the callback.
| **Return:**
| (none)

You can add as many arguments as you want. Please note that you can not use the two predefined arguments ``-h | --help`` or ``-v | --version``. If you pass ``0`` to ``sh`` this argument will
only have a long-form


Commandkit - Parsing
^^^^^^^^^^^^^^^^^^^^

jetspace_parse_cmd_line
"""""""""""""""""""""""

::

 bool jetspace_parse_cmd_line(int argc, char **argv);

| **Parameter:**
| ``argc`` - Number of command-line arguments.
| ``argv`` - Array of all command-line arguments.
| **Return:**
| ``bool`` - true if everything was successful.

You normally want to pass the ``argc`` and ``argv`` of the ``main`` function to this function, so the commandkit
can parse the arguments passed to your application.

Commandkit - Utility
^^^^^^^^^^^^^^^^^^^^

jetspace_cmd_line_print_help
"""""""""""""""""""""""""""""

::

 void jetspace_cmd_line_print_help(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

Print an automatically  generated help output to ``stdout``. Normally you do not need this function because ``-h | --help`` is handled by the commandkit, so you the help output will be done automatically.


Commandkit - Cleanup
^^^^^^^^^^^^^^^^^^^^

jetspace_cmd_line_free
""""""""""""""""""""""

::

 void jetspace_cmd_line_free(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

Free all allocated data from the Commandkit. You should call this after parsing the arguments. You cannot call any Commandkit functions after
this function, unless you call ``jetspace_cmd_line_init``.




Datatypes
---------

JetSpaceCMDArgCallback
^^^^^^^^^^^^^^^^^^^^^^

An callback function used for commandlike arguments::

 bool (*JetSpaceCMDArgCallback) (int argc, char **argv, int id, void *data);

| **Parameter:**
| ``argc``    - Number of arguments passed to ``jetspace_parse_cmd_line``.
| ``argv``    - Array of arguments passed to ``jetspace_parse_cmd_line``.
| ``id``      - ID of the detected argument.
| ``data``    - Data which was choosen in ``jetspace_add_cmd_line_argument``.
| ``data``    - Data which should be passed to the callback.
| **Return:**
| ``bool``    - return ``false`` if there was a problem and you want to stop parsing the arguments.


Compile
-------

All functions are defined in ``jetspace/commandkit.h``

To compile you need to link against jetspace-commandkit, so you normaly have to use ``-ljetspace-commandkit``.

Example Application
-------------------

::

 /*Public Domain (CC0) tool to test the commandkit
  *
  * Compile with: gcc example.c -o example -ljetspace-commandkitx
  * Author: Marius Messerschmidt
  */

 #include <jetspace/commandkit.h>
 #include <stdio.h>

 bool argcb(int argc, char **argv, int id, void *data)
 {
   printf("Recived arg %d with payload {%s | %d}\n", id, (char *) data, *(int *)data);

   return true;
 }

 int main(int argc, char **argv)
 {
   jetspace_cmd_line_init("TestApp", "1.0.2b");

   int x = 42;
   jetspace_add_cmd_line_argument('o', "other-example", 1, "Some ohter example action", argcb, &x);
   jetspace_add_cmd_line_argument('e', "example", 2, "Some example action", argcb, "box");

   jetspace_parse_cmd_line(argc,argv);
   jetspace_cmd_line_free();
   return 0;
 }
