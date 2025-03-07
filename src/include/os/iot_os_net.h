/* ***************************************************************************
 *
 * Copyright 2019 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

 #ifndef _IOT_OS_NET_H_
#define _IOT_OS_NET_H_

#include "iot_os_util.h"
#ifdef CONFIG_STDK_MQTT_USE_SSL
#include "openssl/ssl.h"
#endif

/**
 * @brief Contains "network management structure" data
 */
typedef struct iot_net_socket{
	int socket;				/**< @brief socket handle */
	int (*read)(struct iot_net_socket *, unsigned char *, unsigned int, iot_os_timer);	/**< @brief read handle for socket */
	int (*write)(struct iot_net_socket *, unsigned char *, unsigned int, iot_os_timer);	/**< @brief write handle for socket */
	int read_count;			/**< @brief number of read data */
#ifdef CONFIG_STDK_MQTT_USE_SSL
	SSL_CTX *ctx;			/**< @brief set SSL context */
	SSL *ssl;			/**< @brief SSL Handle */
#endif
} iot_net_socket;

/**
 * @brief print network status
 *
 * @param n           - iot_net_socket struct
 *
 * @return void
 */
void iot_os_net_print_status(iot_net_socket *n);

/**
 * @brief check network socket  status
 *
 * @param n           - iot_net_socket struct
 * @param timeout_ms  - timeout in miliseconds
 *
 * @return
 *              > 0 : there is some data to read
 *              == 0 : there is no data
 *              < 0 : there is error in network
 */

int iot_os_net_select(iot_net_socket *n, unsigned int timeout_ms);

/**
 * @brief Initialize the network structure
 *
 * @param n - iot_net_socket struct
 *
 * @return void
 */
void iot_os_net_init(iot_net_socket *);

/**
 * @brief connect with server
 *
 * @param n           - iot_net_socket struct
 * @param addr        - server address
 * @param port        -  server port
 *
 * @return connect status
 */
int iot_os_net_connet(iot_net_socket *n, char *addr, int port);

/**
 * @brief disconnect with server
 *
 * @param n           - iot_net_socket struct
 *
 * @return void
 */
void iot_os_net_disconnect(iot_net_socket *n);

#ifdef CONFIG_STDK_MQTT_USE_SSL
/**
 * @brief Contains a "SSL handle" data
 */
typedef struct ssl_ca_crt_key {
	unsigned char *cacrt;		/**< @brief CA client certification */
	unsigned int cacrt_len;		/**< @brief length - certification bytes */
	unsigned char *cert;		/**< @brief certification context*/
	unsigned int cert_len;		/**< @brief length - certification bytes */
	unsigned char *key;		/**< @brief private key context */
	unsigned int key_len;		/**< @brief length - private key bytes */
} ssl_ca_crt_key_t;

/**
 * @brief Initialize the network structure for SSL connection
 *
 * @param n - iot_net_socket structure
 *
 * @return void
 */
void iot_os_net_ssl_init(iot_net_socket *n);

/**
 * @brief Use SSL to connect with server
 *
 * @param n           - iot_net_socket struct
 * @param addr        - server address
 * @param port        - server port
 * @param ssl_cck     - client CA, certificate and private key
 * @param method      - SSL context client method
 * @param verify_mode - SSL verifying mode
 * @param frag_len    - SSL read buffer length
 *
 * @return connect status
 */
int iot_os_net_ssl_connet(iot_net_socket *n, char *addr, int port, ssl_ca_crt_key_t *ssl_cck, const SSL_METHOD *method, int verify_mode, unsigned int frag_len);

 /**
 * @brief disconnect with server SSL connection
 *
 * @param n           - iot_net_socket struct
 *
 * @return void
 */
void iot_os_net_ssl_disconnect(iot_net_socket *n);

#endif //CONFIG_STDK_MQTT_USE_SSL

#endif //_IOT_OS_NET_H_
