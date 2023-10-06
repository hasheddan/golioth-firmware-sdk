/*
 * Copyright (c) 2022 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#pragma once

#include <stdint.h>
#include "golioth_status.h"
#include "golioth_client.h"
#include "golioth_config.h"

/// Get a single artfifact block synchronously
///
/// Since some artifacts (e.g. "main" firmware) are larger than the amount of RAM
/// the device has, it is assumed the user will call this function multiple times
/// to handle blocks one at a time.
///
/// This function will block until one of three things happen (whichever comes first):
///
/// 1. A response is received from the server
/// 2. The user-provided timeout_s period expires without receiving a response
/// 3. The default GOLIOTH_COAP_RESPONSE_TIMEOUT_S period expires without receiving a response
///
/// @param client The client handle from @ref golioth_client_create
/// @param package Package name, to identify the artifact
/// @param version Version of package, to identify the artifact
/// @param block_index 0-based index of block to get
/// @param buf Output param, memory allocated by caller, block data will be copied here.
///           Must be at least GOLIOTH_OTA_BLOCKSIZE bytes.
/// @param block_nbytes Output param, memory allocated by caller, populated with number
///             of bytes in the block, 0 to GOLIOTH_OTA_BLOCKSIZE.
/// @param is_last Set to true, if this is the last block
/// @param timeout_s The timeout, in seconds, for receiving a server response
///
/// @return GOLIOTH_OK - response received from server, get was successful
/// @return GOLIOTH_ERR_NULL - invalid client handle
/// @return GOLIOTH_ERR_INVALID_STATE - client is not running, currently stopped
/// @return GOLIOTH_ERR_QUEUE_FULL - request queue is full, this request is dropped
/// @return GOLIOTH_ERR_TIMEOUT - response not received from server, timeout occurred
golioth_status_t golioth_data_post_block_sync(
        golioth_client_t client,
        uint8_t* buf,
        int32_t timeout_s);

