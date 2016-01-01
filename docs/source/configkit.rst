JetSpace Configkit
===================

Overview
--------

The cofigkit is used to parse simple configuration files. These files must have
a specific syntax as shown below:

::
 // Some comment
 NAME:value
 //some other comment
 variable/name: some longer value...

So as you can see, comments start with two slashes (``//``) and variable names are
on the left side, followed by a colon, followed by the value. The value can be as long as ONE line, so
in theory the length is infinite.

API
----

The API contains two ways of parsing: You can either use specific names and lookup/set the values,
or you can get one by one variables.

Configkit - Specific
^^^^^^^^^^^^^^^^^^^^

//TODO

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

All functions are defined in ``jetspace/configkit.h``

To compile you need to link against jetspace-configkit, so you normally have to use ``-ljetspace-configkit``.

Example Application
-------------------

::

 /*Public Domain (CC0) tool to test the configkit
  *
  * Compile with: gcc example.c -o example -ljetspace-configkit
  * Author: Marius Messerschmidt
  */

  //TODO
