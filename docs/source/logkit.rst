JetSpace Logkit
===============

Overview
--------

The Logkit is designed to be used for logging and debugging. By default it requires
GLib, but you can compile it from source with disabled GLib Interface.

It feauters an level driven logging API plus the possibility to control parameters of
the logging system via command line arguments.
It can also attach GDB to your running application depending on a debug level.

API
----

Logkit - Init
^^^^^^^^^^^^^

jetspace_logkit_init
""""""""""""""""""""

::

 void jetspace_logkit_init(int argc, char **argv);

| **Parameter:**
| ``argc`` - number of arguments passed in ``argv``
| ``argv`` - array of arguments
| **Return:**
| (none)

You normally want to pass the arguments from the ``main()`` function. You have to call this
function *before* any other functions of the Logkit.

jetspace_logkit_enable_glib_handler
"""""""""""""""""""""""""""""""""""

::

 void jetspace_logkit_enable_glib_handler(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

You can use this to redirect the output from Gtk/GLib function to the Logkit.

Logkit - Log-Level
^^^^^^^^^^^^^^^^^^

jetspace_logkit_set_log_level_from_environmet
""""""""""""""""""""""""""""""""""""""""""""""

::

 void jetspace_set_log_level_from_environment(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

Reads the ``LOGLEVEL`` environment variable to set the current log-level. It is highly recommended to
call this function, to give the users the opportunity to change the log-level of your application.

jetspace_logkit_set_log_level
""""""""""""""""""""""""""""""

::

 void jetspace_set_log_level(JetSpaceLogLevel x);

| **Parameter:**
| ``x`` - The JetSpaceLogLevel
| **Return:**
| (none)

Set the log-level of your application to a specific setting. You should not use
this to override the settings from the environment.

jetspace_logkit_get_log_level
"""""""""""""""""""""""""""""

::

 int jetspace_logkit_get_log_level(void)

| **Parameter:**
| (none)
| **Return:**
| ``int`` - JetSpaceLogLevel

Returns the current log-level of your application.

Logkit - Logging
^^^^^^^^^^^^^^^^^^

::

 void jetspace_debug(char *msg, ...);
 void jetspace_note(char *msg, ...);
 void jetspace_message(char *msg, ...);
 void jetspace_warning(char *msg, ...);
 void jetspace_error(char *msg, ...);
 void jetspace_critical(char *msg, ...);
 void jetspace_failure(char *msg, ...);

| **Parameter:**
| ``msg`` - Message to log, you can use markup like in ``printf``
| ``...`` - Variable list of arguments depending on the ``msg`` format
| **Return:**
| (none)

Log messages with the specific log-level. Please note, that this functions are just
wrapper functions for ``jetspace_log``.

::

 void jetspace_log(short lvl, char *msg, ...)

| **Parameter:**
| ``lvl`` - JetSpaceLogLevel to use
| ``msg`` - Message to log, you can use markup like in ``printf``
| ``...`` - Variable list of arguments depending on the ``msg`` format
| **Return:**
| (none)

Log Message with log-level ``lvl``. You should might not use this function. You
can use the wrapper functions above.

Logkit - Debug
^^^^^^^^^^^^^^^

jetspace_logkit_backtrace
""""""""""""""""""""""""""

::

 void jetspace_logkit_backtrace(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

Prints a back-trace to the default error output. You can use this function manually, but
it is automatically called by ``jetspace_logkit_debug_promt``.

jetspace_logkit_debug_promt
"""""""""""""""""""""""""""

::

 void jetspace_logkit_debug_promt(void);

| **Parameter:**
| (none)
| **Return:**
| (none)

Prints a selection to ``stdout`` where the user can switch between ``Exit``, ``Continue``, ``Attach to GDB`` or ``Backtrace``.
This function is called if the debug level is lower or equal to the level of the
current message.

Datatypes
---------

JetSpaceLogLevel
^^^^^^^^^^^^^^^^^

A valid log-level is one of the following::

 JETSPACE_LOG_LEVEL_DEBUG,
 JETSPACE_LOG_LEVEL_NOTE,
 JETSPACE_LOG_LEVEL_MESSAGE,
 JETSPACE_LOG_LEVEL_WARNING,
 JETSPACE_LOG_LEVEL_ERROR,
 JETSPACE_LOG_LEVEL_CRITICAL,
 JETSPACE_LOG_LEVEL_FAILURE


Command Line arguments
-----------------------

``--jetspace-debug-level <lvl>``

Use this argument to change the debug-level. This level is used to recognize at which
point the application should print a debug prompt.


``--jetspace-log-to-file <file>``

Redirects ``stderr`` to ``file``.


``--jetspace-logkit-version``

Print the version of the Logkit and exit the Application.

Compile
-------

All functions are defined in ``jetspace/logkit.h``

To compile your application with the Logkit you can use -ljetspace-logkit. **After** this you
need to call ``pkg-config --libs --cflags glib-2.0`` to use GLib.

To get a better backtrace, you should use the complier argument ``-rdynamic``.

Example Application
-------------------

::

 /*Public Domain (CC0) tool to test the logkit
  *
  * Compile with: gcc example.c -o example -ljetspace-logkit `pkg-config --cflags --libs glib-2.0`
  * Author: Marius Messerschmidt
  */

 #include <jetspace/logkit.h>

 int main(int argc, char **argv)
 {
     jetspace_logkit_init(argc, argv);
     jetspace_set_log_level_from_enviroment();

     printf("Current Loglevel is :%d\n", jetspace_get_log_level());
     jetspace_warning("Test Warning with variable parameter %.2f", (float) 10/3);

     return 0;
 }
