CHEOPS Instrument Application {#mainpage}
=============================

IASW Demo Application
---------------------

This is the CHEOPS Instrument Application Software (IASW) demo application. The
implementation is according to the following document.

- CHEOPS-PNP-INST-DD-001, Revision 0.2

Overview
--------

The CHEOPS Instrument is a provider of services to the CHEOPS On-Board Computer
(OBC) and a user of the services of the Sensor Electronics Module (SEM). The
IASW is the part of the CHEOPS Instrument Flight Software (IFSW) which
implements the services provided to the OBC and uses the services provided by
the SEM. 

Scope of the Demo Application
-----------------------------

This demo application provides only a subset of the final IASW application.
More specifically, it implements the following telecommand (TM) and telemetry
(TM) packets.

- Telecommand packet (17,1), Perform Connection Test
- Telemetry packet (17,2), Link Connection Report

This demo application serves as an illustration for an instantiation of the
Cordet Framework and should serve as a starting point for the final IASW
application. It can either be extended directly, or can be used for reference
only.

Applications
------------

This delivery consists of three different applications, covering different
parts of the final setup. Each application can be started as an executable. 

### IASW

This is the main application that implements the Instrument Software
Application. In addition, it provides an emulation of the Instrument Basic
Software (IBSW). The IBSW will eventually be its own application.

The IASW runs in an endless loop, executing all required commands in every
loop.

The name of the executable is `criademo`.

### Ground

This is an emulation of the Ground station for the packets defined above. It
runs in a one-shot mode, where it sends the packets and checks for a correct
response.

The name of the executable is `criademogrnd`.

### SEM

This is an emulation of the Sensor Electronics Module. It also runs in one-shot
mode, where it waits for a certain, predefined command and sends a predefined
response.

The name of the executable is `criademosem`.

IASW and IBSW
-------------

As noted above, the IASW application consists of part of the IASW
implementation, and of an emulation of the IBSW. These two parts eventually
will be deployed in separate applications. Therefore, it is desirable to
separate the source code in this demo application.

To understand the separation, it should be noted that the IASW application is
purely passive. That means that it always receives its execution triggers from
external applications. In the case of the IASW, this external application is
the IBSW.  Therefore, a natural separation is to put the code that emulates the
IBSW into the main module in CrIaDemoMain.c.

In addition, the external interfaces can be found in CrIaIasw.h.

- Demo specific interface which will not be present in the final application.
- Interface provided by the IASW and called by the IASW.
- Interface provided by IBSW and called by the IASW.
- Interface provided by the HK storage buffer.

All other files only contain code that should be available in the final IASW
application.

Types
-----

All types used in the application are defined through `typedef`s. The following
assumptions are made regarding the sizes of the types.

- A byte consists of 8 bits
- `char` is 1 byte long
- `short` is 2 bytes long
- `int` is 4 bytes long

If this assumptions are incorrect for the final applications, then the
`typedef`s must be corrected.

Endianness
----------

The interpretation of multi-byte values (i.e. the endianness) for the final
IASW application is already known and specified. 

To make the demo application portable, it converts the multi-byte values to the
correct host representation by using the functions `htons` (host to network
conversion, and  `ntohs` (network to host conversion) for short values.

The final application presumably does not need to do this anymore. Or, if some
conversion is required, it is unclear what the respective functions will be.
Therefore, in CrIaPckt.c, whenever such a conversion is done, a TODO has been
added.

Directory Layout
----------------

The code is delivered as a self contained package with the following top level folders.

- `fwprofile` which consists of the source code for the FW Profile library.
- `iasw` which consists of the source code for the Cordet Framework and the IASW demo application.

Within each of these two directories, there is a `build` directory which holds
the compilation and documentation output.

The two directories must be placed into the same folder, since the IASW source
code references the FW Profile source code. It is however irrelevant where in
the filesystem the two folders are located.

Dependencies
------------

Besides a compatible C compiler, the IASW demo application has the following dependencies.

- [tup](http://gittup.org/tup/)
- [nanomsg](http://nanomsg.org/)
- [CORDET Framework](http://pnp-software.com/cordetfw/)
- [FW Profile](http://pnp-software.com/fwprofile/)

The first dependency, tup, is a Makefile replacement and is used to build the
application. The second dependency, nanomsg, is a runtime dependency and is
used for communication between the different applications in the IASW demo
setup.

Both programs are straight forward to install on a Posix compatible machine.
Instructions can be found on their web pages.

The other two dependencies, the Cordet Framework and the FW Profile are the
foundation on which the IASW is built. These programs are created, maintained
and provided by P&P Software. The relevant code for both programs is included
in the delivery.
 
Building the IASW Demo
----------------------

In order to follow the steps below, it is required to install `tup` first.

### Building the FW Profile

As a first step, the FW Profile library must be built. For this, change to the
`fwprofile` folder and type

~~~
tup init
tup
~~~

`tup init` is only required the first time `tup` is run. Later builds just
require the command `tup`.

This will build a static library called `build/libfwprofile.a`. This library
will be used by the IASW application.

### Building the IASW applications

In order to build the IASW demo applications, change to the `iasw` folder and
type

~~~
tup init
tup
~~~

This builds all three applications. Note that this build step requires the FW
Profile to be available (see previous step), as well as `nanomsg` to be
installed on the system.

- The IASW demo executable is in `build/CrIaDemo/criademo`
- The Ground demo executable is in `build/CrIaDemoGrnd/criademogrnd`
- The SEM demo executable is in `build/CrIaDemoSem/criademosem`

Building the Documentation
--------------------------

Documentation is provided in the form of doxygen comments. In order to build
the documentation, the `doxygen` program must be available. Note that a
relatively recent version (>= 1.8.0) is required, because the documentation
makes use of the included Markdown support.

The documentation can be build by changing to the correct directory and run the doxygen command.

~~~
cd iasw/build/doxygen/
doxygen
~~~

The output will then be available in the folder `iasw/build/doxygen/html` with
an `index.html` file as a starting point.

Test Cases
----------

The demo application runs two tests.

The first test sends a (17,1) telecommand packet to the IASW application and
checks for a correct (17,2) telemetry packet in response.

The second test sends a (17,1) telecommand packet to the SEM application, and
checks for a correct (17,2) telemetry packet in response. This check verifies
that the routing mechanism works correctly, because the telecommand and the
telemetry packets are routed through the IASW application.

Run the tests
-------------

The tests can be run by executing the demo applications in the following order.

1. Run `build/CrIaDemo/criademo`. This runs the IASW software with the cyclical
activation.
2. Run `build/CrIaDemoSem/criademosem`. This starts the SEM emulation for
telecommand (17,1).
3. Run `build/CrIaDemoGrnd/criademogrnd`. This sends the two (17,1) telecommand
packets (one to the IASW, and one to the SEM) and checks for the expected
telemetry packets.

Check the output from the `criademogrnd` and `criademosem` executables. If all
goes well, the two executables should print an output and terminate
successfully. If an error occurs, then the output of an assertion is shown.

Note that after a test cycle, all applications must be restarted. Otherwise the
sequence counter no longer match.

TODOs
-----

Some tasks are not yet completed in the demo application. Some of them cannot
be completed because they must be implemented in terms of the final hardware or
OS capabilities. Other tasks are completed because they are not relevant for
the demo application.

All todos are marked in the doxygen comments and can be viewed in the html
output in the section `Related Pages`.
