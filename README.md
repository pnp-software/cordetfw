# CORDET Framework

The CORDET Framework is a software framework for service-oriented applications. The CORDET Framework defines an application in terms of the services it provides to other applications and in terms of the services it uses from other applications. A service is implemented by a set of commands through which an application is asked to perform certain activities and by a set of reports through which an application gives visibility over its internal state. The CORDET Framework defines the components to receive, send, distribute, and process commands and reports. The CORDET service concepts supports the definition of distributed systems where individual applications residing on distribution nodes interact with each other by exchanging commands and reports.

The specification of the CORDET Framework is language-independent. This project provides a C-language implementation of the CORDET Framework. Its chief characteristics are:

- Well-Defined Semantics: unambiguously defined behaviour.
- Minimal Memory Requirements: core module footprint of around 20 kBytes.
- Small CPU Demands: efficient implementation in C.
- Excellent Scalability: memory footprint and CPU demands are independent of number of supported services.
- High Reliability: test suite with 100% code, branch, and condition coverage.
- Formal Specification: user requirements formally specify the implementation.
- Requirement Traceability: all requirements individually traced to implementation and verification evidence.
- Documented Code: doxygen documentation for all the source code.
- Demo Application: complete application demonstrating capabilities and mode of use. 

These characteristics make the C2 Implementation especially well-suited for use in embedded and mission-critical applications. 

# Releases
* Version [0.7.1](http://pnp-software.com/cordetfw/CordetFw_C2_Impl_LGPLv3_0.7.1.zip), LGPLv3

# Ownership

The owner of the project is [P&P Software GmbH](http://pnp-software.com/). 

# License

Free use of this software is granted under the terms of the GNU Lesser General Public License (LGPL) v3, see LICENSE.
