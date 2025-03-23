# CORDET Framework
[![Build Status](https://github.com/pnp-software/cordetfw/workflows/Build/badge.svg)](https://github.com/pnp-software/cordetfw/actions)

The CORDET Framework is a software framework for service-oriented applications. It defines an application in terms of the services it provides to other applications and in terms of the services it uses from other applications. A service is implemented by a set of commands through which an application is asked to perform certain activities and by a set of reports through which an application gives visibility over its internal state. The CORDET Framework defines the components to receive, send, distribute, and process commands and reports. The CORDET service concepts supports the definition of distributed systems where individual applications residing on distribution nodes interact with each other by exchanging commands and reports. 

The specification of the CORDET Framework is language-independent. This project provides a C-language implementation of the CORDET Framework. Its chief characteristics are:

- **Well-Defined Semantics**: unambiguously defined behaviour.
- **Minimal Memory Requirements**: core module footprint of around 20 kBytes.
- **Small CPU Demands**: efficient implementation in C.
- **Excellent Scalability**: memory footprint and CPU demands are independent of number of supported services.
- **High Reliability**: test suite with 100% code, branch, and condition coverage.
- **Formal Specification**: user requirements formally specify the implementation.
- **Requirement Traceability**: requirements individually traced to implementation and verification evidence.
- **Documented Code**: doxygen documentation for all the source code.

These characteristics make the C2 Implementation especially well-suited for use in embedded and mission-critical applications. 

The C2 Implementation of the CORDET Framework has been used by the Dept. of Astrophysics at the University of Vienna for the development of the payload software of the **CHEOPS satellite**; it is being used for the development of a payload application on the **SMILE satellite**; and it is baselined for use in the development of a payload application on the **ARIEL satellite**.

# Web Site
An introduction to the CORDET Framework and its documentation can be found [here](https://pnp-software.com/cordetfw).

# PUS Extension
The Packet Utilization Standard (PUS) has been introduced by the European Space Agency (ESA) to define the protocol through which on-board applications make their services available to each other and to the ground. The CORDET Framework uses the service concept of the PUS. Its **PUS Extension** provides implementations for the most commonly used PUS services. The PUS Extension of the CORDET Framework is currently under development and will be published in a dedicated repository in the near future. Access to the development version of the PUS Extension of the CORDET Framework is available [on request](mailto:pnp-software@pnp-software.com).

# Releases
* Version [1.0.0](http://pnp-software.com/cordetfw/CordetFw_C2_Impl_MPLv2_1.0.0_MPLv2.zip).
* Version [1.1.0](http://pnp-software.com/cordetfw/CordetFw_C2_Impl_MPLv2_1.1.0.zip). 

# Ownership

The owner of the project is [P&P Software GmbH](http://pnp-software.com/). 

# License

Free use of this software is granted under the terms of the Mozilla Public Licence v2, see [LICENSE](LICENSE).
