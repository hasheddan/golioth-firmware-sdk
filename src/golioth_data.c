/*
 * Copyright (c) 2022 Golioth, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <errno.h>
#include <string.h>
#include "golioth_coap_client.h"
#include "golioth_statistics.h"
#include "golioth_debug.h"
#include "golioth_util.h"

LOG_TAG_DEFINE(golioth_data);

golioth_status_t golioth_data_post_block_sync(
        golioth_client_t client,
        uint8_t* buf,  // must be at least GOLIOTH_OTA_BLOCKSIZE bytes
        int32_t timeout_s) {

    golioth_status_t status = GOLIOTH_OK;
    status = golioth_coap_client_post_block(
            client,
            COAP_MEDIATYPE_APPLICATION_OCTET_STREAM,
            buf,
            1024,
            true,
            timeout_s);

    return status;
}
