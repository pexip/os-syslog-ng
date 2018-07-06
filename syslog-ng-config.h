#ifndef _SYSLOG_NG_CONFIG_H
#define _SYSLOG_NG_CONFIG_H 1
 
/* syslog-ng-config.h. Generated automatically at end of configure. */
/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Enable debugging */
#ifndef SYSLOG_NG_ENABLE_DEBUG
#define SYSLOG_NG_ENABLE_DEBUG 0
#endif

/* Enable environment wrapper support */
#ifndef SYSLOG_NG_ENABLE_ENV_WRAPPER
#define SYSLOG_NG_ENABLE_ENV_WRAPPER 0
#endif

/* Enable gcc profiling */
#ifndef SYSLOG_NG_ENABLE_GPROF
#define SYSLOG_NG_ENABLE_GPROF 0
#endif

/* Enable IPv6 support */
#ifndef SYSLOG_NG_ENABLE_IPV6
#define SYSLOG_NG_ENABLE_IPV6 1
#endif

/* Support libmongo-client non-URI MongoDB options */
#ifndef SYSLOG_NG_ENABLE_LEGACY_MONGODB_OPTIONS
#define SYSLOG_NG_ENABLE_LEGACY_MONGODB_OPTIONS 1
#endif

/* Enable libuuid support */
#ifndef SYSLOG_NG_ENABLE_LIBUUID
#define SYSLOG_NG_ENABLE_LIBUUID 0
#endif

/* Enable Linux capability management support */
#ifndef SYSLOG_NG_ENABLE_LINUX_CAPS
#define SYSLOG_NG_ENABLE_LINUX_CAPS 0
#endif

/* Enable memtrace */
#ifndef SYSLOG_NG_ENABLE_MEMTRACE
#define SYSLOG_NG_ENABLE_MEMTRACE 0
#endif

/* Enable spoof source support */
#ifndef SYSLOG_NG_ENABLE_SPOOF_SOURCE
#define SYSLOG_NG_ENABLE_SPOOF_SOURCE 1
#endif

/* Enable systemd support */
#ifndef SYSLOG_NG_ENABLE_SYSTEMD
#define SYSLOG_NG_ENABLE_SYSTEMD 1
#endif

/* Enable TCP wrapper support */
#ifndef SYSLOG_NG_ENABLE_TCP_WRAPPER
#define SYSLOG_NG_ENABLE_TCP_WRAPPER 1
#endif

/* set LD_LIBRARY_PATH to this value */
/* #undef ENV_LD_LIBRARY_PATH */

/* Define to 1 if you have the external `altzone' variable. */
/* #undef HAVE_ALTZONE */

/* define if your platform has a broken pread/pwrite (e.g. HP-UX) */
/* #undef HAVE_BROKEN_PREAD */

/* Define to 1 if you have the `clock_gettime' function. */
#ifndef SYSLOG_NG_HAVE_CLOCK_GETTIME
#define SYSLOG_NG_HAVE_CLOCK_GETTIME 1
#endif

/* Whether you have msg_control field in msghdr in socket.h */
#ifndef SYSLOG_NG_HAVE_CTRLBUF_IN_MSGHDR
#define SYSLOG_NG_HAVE_CTRLBUF_IN_MSGHDR 1
#endif

/* Define to 1 if you have the external `daylight' variable. */
#ifndef SYSLOG_NG_HAVE_DAYLIGHT
#define SYSLOG_NG_HAVE_DAYLIGHT 1
#endif

/* Define to 1 if you have the declaration of `tzname', and to 0 if you don't.
   */
/* #undef HAVE_DECL_TZNAME */

/* Define to 1 if you have the <dlfcn.h> header file. */
#ifndef SYSLOG_NG_HAVE_DLFCN_H
#define SYSLOG_NG_HAVE_DLFCN_H 1
#endif

/* Define to 1 if you have the <door.h> header file. */
/* #undef HAVE_DOOR_H */

/* Specifies whether the environ global variable exists */
#ifndef SYSLOG_NG_HAVE_ENVIRON
#define SYSLOG_NG_HAVE_ENVIRON 1
#endif

/* Define to 1 if you have the `getaddrinfo' function. */
#ifndef SYSLOG_NG_HAVE_GETADDRINFO
#define SYSLOG_NG_HAVE_GETADDRINFO 1
#endif

/* Define to 1 if you have the `getnameinfo' function. */
#ifndef SYSLOG_NG_HAVE_GETNAMEINFO
#define SYSLOG_NG_HAVE_GETNAMEINFO 1
#endif

/* Define to 1 if you have the <getopt.h> header file. */
#ifndef SYSLOG_NG_HAVE_GETOPT_H
#define SYSLOG_NG_HAVE_GETOPT_H 1
#endif

/* Define to 1 if you have the `getopt_long' function. */
#ifndef SYSLOG_NG_HAVE_GETOPT_LONG
#define SYSLOG_NG_HAVE_GETOPT_LONG 1
#endif

/* Define to 1 if you have the `getutent' function. */
#ifndef SYSLOG_NG_HAVE_GETUTENT
#define SYSLOG_NG_HAVE_GETUTENT 1
#endif

/* Define to 1 if you have the `getutxent' function. */
#ifndef SYSLOG_NG_HAVE_GETUTXENT
#define SYSLOG_NG_HAVE_GETUTXENT 1
#endif

/* Define to 1 if you have the `gmtime_r' function. */
#ifndef SYSLOG_NG_HAVE_GMTIME_R
#define SYSLOG_NG_HAVE_GMTIME_R 1
#endif

/* Define to 1 if you have the `g_mapped_file_unref' function. */
#ifndef SYSLOG_NG_HAVE_G_MAPPED_FILE_UNREF
#define SYSLOG_NG_HAVE_G_MAPPED_FILE_UNREF 1
#endif

/* Define to 1 if you have the `inet_aton' function. */
#ifndef SYSLOG_NG_HAVE_INET_ATON
#define SYSLOG_NG_HAVE_INET_ATON 1
#endif

/* Define to 1 if you have the `inet_ntoa' function. */
#ifndef SYSLOG_NG_HAVE_INET_NTOA
#define SYSLOG_NG_HAVE_INET_NTOA 1
#endif

/* Define to 1 if you have the <inttypes.h> header file. */
#ifndef SYSLOG_NG_HAVE_INTTYPES_H
#define SYSLOG_NG_HAVE_INTTYPES_H 1
#endif

/* Define to 1 if you have the `pthread' library (-lpthread). */
/* #undef HAVE_LIBPTHREAD */

/* Define to 1 if you have the `localtime_r' function. */
#ifndef SYSLOG_NG_HAVE_LOCALTIME_R
#define SYSLOG_NG_HAVE_LOCALTIME_R 1
#endif

/* Define to 1 if you have the <memory.h> header file. */
#ifndef SYSLOG_NG_HAVE_MEMORY_H
#define SYSLOG_NG_HAVE_MEMORY_H 1
#endif

/* Define to 1 if you have the `memrchr' function. */
#ifndef SYSLOG_NG_HAVE_MEMRCHR
#define SYSLOG_NG_HAVE_MEMRCHR 1
#endif

/* have modern utmp/utmpx format */
#ifndef SYSLOG_NG_HAVE_MODERN_UTMP
#define SYSLOG_NG_HAVE_MODERN_UTMP 1
#endif

/* O_LARGEFILE is present */
#ifndef SYSLOG_NG_HAVE_O_LARGEFILE
#define SYSLOG_NG_HAVE_O_LARGEFILE 1
#endif

/* Define to 1 if you have the `pread' function. */
#ifndef SYSLOG_NG_HAVE_PREAD
#define SYSLOG_NG_HAVE_PREAD 1
#endif

/* have PR_SET_KEEPCAPS */
#ifndef SYSLOG_NG_HAVE_PR_SET_KEEPCAPS
#define SYSLOG_NG_HAVE_PR_SET_KEEPCAPS 1
#endif

/* Define to 1 if you have the <pthread.h> header file. */
/* #undef HAVE_PTHREAD_H */

/* Define to 1 if you have the `pwrite' function. */
#ifndef SYSLOG_NG_HAVE_PWRITE
#define SYSLOG_NG_HAVE_PWRITE 1
#endif

/* SO_ACCEPTCONN is present */
#ifndef SYSLOG_NG_HAVE_SO_ACCEPTCONN
#define SYSLOG_NG_HAVE_SO_ACCEPTCONN 1
#endif

/* Define to 1 if you have the <stdint.h> header file. */
#ifndef SYSLOG_NG_HAVE_STDINT_H
#define SYSLOG_NG_HAVE_STDINT_H 1
#endif

/* Define to 1 if you have the <stdlib.h> header file. */
#ifndef SYSLOG_NG_HAVE_STDLIB_H
#define SYSLOG_NG_HAVE_STDLIB_H 1
#endif

/* Define to 1 if you have the `strcasestr' function. */
#ifndef SYSLOG_NG_HAVE_STRCASESTR
#define SYSLOG_NG_HAVE_STRCASESTR 1
#endif

/* Define to 1 if you have the `strdup' function. */
#ifndef SYSLOG_NG_HAVE_STRDUP
#define SYSLOG_NG_HAVE_STRDUP 1
#endif

/* Define to 1 if you have the <strings.h> header file. */
#ifndef SYSLOG_NG_HAVE_STRINGS_H
#define SYSLOG_NG_HAVE_STRINGS_H 1
#endif

/* Define to 1 if you have the <string.h> header file. */
#ifndef SYSLOG_NG_HAVE_STRING_H
#define SYSLOG_NG_HAVE_STRING_H 1
#endif

/* Define to 1 if you have the <stropts.h> header file. */
#ifndef SYSLOG_NG_HAVE_STROPTS_H
#define SYSLOG_NG_HAVE_STROPTS_H 1
#endif

/* Define to 1 if you have the `strtoimax' function. */
#ifndef SYSLOG_NG_HAVE_STRTOIMAX
#define SYSLOG_NG_HAVE_STRTOIMAX 1
#endif

/* Define to 1 if you have the `strtok_r' function. */
#ifndef SYSLOG_NG_HAVE_STRTOK_R
#define SYSLOG_NG_HAVE_STRTOK_R 1
#endif

/* Define to 1 if you have the `strtol' function. */
#ifndef SYSLOG_NG_HAVE_STRTOL
#define SYSLOG_NG_HAVE_STRTOL 1
#endif

/* Define to 1 if you have the `strtoll' function. */
#ifndef SYSLOG_NG_HAVE_STRTOLL
#define SYSLOG_NG_HAVE_STRTOLL 1
#endif

/* Define to 1 if the system has the type `struct cmsgcred'. */
/* #undef HAVE_STRUCT_CMSGCRED */

/* struct sockaddr_storage is present on your system */
#ifndef SYSLOG_NG_HAVE_STRUCT_SOCKADDR_STORAGE
#define SYSLOG_NG_HAVE_STRUCT_SOCKADDR_STORAGE 1
#endif

/* Whether you have tm_gmtoff field in struct tm */
#ifndef SYSLOG_NG_HAVE_STRUCT_TM_TM_GMTOFF
#define SYSLOG_NG_HAVE_STRUCT_TM_TM_GMTOFF 1
#endif

/* Define to 1 if `tm_zone' is a member of `struct tm'. */
#ifndef SYSLOG_NG_HAVE_STRUCT_TM_TM_ZONE
#define SYSLOG_NG_HAVE_STRUCT_TM_TM_ZONE 1
#endif

/* Define to 1 if the system has the type `struct ucred'. */
#ifndef SYSLOG_NG_HAVE_STRUCT_UCRED
#define SYSLOG_NG_HAVE_STRUCT_UCRED 1
#endif

/* Define to 1 if you have the <sys/capability.h> header file. */
#ifndef SYSLOG_NG_HAVE_SYS_CAPABILITY_H
#define SYSLOG_NG_HAVE_SYS_CAPABILITY_H 1
#endif

/* Define to 1 if you have the <sys/prctl.h> header file. */
#ifndef SYSLOG_NG_HAVE_SYS_PRCTL_H
#define SYSLOG_NG_HAVE_SYS_PRCTL_H 1
#endif

/* Define to 1 if you have the <sys/stat.h> header file. */
#ifndef SYSLOG_NG_HAVE_SYS_STAT_H
#define SYSLOG_NG_HAVE_SYS_STAT_H 1
#endif

/* Define to 1 if you have the <sys/strlog.h> header file. */
/* #undef HAVE_SYS_STRLOG_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#ifndef SYSLOG_NG_HAVE_SYS_TYPES_H
#define SYSLOG_NG_HAVE_SYS_TYPES_H 1
#endif

/* Define to 1 if you have the <tcpd.h> header file. */
#ifndef SYSLOG_NG_HAVE_TCPD_H
#define SYSLOG_NG_HAVE_TCPD_H 1
#endif

/* "Whether Transport Layer Security is supported by the system" */
#ifndef SYSLOG_NG_HAVE_THREAD_KEYWORD
#define SYSLOG_NG_HAVE_THREAD_KEYWORD 1
#endif

/* Define to 1 if you have the external `timezone' variable. */
#ifndef SYSLOG_NG_HAVE_TIMEZONE
#define SYSLOG_NG_HAVE_TIMEZONE 1
#endif

/* Define to 1 if your `struct tm' has `tm_zone'. Deprecated, use
   `HAVE_STRUCT_TM_TM_ZONE' instead. */
#ifndef SYSLOG_NG_HAVE_TM_ZONE
#define SYSLOG_NG_HAVE_TM_ZONE 1
#endif

/* Define to 1 if you don't have `tm_zone' but do have the external array
   `tzname'. */
/* #undef HAVE_TZNAME */

/* Define to 1 if you have the <unistd.h> header file. */
#ifndef SYSLOG_NG_HAVE_UNISTD_H
#define SYSLOG_NG_HAVE_UNISTD_H 1
#endif

/* Define to 1 if you have the <utmpx.h> header file. */
#ifndef SYSLOG_NG_HAVE_UTMPX_H
#define SYSLOG_NG_HAVE_UTMPX_H 1
#endif

/* Define to 1 if you have the <utmp.h> header file. */
#ifndef SYSLOG_NG_HAVE_UTMP_H
#define SYSLOG_NG_HAVE_UTMP_H 1
#endif

/* java module search path */
#ifndef SYSLOG_NG_JAVA_MODULE_PATH
#define SYSLOG_NG_JAVA_MODULE_PATH "${exec_prefix}/lib/syslog-ng/java-modules"
#endif

/* "Disable systemd-journal source" */
#ifndef SYSLOG_NG_JOURNALD_OFF
#define SYSLOG_NG_JOURNALD_OFF 0
#endif

/* "Enable systemd-journal source if journald is available" */
#ifndef SYSLOG_NG_JOURNALD_OPTIONAL
#define SYSLOG_NG_JOURNALD_OPTIONAL 1
#endif

/* "Force systemd-journal source to use system's journald" */
#ifndef SYSLOG_NG_JOURNALD_SYSTEM
#define SYSLOG_NG_JOURNALD_SYSTEM 2
#endif

/* Required license version */
#ifndef SYSLOG_NG_LICENSE_VERSION
#define SYSLOG_NG_LICENSE_VERSION ""
#endif

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#ifndef SYSLOG_NG_LT_OBJDIR
#define SYSLOG_NG_LT_OBJDIR ".libs/"
#endif

/* module search path */
#ifndef SYSLOG_NG_MODULE_PATH
#define SYSLOG_NG_MODULE_PATH "${exec_prefix}/lib/syslog-ng"
#endif

/* Define to the address where bug reports for this package should be sent. */
#ifndef SYSLOG_NG_PACKAGE_BUGREPORT
#define SYSLOG_NG_PACKAGE_BUGREPORT ""
#endif

/* package name */
#ifndef SYSLOG_NG_PACKAGE_NAME
#define SYSLOG_NG_PACKAGE_NAME "syslog-ng"
#endif

/* Define to the full name and version of this package. */
#ifndef SYSLOG_NG_PACKAGE_STRING
#define SYSLOG_NG_PACKAGE_STRING "syslog-ng 3.8.1"
#endif

/* Define to the one symbol short name of this package. */
#ifndef SYSLOG_NG_PACKAGE_TARNAME
#define SYSLOG_NG_PACKAGE_TARNAME "syslog-ng"
#endif

/* Define to the home page for this package. */
#ifndef SYSLOG_NG_PACKAGE_URL
#define SYSLOG_NG_PACKAGE_URL ""
#endif

/* Define to the version of this package. */
#ifndef SYSLOG_NG_PACKAGE_VERSION
#define SYSLOG_NG_PACKAGE_VERSION "3.8.1"
#endif

/* include directory */
#ifndef SYSLOG_NG_PATH_CONFIG_INCLUDEDIR
#define SYSLOG_NG_PATH_CONFIG_INCLUDEDIR "${datadir}/syslog-ng/include"
#endif

/* data directory */
#ifndef SYSLOG_NG_PATH_DATADIR
#define SYSLOG_NG_PATH_DATADIR "${datarootdir}"
#endif

/* data root directory */
#ifndef SYSLOG_NG_PATH_DATAROOTDIR
#define SYSLOG_NG_PATH_DATAROOTDIR "${prefix}/share"
#endif

/* execprefix directory */
#ifndef SYSLOG_NG_PATH_EXECPREFIX
#define SYSLOG_NG_PATH_EXECPREFIX "${prefix}"
#endif

/* libexec directory */
#ifndef SYSLOG_NG_PATH_LIBEXECDIR
#define SYSLOG_NG_PATH_LIBEXECDIR "${exec_prefix}/libexec"
#endif

/* local state directory */
#ifndef SYSLOG_NG_PATH_LOCALSTATEDIR
#define SYSLOG_NG_PATH_LOCALSTATEDIR "${prefix}/var"
#endif

/* module installation directory */
#ifndef SYSLOG_NG_PATH_MODULEDIR
#define SYSLOG_NG_PATH_MODULEDIR "${exec_prefix}/lib/syslog-ng"
#endif

/* local state directory */
#ifndef SYSLOG_NG_PATH_PIDFILEDIR
#define SYSLOG_NG_PATH_PIDFILEDIR "${localstatedir}"
#endif

/* prefix directory */
#ifndef SYSLOG_NG_PATH_PREFIX
#define SYSLOG_NG_PATH_PREFIX "/usr/local"
#endif

/* SCL directory */
#ifndef SYSLOG_NG_PATH_SCLDIR
#define SYSLOG_NG_PATH_SCLDIR "${datadir}/syslog-ng/include/scl"
#endif

/* sysconfdir */
#ifndef SYSLOG_NG_PATH_SYSCONFDIR
#define SYSLOG_NG_PATH_SYSCONFDIR "${prefix}/etc"
#endif

/* timezone base directory */
/* #undef PATH_TIMEZONEDIR */

/* XSD directory */
#ifndef SYSLOG_NG_PATH_XSDDIR
#define SYSLOG_NG_PATH_XSDDIR "${datadir}/syslog-ng/xsd"
#endif

/* source revision */
#ifndef SYSLOG_NG_SOURCE_REVISION
#define SYSLOG_NG_SOURCE_REVISION ""
#endif

/* Define to 1 if you have the ANSI C header files. */
#ifndef SYSLOG_NG_STDC_HEADERS
#define SYSLOG_NG_STDC_HEADERS 1
#endif

/* Systemd-journal support mode */
#ifndef SYSLOG_NG_SYSTEMD_JOURNAL_MODE
#define SYSLOG_NG_SYSTEMD_JOURNAL_MODE SYSLOG_NG_JOURNALD_SYSTEM
#endif

/* Define to 1 if your <sys/time.h> declares `struct tm'. */
/* #undef TM_IN_SYS_TIME */

/* version number */
#ifndef SYSLOG_NG_VERSION
#define SYSLOG_NG_VERSION "3.8.1"
#endif

/* Include the compile date in the binary */
#ifndef SYSLOG_NG_WITH_COMPILE_DATE
#define SYSLOG_NG_WITH_COMPILE_DATE 1
#endif

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#ifndef SYSLOG_NG_YYTEXT_POINTER
#define SYSLOG_NG_YYTEXT_POINTER 1
#endif

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */
 
/* once: _SYSLOG_NG_CONFIG_H */
#endif
