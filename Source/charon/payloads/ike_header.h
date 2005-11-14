/**
 * @file ike_header.h
 * 
 * @brief Declaration of the class ike_header_t. 
 * 
 * An object of this type represents an ike header and is used to 
 * generate and parse ike headers.
 * 
 */

/*
 * Copyright (C) 2005 Jan Hutter, Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#ifndef IKE_HEADER_H_
#define IKE_HEADER_H_

#include "../types.h"
#include "payload.h"

/**
 * Major Version of IKEv2
 */
#define IKE_MAJOR_VERSION 2

/**
 * Minor Version of IKEv2
 */
#define IKE_MINOR_VERSION 0

/**
 * Flag in IKEv2-Header. Always 0
 */
#define HIGHER_VERSION_SUPPORTED_FLAG 0

/**
 * Length of IKE Header in Bytes
 */
#define IKE_HEADER_LENGTH 28

/**
 * @brief Different types of IKE-Exchanges.
 *
 * See RFC for different types.
 */
typedef enum exchange_type_e exchange_type_t;

enum exchange_type_e{

	/**
	 * NOT_SET, not a official message type :-)
	 */
	NOT_SET = 0,

	/**
	 * IKE_SA_INIT
	 */
	IKE_SA_INIT = 34,
	/**
	 * IKE_AUTH
	 */
	IKE_AUTH = 35,
	/**
	 * CREATE_CHILD_SA
	 */
	CREATE_CHILD_SA = 36,
	/**
	 * INFORMATIONAL
	 */
	INFORMATIONAL = 37 
};

/**
 * Object representing an IKEv2-Header
 * 
 * The header format of an IKEv2-Message is compatible to the 
 * ISAKMP-Header format to allow implementations supporting 
 * both versions of the IKE-protocol.
 * 
 */
typedef struct ike_header_s ike_header_t;

struct ike_header_s {
	/**
	 * implements payload_t interface
	 */
	payload_t payload_interface;
	/**
	 * SPI of the initiator
	 */
	u_int64_t initiator_spi;
	/**
	 * SPI of the responder
	 */
	u_int64_t responder_spi;
	/**
	 * next payload type
	 */
	u_int8_t  next_payload;
	/**
	 * IKE major version
	 */
	u_int8_t  maj_version;

	/**
	 * IKE minor version
	 */	
	u_int8_t  min_version;

	/**
	 * Exchange type 
	 */	
	u_int8_t  exchange_type;
	
	/**
	 * Flags of the Message
	 * 
	 */
	struct { 
		/**
		 * Sender is initiator of the associated IKE_SA_INIT-Exchange
		 */
		bool initiator;
		/**
		 * is protocol supporting higher version?
		 */
		bool version;
		/**
		 * TRUE, if this is a response, FALSE if its a Request
		 */
		bool response;
	} flags;
	/**
	 * Associated Message-ID
	 */
	u_int32_t message_id;
	/**
	 * Length of the whole IKEv2-Message (header and all payloads)
	 */
	u_int32_t length;
	
	/**
	 * @brief Destroys a ike_header_t object.
	 *
	 * @param this 	ike_header_t object to destroy
	 * @return 		
	 * 				SUCCESS in any case
	 */
	status_t (*destroy) (ike_header_t *this);
};

/**
 * @brief Create an ike_header_t object
 * 
 * @return			
 * 					- created ike_header, or
 * 					- NULL if failed
 */
 
ike_header_t *ike_header_create();

#endif /*IKE_HEADER_H_*/
