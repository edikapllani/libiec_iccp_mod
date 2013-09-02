/*
 * config.h
 *
 * Contains global defines to configure the stack. You need to recompile the stack to make
 * changes effective (make clean; make)
 *
 */

#ifndef STACK_CONFIG_H_
#define STACK_CONFIG_H_

/* print debugging information with printf */
#define DEBUG 1

#define STATIC_MODEL 1

/* Maximum MMS PDU SIZE - default is 65000 */
//#define MMS_MAXIMUM_PDU_SIZE 65000
//
#define MMS_MAXIMUM_PDU_SIZE 16000
//TODO: sage


/* number of data sets per LN if static option is set */
#define MMS_ALLOW_CLIENTS_TO_CREATE_ASSOCIATION_SPECIFIC_DATASETS 0
#define MMS_NUMBER_OF_ASSOCIATION_SPECIFIC_DATASETS 10 /* -1 for no limit */
#define MMS ALLOW_CLIENTS_TO_CREATE_DOMAIN_DATASETS 1
#define MMS_NUMBER_OF_DOMAIN_DATASETS 10 /* -1 for no limit */

/* number of concurrent TCP connections, -1 for no limit */
#define NUMBER_OF_TCP_CONNECTIONS -1

/* activate TCP keep alive mechanism. 1 -> activate */
#define CONFIG_ACTIVATE_TCP_KEEPALIVE 1

/* time (in s) between last message and first keepalive message */
#define CONFIG_TCP_KEEPALIVE_IDLE 20

/* time between subsequent keepalive messages if no ack received */
#define CONFIG_TCP_KEEPALIVE_INTERVAL 5

/* number of not missing keepalive responses until socket is considered dead */
#define CONFIG_TCP_KEEPALIVE_CNT 3

/* maximum COTP (ISO 8073) TPDU size - valid range is 1024 - 16384 */
#define CONFIG_COTP_MAX_TPDU_SIZE 16394

/* timeout while reading from TCP stream in ms */
#define CONFIG_TCP_READ_TIMEOUT_MS 1000

/* Ethernet interface ID for GOOSE and SV */
#define CONFIG_ETHERNET_INTERFACE_ID "eth0"

/* Set to 1 to include GOOSE support in the build. Otherwise set to 0 */
#define CONFIG_INCLUDE_GOOSE_SUPPORT 1

#ifdef _WIN32

/* GOOSE will be disabled for Windows if ethernet support (winpcap) is not available */
#ifdef EXCLUDE_ETHERNET_WINDOWS
#warning disable GOOSE support
#ifdef CONFIG_INCLUDE_GOOSE_SUPPORT
#undef CONFIG_INCLUDE_GOOSE_SUPPORT
#endif
#define CONFIG_INCLUDE_GOOSE_SUPPORT 0
#define CONFIG_INCUDE_ETHERNET_WINDOWS 0
#else
#define CONFIG_INCLUDE_ETHERNET_WINDOWS 1
#undef CONFIG_ETHERNET_INTERFACE_ID
#define CONFIG_ETHERNET_INTERFACE_ID "0"
#endif
#endif

/* The GOOSE retransmission interval in ms for the stable condition - i.e. no monitored value changed */
#define CONFIG_GOOSE_STABLE_STATE_TRANSMISSION_INTERVAL 5000

/* The default value for the priority field of the 802.1Q header (allowed range 0-7) */
#define CONFIG_GOOSE_DEFAULT_PRIORITY 4

/* The default value for the VLAN ID field of the 802.1Q header - the allowed range is 2-4096 or 0 if VLAN/priority is not used */
#define CONFIG_GOOSE_DEFAULT_VLAN_ID 0

/* Configure the 16 bit APPID field in the GOOSE header */
#define CONFIG_GOOSE_DEFAULT_APPID 0x1000

/* Default destination MAC address for GOOSE */
#define CONFIG_GOOSE_DEFAULT_DST_ADDRESS {0x01, 0x0c, 0xcd, 0x01, 0x00, 0x01}

/* Enable datasets */
#define CONFIG_DATASETS 1

/* Enable reporting - Note reporting also includes datasets */
//#define CONFIG_REPORTING 0

/* Definition of supported services */
#define MMS_DEFAULT_PROFILE 1

#if MMS_DEFAULT_PROFILE
#define MMS_READ_SERVICE 1
#define MMS_WRITE_SERVICE 1
#define MMS_GET_NAME_LIST 1
#define MMS_GET_VARIABLE_ACCESS_ATTRIBUTES 1
#define MMS_DATA_SET_SERVICE 1
#endif /* MMS_DEFAULT_PROFILE */

#endif /* STACK_CONFIG_H_ */
